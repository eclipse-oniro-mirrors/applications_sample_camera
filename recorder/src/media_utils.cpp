/*
 * Copyright (c) 2026 RKH Corp.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <dirent.h>
#include <fcntl.h>
#include <cerrno>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>
#include <iostream>

#include <media_errors.h>

#include "recorder_ability.h"
#include "recorder_log.h"
#include "recorder_config.h"
#include "media_utils.h"

namespace OHOS {
static constexpr size_t DATETIME_BUFFER_SIZE = 0x100;
static constexpr mode_t RECORDER_DIRECTORY_MODE = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;

static std::string GernerateFileName()
{
    time_t stCurrent;
    char aszDatetime[DATETIME_BUFFER_SIZE];
    (void)time(&stCurrent);
    struct tm *pstCurrentTime = localtime(&(stCurrent));
    if (pstCurrentTime == nullptr) {
        return "";
    }
    if (strftime(aszDatetime, DATETIME_BUFFER_SIZE, RECORDER_FILE_NAME_FMT, pstCurrentTime) == 0) {
        return "";
    }
    std::ostringstream oss;
    oss << RECORDER_DIRECTORY << aszDatetime << RECORDER_FILE_POSTFIX;
    return oss.str();
}

static bool IsDirExists(const char *path)
{
    struct stat st;
    int ret = lstat(path, &st);
    if (ret == -1) {
        if (errno == ENOENT) {
            return false;
        }
        perror("lstat failed");
        exit(EXIT_FAILURE);
    }
    return S_ISDIR(st.st_mode);
}

static bool DeleteDirectory(const std::string& dirPath)
{
    std::cout << "DeleteDirectory " << dirPath << std::endl;
    DIR* dir = opendir(dirPath.c_str());
    if (!dir) {
        std::cerr << "opendir failed, dirPath: " << dirPath << " errno:" << errno << std::endl;
        return false;
    }

    struct dirent* entry = nullptr;
    while ((entry = readdir(dir)) != nullptr) {
        std::string fileName = entry->d_name;
        // skip dir "." and ".."
        if (fileName == "." || fileName == "..") {
            continue;
        }
        std::string fullPath = dirPath + "/" + fileName;
        struct stat statBuf;
        if (stat(fullPath.c_str(), &statBuf) == -1) {
            std::cerr << "stat failed, fullPath: " << fullPath << " errno:" << errno << std::endl;
            closedir(dir);
            return false;
        }
        if (S_ISDIR(statBuf.st_mode)) {
            // delete directory recursively
            if (!DeleteDirectory(fullPath)) {
                closedir(dir);
                return false;
            }
        } else {
            // delete normal file
            if (unlink(fullPath.c_str()) == -1) {
                std::cerr << "unlink file failed, fullPath: " << fullPath << " errno:" << errno << std::endl;
                closedir(dir);
                return false;
            }
        }
    }
    closedir(dir);
    if (rmdir(dirPath.c_str()) == -1) {
        std::cerr << "rmdir failed, dirPath: " << dirPath << " errno:" << errno << std::endl;
        return false;
    }
    return true;
}

MediaUtils::~MediaUtils()
{
    CloseRecorder();
    ClosePlayer();
}

#ifdef USE_RECORDER_API
class RecorderCallbackAdapter : public Media::RecorderCallback {
public:
    RecorderCallbackAdapter(Media::RecorderCallback* from)
    {
        target = from;
    }
    ~RecorderCallbackAdapter()
    {
        target = nullptr;
    }
    void OnError(int32_t errorType, int32_t errorCode) override
    {
        if (target) {
            target->OnError(errorType, errorCode);
        }
    }
    void OnInfo(int type, int extra) override
    {
        if (target) {
            target->OnError(type, extra);
        }
    }
private:
    Media::RecorderCallback *target = nullptr;
};

bool MediaUtils::SetRecorderCallback(Media::RecorderCallback* recorderCallback)
{
    recorderCallback_ = recorderCallback;
    return true;
}
#endif

bool MediaUtils::InitRecorder()
{
    LOGI("InitRecorder");
#ifdef USE_RECORDER_API
    int32_t audioSourceId = 0;
    AudioSourceType inputSource = AUDIO_MIC;
    AudioCodecFormat audioFormat = AAC_LC;
    int32_t sampleRate = 48000;
    int32_t channelCount = 1;
    int32_t audioEncodingBitRate = 96000;

    recorder_ = std::make_shared<Media::Recorder>();
    int ret = 0;

    if ((ret = recorder_->SetAudioSource(inputSource, audioSourceId)) != Media::SUCCESS) {
        LOGE("SetAudioSource failed, ret:%d", ret);
        return false;
    }
    if ((ret = recorder_->SetAudioEncoder(audioSourceId, audioFormat)) != Media::SUCCESS) {
        LOGE("SetAudioEncoder failed, ret:%d", ret);
        return false;
    }
    if ((ret = recorder_->SetAudioSampleRate(audioSourceId, sampleRate)) != Media::SUCCESS) {
        LOGE("SetAudioSampleRate failed, ret:%d", ret);
        return false;
    }
    if ((ret = recorder_->SetAudioChannels(audioSourceId, channelCount)) != Media::SUCCESS) {
        LOGE("SetAudioChannels failed, ret:%d", ret);
        return false;
    }
    if ((ret = recorder_->SetAudioEncodingBitRate(audioSourceId, audioEncodingBitRate)) != Media::SUCCESS) {
        LOGE("SetAudioEncodingBitRate failed, ret:%d", ret);
        return false;
    }
    if ((ret = recorder_->SetMaxDuration(36000)) != Media::SUCCESS) { // 36000s=10h
        LOGE("SetMaxDuration failed, ret:%d", ret);
        return false;
    }
    if ((ret = recorder_->SetOutputFormat(Media::FORMAT_M4A)) != Media::SUCCESS) {
        LOGE("SetOutputFormat failed, ret:%d", ret);
        return false;
    }
    recorderCallbackPtr_ = std::make_shared<RecorderCallbackAdapter>(recorderCallback_);
    recorder_->SetRecorderCallback(recorderCallbackPtr_);
#endif
    return true;
}

bool MediaUtils::StartRecord()
{
    LOGI("StartRecord");
    if (recording_) {
        LOGW("already recording!");
        return false;
    }
    if (!EnsureRecorderDirectory()) {
        return false;
    }
#ifdef USE_RECORDER_FD
    std::string filename = GernerateFileName();
    LOGI("GernerateFileName %s", filename.c_str());
    recordFd_ = open(filename.c_str(), O_RDWR | O_CREAT);
    if (recordFd_ == -1) {
        LOGE("open file failed! filename:%s, errno:%d", filename.c_str(), errno);
        return false;
    }
#endif
    if (!StartRecorderService()) {
        return false;
    }
    recording_ = true;
    return true;
}

bool MediaUtils::EnsureRecorderDirectory()
{
    if (IsDirExists(RECORDER_DIRECTORY)) {
        return true;
    }
    if (mkdir(RECORDER_DIRECTORY, RECORDER_DIRECTORY_MODE) != 0) {
        LOGE("mkdir for %s failed, errno:%d", RECORDER_DIRECTORY, errno);
        CloseRecorder();
        return false;
    }
    return true;
}

bool MediaUtils::StartRecorderService()
{
#ifdef USE_RECORDER_API
    if (recorder_ == nullptr) {
        LOGW("recorder is nullptr, do init.");
        if (!InitRecorder()) {
            LOGE("recorder init failed!");
            return false;
        }
    }

    int ret = 0;
#if USE_RECORDER_FD
    if ((ret = recorder_->SetOutputFile(recordFd_)) != Media::SUCCESS) {
        LOGE("SetOutputPath failed. ret:%d", ret);
        CloseRecorder();
        return false;
    }
#else
    DeleteDirectory(RECORDER_TEMP_DIRECTORY);
    if (access(RECORDER_TEMP_DIRECTORY, F_OK) != 0 &&
        mkdir(RECORDER_TEMP_DIRECTORY, RECORDER_DIRECTORY_MODE) != 0) {
        std::cout << "mkdir " << RECORDER_TEMP_DIRECTORY << " failed. errno:" << errno << std::endl;
        return false;
    }
    if ((ret = recorder_->SetOutputPath(RECORDER_DIRECTORY)) != Media::SUCCESS) {
        LOGE("SetOutputPath failed. ret:%d", ret);
        CloseRecorder();
        return false;
    }
#endif

    ret = recorder_->Prepare();
    if (ret != Media::SUCCESS) {
        LOGE("Prepare failed. ret:%d", ret);
        CloseRecorder();
        return false;
    }
    ret = recorder_->Start();
    if (ret != Media::SUCCESS) {
        LOGE("Start failed. ret:%d", ret);
        CloseRecorder();
        return false;
    }
#endif
    return true;
}

bool MediaUtils::StopRecord()
{
    LOGI("StopRecord");
    if (!recording_) {
        LOGW("current not recording!");
        return false;
    }
    CloseRecorder();
    MoveFiles();
    recording_ = false;
    return true;
}

bool MediaUtils::MoveFiles()
{
    LOGI("MoveFiles");
    struct dirent* entry;
    DIR* dir = opendir(RECORDER_TEMP_DIRECTORY);
    if (dir == nullptr) {
        LOGE("open recorder dir failed. errno:%d", errno);
        return false;
    }

    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;
        if (entry->d_type == DT_REG &&
            filename.size() > RECORDER_FILE_POSTFIX_LENGTH &&
            (filename.substr(filename.size() - RECORDER_FILE_POSTFIX_LENGTH) == RECORDER_TEMP_FILE_POSTFIX)) {
            LOGI("find file: %s", filename.c_str());
            std::string src = std::string(RECORDER_TEMP_DIRECTORY) + filename;
            std::string dst = std::string(RECORDER_DIRECTORY) +
                filename.substr(0, filename.size() - RECORDER_FILE_POSTFIX_LENGTH) +
                RECORDER_FILE_POSTFIX;
            if (rename(src.c_str(), dst.c_str()) != 0) {
                LOGE("rename file failed, errno:%d, src:%s, dst:%s", errno, src.c_str(), dst.c_str());
                continue;
            }
        }
    }
    closedir(dir);
    DeleteDirectory(RECORDER_TEMP_DIRECTORY);
    return true;
}

bool MediaUtils::CloseRecorder()
{
    LOGI("CloseRecorder");
#ifdef USE_RECORDER_API
    if (recorder_) {
        recorder_->Stop(true);
        recorder_->Release();
        recorder_ = nullptr;
    }
#endif

#ifdef USE_RECORDER_FD
    if (recordFd_ != -1) {
        FILE *fp = fdopen(recordFd_, "w+");
        if (fp) {
            fflush(fp);
            fsync(recordFd_);
            fclose(fp);
            close(recordFd_);
        }
        recordFd_ = -1;
    }
#endif
    return true;
}

// Player
#ifdef USE_PLAYER_API
class PlayerCallbackAdapter : public Media::PlayerCallback {
public:
    PlayerCallbackAdapter(Media::PlayerCallback* from)
    {
        target = from;
    }
    ~PlayerCallbackAdapter() override
    {
        target = nullptr;
    }
    void OnPlaybackComplete() override
    {
        if (target) {
            target->OnPlaybackComplete();
        }
    }
    void OnError(int32_t errorType, int32_t errorCode) override
    {
        if (target) {
            target->OnError(errorType, errorCode);
        }
    }
    void OnInfo(int type, int extra) override
    {
        if (target) {
            target->OnError(type, extra);
        }
    }
    void OnVideoSizeChanged(int width, int height)      override
    {
        if (target) {
            target->OnVideoSizeChanged(width, height);
        }
    }
    void OnRewindToComplete() override
    {
        if (target) {
            target->OnRewindToComplete();
        }
    }
private:
    Media::PlayerCallback *target = nullptr;
};

bool MediaUtils::SetPlayerCallback(Media::PlayerCallback* playerCallback)
{
    playerCallback_ = playerCallback;
    return true;
}
#endif

bool MediaUtils::InitPlayer(const char* filePath)
{
    LOGI("InitPlayer");
#ifdef USE_PLAYER_API
    player_ = std::make_shared<Media::Player>();
    if (!player_) {
        LOGE("create Player failed!");
        return false;
    }
    std::string uri(filePath);
    Media::Source source(uri);
    int ret = player_->SetSource(source);
    if (ret != Media::SUCCESS) {
        LOGE("SetSource failed!");
        ClosePlayer();
        return false;
    }
    playerCallbackPtr_ = std::make_shared<PlayerCallbackAdapter>(playerCallback_);
    player_->SetPlayerCallback(playerCallbackPtr_);
#endif
    return true;
}

bool MediaUtils::StartPlay(const char* filePath)
{
    LOGI("StartPlay file:%s", filePath);
    if (playing_ && !paused_) {
        LOGW("already playing.");
        return false;
    }
#ifdef USE_PLAYER_API
    if (!player_) {
        LOGE("player is null, do init!");
        if (!InitPlayer(filePath)) {
            LOGE("init player failed");
            return false;
        }
    }
    int ret = 0;
    if (playing_ && paused_) {
        ret = player_->Play();
        if (ret != Media::SUCCESS) {
            LOGE("Play(resume) failed!");
            ClosePlayer();
            return false;
        }
    } else {
        ret = player_->Prepare();
        if (ret != Media::SUCCESS) {
            LOGE("Prepare failed!");
            ClosePlayer();
            return false;
        }
        ret = player_->Play();
        if (ret != Media::SUCCESS) {
            LOGE("Play failed!");
            ClosePlayer();
            return false;
        }
    }
#endif
    playing_ = true;
    paused_ = false;
    return true;
}

bool MediaUtils::PausePlay()
{
    LOGI("PausePlay");
#ifdef USE_PLAYER_API
    int ret = player_->Pause();
    if (ret != Media::SUCCESS) {
        LOGE("Pause failed!");
        ClosePlayer();
        return false;
    }
#endif
    paused_ = true;
    return true;
}

bool MediaUtils::StopPlay()
{
    LOGI("StopPlay");
    if (!playing_) {
        LOGW("current not playing!");
        return false;
    }
    ClosePlayer();
    return true;
}

bool MediaUtils::ClosePlayer()
{
    LOGI("ClosePlayer");
#ifdef USE_PLAYER_API
    if (player_) {
        player_->Stop();
        player_->Release();
        player_ = nullptr;
    }
#endif
    playing_ = false;
    paused_ = false;
    return true;
}

}
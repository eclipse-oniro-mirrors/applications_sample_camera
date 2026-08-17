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

#ifndef OHOS_MEDIA_UTILS_H
#define OHOS_MEDIA_UTILS_H

#include <memory>

#ifdef USE_RECORDER_API
#include <recorder.h>
#endif
#ifdef USE_PLAYER_API
#include <player.h>
#endif

namespace OHOS {
class MediaUtils {
public:
    ~MediaUtils();

    // Recorder
#ifdef USE_RECORDER_API
    bool SetRecorderCallback(Media::RecorderCallback* recorderCallback);
#endif
    bool StartRecord();
    bool StopRecord();

    // Player
#ifdef USE_PLAYER_API
    bool SetPlayerCallback(Media::PlayerCallback* playerCallback);
#endif
    bool StartPlay(const char* filePath);
    bool PausePlay();
    bool StopPlay();

private:
    bool InitRecorder();
    bool CloseRecorder();
    bool MoveFiles();
    bool EnsureRecorderDirectory();
    bool StartRecorderService();

    bool InitPlayer(const char* filePath);
    bool ClosePlayer();

private:
#ifdef USE_RECORDER_API
    std::shared_ptr<Media::Recorder> recorder_;
    Media::RecorderCallback* recorderCallback_ { nullptr };
    std::shared_ptr<Media::RecorderCallback> recorderCallbackPtr_;
#endif

#ifdef USE_PLAYER_API
    std::shared_ptr<Media::Player> player_;
    Media::PlayerCallback* playerCallback_ { nullptr };
    std::shared_ptr<Media::PlayerCallback> playerCallbackPtr_;
#endif
#ifdef USE_RECORDER_FD
    int32_t recordFd_ = -1;
#endif

    bool recording_ = false;
    bool playing_ = false;
    bool paused_ = false;
};
}

#endif // OHOS_RECORDER_ABILITY_H

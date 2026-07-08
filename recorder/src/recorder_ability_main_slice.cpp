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

#include <ability_env.h>
#include <ability_loader.h>
#include <ability_manager.h>
#include <components/text_adapter.h>
#include <common/screen.h>
#include <hal_tick.h>

#include <dirent.h>
#include <algorithm>
#include <cstdio>

#include "recorder_ability_main_slice.h"
#include "recorder_log.h"
#include "recorder_utils.h"

namespace OHOS {
REGISTER_AS(RecorderAbilityMainSlice)

static constexpr uint8_t NOTICE_COLOR_RED = 78;
static constexpr uint8_t NOTICE_COLOR_GREEN = 89;
static constexpr uint8_t NOTICE_COLOR_BLUE = 105;
static constexpr uint8_t ROOT_COLOR_RED = 249;
static constexpr uint8_t ROOT_COLOR_GREEN = 250;
static constexpr uint8_t ROOT_COLOR_BLUE = 251;

RecorderAbilityMainSlice::~RecorderAbilityMainSlice()
{
    LOGI("~RecorderAbilityMainSlice()");
    StopTimer();
}

void RecorderAbilityMainSlice::InitTitle()
{
    LOGI("RecorderAbilityMainSlice::InitTitle");
    titleBar_ = new UIViewGroup();
    titleBar_->SetPosition(TITLE_BAR_X(), TITLE_BAR_Y(), TITLE_BAR_WIDTH(), TITLE_BAR_HEIGHT());
    titleBar_->SetStyle(STYLE_BACKGROUND_COLOR, Color::White().full);
    titleBar_->SetStyle(STYLE_BACKGROUND_OPA, OPA_OPAQUE);

    backButton_ = new UIImageView();
    backButton_->SetPosition(BACK_ICON_X(), BACK_ICON_Y(), BACK_ICON_WIDTH(), BACK_ICON_HEIGHT());
    backButton_->SetAutoEnable(false);
    backButton_->SetResizeMode(UIImageView::ImageResizeMode::CONTAIN);
    backButton_->SetSrc(backIconAbsolutePath);
    backButton_->SetTouchable(true);

    auto onClick = [this] (UIView& view, const Event& event) -> bool {
        LOGI("TerminateAbility by BackPress");
        TerminateAbility();
        return true;
    };
    backButtonListener_ = new EventListener(onClick, nullptr);
    backButton_->SetOnClickListener(backButtonListener_);

    titleLabel_ = new UILabel();
    titleLabel_->SetPosition(TITLE_LABEL_X(), TITLE_LABEL_Y(), TITLE_LABEL_WIDTH(), TITLE_LABEL_HEIGHT());
    titleLabel_->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_LEFT, UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
    titleLabel_->SetFont(FONT_NAME, TITLE_LABEL_FONT_SIZE());
    titleLabel_->SetStyle(STYLE_TEXT_COLOR, Color::Black().full);
    titleLabel_->SetStyle(STYLE_TEXT_OPA, OPA_OPAQUE);
    titleLabel_->SetText("录音机");

    titleBar_->Add(backButton_);
    titleBar_->Add(titleLabel_);
    rootView_->Add(titleBar_);
}

void RecorderAbilityMainSlice::InitRecordCtrl()
{
    InitRecordLabels();
    InitRecordButtons();
    InitRecordListeners();
    AddRecordControlsToRoot();
}

void RecorderAbilityMainSlice::InitRecordLabels()
{
    noticeLabel_ = new UILabel();
    noticeLabel_->SetPosition(NOTICE_LABEL_X(), NOTICE_LABEL_Y(), NOTICE_LABEL_WIDTH(), NOTICE_LABEL_HEIGHT());
    noticeLabel_->SetAlign(
        UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER,
        UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
    noticeLabel_->SetFont(FONT_NAME, NOTICE_LABEL_FONT_SIZE());
    noticeLabel_->SetStyle(
        STYLE_TEXT_COLOR,
        Color::GetColorFromRGB(NOTICE_COLOR_RED, NOTICE_COLOR_GREEN, NOTICE_COLOR_BLUE).full);
    noticeLabel_->SetStyle(STYLE_TEXT_OPA, OPA_OPAQUE);
    noticeLabel_->SetText("点击下方按钮开始录音");

    durationLabel_ = new UILabel();
    durationLabel_->SetPosition(DURATION_LABEL_X(), DURATION_LABEL_Y(), DURATION_LABEL_WIDTH(), DURATION_LABEL_HEIGHT());
    durationLabel_->SetAlign(
        UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER,
        UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
    durationLabel_->SetFont(FONT_NAME, DURATION_LABEL_FONT_SIZE());
    durationLabel_->SetStyle(STYLE_TEXT_COLOR, Color::Black().full);
    durationLabel_->SetStyle(STYLE_TEXT_OPA, OPA_OPAQUE);
    durationLabel_->SetText("00:00:00");
}

void RecorderAbilityMainSlice::InitRecordButtons()
{
    fsImageView_ = new UIImageView();
    fsImageView_->SetPosition(FS_IMAGE_X(), FS_IMAGE_Y(), FS_IMAGE_WIDTH(), FS_IMAGE_HEIGHT());
    fsImageView_->SetAutoEnable(false);
    fsImageView_->SetResizeMode(UIImageView::FILL);
    fsImageView_->SetSrc(fsIconAbsolutePath);
    fsImageView_->SetTouchable(false);

    startButton_ = new UIImageView();
    startButton_->SetPosition(START_BUTTON_X(), START_BUTTON_Y(), START_BUTTON_WIDTH(), START_BUTTON_HEIGHT());
    startButton_->SetAutoEnable(false);
    startButton_->SetResizeMode(UIImageView::CONTAIN);
    startButton_->SetSrc(startIconAbsolutePath);
    startButton_->SetTouchable(true);

    pauseButton_ = new UIImageView();
    pauseButton_->SetPosition(PAUSE_BUTTON_X(), PAUSE_BUTTON_Y(), PAUSE_BUTTON_WIDTH(), PAUSE_BUTTON_HEIGHT());
    pauseButton_->SetAutoEnable(false);
    pauseButton_->SetResizeMode(UIImageView::CONTAIN);
    pauseButton_->SetSrc(pauseIconAbsolutePath);
    pauseButton_->SetTouchable(true);
    pauseButton_->SetVisible(false);

    cancelButton_ = new UIImageView();
    cancelButton_->SetPosition(CANCEL_BUTTON_X(), CANCEL_BUTTON_Y(), CANCEL_BUTTON_WIDTH(), CANCEL_BUTTON_HEIGHT());
    cancelButton_->SetAutoEnable(false);
    cancelButton_->SetResizeMode(UIImageView::CONTAIN);
    cancelButton_->SetSrc(cancelIconAbsolutePath);
    cancelButton_->SetTouchable(true);
    cancelButton_->SetVisible(false);
}

void RecorderAbilityMainSlice::InitRecordListeners()
{
    startButtonListener_ = new EventListener(
        [this] (UIView& view, const Event& event) -> bool {
            LOGI("start button on click");
            Start();
            return true;
        }, nullptr);

    stopButtonListener_ = new EventListener(
        [this] (UIView& view, const Event& event) -> bool {
            LOGI("stop button on click");
            Stop();
            return true;
        }, nullptr);

    pauseButtonListener_ = new EventListener(
        [this] (UIView& view, const Event& event) -> bool {
            LOGI("pause button on click");
            Pause();
            return true;
        }, nullptr);

    resumeButtonListener_ = new EventListener(
        [this] (UIView& view, const Event& event) -> bool {
            LOGI("resume button on click");
            Resume();
            return true;
        }, nullptr);

    cancelButtonListener_ = new EventListener(
        [this] (UIView& view, const Event& event) -> bool {
            LOGI("cancel button on click");
            Cancel();
            return true;
        }, nullptr);

    startButton_->SetOnClickListener(startButtonListener_);
    pauseButton_->SetOnClickListener(pauseButtonListener_);
    cancelButton_->SetOnClickListener(cancelButtonListener_);
}

void RecorderAbilityMainSlice::AddRecordControlsToRoot()
{
    rootView_->Add(noticeLabel_);
    rootView_->Add(durationLabel_);
    rootView_->Add(fsImageView_);
    rootView_->Add(startButton_);
    rootView_->Add(pauseButton_);
    rootView_->Add(cancelButton_);
}

void RecorderAbilityMainSlice::InitRecordList()
{
    listLabel_ = new UILabel();
    listLabel_->SetPosition(LIST_LABEL_X(), LIST_LABEL_Y(), LIST_LABEL_WIDTH(), LIST_LABEL_HEIGHT());
    listLabel_->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_LEFT, UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
    listLabel_->SetFont(FONT_NAME, LIST_LABEL_FONT_SIZE());
    listLabel_->SetStyle(STYLE_TEXT_COLOR, Color::Black().full);
    listLabel_->SetStyle(STYLE_TEXT_OPA, OPA_OPAQUE);
    listLabel_->SetText("录音列表");

    list_ = new UIList(UIList::VERTICAL);
    std::vector<RecordItem> items;
    adapter_ = new RecorderListAdapter();
    adapter_->Init();
    OnItemPlayListener* playListener = new RecorderListItemListener(
        [this](int16_t index, const RecordItem& item) {
            LOGI("OnItemPlayListener index: %d", index);
            this->OnItemPlay(index, item);
        }, nullptr);
    OnItemDeleteListener* deleteListener = new RecorderListItemListener(
        nullptr,
        [this](int16_t index, const RecordItem& item) {
            LOGI("OnItemDeleteListener index: %d", index);
            this->OnItemDelete(index, item);
        });
    adapter_->SetOnItemPlayListener(playListener);
    adapter_->SetOnItemDeleteListener(deleteListener);
    adapter_->SetItems(items);

    list_->SetIntercept(true);
    list_->SetStyle(STYLE_BACKGROUND_OPA, OPA_TRANSPARENT);
    list_->SetStyle(STYLE_TEXT_COLOR, Color::Black().full);
    list_->SetStyle(STYLE_TEXT_OPA, OPA_OPAQUE);
    list_->SetPosition(LIST_X(), LIST_Y(), LIST_WIDTH(), LIST_HEIGHT());
    list_->SetStartIndex(0);
    list_->SetYScrollBarVisible(false);
    list_->SetAdapter(adapter_);

    rootView_->Add(listLabel_);
    rootView_->Add(list_);
}

void RecorderAbilityMainSlice::OnStart(const Want &want)
{
    LOGI(
        "RecorderAbilityMainSlice::OnStart, screen size: %dx%d",
        GetScrWidth(),
        GetScrHeight());
    AbilitySlice::OnStart(want);

    InitRootView();
    const char* pathHeader = GetSrcPath();
    if (!InitIconPaths(pathHeader)) {
        return;
    }

    InitTitle();
    InitRecordCtrl();
    InitRecordList();
    ReloadItems();
    SetUIContent(rootView_);
}

void RecorderAbilityMainSlice::InitRootView()
{
    rootView_ = RootView::GetWindowRootView();
    rootView_->SetPosition(ROOT_VIEW_X(), ROOT_VIEW_Y());
    rootView_->Resize(ROOT_VIEW_WIDTH(), ROOT_VIEW_HEIGHT());
    rootView_->SetStyle(
        STYLE_BACKGROUND_COLOR,
        Color::GetColorFromRGB(ROOT_COLOR_RED, ROOT_COLOR_GREEN, ROOT_COLOR_BLUE).full);
    rootView_->SetStyle(STYLE_BACKGROUND_OPA, OPA_OPAQUE);
}

bool RecorderAbilityMainSlice::InitIconPaths(const char* pathHeader)
{
    return InitImagePath(backIconAbsolutePath, pathHeader, BACK_ICON_PATH, "backIconAbsolutePath") &&
        InitImagePath(fsIconAbsolutePath, pathHeader, FS_ICON_PATH, "fsIconAbsolutePath") &&
        InitImagePath(startIconAbsolutePath, pathHeader, START_ICON_PATH, "startIconAbsolutePath") &&
        InitImagePath(stopIconAbsolutePath, pathHeader, STOP_ICON_PATH, "stopIconAbsolutePath") &&
        InitImagePath(pauseIconAbsolutePath, pathHeader, PAUSE_ICON_PATH, "pauseIconAbsolutePath") &&
        InitImagePath(resumeIconAbsolutePath, pathHeader, RESUME_ICON_PATH, "resumeIconAbsolutePath") &&
        InitImagePath(cancelIconAbsolutePath, pathHeader, CANCEL_ICON_PATH, "cancelIconAbsolutePath");
}

bool RecorderAbilityMainSlice::InitImagePath(
    char* absolutePath,
    const char* pathHeader,
    const char* resourcePath,
    const char* errorTag)
{
    if (sprintf_s(absolutePath, MAX_PATH_LENGTH, "%s%s", pathHeader, resourcePath) >= 0) {
        return true;
    }
    LOGI("RecorderAbilityMainSlice::OnStart | %s error", errorTag);
    return false;
}

void RecorderAbilityMainSlice::OnItemPlay(int16_t index, const RecordItem& item)
{
    LOGI("OnItemPlay index:%d", index);
    RecordItem newItem;
    uint16_t count = adapter_->GetCount();
    for (uint16_t i = 0; i < count; i++) {
        adapter_->GetItem(i, newItem);
        if (index != i) {
            if (newItem.started) {
                mediaUtils_.StopPlay();
                newItem.started = false;
                newItem.paused = false;
                adapter_->UpdateItem(i, newItem);
            }
        }
    }
    newItem = item;
    if (newItem.started && !newItem.paused) {
        if (mediaUtils_.PausePlay()) {
            newItem.paused = true;
            adapter_->UpdateItem(index, newItem);
        }
    } else {
        mediaUtils_.SetPlayerCallback(this);
        if (mediaUtils_.StartPlay(newItem.path.c_str())) {
            newItem.started = true;
            newItem.paused = false;
            adapter_->UpdateItem(index, newItem);
        }
    }
    list_->RefreshList();
}

void RecorderAbilityMainSlice::OnItemDelete(int16_t index, const RecordItem& item)
{
    LOGI("OnItemDelete index:%d", index);
    if (item.started) {
        mediaUtils_.StopPlay();
    }
    if (unlink(item.path.c_str()) == 0) {
        LOGI("file %s delete success.", item.path.c_str());
        adapter_->RemoveItem(index);
        list_->RefreshList();
    } else {
        LOGE("file %s delete failed, errno:%d", item.path.c_str(), errno);
    }
}

// Media::PlayerCallback
void RecorderAbilityMainSlice::OnPlaybackComplete()
{
    LOGI("PlayerCallback OnPlaybackComplete");
    RecordItem newItem;
    uint16_t count = adapter_->GetCount();
    for (uint16_t i = 0; i < count; i++) {
        adapter_->GetItem(i, newItem);
        if (newItem.started) {
            newItem.started = false;
            newItem.paused = false;
            adapter_->UpdateItem(i, newItem);
            break;
        }
    }
    mediaUtils_.StopPlay();
    list_->RefreshList();
}

void RecorderAbilityMainSlice::OnError(int32_t errorType, int32_t errorCode)
{
    LOGE("PlayerCallback OnError errorType:%d, errorCode:%d", errorType, errorCode);
    RecordItem newItem;
    uint16_t count = adapter_->GetCount();
    for (uint16_t i = 0; i < count; i++) {
        adapter_->GetItem(i, newItem);
        if (newItem.started) {
            newItem.started = false;
            newItem.paused = false;
            adapter_->UpdateItem(i, newItem);
            break;
        }
    }
    mediaUtils_.StopPlay();
    list_->RefreshList();
}

void RecorderAbilityMainSlice::OnInfo(int type, int extra)
{
    LOGI("PlayerCallback OnInfo type:%d, extra:%d", type, extra);
}

void RecorderAbilityMainSlice::Start()
{
    LOGI("Start");
    // stop play first
    mediaUtils_.StopPlay();

    if (!mediaUtils_.StartRecord()) {
        LOGE("Start failed!");
        return;
    }
    noticeLabel_->SetText("正在录音...");
    startButton_->SetSrc(stopIconAbsolutePath);
    startButton_->SetOnClickListener(stopButtonListener_);
    pauseButton_->SetSrc(pauseIconAbsolutePath);
    pauseButton_->SetOnClickListener(pauseButtonListener_);
    pauseButton_->SetVisible(true);
    cancelButton_->SetVisible(true);
    StartTimer();
}

void RecorderAbilityMainSlice::Stop()
{
    LOGI("Stop");
    if (!mediaUtils_.StopRecord()) {
        LOGE("Stop failed!");
        return;
    }
    noticeLabel_->SetText("点击下方按钮开始录音");
    startButton_->SetSrc(startIconAbsolutePath);
    startButton_->SetOnClickListener(startButtonListener_);
    pauseButton_->SetVisible(false);
    cancelButton_->SetVisible(false);
    StopTimer();
    ReloadItems();
}

void RecorderAbilityMainSlice::Pause()
{
    LOGI("Pause");
    noticeLabel_->SetText("已暂停");
    pauseButton_->SetSrc(resumeIconAbsolutePath);
    pauseButton_->SetOnClickListener(resumeButtonListener_);
    PauseTimer();
}

void RecorderAbilityMainSlice::Resume()
{
    LOGI("Resume");
    noticeLabel_->SetText("正在录音...");
    pauseButton_->SetSrc(pauseIconAbsolutePath);
    pauseButton_->SetOnClickListener(pauseButtonListener_);
    ResumeTimer();
}

void RecorderAbilityMainSlice::Cancel()
{
    LOGI("Cancel");
    noticeLabel_->SetText("点击下方按钮开始录音");
    startButton_->SetSrc(startIconAbsolutePath);
    startButton_->SetOnClickListener(startButtonListener_);
    pauseButton_->SetVisible(false);
    cancelButton_->SetVisible(false);
    StopTimer();
}

static constexpr uint32_t RECORDER_TIMER_PERIOD = 100; // update per 100 ms.

void RecorderAbilityMainSlice::StartTimer()
{
    LOGI("StartTimer");
    if (!recordTimeUpdateTask_) {
        recordTimeUpdateTask_ = CreateTask(
            [this]() {
                this->UpdateRecordTime();
            });
    }
    if (!recordTimeUpdateTask_) {
        LOGE("create record time update task failed.");
        return;
    }
    recordTimeUpdateTask_->SetPeriod(RECORDER_TIMER_PERIOD);
    TaskManager::GetInstance()->Add(recordTimeUpdateTask_.get());
    lastRecordTime_ = HALTick::GetInstance().GetTime();
    recordDuration_ = 0;
}

void RecorderAbilityMainSlice::PauseTimer()
{
    LOGI("PauseTimer");
    TaskManager::GetInstance()->Remove(recordTimeUpdateTask_.get());
    uint32_t elapse = HALTick::GetInstance().GetElapseTime(lastRecordTime_);
    recordDuration_ += elapse;
    UpdateDurationLabel();
}

void RecorderAbilityMainSlice::ResumeTimer()
{
    LOGI("ResumeTimer");
    TaskManager::GetInstance()->Add(recordTimeUpdateTask_.get());
    lastRecordTime_ = HALTick::GetInstance().GetTime();
}

void RecorderAbilityMainSlice::StopTimer()
{
    LOGI("StopTimer");
    TaskManager::GetInstance()->Remove(recordTimeUpdateTask_.get());
    recordDuration_ = 0;
    UpdateDurationLabel();
}

void RecorderAbilityMainSlice::UpdateRecordTime()
{
    LOGI("UpdateRecordTime");
    uint32_t elapse = HALTick::GetInstance().GetElapseTime(lastRecordTime_);
    lastRecordTime_ = HALTick::GetInstance().GetTime();
    recordDuration_ += elapse;
    UpdateDurationLabel();
}

void RecorderAbilityMainSlice::UpdateDurationLabel()
{
    std::string time = FormatDurationTime(recordDuration_);
    if (durationTime_ != time) {
        durationTime_ = time;
        durationLabel_->SetText(durationTime_.c_str());
    }
}

void RecorderAbilityMainSlice::ReloadItems()
{
    std::vector<RecordItem> list;
#ifdef MOCK_DATA
    list.push_back({"2025-11-12-10-11-01.m4a", "/userdata/audio/2025-11-12-10-11-01.m4a", "今天 17:35", 4, false, false});
    list.push_back({"2025-11-12-10-11-02.m4a", "/userdata/audio/2025-11-12-10-11-02.m4a", "昨天 15:28", 3, false, false});
    list.push_back({"2025-11-12-10-11-03.m4a", "/userdata/audio/2025-11-12-10-11-03.m4a", "前天 09:05", 2, false, false});
    list.push_back(
        {"2025-11-12-10-11-04.m4a", "/userdata/audio/2025-11-12-10-11-04.m4a", "05-18 14:30", 1, false, false});
    list.push_back(
        {"2025-11-12-10-11-05.m4a", "/userdata/audio/2025-11-12-10-11-05.m4a", "2023-12-25 10:00", 0, false, false});
#else
    struct dirent* entry;
    DIR* dir = opendir(RECORDER_DIRECTORY);
    if (dir == nullptr) {
        LOGE("open recorder dir failed. errno:%d", errno);
        return;
    }

    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;
        if (entry->d_type == DT_REG &&
            filename.size() > RECORDER_FILE_POSTFIX_LENGTH &&
            (filename.substr(filename.size() - RECORDER_FILE_POSTFIX_LENGTH) == RECORDER_FILE_POSTFIX)) {
            LOGI("find file: %s", filename.c_str());
            std::string filePath = std::string(RECORDER_DIRECTORY) + filename;
            long time = GetFileTime(filePath);
            std::string timeStr = FormatTime(time, RECORDER_FILE_TIME_FMT);
            RecordItem item = {filename, filePath, timeStr, time, false, false};
            list.push_back(item);
        }
    }
    closedir(dir);
#endif
    if (list.size() > 0) {
        std::sort(list.begin(), list.end(), [](const RecordItem& a, const RecordItem& b) {
                return a.time > b.time;
            });
        adapter_->SetItems(list);
        list_->RefreshList();
    }
}

void RecorderAbilityMainSlice::OnInactive()
{
    LOGI("RecorderAbilityMainSlice::OnInactive");
    AbilitySlice::OnInactive();
}

void RecorderAbilityMainSlice::OnActive(const Want &want)
{
    LOGI("RecorderAbilityMainSlice::OnActive");
    AbilitySlice::OnActive(want);
}

void RecorderAbilityMainSlice::OnBackground()
{
    LOGI("RecorderAbilityMainSlice::OnBackground");
    AbilitySlice::OnBackground();
}

void RecorderAbilityMainSlice::OnStop()
{
    LOGI("RecorderAbilityMainSlice::OnStop");
    AbilitySlice::OnStop();
}
}
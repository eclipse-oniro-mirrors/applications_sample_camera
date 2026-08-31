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

#ifndef OHOS_RECORDER_ABILITY_MAIN_SLICE_H
#define OHOS_RECORDER_ABILITY_MAIN_SLICE_H

#include <ability_slice.h>
#include <components/ui_image_view.h>
#include <components/ui_label.h>
#include <components/ui_list.h>
#include <components/abstract_adapter.h>
#include <event_listener.h>

#include "recorder_config.h"
#include "recorder_list_adapter.h"
#include "media_utils.h"
#include "task_helper.h"

namespace OHOS {
class RecorderAbilityMainSlice : public AbilitySlice, Media::PlayerCallback, Media::RecorderCallback {
public:
    RecorderAbilityMainSlice() = default;
    ~RecorderAbilityMainSlice() override;

public:
    // Media::PlayerCallback overrides
    void OnPlaybackComplete() override;
    void OnError(int32_t errorType, int32_t errorCode) override;
    void OnInfo(int type, int extra) override;
    void OnVideoSizeChanged(int width, int height) override {}
    void OnRewindToComplete() override {}
protected:
    void OnStart(const Want &want) override;
    void OnInactive() override;
    void OnActive(const Want &want) override;
    void OnBackground() override;
    void OnStop() override;

private:
    void InitTitle();
    void InitRecordList();
    void InitRecordCtrl();
    void InitRecordLabels();
    void InitRecordButtons();
    void InitRecordListeners();
    void AddRecordControlsToRoot();
    bool InitImagePath(char* absolutePath, const char* pathHeader, const char* resourcePath, const char* errorTag);
    void InitRootView();
    bool InitIconPaths(const char* pathHeader);
    void Start();
    void Stop();
    void Pause();
    void Resume();
    void Cancel();

    // recorder timer
    void StartTimer();
    void PauseTimer();
    void ResumeTimer();
    void StopTimer();
    void UpdateRecordTime();
    void UpdateDurationLabel();

    void ReloadItems();

    void OnItemPlay(int16_t index, const RecordItem& item);
    void OnItemDelete(int16_t index, const RecordItem& item);

    RootView* rootView_ { nullptr };
    UIViewGroup* titleBar_ { nullptr };
    UIImageView* backButton_ { nullptr };
    EventListener* backButtonListener_ { nullptr };
    UILabel* titleLabel_ { nullptr };
    UILabel* noticeLabel_ { nullptr };
    UILabel* durationLabel_ { nullptr };
    UIImageView* fsImageView_ { nullptr };

    UIImageView* startButton_ { nullptr };  // start/stop
    UIImageView* pauseButton_ { nullptr };  // pause/resume
    UIImageView* cancelButton_ { nullptr };

    EventListener* startButtonListener_ { nullptr };
    EventListener* stopButtonListener_ { nullptr };
    EventListener* pauseButtonListener_ { nullptr };
    EventListener* resumeButtonListener_ { nullptr };
    EventListener* cancelButtonListener_ { nullptr };

    UILabel* listLabel_ { nullptr };
    UIList* list_ { nullptr };
    RecorderListAdapter* adapter_ { nullptr };
    std::string durationTime_;
    MediaUtils mediaUtils_;

    // recorder timer
    std::shared_ptr<Task> recordTimeUpdateTask_;
    uint32_t lastRecordTime_;
    uint32_t recordDuration_;

    char backIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
    char fsIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
    char startIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
    char stopIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
    char pauseIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
    char resumeIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
    char cancelIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
};
}
#endif // OHOS_RECORDER_ABILITY_MAIN_SLICE_H

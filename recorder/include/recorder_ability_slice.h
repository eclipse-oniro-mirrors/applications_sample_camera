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

#ifndef OHOS_RECORDER_ABILITY_SLICE_H
#define OHOS_RECORDER_ABILITY_SLICE_H

#include <ability_slice.h>
#include <components/root_view.h>
#include <components/ui_label.h>
#include <components/ui_image_view.h>
#include <event_listener.h>

#include "recorder_config.h"

namespace OHOS {
class RecorderAbilitySlice : public AbilitySlice {
public:
    RecorderAbilitySlice() = default;
    ~RecorderAbilitySlice() override;
protected:
    void OnStart(const Want &want) override;
    void OnInactive() override;
    void OnActive(const Want &want) override;
    void OnBackground() override;
    void OnStop() override;

private:
    void SetUpRootView();
    void SetUpBackArea();

private:
    RootView* rootView_ { nullptr };
    UIViewGroup* backArea_ { nullptr };
    UIImageView* backIcon_ { nullptr };
    UILabel* titleLabel_ { nullptr };
    EventListener* backIconListener_ { nullptr };
    char backIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
};
} // namespace OHOS
#endif // OHOS_RECORDER_ABILITY_SLICE_H

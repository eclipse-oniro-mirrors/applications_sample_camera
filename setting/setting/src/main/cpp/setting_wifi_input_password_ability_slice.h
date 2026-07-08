/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

#ifndef OHOS_SETTING_WIFI_INPUT_PASSWORD_ABILITY_SLICE_H
#define OHOS_SETTING_WIFI_INPUT_PASSWORD_ABILITY_SLICE_H

#include "ability_loader.h"
#include "common/task.h"
#include "components/ui_checkbox.h"
#include "components/ui_image_view.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_list.h"
#include "components/ui_scroll_view.h"
#include "components/ui_view_group.h"
#include "event_listener.h"
#include "parameter.h"
#include "setting_utils.h"
#include "setting_wifi_input_password_ability_slice.h"
#include "wpa_work.h"

namespace OHOS {
class SettingWifiInputPasswordAbilitySlice : public AbilitySlice {
public:
    SettingWifiInputPasswordAbilitySlice() : headView_(nullptr), inputView_(nullptr), lablelCursorText_(nullptr),
                                             scrollView_(nullptr), rootView_(nullptr), lablelInputText_(nullptr),
                                             buttonBackListener_(nullptr) {}
    virtual ~SettingWifiInputPasswordAbilitySlice();

protected:
    void OnStart(const Want& want) override;
    void OnInactive() override;
    void OnActive(const Want& want) override;
    void OnBackground() override;
    void OnStop() override;

private:
    void SetHead();
    void SetInput();
    void AddInputKeyBoardZero();
    void SetScrollView();
    void SetButtonListener();
    UIViewGroup* headView_;
    UIViewGroup* inputView_;
    UILabel* lablelCursorText_;
    UIScrollView* scrollView_;
    RootView* rootView_;
    UILabel* lablelInputText_;
    EventListener* buttonBackListener_;

    /* Scaled positions from 1920x1080 reference — keep proportions at every resolution */
    static inline int CURSOR_POSITION_OFFSET(){ return HScale(16); }
    static inline int INPUT_X()       { return HScale(36); }
    static inline int INPUT_Y()       { return VScale(108); }
    static inline int INPUT_WIDTH()   { return HScale(888); }
    static inline int INPUT_HEIGHT()  { return VScale(54); }
    static inline int INPUT_CURSOR_X()   { return HScale(20); }
    static inline int INPUT_CURSOR_Y()   { return VScale(10); }
    static inline int INPUT_CURSOR_WIDTH() { return HScale(2); }
    static inline int INPUT_CURSOR_HEIGHT(){ return VScale(36); }
    static inline int INPUT_TEXT_X()      { return HScale(24); }
    static inline int INPUT_TEXT_Y()      { return VScale(11); }
    static inline int INPUT_TEXT_WIDTH()  { return HScale(480); }
    static inline int INPUT_TEXT_HEIGHT() { return VScale(38); }
    static inline int INPUT_ENTER_X()     { return HScale(824); }
    static inline int INPUT_ENTER_Y()     { return VScale(6); }
    static inline int INPUT_ENTER_WIDTH() { return HScale(58); }
    static inline int INPUT_ENTER_HEIGHT(){ return VScale(42); }

    static inline int INPUT_IMAGE_X()      { return HScale(10); }
    static inline int INPUT_IMAGE_Y()      { return VScale(2); }
    static inline int INPUT_IMAGE_WIDTH()  { return HScale(38); }
    static inline int INPUT_IMAGE_HEIGHT() { return VScale(38); }

    static inline int BUTTON_NUM() { return 3; }

    static inline int BUTTON_INTERVAL_X() { return HScale(172); }
    static inline int BUTTON_INTERVAL_Y() { return VScale(66); }
    static inline int BUTTON_WIDTH()      { return HScale(160); }
    static inline int BUTTON_HEIGHT()     { return VScale(54); }

    static inline int SCROLL_WIFI_INPUT_X()      { return HScale(228); }
    static inline int SCROLL_WIFI_INPUT_Y()      { return VScale(198); }
    static inline int SCROLL_WIFI_INPUT_WIDTH()  { return HScale(530); }
    static inline int SCROLL_WIFI_INPUT_HEIGHT() { return VScale(252); }

    /* constants that are resolution-independent */
    constexpr static int RECT_RADIUS = 6;
    constexpr static int INPUT_RADIUS = 32;
    constexpr static int INPUT_FONT_SIZE = 28;
    constexpr static int INPUT_ENTER_RADIUS = 32;
    /* initial cursor X in the 1920x1080 reference; runtime value is HScale-derived */
    static inline int CURSOR_INIT_X() { return HScale(20); }
};

} // namespace OHOS
#endif

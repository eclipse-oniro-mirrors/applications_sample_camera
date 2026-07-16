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
    static constexpr int16_t cursorPositionOffsetRef = 16;
    static constexpr int16_t inputXRef = 36;
    static constexpr int16_t inputYRef = 108;
    static constexpr int16_t inputWidthRef = 888;
    static constexpr int16_t inputHeightRef = 54;
    static constexpr int16_t inputCursorXRef = 20;
    static constexpr int16_t inputCursorYRef = 10;
    static constexpr int16_t inputCursorWidthRef = 2;
    static constexpr int16_t inputCursorHeightRef = 36;
    static constexpr int16_t inputTextXRef = 24;
    static constexpr int16_t inputTextYRef = 11;
    static constexpr int16_t inputTextWidthRef = 480;
    static constexpr int16_t inputTextHeightRef = 38;
    static constexpr int16_t inputEnterXRef = 824;
    static constexpr int16_t inputEnterYRef = 6;
    static constexpr int16_t inputEnterWidthRef = 58;
    static constexpr int16_t inputEnterHeightRef = 42;

    static constexpr int16_t inputImageXRef = 10;
    static constexpr int16_t inputImageYRef = 2;
    static constexpr int16_t inputImageWidthRef = 38;
    static constexpr int16_t inputImageHeightRef = 38;

    static constexpr int buttonNumRef = 3;

    static constexpr int16_t buttonIntervalXRef = 172;
    static constexpr int16_t buttonIntervalYRef = 66;
    static constexpr int16_t buttonWidthRef = 160;
    static constexpr int16_t buttonHeightRef = 54;

    static constexpr int16_t scrollWifiInputXRef = 228;
    static constexpr int16_t scrollWifiInputYRef = 198;
    static constexpr int16_t scrollWifiInputWidthRef = 530;
    static constexpr int16_t scrollWifiInputHeightRef = 252;

    /* constants that are resolution-independent */
    constexpr static int RECT_RADIUS = 6;
    constexpr static int INPUT_RADIUS = 32;
    constexpr static int INPUT_FONT_SIZE = 28;
    constexpr static int INPUT_ENTER_RADIUS = 32;
    /* initial cursor X in the 1920x1080 reference; runtime value is HScale-derived */
    static constexpr int16_t cursorInitXRef = 20;

    static inline int CURSOR_POSITION_OFFSET()
    {
        return HScale(cursorPositionOffsetRef);
    }
    static inline int INPUT_X()
    {
        return HScale(inputXRef);
    }
    static inline int INPUT_Y()
    {
        return VScale(inputYRef);
    }
    static inline int INPUT_WIDTH()
    {
        return HScale(inputWidthRef);
    }
    static inline int INPUT_HEIGHT()
    {
        return VScale(inputHeightRef);
    }
    static inline int INPUT_CURSOR_X()
    {
        return HScale(inputCursorXRef);
    }
    static inline int INPUT_CURSOR_Y()
    {
        return VScale(inputCursorYRef);
    }
    static inline int INPUT_CURSOR_WIDTH()
    {
        return HScale(inputCursorWidthRef);
    }
    static inline int INPUT_CURSOR_HEIGHT()
    {
        return VScale(inputCursorHeightRef);
    }
    static inline int INPUT_TEXT_X()
    {
        return HScale(inputTextXRef);
    }
    static inline int INPUT_TEXT_Y()
    {
        return VScale(inputTextYRef);
    }
    static inline int INPUT_TEXT_WIDTH()
    {
        return HScale(inputTextWidthRef);
    }
    static inline int INPUT_TEXT_HEIGHT()
    {
        return VScale(inputTextHeightRef);
    }
    static inline int INPUT_ENTER_X()
    {
        return HScale(inputEnterXRef);
    }
    static inline int INPUT_ENTER_Y()
    {
        return VScale(inputEnterYRef);
    }
    static inline int INPUT_ENTER_WIDTH()
    {
        return HScale(inputEnterWidthRef);
    }
    static inline int INPUT_ENTER_HEIGHT()
    {
        return VScale(inputEnterHeightRef);
    }

    static inline int INPUT_IMAGE_X()
    {
        return HScale(inputImageXRef);
    }
    static inline int INPUT_IMAGE_Y()
    {
        return VScale(inputImageYRef);
    }
    static inline int INPUT_IMAGE_WIDTH()
    {
        return HScale(inputImageWidthRef);
    }
    static inline int INPUT_IMAGE_HEIGHT()
    {
        return VScale(inputImageHeightRef);
    }

    static inline int BUTTON_NUM()
    {
        return buttonNumRef;
    }

    static inline int BUTTON_INTERVAL_X()
    {
        return HScale(buttonIntervalXRef);
    }
    static inline int BUTTON_INTERVAL_Y()
    {
        return VScale(buttonIntervalYRef);
    }
    static inline int BUTTON_WIDTH()
    {
        return HScale(buttonWidthRef);
    }
    static inline int BUTTON_HEIGHT()
    {
        return VScale(buttonHeightRef);
    }

    static inline int SCROLL_WIFI_INPUT_X()
    {
        return HScale(scrollWifiInputXRef);
    }
    static inline int SCROLL_WIFI_INPUT_Y()
    {
        return VScale(scrollWifiInputYRef);
    }
    static inline int SCROLL_WIFI_INPUT_WIDTH()
    {
        return HScale(scrollWifiInputWidthRef);
    }
    static inline int SCROLL_WIFI_INPUT_HEIGHT()
    {
        return VScale(scrollWifiInputHeightRef);
    }

    static inline int CURSOR_INIT_X()
    {
        return HScale(cursorInitXRef);
    }
};

} // namespace OHOS
#endif

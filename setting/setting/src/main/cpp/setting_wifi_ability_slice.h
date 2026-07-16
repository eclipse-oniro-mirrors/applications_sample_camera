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

#ifndef OHOS_SETTING_WIFI_ABILITY_SLICE_H
#define OHOS_SETTING_WIFI_ABILITY_SLICE_H

#include <cstddef>
#include <cstdio>
#include <cstring>

#include "ability_loader.h"
#include "common/task.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_list.h"
#include "components/ui_scroll_view.h"
#include "components/ui_toggle_button.h"
#include "event_listener.h"
#include "gfx_utils/list.h"
#include "parameter.h"
#include "pthread.h"
#include "setting_utils.h"
#include "wpa_work.h"

namespace OHOS {
class TestBtnOnStateChangeListener : public OHOS::UICheckBox::OnChangeListener, public OHOS::UIView::OnClickListener {
public:
    ~TestBtnOnStateChangeListener() {}
    explicit TestBtnOnStateChangeListener(UIView* uiView) : myUiView(uiView) {}

    bool OnChange(UICheckBox::UICheckBoxState state) override
    {
        return true;
    }
    bool OnClick(UIView& view, const ClickEvent& event) override
    {
        bool ret = myUiView->IsVisible();
        if (ret == false) {
            myUiView->SetVisible(true);
        } else {
            myUiView->SetVisible(false);
        }
        myUiView->Invalidate();
        return true;
    }

private:
    UIView* myUiView;
};

class SettingWifiAbilitySlice : public AbilitySlice, Task {
public:
    SettingWifiAbilitySlice();
    virtual ~SettingWifiAbilitySlice();
    void AddWifi(void);
    void Callback() override;

protected:
    void OnStart(const Want& want) override;
    void OnInactive() override;
    void OnActive(const Want& want) override;
    void OnBackground() override;
    void OnStop() override;

private:
    void MyThread();
    void SetWifiButtonListener(char* ssid);
    void SetButtonListener();
    void SetHead();
    void SetToggleButton();
    void SetUseWifi();
    void SetScrollWifi();

    UIViewGroup* headView_;
    UIViewGroup* toggleButtonView_;
    UIScrollView* scrollView_;
    RootView* rootView_;
    TestBtnOnStateChangeListener* changeListener_;
    EventListener* buttonBackListener_;
    EventListener* buttonInputListener_;
    int wpaCount_;

    /* Scaled positions from 1920x1080 reference — keep proportions at every resolution */
    static constexpr int16_t toggleXRef = 36;
    static constexpr int16_t toggleYRef = 72;

    static constexpr int16_t useWifiFontXRef = 54;
    static constexpr int16_t useWifiFontYRef = 187;

    static constexpr int16_t scrollWifiXRef = 36;
    static constexpr int16_t scrollWifiYRef = 242;
    static constexpr int16_t scrollWifiWidthRef = 960;
    static constexpr int16_t scrollWifiHeightRef = 238;

    static inline int TOGGLE_X()
    {
        return HScale(toggleXRef);
    }
    static inline int TOGGLE_Y()
    {
        return VScale(toggleYRef);
    }

    static inline int USE_WIFI_FONT_X()
    {
        return HScale(useWifiFontXRef);
    }
    static inline int USE_WIFI_FONT_Y()
    {
        return VScale(useWifiFontYRef);
    }

    static inline int ADD_WIFI_X()
    {
        return 0;
    }
    static inline int SCROLL_WIFI_X()
    {
        return HScale(scrollWifiXRef);
    }
    static inline int SCROLL_WIFI_Y()
    {
        return VScale(scrollWifiYRef);
    }
    static inline int SCROLL_WIFI_WIDTH()
    {
        return HScale(scrollWifiWidthRef);
    }
    static inline int SCROLL_WIFI_HEIGHT()
    {
        return VScale(scrollWifiHeightRef);
    }
};
} // namespace OHOS
#endif

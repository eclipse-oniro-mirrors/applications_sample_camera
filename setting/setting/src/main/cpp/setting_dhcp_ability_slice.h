/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef OHOS_SETTING_DHCP_ABILITY_SLICE_H
#define OHOS_SETTING_DHCP_ABILITY_SLICE_H

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <securec.h>

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

namespace OHOS {
extern int g_dhcpStatus;
extern char g_dhcpIp[64];

class DhcpBtnOnStateChangeListener : public OHOS::UICheckBox::OnChangeListener, public OHOS::UIView::OnClickListener {
public:
    ~DhcpBtnOnStateChangeListener() {}
    explicit DhcpBtnOnStateChangeListener(UIView* uiView) : myUiView(uiView) {}

    bool OnChange(UICheckBox::UICheckBoxState state) override
    {
        return true;
    }
    bool OnClick(UIView& view, const ClickEvent& event) override;

private:
    UIView* myUiView;
};

class SettingDhcpAbilitySlice : public AbilitySlice, Task {
public:
    SettingDhcpAbilitySlice();
    virtual ~SettingDhcpAbilitySlice();
    void Callback() override;
protected:
    void OnStart(const Want& want) override;
    void OnInactive() override;
    void OnActive(const Want& want) override;
    void OnBackground() override;
    void OnStop() override;

private:
    void SetButtonListener();
    void SetHead();
    void SetToggleButton();
    void SetUseDhcp();
    void SetScrollDhcp();

    UIViewGroup* headView_;
    UIViewGroup* toggleButtonView_;
    UIScrollView* scrollView_;
    RootView* rootView_;
    DhcpBtnOnStateChangeListener* changeListener_;
    EventListener* buttonBackListener_;

    /* Scaled positions from 1920x1080 reference — keep proportions at every resolution */
    static constexpr int16_t toggleXRef = 36;
    static constexpr int16_t toggleYRef = 72;
    static constexpr int16_t useDhcpFontXRef = 54;
    static constexpr int16_t useDhcpFontYRef = 187;
    static constexpr int16_t scrollDhcpXRef = 36;
    static constexpr int16_t scrollDhcpYRef = 242;
    static constexpr int16_t scrollDhcpWidthRef = 960;
    static constexpr int16_t scrollDhcpHeightRef = 238;

    static inline int ToggleX()
    {
        return HScale(toggleXRef);
    }
    static inline int ToggleY()
    {
        return VScale(toggleYRef);
    }

    static inline int UseDhcpFontX()
    {
        return HScale(useDhcpFontXRef);
    }
    static inline int UseDhcpFontY()
    {
        return VScale(useDhcpFontYRef);
    }

    static inline int ScrollDhcpX()
    {
        return HScale(scrollDhcpXRef);
    }
    static inline int ScrollDhcpY()
    {
        return VScale(scrollDhcpYRef);
    }
    static inline int ScrollDhcpWidth()
    {
        return HScale(scrollDhcpWidthRef);
    }
    static inline int ScrollDhcpHeight()
    {
        return VScale(scrollDhcpHeightRef);
    }
};
} // namespace OHOS
#endif

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
    static inline int toggleX()        { return HScale(36); }
    static inline int toggleY()        { return VScale(72); }

    static inline int useDhcpFontX()   { return HScale(54); }
    static inline int useDhcpFontY()   { return VScale(187); }

    static inline int scrollDhcpX()      { return HScale(36); }
    static inline int scrollDhcpY()      { return VScale(242); }
    static inline int scrollDhcpWidth() { return HScale(960); }
    static inline int scrollDhcpHeight(){ return VScale(238); }
};
} // namespace OHOS
#endif

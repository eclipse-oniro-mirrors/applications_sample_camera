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

#ifndef OHOS_APP_INFO_ABILITY_SLICE_H
#define OHOS_APP_INFO_ABILITY_SLICE_H

#include "ability_info.h"
#include "ability_loader.h"
#include "ability_manager.h"
#include "ability_slice.h"
#include "bundle_manager.h"
#include "components/ui_image_view.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_list.h"
#include "components/ui_scroll_view.h"
#include "components/ui_toggle_button.h"
#include "element_name.h"
#include "event_listener.h"
#include "list.h"
#include "module_info.h"
#include "setting_utils.h"
#include "want.h"
#include "pms_interface.h"
#include<stdio.h>
#include<securec.h>

namespace OHOS {

class ToggBtnOnListener : public UIView::OnClickListener {
public:
    ToggBtnOnListener(UIToggleButton* togglebutton, const char* name, int len1, const char* bundleName, int len2)
    {
        memcpy_s(name_, sizeof(name_), name, len1);
        name_[len1] = 0;
        memcpy_s(bundleName_, sizeof(bundleName_), bundleName, len2);
        bundleName_[len2] = 0;
        status_ = false;
        togglebutton_ = togglebutton;
    }

    bool OnClick(UIView& view, const ClickEvent& event) override
    {
        int ret = -1;
        if (status_) {
            if ((ret = RevokePermission(bundleName_, name_)) == 0) {
                status_ = false;
                togglebutton_->SetState(false);
            } else {
            }
        } else {
            if ((ret = GrantPermission(bundleName_, name_)) == 0) {
                status_ = true;
                togglebutton_->SetState(true);
            } else {
            }
        }
        return true;
    }
private:
    char name_[128];
    char bundleName_[128];
    bool status_;
    UIToggleButton* togglebutton_;
};

class AppInfoAbilitySlice : public AbilitySlice {
public:
    AppInfoAbilitySlice()
        : headView_(nullptr), scrollView_(nullptr), rootView_(nullptr), permissions_(nullptr),
          buttonBackListener_(nullptr) {}
    virtual ~AppInfoAbilitySlice();
protected:
    void OnStart(const Want& want) override;
    void OnInactive() override;
    void OnActive(const Want& want) override;
    void OnBackground() override;
    void OnStop() override;
private:
    void SetAppButtonListener(const char* appName);
    void SetButtonListener(void);
    void SetHead(void);
    UIViewGroup* headView_;
    UIScrollView* scrollView_;
    RootView* rootView_;
    PermissionSaved* permissions_;
    EventListener* buttonBackListener_;
    List<ToggBtnOnListener*> listListener_;

    void PermissionInfoList();
    void SetAppPermissionInfo(int index, PermissionSaved& permissions);
    char bundleName_[128];

};
} // namespace OHOS
#endif

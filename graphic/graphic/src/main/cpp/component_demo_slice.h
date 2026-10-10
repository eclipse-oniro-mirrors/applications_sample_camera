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

#ifndef GRAPHIC_COMPONENT_DEMO_SLICE_H
#define GRAPHIC_COMPONENT_DEMO_SLICE_H

#include "ability_slice.h"
#include "ability_loader.h"
#include "want.h"
#include "components/root_view.h"
#include "components/ui_view_group.h"
#include "components/ui_label.h"
#include "components/ui_image_view.h"
#include "event_listener.h"

namespace OHOS {
class ComponentDemoSlice : public AbilitySlice {
public:
    explicit ComponentDemoSlice(const char* title);
    ~ComponentDemoSlice() override;

    void OnStart(const Want& want) override;

protected:
    virtual void SetupContent(UIViewGroup* content) = 0;

    // 顶栏返回动作，默认跳回主菜单，主菜单覆写为退出应用
    virtual void GoBack();

    static constexpr int16_t headHeight = 80;
    static constexpr int16_t headTitleFontSize = 36;

private:
    void SetupHead();

    RootView* rootView_ = nullptr;
    UIViewGroup* headView_ = nullptr;
    UIViewGroup* contentView_ = nullptr;
    EventListener* buttonBackListener_ = nullptr;
    const char* const title_;
};
} // namespace OHOS
#endif // GRAPHIC_COMPONENT_DEMO_SLICE_H

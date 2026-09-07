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

#ifndef GRAPHIC_MAIN_MENU_ABILITY_SLICE_H
#define GRAPHIC_MAIN_MENU_ABILITY_SLICE_H

#include "component_demo_slice.h"
#include "components/ui_scroll_view.h"
#include "event_listener.h"
#include <memory>

namespace OHOS {
class MainMenuAbilitySlice : public ComponentDemoSlice {
public:
    MainMenuAbilitySlice() : ComponentDemoSlice("UI组件验证") {}
    ~MainMenuAbilitySlice() override;

protected:
    void SetupContent(UIViewGroup* content) override;
    void GoBack() override;

private:
    void AddMenuItem(const char* title, const char* target, int16_t y, int16_t index);

    // UI布局常量
    static constexpr int16_t menuItemCount = 4;
    static constexpr int16_t menuItemHeight = 80;
    static constexpr int16_t menuItemGap = 12;
    static constexpr int16_t menuItemStartY = 16;
    static constexpr int16_t menuItemMarginX = 36;
    static constexpr int16_t menuItemRadius = 16;
    static constexpr int16_t menuItemPaddingX = 24;
    static constexpr int16_t menuItemTitleY = 20;
    static constexpr int16_t menuItemTitleHeight = 40;
    static constexpr int16_t menuItemTitleReserved = 120;
    static constexpr int16_t menuItemTitleSize = 30;
    static constexpr int16_t menuForwardImgOffsetX = 48;
    static constexpr int16_t menuForwardImgY = 16;

    UIScrollView* scrollView_ = nullptr;
    // 菜单项归属 scrollView_ 视图树；保存指针仅为析构时解除监听绑定
    UIViewGroup* itemViews_[menuItemCount] = {};
    std::unique_ptr<EventListener> itemListeners_[menuItemCount] = {};
};
} // namespace OHOS
#endif // GRAPHIC_MAIN_MENU_ABILITY_SLICE_H

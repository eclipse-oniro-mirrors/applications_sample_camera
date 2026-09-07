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

#include "main_menu_ability_slice.h"
#include <cstdio>
#include "ability_loader.h"
#include "common/screen.h"
#include "graphic_utils.h"
#include "components/ui_image_view.h"
#include "components/ui_label.h"

namespace OHOS {
REGISTER_AS(MainMenuAbilitySlice)

MainMenuAbilitySlice::~MainMenuAbilitySlice()
{
    // 先解除菜单项对 listener 的引用并释放 listener，再销毁视图树，
    // 防止视图树销毁过程中触发回调访问已释放的 listener
    for (int16_t i = 0; i < menuItemCount; i++) {
        if (itemViews_[i] != nullptr) {
            itemViews_[i]->SetOnClickListener(nullptr);
        }
        itemListeners_[i] = nullptr;
    }
    if (scrollView_ != nullptr) {
        GraphicDeleteViewTree(scrollView_);
        scrollView_ = nullptr;
    }
}

void MainMenuAbilitySlice::GoBack()
{
    printf("[MainMenu] Back button clicked, exit to desktop\n");
    // 主菜单的返回动作是结束当前Ability，退出到桌面
    TerminateAbility();
}

void MainMenuAbilitySlice::SetupContent(UIViewGroup* content)
{
    int16_t screenWidth = Screen::GetInstance().GetWidth();
    int16_t screenHeight = Screen::GetInstance().GetHeight();

    scrollView_ = GraphicCreateView<UIScrollView>(content);
    if (scrollView_ == nullptr) {
        printf("[MainMenu] create scroll view failed\n");
        return;
    }
    scrollView_->SetPosition(0, 0, screenWidth, screenHeight - headHeight);
    scrollView_->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::Black()));
    scrollView_->SetXScrollBarVisible(false);
    scrollView_->SetYScrollBarVisible(true);

    struct MenuItem {
        const char* title;
        const char* target;
    };

    const MenuItem items[menuItemCount] = {
        { "Button组件验证", "ButtonDemoAbilitySlice" },
        { "Scroller组件验证", "ScrollerDemoAbilitySlice" },
        { "Switch组件验证", "SwitchDemoAbilitySlice" },
        { "Slider组件验证", "SliderDemoAbilitySlice" },
    };

    for (int16_t i = 0; i < menuItemCount; i++) {
        int16_t itemY = menuItemStartY + i * (menuItemHeight + menuItemGap);
        AddMenuItem(items[i].title, items[i].target, itemY, i);
    }
}

void MainMenuAbilitySlice::AddMenuItem(const char* title, const char* target, int16_t y, int16_t index)
{
    int16_t screenWidth = Screen::GetInstance().GetWidth();
    int16_t itemWidth = screenWidth - menuItemMarginX - menuItemMarginX;

    UIViewGroup* itemView = GraphicCreateView<UIViewGroup>(scrollView_);
    if (itemView == nullptr) {
        printf("[MainMenu] create menu item failed\n");
        return;
    }
    itemViews_[index] = itemView;
    itemView->SetPosition(menuItemMarginX, y, itemWidth, menuItemHeight);
    itemView->SetStyle(STYLE_BORDER_RADIUS, menuItemRadius);
    itemView->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x33, 0x33, 0x33)));
    itemView->SetTouchable(true);

    UILabel* titleLabel = GraphicCreateView<UILabel>(itemView);
    if (titleLabel == nullptr) {
        printf("[MainMenu] create menu item title failed\n");
        return;
    }
    titleLabel->SetPosition(menuItemPaddingX, menuItemTitleY,
                            itemWidth - menuItemTitleReserved, menuItemTitleHeight);
    titleLabel->SetText(title);
    titleLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, menuItemTitleSize);
    titleLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));

    UIImageView* forwardImage = GraphicCreateView<UIImageView>(itemView);
    if (forwardImage == nullptr) {
        printf("[MainMenu] create forward image failed\n");
        return;
    }
    forwardImage->SetPosition(itemWidth - menuForwardImgOffsetX, menuForwardImgY);
    forwardImage->SetSrc(GRAPHIC_IMAGE_FORWARD);

    auto onClick = [this, target](UIView& view, const Event& event) -> bool {
        Want want{};
        AbilitySlice* nextSlice = AbilityLoader::GetInstance().GetAbilitySliceByName(target);
        if (nextSlice == nullptr) {
            printf("[MainMenu] undefined %s\n", target);
        } else {
            Present(*nextSlice, want);
        }
        return true;
    };
    itemListeners_[index] = std::make_unique<EventListener>(onClick, nullptr);
    if (itemListeners_[index] == nullptr) {
        printf("[MainMenu] create menu item listener failed\n");
        return;
    }
    itemView->SetOnClickListener(itemListeners_[index].get());
}
} // namespace OHOS

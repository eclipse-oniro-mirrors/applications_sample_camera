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

#include "component_demo_slice.h"
#include <cstdio>
#include <new>
#include "common/screen.h"
#include "graphic_utils.h"

namespace OHOS {
ComponentDemoSlice::ComponentDemoSlice(const char* title) : title_(title) {}

ComponentDemoSlice::~ComponentDemoSlice()
{
    if (headView_ != nullptr) {
        GraphicDeleteViewTree(headView_);
        headView_ = nullptr;
    }
    if (contentView_ != nullptr) {
        GraphicDeleteViewTree(contentView_);
        contentView_ = nullptr;
    }
    if (buttonBackListener_ != nullptr) {
        delete buttonBackListener_;
        buttonBackListener_ = nullptr;
    }
    if (rootView_ != nullptr) {
        RootView::DestroyWindowRootView(rootView_);
        rootView_ = nullptr;
    }
}

void ComponentDemoSlice::GoBack()
{
    Want want{};
    AbilitySlice* nextSlice = AbilityLoader::GetInstance().GetAbilitySliceByName("MainMenuAbilitySlice");
    if (nextSlice == nullptr) {
        printf("[ComponentDemo] undefined MainMenuAbilitySlice\n");
    } else {
        Present(*nextSlice, want);
    }
}

void ComponentDemoSlice::SetupHead()
{
    int16_t screenWidth = Screen::GetInstance().GetWidth();

    headView_ = GraphicCreateView<UIViewGroup>(rootView_);
    if (headView_ == nullptr) {
        printf("[ComponentDemo] create head view failed\n");
        return;
    }
    headView_->SetPosition(0, 0, screenWidth, headHeight);
    headView_->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x33, 0x33, 0x33)));
    headView_->SetStyle(STYLE_BACKGROUND_OPA, OPA_OPAQUE);
    headView_->SetTouchable(true);

    // 返回按钮：图标本身不设为触摸目标，点击穿透到顶栏整条热区
    UIImageView* backButton = GraphicCreateView<UIImageView>(headView_);
    if (backButton == nullptr) {
        printf("[ComponentDemo] create back button failed\n");
        return;
    }
    backButton->SetPosition(GRAPHIC_HEAD_IMAGE_X, GRAPHIC_HEAD_IMAGE_Y,
                            GRAPHIC_HEAD_IMAGE_WIDTH, GRAPHIC_HEAD_IMAGE_HEIGHT);
    backButton->SetSrc(GRAPHIC_IMAGE_BACK);

    auto onBack = [this](UIView& view, const Event& event) -> bool {
        GoBack();
        return true;
    };
    buttonBackListener_ = new (std::nothrow) EventListener(onBack, nullptr);
    if (buttonBackListener_ == nullptr) {
        printf("[ComponentDemo] create back listener failed\n");
        return;
    }
    headView_->SetOnClickListener(buttonBackListener_);

    // 标题：占满顶栏并水平居中，文字不拦截点击（事件穿透到顶栏）
    UILabel* titleLabel = GraphicCreateView<UILabel>(headView_);
    if (titleLabel == nullptr) {
        printf("[ComponentDemo] create title label failed\n");
        return;
    }
    titleLabel->SetPosition(0, 0, screenWidth, headHeight);
    titleLabel->SetText(title_);
    titleLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, headTitleFontSize);
    titleLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    titleLabel->SetAlign(TEXT_ALIGNMENT_CENTER, TEXT_ALIGNMENT_CENTER);
}

void ComponentDemoSlice::OnStart(const Want& want)
{
    AbilitySlice::OnStart(want);

    rootView_ = RootView::GetWindowRootView();
    if (rootView_ == nullptr) {
        printf("[ComponentDemo] get window root view failed\n");
        return;
    }

    int16_t screenWidth = Screen::GetInstance().GetWidth();
    int16_t screenHeight = Screen::GetInstance().GetHeight();
    rootView_->SetPosition(0, 0, screenWidth, screenHeight);
    rootView_->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::Black()));

    SetupHead();
    if (headView_ == nullptr) {
        return;
    }

    contentView_ = GraphicCreateView<UIViewGroup>(rootView_);
    if (contentView_ == nullptr) {
        printf("[ComponentDemo] create content view failed\n");
        return;
    }
    contentView_->SetPosition(0, headHeight, screenWidth, screenHeight - headHeight);
    contentView_->SetStyle(STYLE_BACKGROUND_OPA, OPA_TRANSPARENT);

    SetupContent(contentView_);
    SetUIContent(rootView_);
}
} // namespace OHOS

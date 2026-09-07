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

#include "button_demo_ability_slice.h"
#include <cstdio>
#include "common/screen.h"
#include "graphic_utils.h"
#include "securec.h"
#include "components/ui_label.h"

namespace OHOS {
REGISTER_AS(ButtonDemoAbilitySlice)

ButtonDemoAbilitySlice::~ButtonDemoAbilitySlice()
{
    // 先解除按钮对 listener 的引用，再释放 listener，避免组件持有悬空指针
    for (int16_t i = 0; i < buttonCount; i++) {
        if (demoButtons_[i] != nullptr) {
            demoButtons_[i]->SetOnClickListener(nullptr);
        }
    }
    buttonClickListener_ = nullptr;
}

void ButtonDemoAbilitySlice::SetupContent(UIViewGroup* content)
{
    int16_t screenWidth = Screen::GetInstance().GetWidth();
    int16_t buttonWidth = screenWidth - pageMarginX - pageMarginX;
    int16_t buttonStep = buttonHeight + buttonGap;

    UILabel* hintLabel = AddHintLabel(content);
    if (hintLabel == nullptr) {
        return;
    }
    UILabel* countLabel = AddCountLabel(content);
    if (countLabel == nullptr) {
        return;
    }
    CreateClickListener(countLabel);
    if (buttonClickListener_ == nullptr) {
        return;
    }

    const char* buttonNames[buttonCount] = { "主按钮", "普通按钮", "描边按钮" };
    for (int16_t i = 0; i < buttonCount; i++) {
        AddDemoButton(content, buttonNames[i], i, buttonWidth, buttonStep);
    }
}

UILabel* ButtonDemoAbilitySlice::AddHintLabel(UIViewGroup* content)
{
    int16_t screenWidth = Screen::GetInstance().GetWidth();
    UILabel* hintLabel = GraphicCreateView<UILabel>(content);
    if (hintLabel == nullptr) {
        printf("[ButtonDemo] create hint label failed\n");
        return nullptr;
    }
    hintLabel->SetPosition(0, hintY, screenWidth, hintHeight);
    hintLabel->SetText("点击按钮触发回调");
    hintLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, hintFontSize);
    hintLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xAA, 0xAA, 0xAA)));
    hintLabel->SetAlign(TEXT_ALIGNMENT_CENTER, TEXT_ALIGNMENT_CENTER);
    return hintLabel;
}

UILabel* ButtonDemoAbilitySlice::AddCountLabel(UIViewGroup* content)
{
    int16_t screenWidth = Screen::GetInstance().GetWidth();
    UILabel* countLabel = GraphicCreateView<UILabel>(content);
    if (countLabel == nullptr) {
        printf("[ButtonDemo] create count label failed\n");
        return nullptr;
    }
    countLabel->SetPosition(0, countY, screenWidth, countHeight);
    countLabel->SetText("点击次数: 0");
    countLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, countFontSize);
    countLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    countLabel->SetAlign(TEXT_ALIGNMENT_CENTER, TEXT_ALIGNMENT_CENTER);
    return countLabel;
}

void ButtonDemoAbilitySlice::CreateClickListener(UILabel* countLabel)
{
    auto onClick = [this, countLabel](UIView& view, const Event& event) -> bool {
        clickCount_++;
        if (countLabel == nullptr) {
            return true;
        }
        char text[32] = {0};
        int ret = snprintf_s(text, sizeof(text), sizeof(text) - 1, "点击次数: %d", clickCount_);
        if (ret < 0) {
            return true;
        }
        countLabel->SetText(text);
        return true;
    };
    buttonClickListener_ = std::make_unique<EventListener>(onClick, nullptr);
    if (buttonClickListener_ == nullptr) {
        printf("[ButtonDemo] create button listener failed\n");
    }
}

void ButtonDemoAbilitySlice::AddDemoButton(UIViewGroup* content, const char* name, int16_t index,
                                           int16_t buttonWidth, int16_t buttonStep)
{
    demoButtons_[index] = GraphicCreateView<UILabelButton>(content);
    if (demoButtons_[index] == nullptr) {
        printf("[ButtonDemo] create button %d failed\n", index);
        return;
    }
    UILabelButton* button = demoButtons_[index];
    button->SetPosition(pageMarginX, buttonStartY + index * buttonStep, buttonWidth, buttonHeight);
    button->SetText(name);
    button->SetAlign(TEXT_ALIGNMENT_CENTER);
    button->SetFont(DEFAULT_VECTOR_FONT_FILENAME, buttonFontSize);
    button->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    if (index == 0) {
        button->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xFF, 0x7A, 0x00)));
    } else if (index == 1) {
        button->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x33, 0x33, 0x33)));
    } else {
        button->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::Black()));
        button->SetStyle(STYLE_BORDER_WIDTH, buttonBorderWidth);
        button->SetStyle(STYLE_BORDER_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xFF, 0x7A, 0x00)));
    }
    button->SetStyle(STYLE_BORDER_RADIUS, buttonRadius);
    button->SetTouchable(true);
    button->SetOnClickListener(buttonClickListener_.get());
}
} // namespace OHOS

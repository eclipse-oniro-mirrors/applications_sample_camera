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

#include "slider_demo_ability_slice.h"
#include <cstdio>
#include "common/screen.h"
#include "graphic_utils.h"
#include "securec.h"
#include "components/ui_label.h"
#include "components/ui_slider.h"

namespace OHOS {
class SliderValueListener : public UISlider::UISliderEventListener {
public:
    explicit SliderValueListener(UILabel* valueLabel) : valueLabel_(valueLabel) {}
    ~SliderValueListener() override = default;

    void OnChange(int32_t value) override
    {
        UpdateValue(value);
    }

    void OnRelease(int32_t value) override
    {
        UpdateValue(value);
    }

private:
    void UpdateValue(int32_t value)
    {
        if (valueLabel_ == nullptr) {
            return;
        }
        char text[32] = {0};
        int ret = snprintf_s(text, sizeof(text), sizeof(text) - 1, "当前值: %d", value);
        if (ret < 0) {
            return;
        }
        valueLabel_->SetText(text);
    }

    // valueLabel 归属内容视图树，生命周期长于本 listener（listener 先于视图树释放）
    UILabel* valueLabel_;
};

REGISTER_AS(SliderDemoAbilitySlice)

SliderDemoAbilitySlice::~SliderDemoAbilitySlice()
{
    // 先解除 slider 对 listener 的引用，再释放 listener，避免组件持有悬空指针
    if (slider_ != nullptr) {
        slider_->SetSliderEventListener(nullptr);
    }
    sliderListener_ = nullptr;
}

void SliderDemoAbilitySlice::SetupContent(UIViewGroup* content)
{
    int16_t screenWidth = Screen::GetInstance().GetWidth();
    int16_t sliderWidth = screenWidth - pageMarginX - pageMarginX;

    UILabel* hintLabel = AddHintLabel(content);
    if (hintLabel == nullptr) {
        return;
    }
    UILabel* valueLabel = AddValueLabel(content);
    if (valueLabel == nullptr) {
        return;
    }
    CreateSlider(content, sliderWidth);
    if (slider_ == nullptr) {
        return;
    }
    BindSliderListener(valueLabel);
}

UILabel* SliderDemoAbilitySlice::AddHintLabel(UIViewGroup* content)
{
    int16_t screenWidth = Screen::GetInstance().GetWidth();
    UILabel* hintLabel = GraphicCreateView<UILabel>(content);
    if (hintLabel == nullptr) {
        printf("[SliderDemo] create hint label failed\n");
        return nullptr;
    }
    hintLabel->SetPosition(0, hintY, screenWidth, hintHeight);
    hintLabel->SetText("拖动滑块调节数值");
    hintLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, hintFontSize);
    hintLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xAA, 0xAA, 0xAA)));
    hintLabel->SetAlign(TEXT_ALIGNMENT_CENTER, TEXT_ALIGNMENT_CENTER);
    return hintLabel;
}

UILabel* SliderDemoAbilitySlice::AddValueLabel(UIViewGroup* content)
{
    int16_t screenWidth = Screen::GetInstance().GetWidth();
    UILabel* valueLabel = GraphicCreateView<UILabel>(content);
    if (valueLabel == nullptr) {
        printf("[SliderDemo] create value label failed\n");
        return nullptr;
    }
    valueLabel->SetPosition(0, valueY, screenWidth, valueHeight);
    char initText[32] = {0};
    int ret = snprintf_s(initText, sizeof(initText), sizeof(initText) - 1, "当前值: %d", sliderInitValue);
    if (ret < 0) {
        printf("[SliderDemo] format init text failed\n");
        return nullptr;
    }
    valueLabel->SetText(initText);
    valueLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, valueFontSize);
    valueLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    valueLabel->SetAlign(TEXT_ALIGNMENT_CENTER, TEXT_ALIGNMENT_CENTER);
    return valueLabel;
}

void SliderDemoAbilitySlice::CreateSlider(UIViewGroup* content, int16_t sliderWidth)
{
    slider_ = GraphicCreateView<UISlider>(content);
    if (slider_ == nullptr) {
        printf("[SliderDemo] create slider failed\n");
        return;
    }
    slider_->SetPosition(pageMarginX, sliderY);
    slider_->SetWidth(sliderWidth);
    slider_->SetHeight(sliderHeight);
    slider_->SetRange(sliderRangeMax, 0);
    slider_->SetValue(sliderInitValue);
    slider_->SetKnobWidth(sliderKnobWidth);
    slider_->SetBackgroundStyle(STYLE_BACKGROUND_COLOR,
                                Color::ColorTo32(Color::GetColorFromRGB(0x55, 0x55, 0x55)));
    slider_->SetForegroundStyle(STYLE_BACKGROUND_COLOR,
                                Color::ColorTo32(Color::GetColorFromRGB(0xFF, 0x7A, 0x00)));
}

void SliderDemoAbilitySlice::BindSliderListener(UILabel* valueLabel)
{
    sliderListener_ = std::make_unique<SliderValueListener>(valueLabel);
    if (sliderListener_ == nullptr) {
        printf("[SliderDemo] create slider listener failed\n");
        slider_->SetSliderEventListener(nullptr);
        return;
    }
    slider_->SetSliderEventListener(sliderListener_.get());
}
} // namespace OHOS

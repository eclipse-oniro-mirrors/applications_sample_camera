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

#ifndef GRAPHIC_SLIDER_DEMO_ABILITY_SLICE_H
#define GRAPHIC_SLIDER_DEMO_ABILITY_SLICE_H

#include "component_demo_slice.h"
#include <memory>

namespace OHOS {
class SliderValueListener;
class UISlider;

class SliderDemoAbilitySlice : public ComponentDemoSlice {
public:
    SliderDemoAbilitySlice() : ComponentDemoSlice("Slider组件验证") {}
    ~SliderDemoAbilitySlice() override;

protected:
    void SetupContent(UIViewGroup* content) override;

private:
    UILabel* AddHintLabel(UIViewGroup* content);
    UILabel* AddValueLabel(UIViewGroup* content);
    void CreateSlider(UIViewGroup* content, int16_t sliderWidth);
    void BindSliderListener(UILabel* valueLabel);

    // 布局常量
    static constexpr int16_t pageMarginX = 80;
    static constexpr int16_t hintY = 50;
    static constexpr int16_t hintHeight = 40;
    static constexpr int16_t hintFontSize = 26;
    static constexpr int16_t valueY = 110;
    static constexpr int16_t valueHeight = 60;
    static constexpr int16_t valueFontSize = 40;
    static constexpr int16_t sliderY = 230;
    static constexpr int16_t sliderHeight = 60;
    static constexpr int16_t sliderKnobWidth = 20;
    static constexpr int16_t sliderRangeMax = 100;
    static constexpr int16_t sliderInitValue = 50;

    std::unique_ptr<SliderValueListener> sliderListener_;
    // slider 归属内容视图树，由基类析构统一释放；保存指针仅为析构时解除监听绑定
    UISlider* slider_ = nullptr;
};
} // namespace OHOS
#endif // GRAPHIC_SLIDER_DEMO_ABILITY_SLICE_H

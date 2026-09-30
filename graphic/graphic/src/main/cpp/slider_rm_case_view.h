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

#ifndef SLIDER_RM_CASE_VIEW_H
#define SLIDER_RM_CASE_VIEW_H

#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_slider.h"
#include "components/ui_view_group.h"
#include "graphic_config.h"
#include "rm_test_utils.h"

namespace OHOS {
#if GRAPHIC_ENABLE_SLIDER_FLAG

class SliderRmValueListener;

/**
 * @brief RM013/014/015 Slider 单个验收用例的配置。
 *
 * 字段与 PR1230 实际 API 一一对应：
 * - 刻度：EnableMarkings / SetMarkingsType(LINE|DOT) / SetMarkingsSize
 * - 刻度文本：EnableMarkText
 * - 吸附：EnableTicks（或设置 values）
 * - 自定义刻度值：SetValues
 * - 扩展点击：SetExpandClickArea；disabled：SetDisabled + SetDisabledToastMsg
 * - 值 Toast：EnableToast；渐变：SetBgGradientColors / SetOnTintGradientColors
 */
struct SliderRmCase {
    const char* id;
    const char* name;
    const char* expect;
    int32_t rangeMin;
    int32_t rangeMax;
    uint32_t step;
    int32_t initValue;
    uint8_t direction;
    bool enableMarkings;
    uint8_t markingsType;
    int16_t markingsSize;
    bool enableMarkText;
    bool enableTicks;
    const int32_t* values;
    uint16_t valuesCount;
    bool expandClickArea;
    bool disabled;
    const char* disabledToastMsg;
    bool enableToast;
    int8_t colorScheme;
    int8_t gradientScheme;
    uint8_t loopAction;
};

extern const SliderRmCase g_sliderRmCases[];
extern const uint32_t g_sliderRmCaseNum;

/**
 * @brief Slider RM 单个用例的视图构建与清理器。
 *
 * Build() 在 content 内部创建并返回用例容器；析构时先剥离监听器再删除容器子树。
 */
class SliderRmCaseRunner {
public:
    explicit SliderRmCaseRunner(const SliderRmCase* testCase);
    ~SliderRmCaseRunner();

    UIViewGroup* Build(UIViewGroup* content);

private:
    void ResetState();
    void ShowCase(const SliderRmCase& testCase);
    void AddClickListener(UIView* view, std::function<bool(UIView&, const ClickEvent&)> fn);

    struct SliderLayout;
    SliderLayout ComputeSliderLayout(const SliderRmCase& testCase, bool vertical);
    void ApplyMarkTextLayout(SliderLayout& layout, bool vertical, const SliderRmCase& testCase);
    void ApplyExtendClickLayout(SliderLayout& layout, const SliderRmCase& testCase);
    UISlider* CreateAndConfigSlider(const SliderRmCase& testCase, const SliderLayout& layout);
    void CreateValueAndListener(const SliderRmCase& testCase, const SliderLayout& layout, UISlider* slider);
    void CreateActionControls(const SliderRmCase& testCase, const SliderLayout& layout);
    void CreateLoopButton(const SliderRmCase& testCase, const SliderLayout& layout);
    void RunMarkTextLoop(UILabelButton& btn);
    void RunDirectionColorLoop(UILabelButton& btn);
    void CreateInputAndJump(const SliderRmCase& testCase, const SliderLayout& layout);
    void CreateInfoLabels(const SliderRmCase& testCase, const SliderLayout& layout);

    struct ListenerEntry {
        UIView* view;
        RmClickListener* listener;
    };
    static constexpr uint8_t MAX_LISTENERS = 8;

    const SliderRmCase* case_;
    UIViewGroup* container_;
    UISlider* slider_;
    UILabel* valueLabel_;
    SliderRmValueListener* valueListener_;
    ListenerEntry listeners_[MAX_LISTENERS];
    uint8_t listenerCount_;
};

#endif // GRAPHIC_ENABLE_SLIDER_FLAG
} // namespace OHOS
#endif // SLIDER_RM_CASE_VIEW_H

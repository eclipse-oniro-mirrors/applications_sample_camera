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

#ifndef GRAPHIC_BUTTON_DEMO_ABILITY_SLICE_H
#define GRAPHIC_BUTTON_DEMO_ABILITY_SLICE_H

#include "component_demo_slice.h"
#include "components/ui_label_button.h"
#include "event_listener.h"
#include <memory>

namespace OHOS {
class ButtonDemoAbilitySlice : public ComponentDemoSlice {
public:
    ButtonDemoAbilitySlice() : ComponentDemoSlice("Button组件验证") {}
    ~ButtonDemoAbilitySlice() override;

protected:
    void SetupContent(UIViewGroup* content) override;

private:
    UILabel* AddHintLabel(UIViewGroup* content);
    UILabel* AddCountLabel(UIViewGroup* content);
    void CreateClickListener(UILabel* countLabel);
    void AddDemoButton(UIViewGroup* content, const char* name, int16_t index,
                       int16_t buttonWidth, int16_t buttonStep);

    static constexpr int16_t buttonCount = 3;

    // 布局常量
    static constexpr int16_t pageMarginX = 40;
    static constexpr int16_t hintY = 40;
    static constexpr int16_t hintHeight = 40;
    static constexpr int16_t hintFontSize = 26;
    static constexpr int16_t countY = 100;
    static constexpr int16_t countHeight = 50;
    static constexpr int16_t countFontSize = 30;
    static constexpr int16_t buttonStartY = 200;
    static constexpr int16_t buttonHeight = 72;
    static constexpr int16_t buttonGap = 20;
    static constexpr int16_t buttonFontSize = 30;
    static constexpr int16_t buttonRadius = 12;
    static constexpr int16_t buttonBorderWidth = 2;

    std::unique_ptr<EventListener> buttonClickListener_;
    // 按钮归属内容视图树，由基类析构统一释放；保存指针仅为析构时解除监听绑定
    UILabelButton* demoButtons_[buttonCount] = {};
    int32_t clickCount_ = 0;
};
} // namespace OHOS
#endif // GRAPHIC_BUTTON_DEMO_ABILITY_SLICE_H

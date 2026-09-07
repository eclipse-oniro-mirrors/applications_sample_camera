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

#ifndef GRAPHIC_SWITCH_DEMO_ABILITY_SLICE_H
#define GRAPHIC_SWITCH_DEMO_ABILITY_SLICE_H

#include "component_demo_slice.h"
#include "event_listener.h"
#include <memory>

namespace OHOS {
class UIToggleButton;

class SwitchDemoAbilitySlice : public ComponentDemoSlice {
public:
    SwitchDemoAbilitySlice() : ComponentDemoSlice("Switch组件验证") {}
    ~SwitchDemoAbilitySlice() override;

protected:
    void SetupContent(UIViewGroup* content) override;

private:
    void AddSwitchRow(UIViewGroup* content, const char* rowName, int16_t rowY, int16_t index);
    void BindSwitchListener(UILabel* stateLabel, int16_t index);

    static constexpr int16_t rowCount = 2;

    // 布局常量
    static constexpr int16_t pageMarginX = 40;
    static constexpr int16_t listStartY = 60;
    static constexpr int16_t rowHeight = 96;
    static constexpr int16_t rowGap = 36;
    static constexpr int16_t rowPaddingX = 24;
    static constexpr int16_t rowRadius = 12;
    static constexpr int16_t toggleWidth = 46;
    static constexpr int16_t toggleStateGap = 16;
    static constexpr int16_t nameLabelWidth = 300;
    static constexpr int16_t stateLabelWidth = 160;
    static constexpr int16_t labelHeight = 40;
    // 行内元素垂直居中偏移
    static constexpr int16_t labelOffsetY = (rowHeight - labelHeight) / 2;
    static constexpr int16_t toggleOffsetY = (rowHeight - toggleWidth) / 2;
    static constexpr int16_t nameFontSize = 28;
    static constexpr int16_t stateFontSize = 26;

    std::unique_ptr<EventListener> switchListeners_[rowCount] = {};
    // 开关归属内容视图树，由基类析构统一释放；保存指针仅为析构时解除监听绑定
    UIToggleButton* toggleButtons_[rowCount] = { nullptr, nullptr };
};
} // namespace OHOS
#endif // GRAPHIC_SWITCH_DEMO_ABILITY_SLICE_H

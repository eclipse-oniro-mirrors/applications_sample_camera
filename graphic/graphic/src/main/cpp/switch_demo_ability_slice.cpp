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

#include "switch_demo_ability_slice.h"
#include <cstdio>
#include "common/screen.h"
#include "graphic_utils.h"
#include "components/ui_label.h"
#include "components/ui_toggle_button.h"

namespace OHOS {
namespace {
const char* GetStateText(bool state)
{
    if (state) {
        return "已开启";
    }
    return "已关闭";
}
}

REGISTER_AS(SwitchDemoAbilitySlice)

SwitchDemoAbilitySlice::~SwitchDemoAbilitySlice()
{
    for (int16_t i = 0; i < rowCount; i++) {
        // 先解除开关对 listener 的引用，再释放 listener，避免组件持有悬空指针
        if (toggleButtons_[i] != nullptr) {
            toggleButtons_[i]->SetOnClickListener(nullptr);
        }
        switchListeners_[i] = nullptr;
    }
}

void SwitchDemoAbilitySlice::SetupContent(UIViewGroup* content)
{
    static const char* rowNames[rowCount] = { "开关选项一", "开关选项二" };

    for (int16_t i = 0; i < rowCount; i++) {
        int16_t rowY = listStartY + i * (rowHeight + rowGap);
        AddSwitchRow(content, rowNames[i], rowY, i);
    }
}

void SwitchDemoAbilitySlice::AddSwitchRow(UIViewGroup* content, const char* rowName, int16_t rowY, int16_t index)
{
    int16_t screenWidth = Screen::GetInstance().GetWidth();
    int16_t rowWidth = screenWidth - pageMarginX - pageMarginX;
    // 开关贴行右边缘，状态文字在开关左侧
    int16_t toggleX = rowWidth - rowPaddingX - toggleWidth;
    int16_t stateX = toggleX - toggleStateGap - stateLabelWidth;

    UIViewGroup* rowView = GraphicCreateView<UIViewGroup>(content);
    if (rowView == nullptr) {
        printf("[SwitchDemo] create row view failed\n");
        return;
    }
    rowView->SetPosition(pageMarginX, rowY, rowWidth, rowHeight);
    rowView->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x33, 0x33, 0x33)));
    rowView->SetStyle(STYLE_BORDER_RADIUS, rowRadius);

    UILabel* nameLabel = GraphicCreateView<UILabel>(rowView);
    if (nameLabel == nullptr) {
        printf("[SwitchDemo] create name label failed\n");
        return;
    }
    nameLabel->SetPosition(rowPaddingX, labelOffsetY, nameLabelWidth, labelHeight);
    nameLabel->SetText(rowName);
    nameLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, nameFontSize);
    nameLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));

    UILabel* stateLabel = GraphicCreateView<UILabel>(rowView);
    if (stateLabel == nullptr) {
        printf("[SwitchDemo] create state label failed\n");
        return;
    }
    stateLabel->SetPosition(stateX, labelOffsetY, stateLabelWidth, labelHeight);
    stateLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, stateFontSize);
    stateLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xAA, 0xAA, 0xAA)));
    stateLabel->SetAlign(TEXT_ALIGNMENT_RIGHT, TEXT_ALIGNMENT_CENTER);
    stateLabel->SetText(GetStateText(index == 0));

    toggleButtons_[index] = GraphicCreateView<UIToggleButton>(rowView);
    if (toggleButtons_[index] == nullptr) {
        printf("[SwitchDemo] create toggle button failed\n");
        return;
    }
    toggleButtons_[index]->SetPosition(toggleX, toggleOffsetY);
    toggleButtons_[index]->SetState(index == 0);
    BindSwitchListener(stateLabel, index);
}

void SwitchDemoAbilitySlice::BindSwitchListener(UILabel* stateLabel, int16_t index)
{
    auto onToggle = [stateLabel](UIView& view, const Event& event) -> bool {
        if ((stateLabel == nullptr) || (view.GetViewType() != UI_TOGGLE_BUTTON)) {
            return false;
        }
        bool state = static_cast<UIToggleButton&>(view).GetState();
        stateLabel->SetText(GetStateText(state));
        return true;
    };
    switchListeners_[index] = std::make_unique<EventListener>(onToggle, nullptr);
    if (switchListeners_[index] == nullptr) {
        printf("[SwitchDemo] create switch listener failed\n");
        toggleButtons_[index]->SetOnClickListener(nullptr);
        return;
    }
    toggleButtons_[index]->SetOnClickListener(switchListeners_[index].get());
}
} // namespace OHOS

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

#ifndef GRAPHIC_SCROLLER_DEMO_ABILITY_SLICE_H
#define GRAPHIC_SCROLLER_DEMO_ABILITY_SLICE_H

#include "component_demo_slice.h"

namespace OHOS {
class ScrollerDemoAbilitySlice : public ComponentDemoSlice {
public:
    ScrollerDemoAbilitySlice() : ComponentDemoSlice("Scroller组件验证") {}
    ~ScrollerDemoAbilitySlice() override = default;

protected:
    void SetupContent(UIViewGroup* content) override;

private:
    // 布局常量
    static constexpr int16_t pageMarginX = 40;
    static constexpr int16_t scrollMarginY = 40;
    static constexpr int16_t itemCount = 10;
    static constexpr int16_t itemHeight = 72;
    static constexpr int16_t itemGap = 12;
    static constexpr int16_t itemPaddingX = 24;
    static constexpr int16_t itemLabelOffsetY = 16;
    static constexpr int16_t itemLabelHeight = 40;
    static constexpr int16_t itemFontSize = 28;
    static constexpr int16_t itemRadius = 12;
};
} // namespace OHOS
#endif // GRAPHIC_SCROLLER_DEMO_ABILITY_SLICE_H

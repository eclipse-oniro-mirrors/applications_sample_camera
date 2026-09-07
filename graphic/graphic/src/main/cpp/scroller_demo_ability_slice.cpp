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

#include "scroller_demo_ability_slice.h"
#include <cstdio>
#include "common/screen.h"
#include "graphic_utils.h"
#include "securec.h"
#include "components/ui_label.h"
#include "components/ui_scroll_view.h"

namespace OHOS {
REGISTER_AS(ScrollerDemoAbilitySlice)

void ScrollerDemoAbilitySlice::SetupContent(UIViewGroup* content)
{
    int16_t screenWidth = Screen::GetInstance().GetWidth();
    int16_t screenHeight = Screen::GetInstance().GetHeight();
    int16_t contentHeight = screenHeight - headHeight;
    int16_t scrollWidth = screenWidth - pageMarginX - pageMarginX;

    UIScrollView* scrollView = GraphicCreateView<UIScrollView>(content);
    if (scrollView == nullptr) {
        printf("[ScrollerDemo] create scroll view failed\n");
        return;
    }
    scrollView->SetPosition(pageMarginX, scrollMarginY, scrollWidth,
                            contentHeight - scrollMarginY - scrollMarginY);
    scrollView->SetXScrollBarVisible(false);
    scrollView->SetYScrollBarVisible(true);

    // 相邻条目底色深浅交替，便于区分
    bool darkStripe = true;
    for (int16_t i = 0; i < itemCount; i++) {
        UIViewGroup* itemView = GraphicCreateView<UIViewGroup>(scrollView);
        if (itemView == nullptr) {
            printf("[ScrollerDemo] create item view failed\n");
            return;
        }
        itemView->SetPosition(0, i * (itemHeight + itemGap), scrollWidth, itemHeight);
        if (darkStripe) {
            itemView->SetStyle(STYLE_BACKGROUND_COLOR,
                               Color::ColorTo32(Color::GetColorFromRGB(0x2E, 0x2E, 0x2E)));
        } else {
            itemView->SetStyle(STYLE_BACKGROUND_COLOR,
                               Color::ColorTo32(Color::GetColorFromRGB(0x38, 0x38, 0x38)));
        }
        darkStripe = !darkStripe;
        itemView->SetStyle(STYLE_BORDER_RADIUS, itemRadius);

        UILabel* itemLabel = GraphicCreateView<UILabel>(itemView);
        if (itemLabel == nullptr) {
            printf("[ScrollerDemo] create item label failed\n");
            return;
        }
        itemLabel->SetPosition(itemPaddingX, itemLabelOffsetY,
                               scrollWidth - itemPaddingX - itemPaddingX, itemLabelHeight);
        char text[32] = {0};
        int ret = snprintf_s(text, sizeof(text), sizeof(text) - 1, "列表项 %d", i + 1);
        if (ret < 0) {
            printf("[ScrollerDemo] format item text failed\n");
            return;
        }
        itemLabel->SetText(text);
        itemLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, itemFontSize);
        itemLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    }
}
} // namespace OHOS

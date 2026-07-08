/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

#ifndef OHOS_SETTING_UTILS_H
#define OHOS_SETTING_UTILS_H

#include "components/ui_view_group.h"
#include "graphic_config.h"
#include <common/screen.h>

namespace OHOS {
/* Screen-aware scaling helpers — designed for 1920x1080 reference.
 * Every layout coordinate below is expressed against the 1920x1080 design and
 * scaled at runtime via HScale/VScale, so the UI keeps the same proportions
 * at every resolution (e.g. 1024x600). Mirrors the camera app approach. */
static inline int16_t GetScrWidth()  { return Screen::GetInstance().GetWidth(); }
static inline int16_t GetScrHeight() { return Screen::GetInstance().GetHeight(); }
static inline int16_t HScale(int16_t ref) { return static_cast<int16_t>(static_cast<int32_t>(ref) * GetScrWidth()  / 1920); }
static inline int16_t VScale(int16_t ref) { return static_cast<int16_t>(static_cast<int32_t>(ref) * GetScrHeight() / 1080); }
static inline uint16_t FontScale(uint16_t ref) {
    int32_t s = static_cast<int32_t>(ref) * GetScrHeight() / 1080;
    return static_cast<uint16_t>(s < 14 ? 14 : s);
}

#define DE_IMAGE_BACK "/storage/app/run/com.huawei.setting/setting/assets/setting/resources/base/media/back.png"
#define DE_IMAGE_FORWORD \
    "/storage/app/run/com.huawei.setting/setting/assets/setting/resources/base/media/forward.png"
#define DE_IMAGE_ENTER "/storage/app/run/com.huawei.setting/setting/assets/setting/resources/base/media/enter.png"
#define DE_IMAGE_APP "/storage/app/run/com.huawei.setting/setting/assets/setting/resources/base/media/app.png"
#define DE_FONT_OTF "SourceHanSansSC-Regular.otf"

/* Root view — runtime screen dimensions */
#define DE_ROOT_X 0
#define DE_ROOT_Y 0
#define DE_ROOT_WIDTH  GetScrWidth()
#define DE_ROOT_HEIGHT GetScrHeight()
#define DE_ROOT_BACKGROUND_COLOR Color::ColorTo32(Color::Gray())

/* Scroll area — scaled from 1920x1080 reference */
#define DE_SCROLL_X     HScale(36)
#define DE_SCROLL_Y     VScale(72)
#define DE_SCROLL_WIDTH  HScale(1840)
#define DE_SCROLL_HEIGHT VScale(1008)
#define DE_SCROLL_COLOR  Color::ColorTo32(Color::Gray())

/* Head bar (back button row) */
#define DE_HEAD_X      0
#define DE_HEAD_Y      0
#define DE_HEAD_WIDTH  HScale(300)
#define DE_HEAD_HEIGHT VScale(72)

#define DE_HEAD_IMAGE_X      HScale(39)
#define DE_HEAD_IMAGE_Y      VScale(21)
#define DE_HEAD_IMAGE_WIDTH  HScale(36)
#define DE_HEAD_IMAGE_HEIGHT VScale(36)

#define DE_HEAD_TEXT_X      HScale(100)
#define DE_HEAD_TEXT_Y      VScale(15)
#define DE_HEAD_TEXT_WIDTH  HScale(180)
#define DE_HEAD_TEXT_HEIGHT VScale(60)
#define DE_HEAD_TEXT_SIZE   FontScale(32)
#define DE_HEAD_TEXT_COLOR  Color::ColorTo32(Color::White())

/* Setting row button */
#define DE_BUTTON_WIDTH  HScale(1840)
#define DE_BUTTON_HEIGHT VScale(89)
#define DE_BUTTON_BACKGROUND_COLOR Color::ColorTo32(Color::GetColorFromRGB(0x33, 0x33, 0x33))
#define DE_BUTTON_RADIUS 16

/* Title text (left-aligned label inside a row button) */
#define DE_TITLE_TEXT_X      HScale(18)
#define DE_TITLE_TEXT_Y      VScale(28)
#define DE_TITLE_TEXT_WIDTH  HScale(400)
#define DE_TITLE_TEXT_HEIGHT VScale(50)
#define DE_TITLE_TEXT_SIZE   FontScale(26)
#define DE_TITLE_TEXT_COLOR  Color::ColorTo32(Color::White())

/* Subtitle text (secondary line inside a row button) */
#define DE_SUBTITLE_TEXT_WIDTH  HScale(600)
#define DE_SUBTITLE_TEXT_HEIGHT VScale(40)
#define DE_SUBTITLE_TEXT_COLOR  Color::ColorTo32(Color::GetColorFromRGB(0x9F, 0x9F, 0x9F))
#define DE_SUBTITLE_TEXT_SIZE   FontScale(24)

/* Forward arrow icon (right side of a row button) */
#define DE_FORWARD_IMG_X      HScale(1805)
#define DE_FORWARD_IMG_Y      VScale(30)
#define DE_FORWARD_IMG_WIDTH  HScale(24)
#define DE_FORWARD_IMG_HEIGHT VScale(24)

/* Toggle switch (right side of a row button) */
#define DE_TOGGLE_BUTTON_X HScale(1776)
#define DE_TOGGLE_BUTTON_Y VScale(14)
#define DE_TOGGLE_BUTTON_WIDTH  HScale(60)
#define DE_TOGGLE_BUTTON_HEIGHT VScale(60)

/* Item spacing and shared constants */
#define DE_ITEM_INTERVAL     VScale(95)
#define DE_CONTENT_FONT_SIZE FontScale(28)
#define DE_OPACITY_ALL 255

void DeleteChildren(UIView *view);
} // namespace OHOS
#endif

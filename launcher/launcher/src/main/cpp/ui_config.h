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

#ifndef OHOS_UI_CONFIG_H
#define OHOS_UI_CONFIG_H

#include <cstdint>
#include <securec.h>
#include <common/screen.h>

namespace OHOS {
/* Screen-aware scaling helpers — designed for 1920x1080 reference */
static inline int16_t GetScrWidth() { return Screen::GetInstance().GetWidth(); }
static inline int16_t GetScrHeight() { return Screen::GetInstance().GetHeight(); }
static inline int16_t HScale(int16_t ref) { return static_cast<int16_t>(static_cast<int32_t>(ref) * Screen::GetInstance().GetWidth() / 1920); }
static inline int16_t VScale(int16_t ref) { return static_cast<int16_t>(static_cast<int32_t>(ref) * Screen::GetInstance().GetHeight() / 1080); }
static inline int16_t UScale(int16_t ref) {
    float rw = static_cast<float>(Screen::GetInstance().GetWidth()) / 1920.0f;
    float rh = static_cast<float>(Screen::GetInstance().GetHeight()) / 1080.0f;
    return static_cast<int16_t>(ref * ((rw < rh) ? rw : rh));
}
static inline uint16_t FontScale(uint16_t ref) {
    int32_t s = static_cast<int32_t>(ref) * Screen::GetInstance().GetHeight() / 1080;
    return static_cast<uint16_t>(s < 14 ? 14 : s);
}
static inline bool IsScrRes(int16_t w, int16_t h) {
    return Screen::GetInstance().GetWidth() == w && Screen::GetInstance().GetHeight() == h;
}

constexpr int16_t LABLE_TITLE_HEIGHT = 30; // tail lable height
constexpr int16_t LABLE_TAIL_HEIGHT = 30;
constexpr int16_t APP_WIDTH_COUNT = 7;       // blank + app + blank + app + blank
constexpr int16_t APP_HEIGHT_COUNT = 4;      // app + lable + app + lable
constexpr int16_t MAX_VIEWGROUP = 3;         // swipe window count
constexpr int16_t APP_ROW_COUNT = 2;         // a swipe view app count in row
constexpr int16_t APP_COL_COUNT = 3;         // a sswipe view app count in col
constexpr int16_t LAUNCHER_FOND_ID = 16;     // other view fond id
constexpr int16_t APP_FOND_ID = 16;          // app name fond id
constexpr int16_t BIGLAUNCHER_FOND_ID = 48;  // time big fond id
constexpr int16_t TOTAL_OPACITY = 0;         // transparent
constexpr int16_t HALF_OPACITY = 50;         // diaphanous
constexpr int16_t UN_OPACITY = 255;          // opaque
constexpr int16_t BUTTON_RADIUS = 20;        // app icon radius
constexpr int16_t LABLE_RADIUS = 0;          // lable icon radius
constexpr int16_t TITLE_LABLE_OPACITY = 255; // translucent
constexpr int16_t GROUP_VIEW_RADIUS = 20;    // view radius
/* App icon size — scaled from the 1920x1080 reference */
static inline int16_t APP_ICON_SIZE() { return HScale(88); }

#ifndef TMP_BUF_SIZE
#define TMP_BUF_SIZE 128
#endif

#define LAUNCHER_BUNDLE_NAME "com.huawei.launcher"
#define SCREENSAVER_BUNDLE_NAME "com.huawei.screensaver"
/* Background image — always use the high-res 1920x1080 version, COVER mode scales it down */
#define TABLE_BACKGROUND \
    "/storage/app/run/com.huawei.launcher/launcher/assets/launcher/resources/base/media/background_1920x1080.png"
#define RES_WEATHER "/storage/app/run/com.huawei.launcher/launcher/assets/launcher/resources/base/media/weather.png"
#define FOND_PATH "SourceHanSansSC-Regular.otf"

#ifndef LAUNCHER_SUCCESS
#define LAUNCHER_SUCCESS 0
#endif

#ifndef LAUNCHER_PARAMERROR
#define LAUNCHER_PARAMERROR (-1)
#endif

#ifndef WEEK_DAY_MAX
#define WEEK_DAY_MAX 7
#endif
} // namespace OHOS
#endif

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

#ifndef OHOS_GALLERY_CONFIG_H
#define OHOS_GALLERY_CONFIG_H

#include "components/ui_view_group.h"
#include "graphic_config.h"
#include <common/screen.h>

#define GALLERY_BACKGROUND_COLOR Color::ColorTo32(Color::GetColorFromRGB(0xdd, 0xdd, 0xdd))

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

/** icon resource file path */
static const char* const BACK_ICON_PATH = "/gallery/assets/gallery/resources/drawable/ic_back.png";
static const char* const VIDEO_TAG_ICON_PATH = "/gallery/assets/gallery/resources/drawable/ic_gallery_video_tag.png";
static const char* const VIDEO_PALY_PATH = "/gallery/assets/gallery/resources/drawable/ic_gallery_play.png";
static const char* const VIDEO_PAUSE_PATH = "/gallery/assets/gallery/resources/drawable/ic_gallery_pause.png";

static constexpr int16_t MAX_PICTURE_COUNT = 256;
static constexpr uint16_t MAX_PATH_LENGTH = 512;

/** thumb, photo, and video folder path */
static const char* const THUMBNAIL_DIRECTORY = "/userdata/thumb";
static const char* const PHOTO_DIRECTORY = "/userdata/photo";
static const char* const VIDEO_SOURCE_DIRECTORY = "/userdata/photo";

/** general page configuration — runtime screen aware */
static inline int ROOT_VIEW_WIDTH() { return GetScrWidth(); }
static inline int ROOT_VIEW_HEIGHT() { return GetScrHeight(); }
static constexpr int ROOT_VIEW_POSITION_X = 0;
static constexpr int ROOT_VIEW_POSITION_Y = 0;
static constexpr uint16_t ROOT_VIEW_OPACITY = 255;

static const char* const FONT_NAME = "SourceHanSansSC-Regular.otf";

/** back icon 36 x 36 — scaled from 36 at 1920x1080 */
static inline int16_t BACK_ICON_POSITION_X() { return HScale(38); }
static inline int16_t BACK_ICON_POSITION_Y() { return VScale(17); }
static inline int16_t BACK_ICON_WIDTH() { return HScale(36); }
static inline int16_t BACK_ICON_HEIGHT() { return VScale(36); }

/** THUMBNAIL — scaled proportionally from 1920x1080 */
static inline int16_t THUMBNAIL_RESOLUTION_X() { return HScale(236); }
static inline int16_t THUMBNAIL_RESOLUTION_Y() { return VScale(236); }
static constexpr int16_t THUMBNAIL_SPACE = 4;
static constexpr int16_t THUMBNAIL_COLUMN = 3;

static inline int16_t VIDEO_TAG_POSITION_X() { return HScale(10); }
static inline int16_t VIDEO_TAG_POSITION_Y() { return THUMBNAIL_RESOLUTION_Y() - VScale(37); }
static inline int16_t VIDEO_TAG_WIDTH() { return HScale(27); }
static inline int16_t VIDEO_TAG_HEIGHT() { return VScale(27); }

/** title */
static inline int16_t LABEL_POSITION_X() { return BACK_ICON_POSITION_X() + HScale(60); }
static constexpr int16_t LABEL_POSITION_Y = 0;
static inline int16_t LABEL_WIDTH() { return HScale(200); }
static inline int16_t LABEL_HEIGHT() { return VScale(70); }
static inline uint16_t GALLERY_FONT_SIZE() { return FontScale(25); }
static inline uint16_t GALLERY_DELETE_FONT_SIZE() { return FontScale(22); }
static inline int16_t DELETE_LABEL_WIDTH() { return HScale(150); }

/** prefix and File Type */
static const char* const PHOTO_PREFIX = "photo";
static const char* const AVAILABEL_SOURCE_TYPE = ".mp4";
static const char* const AVAILABEL_SOURCE_TYPE_MP4 = ".MP4";

/** playback status bar */
static inline uint16_t STATUS_BAR_GROUP_HEIGHT() { return VScale(96); }
static inline uint16_t TOGGLE_BUTTON_OFFSET_X() { return HScale(36); }
static inline uint16_t TOGGLE_BUTTON_OFFSET_Y() { return VScale(18); }
static inline uint16_t TOGGLE_BUTTON_WIDTH() { return HScale(60); }
static inline uint16_t TOGGLE_BUTTON_HEIGHT() { return VScale(60); }

static inline uint16_t CURRENT_TIME_LABEL_X() {
    return TOGGLE_BUTTON_OFFSET_X() + TOGGLE_BUTTON_WIDTH() + TOGGLE_BUTTON_OFFSET_Y();
}
static constexpr uint16_t CURRENT_TIME_LABEL_Y = 0;
static inline uint16_t CURRENT_TIME_LABEL_WIDTH() { return HScale(60); }
static inline uint16_t CURRENT_TIME_LABEL_HEIGHT() { return STATUS_BAR_GROUP_HEIGHT(); }

static inline uint16_t TOTAL_TIME_LABEL_WIDTH() { return HScale(90); }
static inline uint16_t TOTAL_TIME_LABEL_HEIGHT() { return STATUS_BAR_GROUP_HEIGHT(); }
static inline uint16_t TOTAL_TIME_LABEL_X() { return ROOT_VIEW_WIDTH() - TOTAL_TIME_LABEL_WIDTH(); }
static constexpr uint16_t TOTAL_TIME_LABEL_Y = 0;

static inline uint16_t SLIDER_X() { return CURRENT_TIME_LABEL_X() + CURRENT_TIME_LABEL_WIDTH(); }
static inline uint16_t SLIDER_Y() { return VScale(2); }
static inline uint16_t SLIDER_HEIGHT() { return VScale(3); }
static inline uint16_t SLIDER_WIDTH() {
    return ROOT_VIEW_WIDTH() - SLIDER_X() - TOTAL_TIME_LABEL_WIDTH() - HScale(20);
}
static inline uint16_t KNOB_WIDTH() { return HScale(25); }

static inline uint16_t PLAYER_FONT_SIZE() { return FontScale(18); }

} // namespace OHOS
#endif // OHOS_GALLERY_CONFIG_H

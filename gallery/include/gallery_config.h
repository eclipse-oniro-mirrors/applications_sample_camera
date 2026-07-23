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
/* Screen-aware scaling helpers — designed for 1920x1080 reference.
 * Default fallback resolution is 960x480 when Screen reports 0. */
constexpr int16_t DESIGN_WIDTH = 1920;
constexpr int16_t DESIGN_HEIGHT = 1080;
constexpr int16_t DEFAULT_SCR_WIDTH = 960;
constexpr int16_t DEFAULT_SCR_HEIGHT = 480;
constexpr uint16_t MIN_FONT_SIZE = 14;

constexpr int16_t BACK_ICON_POS_X_REF = 38;
constexpr int16_t BACK_ICON_POS_Y_REF = 17;
constexpr int16_t BACK_ICON_SIZE_REF = 36;
constexpr int16_t THUMBNAIL_SIZE_REF = 236;
constexpr int16_t VIDEO_TAG_POS_X_REF = 10;
constexpr int16_t VIDEO_TAG_POS_Y_OFFSET_REF = 37;
constexpr int16_t VIDEO_TAG_SIZE_REF = 27;
constexpr int16_t LABEL_OFFSET_X_REF = 60;
constexpr int16_t LABEL_WIDTH_REF = 200;
constexpr int16_t LABEL_HEIGHT_REF = 70;
constexpr uint16_t GALLERY_FONT_SIZE_REF = 25;
constexpr uint16_t GALLERY_DELETE_FONT_SIZE_REF = 22;
constexpr int16_t DELETE_LABEL_WIDTH_REF = 150;
constexpr uint16_t STATUS_BAR_GROUP_HEIGHT_REF = 96;
constexpr uint16_t TOGGLE_BUTTON_OFFSET_X_REF = 36;
constexpr uint16_t TOGGLE_BUTTON_OFFSET_Y_REF = 18;
constexpr uint16_t TOGGLE_BUTTON_SIZE_REF = 60;
constexpr uint16_t CURRENT_TIME_LABEL_WIDTH_REF = 60;
constexpr uint16_t TOTAL_TIME_LABEL_WIDTH_REF = 90;
constexpr uint16_t SLIDER_Y_REF = 2;
constexpr uint16_t SLIDER_HEIGHT_REF = 3;
constexpr uint16_t SLIDER_MARGIN_RIGHT_REF = 20;
constexpr uint16_t KNOB_WIDTH_REF = 25;
constexpr uint16_t PLAYER_FONT_SIZE_REF = 18;

static inline int16_t GetScrWidth()
{
    uint16_t w = Screen::GetInstance().GetWidth();
    return (w == 0) ? DEFAULT_SCR_WIDTH : static_cast<int16_t>(w);
}
static inline int16_t GetScrHeight()
{
    uint16_t h = Screen::GetInstance().GetHeight();
    return (h == 0) ? DEFAULT_SCR_HEIGHT : static_cast<int16_t>(h);
}
static inline int16_t HScale(int16_t ref)
{
    return static_cast<int16_t>(
        static_cast<int32_t>(ref) * Screen::GetInstance().GetWidth() / DESIGN_WIDTH);
}
static inline int16_t VScale(int16_t ref)
{
    return static_cast<int16_t>(
        static_cast<int32_t>(ref) * Screen::GetInstance().GetHeight() / DESIGN_HEIGHT);
}
static inline int16_t UScale(int16_t ref)
{
    float rw = static_cast<float>(Screen::GetInstance().GetWidth()) /
        static_cast<float>(DESIGN_WIDTH);
    float rh = static_cast<float>(Screen::GetInstance().GetHeight()) /
        static_cast<float>(DESIGN_HEIGHT);
    return static_cast<int16_t>(ref * ((rw < rh) ? rw : rh));
}
static inline uint16_t FontScale(uint16_t ref)
{
    int32_t s = static_cast<int32_t>(ref) * Screen::GetInstance().GetHeight() / DESIGN_HEIGHT;
    return static_cast<uint16_t>(s < MIN_FONT_SIZE ? MIN_FONT_SIZE : s);
}
static inline bool IsScrRes(int16_t w, int16_t h)
{
    return Screen::GetInstance().GetWidth() == w && Screen::GetInstance().GetHeight() == h;
}

/** icon resource file path */
static const char* const BACK_ICON_PATH = "/gallery/assets/gallery/resources/drawable/ic_back.png";
static const char* const VIDEO_TAG_ICON_PATH =
    "/gallery/assets/gallery/resources/drawable/ic_gallery_video_tag.png";
static const char* const VIDEO_PALY_PATH = "/gallery/assets/gallery/resources/drawable/ic_gallery_play.png";
static const char* const VIDEO_PAUSE_PATH = "/gallery/assets/gallery/resources/drawable/ic_gallery_pause.png";

static constexpr int16_t MAX_PICTURE_COUNT = 256;
static constexpr uint16_t MAX_PATH_LENGTH = 512;

/** thumb, photo, and video folder path */
static const char* const THUMBNAIL_DIRECTORY = "/userdata/thumb";
static const char* const PHOTO_DIRECTORY = "/userdata/photo";
static const char* const VIDEO_SOURCE_DIRECTORY = "/userdata/photo";

/** general page configuration — runtime screen aware */
static inline int ROOT_VIEW_WIDTH()
{
    return GetScrWidth();
}
static inline int ROOT_VIEW_HEIGHT()
{
    return GetScrHeight();
}
static constexpr int ROOT_VIEW_POSITION_X = 0;
static constexpr int ROOT_VIEW_POSITION_Y = 0;
static constexpr uint16_t ROOT_VIEW_OPACITY = 255;

static const char* const FONT_NAME = "SourceHanSansSC-Regular.otf";

/** back icon 36 x 36 — scaled from 36 at 1920x1080 */
static inline int16_t BACK_ICON_POSITION_X()
{
    return HScale(BACK_ICON_POS_X_REF);
}
static inline int16_t BACK_ICON_POSITION_Y()
{
    return VScale(BACK_ICON_POS_Y_REF);
}
static inline int16_t BACK_ICON_WIDTH()
{
    return HScale(BACK_ICON_SIZE_REF);
}
static inline int16_t BACK_ICON_HEIGHT()
{
    return VScale(BACK_ICON_SIZE_REF);
}

/** THUMBNAIL — scaled proportionally from 1920x1080 */
static inline int16_t THUMBNAIL_RESOLUTION_X()
{
    return HScale(THUMBNAIL_SIZE_REF);
}
static inline int16_t THUMBNAIL_RESOLUTION_Y()
{
    return VScale(THUMBNAIL_SIZE_REF);
}
static constexpr int16_t THUMBNAIL_SPACE = 4;
static constexpr int16_t THUMBNAIL_COLUMN = 3;

static inline int16_t VIDEO_TAG_POSITION_X()
{
    return HScale(VIDEO_TAG_POS_X_REF);
}
static inline int16_t VIDEO_TAG_POSITION_Y()
{
    return THUMBNAIL_RESOLUTION_Y() - VScale(VIDEO_TAG_POS_Y_OFFSET_REF);
}
static inline int16_t VIDEO_TAG_WIDTH()
{
    return HScale(VIDEO_TAG_SIZE_REF);
}
static inline int16_t VIDEO_TAG_HEIGHT()
{
    return VScale(VIDEO_TAG_SIZE_REF);
}

/** title */
static inline int16_t LABEL_POSITION_X()
{
    return BACK_ICON_POSITION_X() + HScale(LABEL_OFFSET_X_REF);
}
static constexpr int16_t LABEL_POSITION_Y = 0;
static inline int16_t LABEL_WIDTH()
{
    return HScale(LABEL_WIDTH_REF);
}
static inline int16_t LABEL_HEIGHT()
{
    return VScale(LABEL_HEIGHT_REF);
}
static inline uint16_t GALLERY_FONT_SIZE()
{
    return FontScale(GALLERY_FONT_SIZE_REF);
}
static inline uint16_t GALLERY_DELETE_FONT_SIZE()
{
    return FontScale(GALLERY_DELETE_FONT_SIZE_REF);
}
static inline int16_t DELETE_LABEL_WIDTH()
{
    return HScale(DELETE_LABEL_WIDTH_REF);
}

/** prefix and File Type */
static const char* const PHOTO_PREFIX = "photo";
static const char* const AVAILABEL_SOURCE_TYPE = ".mp4";
static const char* const AVAILABEL_SOURCE_TYPE_MP4 = ".MP4";

/** playback status bar */
static inline uint16_t STATUS_BAR_GROUP_HEIGHT()
{
    return VScale(STATUS_BAR_GROUP_HEIGHT_REF);
}
static inline uint16_t TOGGLE_BUTTON_OFFSET_X()
{
    return HScale(TOGGLE_BUTTON_OFFSET_X_REF);
}
static inline uint16_t TOGGLE_BUTTON_OFFSET_Y()
{
    return VScale(TOGGLE_BUTTON_OFFSET_Y_REF);
}
static inline uint16_t TOGGLE_BUTTON_WIDTH()
{
    return HScale(TOGGLE_BUTTON_SIZE_REF);
}
static inline uint16_t TOGGLE_BUTTON_HEIGHT()
{
    return VScale(TOGGLE_BUTTON_SIZE_REF);
}

static inline uint16_t CURRENT_TIME_LABEL_X()
{
    return TOGGLE_BUTTON_OFFSET_X() + TOGGLE_BUTTON_WIDTH() + TOGGLE_BUTTON_OFFSET_Y();
}
static constexpr uint16_t CURRENT_TIME_LABEL_Y = 0;
static inline uint16_t CURRENT_TIME_LABEL_WIDTH()
{
    return HScale(CURRENT_TIME_LABEL_WIDTH_REF);
}
static inline uint16_t CURRENT_TIME_LABEL_HEIGHT()
{
    return STATUS_BAR_GROUP_HEIGHT();
}

static inline uint16_t TOTAL_TIME_LABEL_WIDTH()
{
    return HScale(TOTAL_TIME_LABEL_WIDTH_REF);
}
static inline uint16_t TOTAL_TIME_LABEL_HEIGHT()
{
    return STATUS_BAR_GROUP_HEIGHT();
}
static inline uint16_t TOTAL_TIME_LABEL_X()
{
    return ROOT_VIEW_WIDTH() - TOTAL_TIME_LABEL_WIDTH();
}
static constexpr uint16_t TOTAL_TIME_LABEL_Y = 0;

static inline uint16_t SLIDER_X()
{
    return CURRENT_TIME_LABEL_X() + CURRENT_TIME_LABEL_WIDTH();
}
static inline uint16_t SLIDER_Y()
{
    return VScale(SLIDER_Y_REF);
}
static inline uint16_t SLIDER_HEIGHT()
{
    return VScale(SLIDER_HEIGHT_REF);
}
static inline uint16_t SLIDER_WIDTH()
{
    return ROOT_VIEW_WIDTH() - SLIDER_X() - TOTAL_TIME_LABEL_WIDTH() -
        HScale(SLIDER_MARGIN_RIGHT_REF);
}
static inline uint16_t KNOB_WIDTH()
{
    return HScale(KNOB_WIDTH_REF);
}

static inline uint16_t PLAYER_FONT_SIZE()
{
    return FontScale(PLAYER_FONT_SIZE_REF);
}

} // namespace OHOS
#endif // OHOS_GALLERY_CONFIG_H

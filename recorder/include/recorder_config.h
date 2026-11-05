/*
 * Copyright (c) 2026 RKH Corp.
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

#ifndef OHOS_RECORDER_CONFIG_H
#define OHOS_RECORDER_CONFIG_H

#include "components/ui_view_group.h"
#include "graphic_config.h"
#include <common/screen.h>

namespace OHOS {
/* Screen-aware scaling helpers — designed for 1920x1080 reference.
 * Default fallback resolution is 960x480 when Screen reports 0. */
constexpr int16_t DESIGN_WIDTH = 1920;
constexpr int16_t DESIGN_HEIGHT = 1080;
constexpr int16_t DEFAULT_SCR_WIDTH = 960;
constexpr int16_t DEFAULT_SCR_HEIGHT = 480;
constexpr uint16_t MIN_FONT_SIZE = 14;
constexpr int16_t HALF_DIVISOR = 2;
constexpr int16_t DOUBLE_COUNT = 2;

constexpr int16_t TITLE_BAR_HEIGHT_REF = 70;
constexpr int16_t BACK_ICON_SIZE_REF = 36;
constexpr int16_t BACK_ICON_PADDING_H_REF = 30;
constexpr int16_t TITLE_LABEL_WIDTH_REF = 100;
constexpr uint16_t TITLE_LABEL_FONT_SIZE_REF = 25;
constexpr int16_t NOTICE_LABEL_WIDTH_REF = 400;
constexpr int16_t NOTICE_LABEL_HEIGHT_REF = 36;
constexpr int16_t NOTICE_LABEL_MARGIN_TOP_REF = 30;
constexpr uint16_t NOTICE_LABEL_FONT_SIZE_REF = 32;
constexpr int16_t DURATION_LABEL_WIDTH_REF = 400;
constexpr int16_t DURATION_LABEL_HEIGHT_REF = 50;
constexpr int16_t DURATION_LABEL_MARGIN_TOP_REF = 30;
constexpr uint16_t DURATION_LABEL_FONT_SIZE_REF = 48;
constexpr int16_t FS_IMAGE_WIDTH_REF = 260;
constexpr int16_t FS_IMAGE_HEIGHT_REF = 110;
constexpr int16_t FS_IMAGE_MARGIN_TOP_REF = 40;
constexpr int16_t START_BUTTON_SIZE_REF = 140;
constexpr int16_t START_BUTTON_MARGIN_TOP_REF = 40;
constexpr int16_t CANCEL_BUTTON_SIZE_REF = 80;
constexpr int16_t CANCEL_BUTTON_MARGIN_RIGHT_REF = 40;
constexpr int16_t LIST_LABEL_MARGIN_TOP_REF = 20;
constexpr int16_t LIST_LABEL_WIDTH_REF = 200;
constexpr int16_t LIST_LABEL_HEIGHT_REF = 36;
constexpr uint16_t LIST_LABEL_FONT_SIZE_REF = 32;
constexpr int16_t LIST_MARGIN_TOP_REF = 20;
constexpr int16_t LIST_MARGIN_BOTTOM_REF = 20;
constexpr int16_t LIST_ITEM_HEIGHT_REF = 110;
constexpr int16_t LIST_ITEM_FILE_ICON_SIZE_REF = 72;
constexpr int16_t LIST_ITEM_NAME_LABEL_WIDTH_REF = 500;
constexpr int16_t LIST_ITEM_NAME_LABEL_HEIGHT_REF = 28;
constexpr uint16_t LIST_ITEM_NAME_LABEL_FONT_SIZE_REF = 24;
constexpr int16_t LIST_ITEM_TIME_PADDING_TOP_REF = 10;
constexpr int16_t LIST_ITEM_TIME_LABEL_WIDTH_REF = 200;
constexpr int16_t LIST_ITEM_TIME_LABEL_HEIGHT_REF = 22;
constexpr uint16_t LIST_ITEM_TIME_LABEL_FONT_SIZE_REF = 20;
constexpr int16_t LIST_ITEM_BUTTON_SIZE_REF = 56;

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
static const char* const BACK_ICON_PATH = "/recorder/assets/recorder/resources/drawable/ic_back.png";
static const char* const FS_ICON_PATH = "/recorder/assets/recorder/resources/drawable/fs.png";
static const char* const START_ICON_PATH = "/recorder/assets/recorder/resources/drawable/start.png";
static const char* const STOP_ICON_PATH = "/recorder/assets/recorder/resources/drawable/stop.png";
static const char* const PAUSE_ICON_PATH = "/recorder/assets/recorder/resources/drawable/pause.png";
static const char* const RESUME_ICON_PATH = "/recorder/assets/recorder/resources/drawable/resume.png";
static const char* const CANCEL_ICON_PATH = "/recorder/assets/recorder/resources/drawable/cancel.png";
static const char* const LIST_FILE_ICON_PATH = "/recorder/assets/recorder/resources/drawable/list_file.png";
static const char* const LIST_PLAY_ICON_PATH = "/recorder/assets/recorder/resources/drawable/list_play.png";
static const char* const LIST_PAUSE_ICON_PATH = "/recorder/assets/recorder/resources/drawable/list_pause.png";
static const char* const LIST_DEL_ICON_PATH = "/recorder/assets/recorder/resources/drawable/list_del.png";

static constexpr int16_t MAX_PICTURE_COUNT = 256;
static constexpr uint16_t MAX_PATH_LENGTH = 512;
static constexpr uint16_t TIME_FIELD_WIDTH = 2;

/** recorder folder path */
static const char* const RECORDER_DIRECTORY = "/userdata/audio/";
static const char* const RECORDER_TEMP_DIRECTORY = "/userdata/audio/norm/";
static const char* const RECORDER_TEMP_FILE_POSTFIX = ".MP4";
static const char* const RECORDER_FILE_POSTFIX = ".m4a";
static const char* const RECORDER_FILE_NAME_FMT = "%Y%m%d_%H%M%S";
static const char* const RECORDER_FILE_TIME_FMT = "%Y/%m/%d";
static constexpr uint16_t RECORDER_FILE_POSTFIX_LENGTH = 4;

/** general page configuration — runtime screen aware */
static inline int ROOT_VIEW_X()
{
    return 0;
}
static inline int ROOT_VIEW_Y()
{
    return 0;
}
static inline int ROOT_VIEW_WIDTH()
{
    return GetScrWidth();
}
static inline int ROOT_VIEW_HEIGHT()
{
    return GetScrHeight();
}
static constexpr uint16_t ROOT_VIEW_OPACITY = 255;

static const char* const FONT_NAME = "SourceHanSansSC-Regular.otf";

/** title bar */
static inline int16_t TITLE_BAR_X()
{
    return 0;
}
static inline int16_t TITLE_BAR_Y()
{
    return 0;
}
static inline int16_t TITLE_BAR_WIDTH()
{
    return ROOT_VIEW_WIDTH();
}
static inline int16_t TITLE_BAR_HEIGHT()
{
    return VScale(TITLE_BAR_HEIGHT_REF);
}
// title back icon
static inline int16_t BACK_ICON_SIZE()
{
    return UScale(BACK_ICON_SIZE_REF);
}
static inline int16_t BACK_ICON_PADDING_H()
{
    return HScale(BACK_ICON_PADDING_H_REF);
}
static inline int16_t BACK_ICON_PADDING_V()
{
    return (TITLE_BAR_HEIGHT() - BACK_ICON_SIZE()) / HALF_DIVISOR;
}
static inline int16_t BACK_ICON_X()
{
    return BACK_ICON_PADDING_H();
}
static inline int16_t BACK_ICON_Y()
{
    return TITLE_BAR_Y() + BACK_ICON_PADDING_V();
}
static inline int16_t BACK_ICON_WIDTH()
{
    return BACK_ICON_SIZE();
}
static inline int16_t BACK_ICON_HEIGHT()
{
    return BACK_ICON_SIZE();
}
// title label
static inline int16_t TITLE_LABEL_X()
{
    return BACK_ICON_X() + BACK_ICON_SIZE() + BACK_ICON_PADDING_H() * DOUBLE_COUNT;
}
static inline int16_t TITLE_LABEL_Y()
{
    return 0;
}
static inline int16_t TITLE_LABEL_WIDTH()
{
    return HScale(TITLE_LABEL_WIDTH_REF);
}
static inline int16_t TITLE_LABEL_HEIGHT()
{
    return TITLE_BAR_HEIGHT();
}
static inline uint16_t TITLE_LABEL_FONT_SIZE()
{
    return FontScale(TITLE_LABEL_FONT_SIZE_REF);
}

/** notice label **/
static inline int16_t NOTICE_LABEL_WIDTH()
{
    return HScale(NOTICE_LABEL_WIDTH_REF);
}
static inline int16_t NOTICE_LABEL_HEIGHT()
{
    return VScale(NOTICE_LABEL_HEIGHT_REF);
}
static inline int16_t NOTICE_LABEL_MARGIN_TOP()
{
    return VScale(NOTICE_LABEL_MARGIN_TOP_REF);
}
static inline uint16_t NOTICE_LABEL_FONT_SIZE()
{
    return FontScale(NOTICE_LABEL_FONT_SIZE_REF);
}
static inline int16_t NOTICE_LABEL_X()
{
    return (ROOT_VIEW_WIDTH() - NOTICE_LABEL_WIDTH()) / HALF_DIVISOR;
}
static inline int16_t NOTICE_LABEL_Y()
{
    return TITLE_BAR_Y() + TITLE_BAR_HEIGHT() + NOTICE_LABEL_MARGIN_TOP();
}

/** duration **/
static inline int16_t DURATION_LABEL_WIDTH()
{
    return HScale(DURATION_LABEL_WIDTH_REF);
}
static inline int16_t DURATION_LABEL_HEIGHT()
{
    return VScale(DURATION_LABEL_HEIGHT_REF);
}
static inline int16_t DURATION_LABEL_MARGIN_TOP()
{
    return VScale(DURATION_LABEL_MARGIN_TOP_REF);
}
static inline uint16_t DURATION_LABEL_FONT_SIZE()
{
    return FontScale(DURATION_LABEL_FONT_SIZE_REF);
}
static inline int16_t DURATION_LABEL_X()
{
    return (ROOT_VIEW_WIDTH() - DURATION_LABEL_WIDTH()) / HALF_DIVISOR;
}
static inline int16_t DURATION_LABEL_Y()
{
    return NOTICE_LABEL_Y() + NOTICE_LABEL_HEIGHT() + DURATION_LABEL_MARGIN_TOP();
}

/** fs **/
static inline int16_t FS_IMAGE_WIDTH()
{
    return HScale(FS_IMAGE_WIDTH_REF);
}
static inline int16_t FS_IMAGE_HEIGHT()
{
    return VScale(FS_IMAGE_HEIGHT_REF);
}
static inline int16_t FS_IMAGE_MARGIN_TOP()
{
    return VScale(FS_IMAGE_MARGIN_TOP_REF);
}
static inline int16_t FS_IMAGE_X()
{
    return (ROOT_VIEW_WIDTH() - FS_IMAGE_WIDTH()) / HALF_DIVISOR;
}
static inline int16_t FS_IMAGE_Y()
{
    return DURATION_LABEL_Y() + DURATION_LABEL_HEIGHT() + FS_IMAGE_MARGIN_TOP();
}

/** start/stop button */
static inline int16_t START_BUTTON_SIZE()
{
    return UScale(START_BUTTON_SIZE_REF);
}
static inline int16_t START_BUTTON_MARGIN_TOP()
{
    return VScale(START_BUTTON_MARGIN_TOP_REF);
}
static inline int16_t START_BUTTON_WIDTH()
{
    return START_BUTTON_SIZE();
}
static inline int16_t START_BUTTON_HEIGHT()
{
    return START_BUTTON_SIZE();
}
static inline int16_t START_BUTTON_X()
{
    return (ROOT_VIEW_WIDTH() - START_BUTTON_WIDTH()) / HALF_DIVISOR;
}
static inline int16_t START_BUTTON_Y()
{
    return FS_IMAGE_Y() + FS_IMAGE_HEIGHT() + START_BUTTON_MARGIN_TOP();
}

/** cancel button */
static inline int16_t CANCEL_BUTTON_SIZE()
{
    return UScale(CANCEL_BUTTON_SIZE_REF);
}
static inline int16_t CANCEL_BUTTON_WIDTH()
{
    return CANCEL_BUTTON_SIZE();
}
static inline int16_t CANCEL_BUTTON_HEIGHT()
{
    return CANCEL_BUTTON_SIZE();
}
static inline int16_t CANCEL_BUTTON_MARGIN_RIGHT()
{
    return HScale(CANCEL_BUTTON_MARGIN_RIGHT_REF);
}
static inline int16_t CANCEL_BUTTON_X()
{
    return START_BUTTON_X() - CANCEL_BUTTON_WIDTH() - CANCEL_BUTTON_MARGIN_RIGHT();
}
static inline int16_t CANCEL_BUTTON_Y()
{
    return START_BUTTON_Y();
}

/** pause/resume button */
static inline int16_t PAUSE_BUTTON_SIZE()
{
    return CANCEL_BUTTON_SIZE();
}
static inline int16_t PAUSE_BUTTON_WIDTH()
{
    return PAUSE_BUTTON_SIZE();
}
static inline int16_t PAUSE_BUTTON_HEIGHT()
{
    return PAUSE_BUTTON_SIZE();
}
static inline int16_t PAUSE_BUTTON_MARGIN_LEFT()
{
    return CANCEL_BUTTON_MARGIN_RIGHT();
}
static inline int16_t PAUSE_BUTTON_X()
{
    return START_BUTTON_X() + START_BUTTON_WIDTH() + PAUSE_BUTTON_MARGIN_LEFT();
}
static inline int16_t PAUSE_BUTTON_Y()
{
    return START_BUTTON_Y();
}

/** list */
static constexpr int16_t LIST_MARGIN_H = 20;
// list lable
static inline int16_t LIST_LABEL_MARGIN_TOP()
{
    return VScale(LIST_LABEL_MARGIN_TOP_REF);
}
static inline int16_t LIST_LABEL_X()
{
    return LIST_MARGIN_H;
}
static inline int16_t LIST_LABEL_Y()
{
    return START_BUTTON_Y() + START_BUTTON_HEIGHT() + LIST_LABEL_MARGIN_TOP();
}
static inline int16_t LIST_LABEL_WIDTH()
{
    return HScale(LIST_LABEL_WIDTH_REF);
}
static inline int16_t LIST_LABEL_HEIGHT()
{
    return VScale(LIST_LABEL_HEIGHT_REF);
}
static inline uint16_t LIST_LABEL_FONT_SIZE()
{
    return FontScale(LIST_LABEL_FONT_SIZE_REF);
}
// list
static inline int16_t LIST_MARGIN_TOP()
{
    return VScale(LIST_MARGIN_TOP_REF);
}
static inline int16_t LIST_MARGIN_BOTTOM()
{
    return VScale(LIST_MARGIN_BOTTOM_REF);
}
static inline int16_t LIST_X()
{
    return LIST_MARGIN_H;
}
static inline int16_t LIST_Y()
{
    return LIST_LABEL_Y() + LIST_LABEL_HEIGHT() + LIST_MARGIN_TOP();
}
static inline int16_t LIST_WIDTH()
{
    return ROOT_VIEW_WIDTH() - (LIST_MARGIN_H * DOUBLE_COUNT);
}
static inline int16_t LIST_HEIGHT()
{
    return ROOT_VIEW_HEIGHT() - LIST_MARGIN_BOTTOM() - LIST_Y();
}
// list divider
static constexpr int16_t LIST_DIVIDER_HEIGHT = 8;
// list item
static constexpr int16_t LIST_ITEM_X = 0;
static constexpr int16_t LIST_ITEM_Y = 0;
static inline int16_t LIST_ITEM_WIDTH()
{
    return LIST_WIDTH();
}
static inline int16_t LIST_ITEM_HEIGHT()
{
    return VScale(LIST_ITEM_HEIGHT_REF);
}
static constexpr int16_t LIST_ITEM_PADDING_H = 20;
static constexpr int16_t LIST_ITEM_PADDING_V = 20;
// list item file icon
static inline int16_t LIST_ITEM_FILE_ICON_WIDTH()
{
    return HScale(LIST_ITEM_FILE_ICON_SIZE_REF);
}
static inline int16_t LIST_ITEM_FILE_ICON_HEIGHT()
{
    return VScale(LIST_ITEM_FILE_ICON_SIZE_REF);
}
static inline int16_t LIST_ITEM_FILE_ICON_X()
{
    return LIST_ITEM_PADDING_H;
}
static inline int16_t LIST_ITEM_FILE_ICON_Y()
{
    return (LIST_ITEM_HEIGHT() - LIST_ITEM_FILE_ICON_HEIGHT()) / HALF_DIVISOR;
}
// list item name label
static constexpr int16_t LIST_ITEM_NAME_LABEL_MARGIN_LEFT = 20;
static inline int16_t LIST_ITEM_NAME_LABEL_X()
{
    return LIST_ITEM_FILE_ICON_X() + LIST_ITEM_FILE_ICON_WIDTH() + LIST_ITEM_NAME_LABEL_MARGIN_LEFT;
}
static inline int16_t LIST_ITEM_NAME_LABEL_WIDTH()
{
    return HScale(LIST_ITEM_NAME_LABEL_WIDTH_REF);
}
static inline int16_t LIST_ITEM_NAME_LABEL_HEIGHT()
{
    return VScale(LIST_ITEM_NAME_LABEL_HEIGHT_REF);
}
static inline uint16_t LIST_ITEM_NAME_LABEL_FONT_SIZE()
{
    return FontScale(LIST_ITEM_NAME_LABEL_FONT_SIZE_REF);
}
// list item time label
static inline int16_t LIST_ITEM_TIME_PADDING_TOP()
{
    return VScale(LIST_ITEM_TIME_PADDING_TOP_REF);
}
static inline int16_t LIST_ITEM_TIME_LABEL_X()
{
    return LIST_ITEM_NAME_LABEL_X();
}
static inline int16_t LIST_ITEM_TIME_LABEL_WIDTH()
{
    return HScale(LIST_ITEM_TIME_LABEL_WIDTH_REF);
}
static inline int16_t LIST_ITEM_TIME_LABEL_HEIGHT()
{
    return VScale(LIST_ITEM_TIME_LABEL_HEIGHT_REF);
}
static inline uint16_t LIST_ITEM_TIME_LABEL_FONT_SIZE()
{
    return FontScale(LIST_ITEM_TIME_LABEL_FONT_SIZE_REF);
}
// refactor list time name/time label Y
static inline int16_t LIST_ITEM_NAME_LABEL_Y()
{
    return (LIST_ITEM_HEIGHT() -
        (LIST_ITEM_NAME_LABEL_HEIGHT() + LIST_ITEM_TIME_PADDING_TOP() +
            LIST_ITEM_TIME_LABEL_HEIGHT())) /
        HALF_DIVISOR;
}
static inline int16_t LIST_ITEM_TIME_LABEL_Y()
{
    return LIST_ITEM_NAME_LABEL_Y() + LIST_ITEM_NAME_LABEL_HEIGHT() + LIST_ITEM_TIME_PADDING_TOP();
}
// list item play button
static inline int16_t LIST_ITEM_BUTTON_SIZE()
{
    return HScale(LIST_ITEM_BUTTON_SIZE_REF);
}
static constexpr int16_t LIST_ITEM_BUTTON_MARGIN = 20;
static constexpr int16_t LIST_ITEM_BORDER_RADIUS = 16;
static inline int16_t LIST_ITEM_PLAY_BUTTON_X()
{
    return LIST_ITEM_WIDTH() - LIST_ITEM_PADDING_H -
        LIST_ITEM_BUTTON_SIZE() * DOUBLE_COUNT - LIST_ITEM_BUTTON_MARGIN;
}
static inline int16_t LIST_ITEM_PLAY_BUTTON_Y()
{
    return (LIST_ITEM_HEIGHT() - LIST_ITEM_BUTTON_SIZE()) / HALF_DIVISOR;
}
static inline int16_t LIST_ITEM_PLAY_BUTTON_WIDTH()
{
    return LIST_ITEM_BUTTON_SIZE();
}
static inline int16_t LIST_ITEM_PLAY_BUTTON_HEIGHT()
{
    return LIST_ITEM_BUTTON_SIZE();
}
// list item delete button
static inline int16_t LIST_ITEM_DEL_BUTTON_X()
{
    return LIST_ITEM_WIDTH() - LIST_ITEM_PADDING_H - LIST_ITEM_BUTTON_SIZE();
}
static inline int16_t LIST_ITEM_DEL_BUTTON_Y()
{
    return (LIST_ITEM_HEIGHT() - LIST_ITEM_BUTTON_SIZE()) / HALF_DIVISOR;
}
static inline int16_t LIST_ITEM_DEL_BUTTON_WIDTH()
{
    return LIST_ITEM_BUTTON_SIZE();
}
static inline int16_t LIST_ITEM_DEL_BUTTON_HEIGHT()
{
    return LIST_ITEM_BUTTON_SIZE();
}

/** prefix and File Type */
static const char* const AVAILABEL_SOURCE_TYPE = ".aac";
} // namespace OHOS
#endif // OHOS_RECORDER_CONFIG_H

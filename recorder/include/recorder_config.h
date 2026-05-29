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

namespace OHOS {

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

/** general page configuration */
static constexpr int ROOT_VIEW_X = 0;
static constexpr int ROOT_VIEW_Y = 0;
static constexpr int ROOT_VIEW_WIDTH = HORIZONTAL_RESOLUTION;
static constexpr int ROOT_VIEW_HEIGHT = VERTICAL_RESOLUTION;
static constexpr uint16_t ROOT_VIEW_OPACITY = 255;

static const char* const FONT_NAME = "SourceHanSansSC-Regular.otf";

/** title bar */
static constexpr int16_t TITLE_BAR_X = 0;
static constexpr int16_t TITLE_BAR_Y = 0;
static constexpr int16_t TITLE_BAR_WIDTH = ROOT_VIEW_WIDTH;
static constexpr int16_t TITLE_BAR_HEIGHT = 70;
// title back icon
static constexpr int16_t BACK_ICON_SIZE = 36;   // 36 x 36
static constexpr int16_t BACK_ICON_PADDING_H = 30;
static constexpr int16_t BACK_ICON_PADDING_V = (TITLE_BAR_HEIGHT - BACK_ICON_SIZE) / 2;
static constexpr int16_t BACK_ICON_X = 0;
static constexpr int16_t BACK_ICON_Y = TITLE_BAR_Y;
static constexpr int16_t BACK_ICON_WIDTH = BACK_ICON_SIZE + BACK_ICON_PADDING_H * 2;
static constexpr int16_t BACK_ICON_HEIGHT = TITLE_BAR_HEIGHT;
// title label
static constexpr int16_t TITLE_LABEL_X = BACK_ICON_X + BACK_ICON_SIZE + BACK_ICON_PADDING_H * 2;
static constexpr int16_t TITLE_LABEL_Y = 0;
static constexpr int16_t TITLE_LABEL_WIDTH = 100;
static constexpr int16_t TITLE_LABEL_HEIGHT = TITLE_BAR_HEIGHT;
static constexpr uint16_t TITLE_LABEL_FONT_SIZE = 25;

/** notice label **/
static constexpr int16_t NOTICE_LABEL_WIDTH = 400;
#if (HORIZONTAL_RESOLUTION == 1920 && VERTICAL_RESOLUTION == 1080)
static constexpr int16_t NOTICE_LABEL_HEIGHT = 36;
static constexpr int16_t NOTICE_LABEL_MARGIN_TOP = 30;
static constexpr uint16_t NOTICE_LABEL_FONT_SIZE = 32;
#else
static constexpr int16_t NOTICE_LABEL_HEIGHT = 26;
static constexpr int16_t NOTICE_LABEL_MARGIN_TOP = 16;
static constexpr uint16_t NOTICE_LABEL_FONT_SIZE = 24;
#endif
static constexpr int16_t NOTICE_LABEL_X = (ROOT_VIEW_WIDTH - NOTICE_LABEL_WIDTH) / 2;
static constexpr int16_t NOTICE_LABEL_Y = TITLE_BAR_Y + TITLE_BAR_HEIGHT + NOTICE_LABEL_MARGIN_TOP;

/** duration **/
static constexpr int16_t DURATION_LABEL_WIDTH = 400;
#if (HORIZONTAL_RESOLUTION == 1920 && VERTICAL_RESOLUTION == 1080)
static constexpr int16_t DURATION_LABEL_HEIGHT = 50;
static constexpr int16_t DURATION_LABEL_MARGIN_TOP = 30;
static constexpr uint16_t DURATION_LABEL_FONT_SIZE = 48;
#else
static constexpr int16_t DURATION_LABEL_HEIGHT = 38;
static constexpr int16_t DURATION_LABEL_MARGIN_TOP = 16;
static constexpr uint16_t DURATION_LABEL_FONT_SIZE = 36;
#endif
static constexpr int16_t DURATION_LABEL_X = (ROOT_VIEW_WIDTH - DURATION_LABEL_WIDTH) / 2;
static constexpr int16_t DURATION_LABEL_Y = NOTICE_LABEL_Y + NOTICE_LABEL_HEIGHT + DURATION_LABEL_MARGIN_TOP;

/** fs **/
static constexpr int16_t FS_IMAGE_WIDTH = 260;
#if (HORIZONTAL_RESOLUTION == 1920 && VERTICAL_RESOLUTION == 1080)
static constexpr int16_t FS_IMAGE_HEIGHT = 110;
static constexpr int16_t FS_IMAGE_MARGIN_TOP = 40;
#else
static constexpr int16_t FS_IMAGE_HEIGHT = 0;
static constexpr int16_t FS_IMAGE_MARGIN_TOP = 0;
#endif
static constexpr int16_t FS_IMAGE_X = (ROOT_VIEW_WIDTH - FS_IMAGE_WIDTH) / 2;
static constexpr int16_t FS_IMAGE_Y = DURATION_LABEL_Y + DURATION_LABEL_HEIGHT + FS_IMAGE_MARGIN_TOP;

/** start/stop button */
#if (HORIZONTAL_RESOLUTION == 1920 && VERTICAL_RESOLUTION == 1080)
static constexpr int16_t START_BUTTON_SIZE = 140;
static constexpr int16_t START_BUTTON_MARGIN_TOP = 40;
#else
static constexpr int16_t START_BUTTON_SIZE = 80;
static constexpr int16_t START_BUTTON_MARGIN_TOP = 20;
#endif
static constexpr int16_t START_BUTTON_WIDTH = START_BUTTON_SIZE;
static constexpr int16_t START_BUTTON_HEIGHT = START_BUTTON_SIZE;
static constexpr int16_t START_BUTTON_X = (ROOT_VIEW_WIDTH - START_BUTTON_WIDTH) / 2;
static constexpr int16_t START_BUTTON_Y = FS_IMAGE_Y + FS_IMAGE_HEIGHT + START_BUTTON_MARGIN_TOP;

/** cancel button */
#if (HORIZONTAL_RESOLUTION == 1920 && VERTICAL_RESOLUTION == 1080)
static constexpr int16_t CANCEL_BUTTON_SIZE = 80;
#else
static constexpr int16_t CANCEL_BUTTON_SIZE = 48;
#endif
static constexpr int16_t CANCEL_BUTTON_WIDTH = CANCEL_BUTTON_SIZE;
static constexpr int16_t CANCEL_BUTTON_HEIGHT = CANCEL_BUTTON_SIZE;
static constexpr int16_t CANCEL_BUTTON_MARGIN_RIGHT = 40;
static constexpr int16_t CANCEL_BUTTON_X = START_BUTTON_X - CANCEL_BUTTON_WIDTH - CANCEL_BUTTON_MARGIN_RIGHT;
static constexpr int16_t CANCEL_BUTTON_Y = START_BUTTON_Y;

/** pause/resume button */
static constexpr int16_t PAUSE_BUTTON_SIZE = CANCEL_BUTTON_SIZE;
static constexpr int16_t PAUSE_BUTTON_WIDTH = PAUSE_BUTTON_SIZE;
static constexpr int16_t PAUSE_BUTTON_HEIGHT = PAUSE_BUTTON_SIZE;
static constexpr int16_t PAUSE_BUTTON_MARGIN_LEFT = CANCEL_BUTTON_MARGIN_RIGHT;
static constexpr int16_t PAUSE_BUTTON_X = START_BUTTON_X + START_BUTTON_WIDTH + PAUSE_BUTTON_MARGIN_LEFT;
static constexpr int16_t PAUSE_BUTTON_Y = START_BUTTON_Y;

/** list */
static constexpr int16_t LIST_MARGIN_H = 20;
// list lable
static constexpr int16_t LIST_LABEL_MARGIN_TOP = 20;
static constexpr int16_t LIST_LABEL_X = LIST_MARGIN_H;
static constexpr int16_t LIST_LABEL_Y = START_BUTTON_Y + START_BUTTON_HEIGHT + LIST_LABEL_MARGIN_TOP;
static constexpr int16_t LIST_LABEL_WIDTH = 200;
#if (HORIZONTAL_RESOLUTION == 1920 && VERTICAL_RESOLUTION == 1080)
static constexpr int16_t LIST_LABEL_HEIGHT = 36;
static constexpr uint16_t LIST_LABEL_FONT_SIZE = 32;
#else
static constexpr int16_t LIST_LABEL_HEIGHT = 26;
static constexpr uint16_t LIST_LABEL_FONT_SIZE = 24;
#endif
// list
static constexpr int16_t LIST_MARGIN_TOP = 20;
static constexpr int16_t LIST_MARGIN_BOTTOM = 20;
static constexpr int16_t LIST_X = LIST_MARGIN_H;
static constexpr int16_t LIST_Y = LIST_LABEL_Y + LIST_LABEL_HEIGHT + LIST_MARGIN_TOP;
static constexpr int16_t LIST_WIDTH = ROOT_VIEW_WIDTH - (LIST_MARGIN_H * 2);
static constexpr int16_t LIST_HEIGHT = ROOT_VIEW_HEIGHT - LIST_MARGIN_BOTTOM - LIST_Y;
// list divider
static constexpr int16_t LIST_DIVIDER_HEIGHT = 8;
// list item
static constexpr int16_t LIST_ITEM_X = 0;
static constexpr int16_t LIST_ITEM_Y = 0;
static constexpr int16_t LIST_ITEM_WIDTH = LIST_WIDTH;
#if (HORIZONTAL_RESOLUTION == 1920 && VERTICAL_RESOLUTION == 1080)
static constexpr int16_t LIST_ITEM_HEIGHT = 110;
#else
static constexpr int16_t LIST_ITEM_HEIGHT = 80;
#endif
static constexpr int16_t LIST_ITEM_PADDING_H = 20;
static constexpr int16_t LIST_ITEM_PADDING_V = 20;
// list item file icon
#if (HORIZONTAL_RESOLUTION == 1920 && VERTICAL_RESOLUTION == 1080)
static constexpr int16_t LIST_ITEM_FILE_ICON_WIDTH = 72;
static constexpr int16_t LIST_ITEM_FILE_ICON_HEIGHT = 72;
#else
static constexpr int16_t LIST_ITEM_FILE_ICON_WIDTH = 56;
static constexpr int16_t LIST_ITEM_FILE_ICON_HEIGHT = 56;
#endif
static constexpr int16_t LIST_ITEM_FILE_ICON_X = LIST_ITEM_PADDING_H;
static constexpr int16_t LIST_ITEM_FILE_ICON_Y = (LIST_ITEM_HEIGHT - LIST_ITEM_FILE_ICON_HEIGHT) / 2;
// list item name label
static constexpr int16_t LIST_ITEM_NAME_LABEL_MARGIN_LEFT = 20;
static constexpr int16_t LIST_ITEM_NAME_LABEL_X =
    LIST_ITEM_FILE_ICON_X + LIST_ITEM_FILE_ICON_WIDTH + LIST_ITEM_NAME_LABEL_MARGIN_LEFT;
static constexpr int16_t LIST_ITEM_NAME_LABEL_WIDTH = 500;
static constexpr int16_t LIST_ITEM_NAME_LABEL_HEIGHT = 28;
static constexpr uint16_t LIST_ITEM_NAME_LABEL_FONT_SIZE = 24;
// list item time label
static constexpr int16_t LIST_ITEM_TIME_PADDING_TOP = 10;
static constexpr int16_t LIST_ITEM_TIME_LABEL_X = LIST_ITEM_NAME_LABEL_X;
static constexpr int16_t LIST_ITEM_TIME_LABEL_WIDTH = 200;
static constexpr int16_t LIST_ITEM_TIME_LABEL_HEIGHT = 22;
static constexpr uint16_t LIST_ITEM_TIME_LABEL_FONT_SIZE = 20;
// refactor list time name/time label Y
static constexpr int16_t LIST_ITEM_NAME_LABEL_Y =
    (LIST_ITEM_HEIGHT -
    (LIST_ITEM_NAME_LABEL_HEIGHT + LIST_ITEM_TIME_PADDING_TOP + LIST_ITEM_TIME_LABEL_HEIGHT)) /
    2;
static constexpr int16_t LIST_ITEM_TIME_LABEL_Y =
    LIST_ITEM_NAME_LABEL_Y + LIST_ITEM_NAME_LABEL_HEIGHT + LIST_ITEM_TIME_PADDING_TOP;
// list item play button
#if (HORIZONTAL_RESOLUTION == 1920 && VERTICAL_RESOLUTION == 1080)
static constexpr int16_t LIST_ITEM_BUTTON_SIZE = 56;
#else
static constexpr int16_t LIST_ITEM_BUTTON_SIZE = 48;
#endif
static constexpr int16_t LIST_ITEM_BUTTON_MARGIN = 20;
static constexpr int16_t LIST_ITEM_BORDER_RADIUS = 16;
static constexpr int16_t LIST_ITEM_PLAY_BUTTON_X =
    LIST_ITEM_WIDTH - LIST_ITEM_PADDING_H - LIST_ITEM_BUTTON_SIZE * 2 - LIST_ITEM_BUTTON_MARGIN;
static constexpr int16_t LIST_ITEM_PLAY_BUTTON_Y = (LIST_ITEM_HEIGHT - LIST_ITEM_BUTTON_SIZE) / 2;
static constexpr int16_t LIST_ITEM_PLAY_BUTTON_WIDTH = LIST_ITEM_BUTTON_SIZE;
static constexpr int16_t LIST_ITEM_PLAY_BUTTON_HEIGHT = LIST_ITEM_BUTTON_SIZE;
// list item delete button
static constexpr int16_t LIST_ITEM_DEL_BUTTON_X = LIST_ITEM_WIDTH - LIST_ITEM_PADDING_H - LIST_ITEM_BUTTON_SIZE;
static constexpr int16_t LIST_ITEM_DEL_BUTTON_Y = (LIST_ITEM_HEIGHT - LIST_ITEM_BUTTON_SIZE) / 2;
static constexpr int16_t LIST_ITEM_DEL_BUTTON_WIDTH = LIST_ITEM_BUTTON_SIZE;
static constexpr int16_t LIST_ITEM_DEL_BUTTON_HEIGHT = LIST_ITEM_BUTTON_SIZE;


/** prefix and File Type */
static const char* const AVAILABEL_SOURCE_TYPE = ".aac";
} // namespace OHOS
#endif // OHOS_RECORDER_CONFIG_H

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

#ifndef __UI_CONFIG_H__
#define __UI_CONFIG_H__

#include <common/screen.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Screen-aware scaling helpers — designed for 1920x1080 reference */
static inline int16_t ScrWidth() { return OHOS::Screen::GetInstance().GetWidth(); }
static inline int16_t ScrHeight() { return OHOS::Screen::GetInstance().GetHeight(); }
static inline int16_t HScale(int16_t ref) { return static_cast<int16_t>(static_cast<int32_t>(ref) * ScrWidth() / 1920); }
static inline int16_t VScale(int16_t ref) { return static_cast<int16_t>(static_cast<int32_t>(ref) * ScrHeight() / 1080); }

/* Orientation detection: horizontal if width >= height, else vertical */
static inline bool IsHorizontalMode()
{
    return ScrWidth() >= ScrHeight();
}

/* Base starting point */
#define START_X 0
#define START_Y 0

/* Button icon sizes — scaled from 1920x1080 reference */
static inline int16_t BUTTON_ICON_SW() { return HScale(60); }
static inline int16_t BUTTON_ICON_SH() { return VScale(60); }
static inline int16_t BUTTON_ICON_BW() { return HScale(114); }
static inline int16_t BUTTON_ICON_BH() { return VScale(114); }

static inline int16_t TITLE_HEIGHT() { return VScale(80); }

static inline int16_t ICON_B_WIDTH()  { return HScale(50); }
static inline int16_t ICON_B_HEIGHT() { return VScale(50); }
static inline int16_t ICON_M_WIDTH()  { return HScale(36); }
static inline int16_t ICON_M_HEIGHT() { return VScale(36); }
static inline int16_t ICON_S_WIDTH()  { return HScale(12); }
static inline int16_t ICON_S_HEIGHT() { return VScale(12); }

/* coord define — using runtime screen dimensions */
static inline int16_t V_GROUP_X() { return START_X; }
static inline int16_t V_GROUP_Y() { return START_Y; }
static inline int16_t V_GROUP_W() { return ScrWidth(); }
static inline int16_t V_GROUP_H() { return ScrHeight(); }

/* Layout computed from runtime screen size and scaled icon sizes */
static inline int16_t BACK_LABEL_X() { return START_X + HScale(30); }
static inline int16_t BACK_LABEL_Y() { return (TITLE_HEIGHT() - ICON_M_HEIGHT()) / 2; }
static inline int16_t BACK_LABEL_W() { return ICON_M_WIDTH(); }
static inline int16_t BACK_LABEL_H() { return ICON_M_HEIGHT(); }

static inline int16_t TXT_LABEL_X() { return BACK_LABEL_X() + BUTTON_ICON_SW(); }
static inline int16_t TXT_LABEL_Y() { return START_Y + (TITLE_HEIGHT() - ICON_B_HEIGHT()) / 2; }
static inline int16_t TXT_LABEL_W() { return ICON_B_WIDTH() * 3; }
static inline int16_t TXT_LABEL_H() { return ICON_B_HEIGHT(); }

static inline int16_t RECORD_IMAGE_X() { return ScrWidth() / 2 - BUTTON_ICON_SW(); }
static inline int16_t RECORD_IMAGE_Y() { return START_Y + (TITLE_HEIGHT() - ICON_S_HEIGHT()) / 2; }
static inline int16_t RECORD_IMAGE_W() { return ICON_S_WIDTH(); }
static inline int16_t RECORD_IMAGE_H() { return ICON_S_HEIGHT(); }

static inline int16_t TIME_LABEL_X() { return RECORD_IMAGE_X() + RECORD_IMAGE_W() + HScale(14); }
static inline int16_t TIME_LABEL_Y() { return START_Y + (TITLE_HEIGHT() - ICON_B_HEIGHT()) / 2; }
static inline int16_t TIME_LABEL_W() {
    return ScrWidth() - (RECORD_IMAGE_X() + RECORD_IMAGE_W() + HScale(14));
}
static inline int16_t TIME_LABEL_H() { return ICON_B_HEIGHT(); }

static inline int16_t SCROLL_VIEW_X() { return START_X; }
static inline int16_t SCROLL_VIEW_Y() { return (ScrHeight() - BUTTON_ICON_BH()) - VScale(30); }
static inline int16_t SCROLL_VIEW_W() { return ScrWidth(); }
static inline int16_t SCROLL_VIEW_H() { return BUTTON_ICON_BH() + VScale(6); }

static inline int16_t LEFT_BUTTON_X() { return ScrWidth() / 3; }
static inline int16_t LEFT_BUTTON_Y() { return (SCROLL_VIEW_H() - BUTTON_ICON_SH()) / 2; }
static inline int16_t LEFT_BUTTON_W() { return BUTTON_ICON_SW(); }
static inline int16_t LEFT_BUTTON_H() { return BUTTON_ICON_SH(); }

static inline int16_t MID_BUTTON_X() {
    return ((ScrWidth() / 3) - BUTTON_ICON_BW()) / 2 + 1 * (ScrWidth() / 3);
}
static inline int16_t MID_BUTTON_Y() { return (SCROLL_VIEW_H() - BUTTON_ICON_BH()) / 2; }
static inline int16_t MID_BUTTON_W() { return BUTTON_ICON_BW(); }
static inline int16_t MID_BUTTON_H() { return BUTTON_ICON_BH(); }

static inline int16_t RIGHT_BUTTON_X() {
    return 2 * (ScrWidth() / 3) - BUTTON_ICON_SW();
}
static inline int16_t RIGHT_BUTTON_Y() { return (SCROLL_VIEW_H() - BUTTON_ICON_SH()) / 2; }
static inline int16_t RIGHT_BUTTON_W() { return BUTTON_ICON_SW(); }
static inline int16_t RIGHT_BUTTON_H() { return BUTTON_ICON_SH(); }

#define UI_IMAGE_PATH \
    "/storage/app/run/com.huawei.camera/cameraApp/assets/cameraApp/resources/base/media/"
#define TTF_PATH "SourceHanSansSC-Regular.otf"

#define PHOTO_PATH "/userdata/photo/"
#define VIDEO_PATH "/userdata/video/"
#define THUMB_PATH "/userdata/thumb/"

#define MAX_NAME_LEN 256
#define PAGE_SIZE 1024

#define IMAGE_WIDTH 1920
#define IMAGE_HEIGHT 1080

#define SAMPLE_RATE 48000
#define CHANNEL_COUNT 1
#define AUDIO_ENCODING_BITRATE SAMPLE_RATE
#define FRAME_RATE 30
#define BIT_RATE 4096

#define FILE_MODE 0777

#ifdef __cplusplus
}
#endif

#endif

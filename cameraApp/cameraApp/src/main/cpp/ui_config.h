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

/* Screen-aware scaling helpers — designed for 1920x1080 reference.
 * Default fallback resolution is 960x480 when Screen reports 0. */
static constexpr int16_t DESIGN_WIDTH = 1920;
static constexpr int16_t DESIGN_HEIGHT = 1080;
static constexpr int16_t DEFAULT_SCR_WIDTH = 960;
static constexpr int16_t DEFAULT_SCR_HEIGHT = 480;
static constexpr int16_t HALF_DIVISOR = 2;
static constexpr int16_t THIRD_DIVISOR = 3;
static constexpr int16_t MID_BUTTON_COL_INDEX = 1;
static constexpr int16_t RIGHT_BUTTON_COL_INDEX = 2;

static constexpr int16_t BUTTON_ICON_S_REF = 60;
static constexpr int16_t BUTTON_ICON_B_REF = 114;
static constexpr int16_t TITLE_HEIGHT_REF = 80;
static constexpr int16_t ICON_B_REF = 50;
static constexpr int16_t ICON_M_REF = 36;
static constexpr int16_t ICON_S_REF = 12;
static constexpr int16_t BACK_LABEL_OFFSET_X = 30;
static constexpr int16_t TXT_LABEL_WIDTH_MULTIPLIER = 3;
static constexpr int16_t TIME_LABEL_GAP_X = 14;
static constexpr int16_t SCROLL_VIEW_MARGIN_BOTTOM = 30;
static constexpr int16_t SCROLL_VIEW_EXTRA_H = 6;
static constexpr int16_t TITLE_LABEL_WIDTH_REF = 100;
static constexpr int16_t TITLE_LABEL_HEIGHT_REF = 70;
static constexpr uint16_t TITLE_LABEL_FONT_SIZE_REF = 25;

static inline int16_t ScrWidth()
{
    uint16_t w = OHOS::Screen::GetInstance().GetWidth();
    return (w == 0) ? DEFAULT_SCR_WIDTH : static_cast<int16_t>(w);
}
static inline int16_t ScrHeight()
{
    uint16_t h = OHOS::Screen::GetInstance().GetHeight();
    return (h == 0) ? DEFAULT_SCR_HEIGHT : static_cast<int16_t>(h);
}
static inline int16_t HScale(int16_t ref)
{
    return static_cast<int16_t>(
        static_cast<int32_t>(ref) * ScrWidth() / DESIGN_WIDTH);
}
static inline int16_t VScale(int16_t ref)
{
    return static_cast<int16_t>(
        static_cast<int32_t>(ref) * ScrHeight() / DESIGN_HEIGHT);
}

/* Orientation detection: horizontal if width >= height, else vertical */
static inline bool IsHorizontalMode()
{
    return ScrWidth() >= ScrHeight();
}

static inline int16_t TITLE_LABEL_Y()
{
    return 0;
}
static inline int16_t TITLE_LABEL_WIDTH()
{
    return HScale(TITLE_LABEL_WIDTH_REF);
}

/* Base starting point */
#define START_X 0
#define START_Y 0

/* Button icon sizes — scaled from 1920x1080 reference */
static inline int16_t BUTTON_ICON_SW()
{
    return HScale(BUTTON_ICON_S_REF);
}
static inline int16_t BUTTON_ICON_SH()
{
    return VScale(BUTTON_ICON_S_REF);
}
static inline int16_t BUTTON_ICON_BW()
{
    return HScale(BUTTON_ICON_B_REF);
}
static inline int16_t BUTTON_ICON_BH()
{
    return VScale(BUTTON_ICON_B_REF);
}

static inline int16_t TITLE_HEIGHT()
{
    return VScale(TITLE_HEIGHT_REF);
}
static inline int16_t TITLE_LABEL_HEIGHT()
{
    return TITLE_HEIGHT();
}

static inline int16_t ICON_B_WIDTH()
{
    return HScale(ICON_B_REF);
}
static inline int16_t ICON_B_HEIGHT()
{
    return VScale(ICON_B_REF);
}
static inline int16_t ICON_M_WIDTH()
{
    return HScale(ICON_M_REF);
}
static inline int16_t ICON_M_HEIGHT()
{
    return VScale(ICON_M_REF);
}
static inline int16_t ICON_S_WIDTH()
{
    return HScale(ICON_S_REF);
}
static inline int16_t ICON_S_HEIGHT()
{
    return VScale(ICON_S_REF);
}

/* coord define — using runtime screen dimensions */
static inline int16_t V_GROUP_X()
{
    return START_X;
}
static inline int16_t V_GROUP_Y()
{
    return START_Y;
}
static inline int16_t V_GROUP_W()
{
    return ScrWidth();
}
static inline int16_t V_GROUP_H()
{
    return ScrHeight();
}

/* Layout computed from runtime screen size and scaled icon sizes */
static inline int16_t BACK_LABEL_X()
{
    return START_X + HScale(BACK_LABEL_OFFSET_X);
}
static inline int16_t BACK_LABEL_Y()
{
    return (TITLE_HEIGHT() - ICON_M_HEIGHT()) / HALF_DIVISOR;
}
static inline int16_t BACK_LABEL_W()
{
    return ICON_M_WIDTH();
}
static inline int16_t BACK_LABEL_H()
{
    return ICON_M_HEIGHT();
}

static inline int16_t TXT_LABEL_X()
{
    return BACK_LABEL_X() + BUTTON_ICON_SW();
}
static inline int16_t TXT_LABEL_Y()
{
    return START_Y + (TITLE_HEIGHT() - ICON_B_HEIGHT()) / HALF_DIVISOR;
}
static inline int16_t TXT_LABEL_W()
{
    return ICON_B_WIDTH() * TXT_LABEL_WIDTH_MULTIPLIER;
}
static inline int16_t TXT_LABEL_H()
{
    return ICON_B_HEIGHT();
}

static inline int16_t RECORD_IMAGE_X()
{
    return ScrWidth() / HALF_DIVISOR - BUTTON_ICON_SW();
}
static inline int16_t RECORD_IMAGE_Y()
{
    return START_Y + (TITLE_HEIGHT() - ICON_S_HEIGHT()) / HALF_DIVISOR;
}
static inline int16_t RECORD_IMAGE_W()
{
    return ICON_S_WIDTH();
}
static inline int16_t RECORD_IMAGE_H()
{
    return ICON_S_HEIGHT();
}

static inline int16_t TIME_LABEL_X()
{
    return RECORD_IMAGE_X() + RECORD_IMAGE_W() + HScale(TIME_LABEL_GAP_X);
}
static inline int16_t TIME_LABEL_Y()
{
    return START_Y + (TITLE_HEIGHT() - ICON_B_HEIGHT()) / HALF_DIVISOR;
}
static inline int16_t TIME_LABEL_W()
{
    return ScrWidth() - (RECORD_IMAGE_X() + RECORD_IMAGE_W() + HScale(TIME_LABEL_GAP_X));
}
static inline int16_t TIME_LABEL_H()
{
    return ICON_B_HEIGHT();
}

static inline int16_t SCROLL_VIEW_X()
{
    return START_X;
}
static inline int16_t SCROLL_VIEW_Y()
{
    return (ScrHeight() - BUTTON_ICON_BH()) - VScale(SCROLL_VIEW_MARGIN_BOTTOM);
}
static inline int16_t SCROLL_VIEW_W()
{
    return ScrWidth();
}
static inline int16_t SCROLL_VIEW_H()
{
    return BUTTON_ICON_BH() + VScale(SCROLL_VIEW_EXTRA_H);
}

static inline int16_t LEFT_BUTTON_X()
{
    return ScrWidth() / THIRD_DIVISOR;
}
static inline int16_t LEFT_BUTTON_Y()
{
    return (SCROLL_VIEW_H() - BUTTON_ICON_SH()) / HALF_DIVISOR;
}
static inline int16_t LEFT_BUTTON_W()
{
    return BUTTON_ICON_SW();
}
static inline int16_t LEFT_BUTTON_H()
{
    return BUTTON_ICON_SH();
}

static inline int16_t MID_BUTTON_X()
{
    return ((ScrWidth() / THIRD_DIVISOR) - BUTTON_ICON_BW()) / HALF_DIVISOR +
        MID_BUTTON_COL_INDEX * (ScrWidth() / THIRD_DIVISOR);
}
static inline int16_t MID_BUTTON_Y()
{
    return (SCROLL_VIEW_H() - BUTTON_ICON_BH()) / HALF_DIVISOR;
}
static inline int16_t MID_BUTTON_W()
{
    return BUTTON_ICON_BW();
}
static inline int16_t MID_BUTTON_H()
{
    return BUTTON_ICON_BH();
}

static inline int16_t RIGHT_BUTTON_X()
{
    return RIGHT_BUTTON_COL_INDEX * (ScrWidth() / THIRD_DIVISOR) - BUTTON_ICON_SW();
}
static inline int16_t RIGHT_BUTTON_Y()
{
    return (SCROLL_VIEW_H() - BUTTON_ICON_SH()) / HALF_DIVISOR;
}
static inline int16_t RIGHT_BUTTON_W()
{
    return BUTTON_ICON_SW();
}
static inline int16_t RIGHT_BUTTON_H()
{
    return BUTTON_ICON_SH();
}

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

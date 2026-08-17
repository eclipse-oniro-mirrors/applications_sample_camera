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

#ifndef OHOS_MAIN_ABILITY_SLICE_H
#define OHOS_MAIN_ABILITY_SLICE_H

#include <cstdio>

#include "ability_info.h"
#include "ability_loader.h"
#include "ability_manager.h"
#include "ability_slice.h"
#include "bundle_manager.h"
#include "components/ui_image_view.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_list.h"
#include "components/ui_scroll_view.h"
#include "components/ui_toggle_button.h"
#include "element_name.h"
#include "event_listener.h"
#include "gfx_utils/list.h"
#include "module_info.h"
#include "parameter.h"
#include "pthread.h"
#include "setting_utils.h"
#include "want.h"
#include "wpa_work.h"

namespace OHOS {
class MainAbilitySlice : public AbilitySlice {
public:
    MainAbilitySlice()
        : headView_(nullptr), scrollView_(nullptr), rootView_(nullptr), lablelFontSsid_(nullptr),
          lablelFontIp_(nullptr),
          buttonWifiListener_(nullptr), buttonAppListener_(nullptr), buttonDisplayListener_(nullptr),
          buttonAboutListener_(nullptr), buttonBackListener_(nullptr) {}
    virtual ~MainAbilitySlice();

protected:
    void OnStart(const Want &want) override;
    void OnInactive() override;
    void OnActive(const Want &want) override;
    void OnBackground() override;
    void OnStop() override;

private:
    void SetButtonListenerWifi();
    void SetButtonListenerApp();
    void SetButtonListenerDisplay();
    void SetButtonListenerAbout();
    void SetButtonListenerDhcp();
    void SetAboutButtonView();
    void SetAppButtonView();
    void SetDisplayButtonView();
    void SetWifiButtonView();
    void SetDhcpButtonView();
    void SetScrollView();
    void SetHead();

    UIViewGroup* headView_;
    UIScrollView* scrollView_;
    RootView* rootView_;
    UILabel* lablelFontSsid_;
    UILabel* lablelFontIp_;
    EventListener* buttonWifiListener_;
    EventListener* buttonAppListener_;
    EventListener* buttonDisplayListener_;
    EventListener* buttonAboutListener_;
    EventListener* buttonBackListener_;
    EventListener* buttonDhcpListener_;

    /* Scaled positions from 1920x1080 reference — keep proportions at every resolution */
    static constexpr int16_t wifiButtonTextWifiYRef = 13;
    static constexpr int16_t wifiButtonTextSsidXRef = 18;
    static constexpr int16_t wifiButtonTextSsidYRef = 45;

    static constexpr int16_t dhcpButtonXRef = 0;
    static constexpr int16_t dhcpButtonYRef = 95;
    static constexpr int16_t dhcpButtonTextDhcpYRef = 13;
    static constexpr int16_t dhcpButtonTextIpXRef = 18;
    static constexpr int16_t dhcpButtonTextIpYRef = 45;

    static constexpr int16_t appButtonYRef = 95;

    static constexpr int16_t dispalyButtonYRef = 190;

    static constexpr int16_t aboutButtonYRef = 190;
    static constexpr int16_t aboutButtonHeightRef = 113;
    static constexpr int16_t aboutButtonTextAboutYRef = 5;
    static constexpr int16_t aboutButtonTextSystemXRef = 18;
    static constexpr int16_t aboutButtonTextSystemYRef = 39;
    static constexpr int16_t aboutButtonTextDeviceXRef = 18;
    static constexpr int16_t aboutButtonTextDeviceYRef = 72;
    static constexpr int16_t aboutButtonImageYRef = 34;

    static inline int WIFI_BUTTON_X()
    {
        return 0;
    }
    static inline int WIFI_BUTTON_Y()
    {
        return 0;
    }
    static inline int WIFI_BUTTON_TEXT_WIFI_Y()
    {
        return VScale(wifiButtonTextWifiYRef);
    }
    static inline int WIFI_BUTTON_TEXT_SSID_X()
    {
        return HScale(wifiButtonTextSsidXRef);
    }
    static inline int WIFI_BUTTON_TEXT_SSID_Y()
    {
        return VScale(wifiButtonTextSsidYRef);
    }

    static inline int DhcpButtonX()
    {
        return dhcpButtonXRef;
    }
    static inline int DhcpButtonY()
    {
        return VScale(dhcpButtonYRef);
    }
    static inline int DhcpButtonTextDhcpY()
    {
        return VScale(dhcpButtonTextDhcpYRef);
    }
    static inline int DhcpButtonTextIpX()
    {
        return HScale(dhcpButtonTextIpXRef);
    }
    static inline int DhcpButtonTextIpY()
    {
        return VScale(dhcpButtonTextIpYRef);
    }

    static inline int APP_BUTTON_X()
    {
        return 0;
    }
    static inline int APP_BUTTON_Y()
    {
        return VScale(appButtonYRef);
    }

    static inline int DISPALY_BUTTON_X()
    {
        return 0;
    }
    static inline int DISPALY_BUTTON_Y()
    {
        return VScale(dispalyButtonYRef);
    }

    static inline int ABOUT_BUTTON_X()
    {
        return 0;
    }
    static inline int ABOUT_BUTTON_Y()
    {
        return VScale(aboutButtonYRef);
    }
    static inline int ABOUT_BUTTON_HEIGHT()
    {
        return VScale(aboutButtonHeightRef);
    }
    static inline int ABOUT_BUTTON_TEXT_ABOUT_Y()
    {
        return VScale(aboutButtonTextAboutYRef);
    }
    static inline int ABOUT_BUTTON_TEXT_SYSTEM_X()
    {
        return HScale(aboutButtonTextSystemXRef);
    }
    static inline int ABOUT_BUTTON_TEXT_SYSTEM_Y()
    {
        return VScale(aboutButtonTextSystemYRef);
    }
    static inline int ABOUT_BUTTON_TEXT_DEVICE_X()
    {
        return HScale(aboutButtonTextDeviceXRef);
    }
    static inline int ABOUT_BUTTON_TEXT_DEVICE_Y()
    {
        return VScale(aboutButtonTextDeviceYRef);
    }
    static inline int ABOUT_BUTTON_IMAGE_Y()
    {
        return VScale(aboutButtonImageYRef);
    }
};
}

#endif // OHOS_MAIN_ABILITY_SLICE_H

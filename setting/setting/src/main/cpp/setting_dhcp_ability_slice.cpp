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

#include "setting_dhcp_ability_slice.h"
#include <iostream>
#include <thread>
#include "gfx_utils/style.h"
#include "dhcp_lite_c_client_api.h"
#include "parameter.h"

namespace OHOS {
REGISTER_AS(SettingDhcpAbilitySlice)
int g_dhcpStatus = 0;
char g_dhcpIp[64] = {0};

void OnIpSuccessChanged(int status, const char *ifname, DhcpResult *result)
{
    printf("OnIpSuccessChanged, status = %d, ifname = %s, result ip= %s\n", status, ifname, result->strOptClientId);
    if (result != nullptr && result->strOptClientId != nullptr && ifname != nullptr) {
        if (strncmp(ifname, "eth", strlen("eth")) == 0) {
            (void)strcpy_s(g_dhcpIp, sizeof(g_dhcpIp), result->strOptClientId);
        }
    }
}

void OnIpFailChanged(int status, const char *ifname, const char *reason)
{
    printf("OnIpFailChanged, status = %d, ifname = %s, reason = %s\n", status, ifname, reason);
}

ClientCallBack g_callback = {
    OnIpSuccessChanged,
    OnIpFailChanged,
};

bool DhcpBtnOnStateChangeListener::OnClick(UIView& view, const ClickEvent& event)
{
    int result = 0;
    bool ret = myUiView->IsVisible();
    if (ret == false) {
        myUiView->SetVisible(true);
        int registerResult = RegisterDhcpClientCallBack("eth0", &g_callback);
        if (registerResult != DHCP_SUCCESS) {
            printf("RegisterDhcpClientCallBack failed, ret = %d\n", registerResult);
        }
        RouterConfig config = {0};
        if (strcpy_s(config.ifname, sizeof(config.ifname), "eth0") != EOK) {
            printf("strcpy_s ifname failed\n");
            return false;
        }
        result = StartDhcpClient(config);
        if (result != DHCP_SUCCESS) {
            printf("StartDhcpClient failed, ret = %d\n", result);
            g_dhcpStatus = 0;
        } else {
            g_dhcpStatus = 1;
        }
    } else {
        myUiView->SetVisible(false);
        result = StopDhcpClient("eth0", false);
        if (result != DHCP_SUCCESS) {
            printf("StopDhcpClient failed, ret = %d\n", result);
            g_dhcpStatus = 1;
        } else {
            g_dhcpStatus = 0;
        }
    }
    // Persist DHCP state across reboot
    SetParameter("persist.dhcp.enable", (g_dhcpStatus != 0) ? "1" : "0");
    myUiView->Invalidate();
    return true;
}

SettingDhcpAbilitySlice::SettingDhcpAbilitySlice()
    : headView_(nullptr), toggleButtonView_(nullptr), scrollView_(nullptr), rootView_(nullptr),
      changeListener_(nullptr), buttonBackListener_(nullptr)
{
    int taskPeriod = 5000;
    Task::Init();
    SetPeriod(taskPeriod);
}

SettingDhcpAbilitySlice::~SettingDhcpAbilitySlice()
{
    if (toggleButtonView_) {
        DeleteChildren(toggleButtonView_);
        toggleButtonView_ = nullptr;
    }

    if (scrollView_) {
        DeleteChildren(scrollView_);
        scrollView_ = nullptr;
    }

    if (headView_) {
        DeleteChildren(headView_);
        headView_ = nullptr;
    }

    if (changeListener_) {
        delete changeListener_;
        changeListener_ = nullptr;
    }

    if (buttonBackListener_) {
        delete buttonBackListener_;
        buttonBackListener_ = nullptr;
    }
}

void SettingDhcpAbilitySlice::SetButtonListener(void)
{
    auto onClick = [this](UIView& view, const Event& event) -> bool {
        Want want1 = { nullptr };
        AbilitySlice* nextSlice = AbilityLoader::GetInstance().GetAbilitySliceByName("MainAbilitySlice");
        if (nextSlice == nullptr) {
            printf("[warning]undefined SettingDhcpAbilitySlice\n");
        } else {
            Present(*nextSlice, want1);
        }
        return true;
    };
    buttonBackListener_ = new EventListener(onClick, nullptr);
}

void SettingDhcpAbilitySlice::SetHead(void)
{
    headView_ = new UIViewGroup();
    rootView_->Add(headView_);
    headView_->SetPosition(DE_HEAD_X, DE_HEAD_Y, DE_HEAD_WIDTH, DE_HEAD_HEIGHT);
    headView_->SetStyle(STYLE_BACKGROUND_OPA, 0);
    headView_->SetTouchable(true);
    headView_->SetOnClickListener(buttonBackListener_);

    UIImageView* imageView = new UIImageView();
    headView_->Add(imageView);
    imageView->SetPosition(DE_HEAD_IMAGE_X, DE_HEAD_IMAGE_Y, DE_HEAD_IMAGE_WIDTH, DE_HEAD_IMAGE_HEIGHT);
    imageView->SetAutoEnable(false);
    imageView->SetResizeMode(UIImageView::ImageResizeMode::CONTAIN);
    imageView->SetSrc(DE_IMAGE_BACK);

    UILabel* lablelFont = new UILabel();
    lablelFont->SetPosition(DE_HEAD_TEXT_X, DE_HEAD_TEXT_Y, DE_HEAD_TEXT_WIDTH, DE_HEAD_TEXT_HEIGHT);
    lablelFont->SetText("DHCP");
    lablelFont->SetFont(DE_FONT_OTF, DE_HEAD_TEXT_SIZE);
    lablelFont->SetStyle(STYLE_TEXT_COLOR, DE_HEAD_TEXT_COLOR);
    headView_->Add(lablelFont);
}

void SettingDhcpAbilitySlice::SetToggleButton(void)
{
    toggleButtonView_ = new UIViewGroup();
    toggleButtonView_->SetPosition(ToggleX(), ToggleY(), DE_BUTTON_WIDTH, DE_BUTTON_HEIGHT);
    toggleButtonView_->SetStyle(STYLE_BACKGROUND_COLOR, DE_BUTTON_BACKGROUND_COLOR);
    toggleButtonView_->SetStyle(STYLE_BACKGROUND_OPA, DE_OPACITY_ALL);
    toggleButtonView_->SetStyle(STYLE_BORDER_RADIUS, DE_BUTTON_RADIUS);
    rootView_->Add(toggleButtonView_);

    auto lablelFont = new UILabel();
    lablelFont->SetPosition(DE_TITLE_TEXT_X, DE_TITLE_TEXT_Y, DE_TITLE_TEXT_WIDTH, DE_TITLE_TEXT_HEIGHT);
    lablelFont->SetText("DHCP");
    lablelFont->SetFont(DE_FONT_OTF, DE_TITLE_TEXT_SIZE);
    lablelFont->SetStyle(STYLE_TEXT_COLOR, DE_TITLE_TEXT_COLOR);
    toggleButtonView_->Add(lablelFont);

    UIToggleButton* togglebutton = new UIToggleButton();
    changeListener_ = new DhcpBtnOnStateChangeListener(reinterpret_cast<UIView*>(scrollView_));
    togglebutton->SetOnClickListener(changeListener_);
    togglebutton->SetPosition(DE_TOGGLE_BUTTON_X, DE_TOGGLE_BUTTON_Y, DE_TOGGLE_BUTTON_WIDTH, DE_TOGGLE_BUTTON_HEIGHT);
    togglebutton->SetState(g_dhcpStatus != 0);
    scrollView_->SetVisible(g_dhcpStatus != 0);

    toggleButtonView_->Add(togglebutton);
}

void SettingDhcpAbilitySlice::SetUseDhcp(void)
{
    UILabel* lablelFont = new UILabel();
    lablelFont->SetPosition(UseDhcpFontX(), UseDhcpFontY(), DE_TITLE_TEXT_WIDTH, DE_TITLE_TEXT_HEIGHT);
    lablelFont->SetText("DHCP信息");
    lablelFont->SetFont(DE_FONT_OTF, DE_TITLE_TEXT_SIZE);
    lablelFont->SetStyle(STYLE_TEXT_COLOR, DE_SUBTITLE_TEXT_COLOR);
    rootView_->Add(lablelFont);
}

void SettingDhcpAbilitySlice::SetScrollDhcp(void)
{
    scrollView_ = new UIScrollView();
    scrollView_->SetStyle(STYLE_BACKGROUND_COLOR, DE_SCROLL_COLOR);
    scrollView_->SetPosition(ScrollDhcpX(), ScrollDhcpY(), ScrollDhcpWidth(), ScrollDhcpHeight());
    scrollView_->SetXScrollBarVisible(false);
    scrollView_->SetYScrollBarVisible(false);
    rootView_->Add(scrollView_);
}

void SettingDhcpAbilitySlice::Callback()
{
}

void SettingDhcpAbilitySlice::OnStart(const Want& want)
{
    AbilitySlice::OnStart(want);
    rootView_ = RootView::GetWindowRootView();
    rootView_->SetPosition(DE_ROOT_X, DE_ROOT_Y, DE_ROOT_WIDTH, DE_ROOT_HEIGHT);
    rootView_->Resize(DE_ROOT_WIDTH, DE_ROOT_HEIGHT);
    rootView_->SetStyle(STYLE_BACKGROUND_COLOR, DE_ROOT_BACKGROUND_COLOR);

    // Restore DHCP state from persistent parameter
    char dhcpEnable[8] = {0};
    GetParameter("persist.dhcp.enable", "0", dhcpEnable, sizeof(dhcpEnable));
    if (strcmp(dhcpEnable, "1") == 0) {
        g_dhcpStatus = 1;
    } else {
        g_dhcpStatus = 0;
    }

    SetButtonListener();
    SetHead();
    SetScrollDhcp();
    SetToggleButton();

    // Auto-start DHCP if it was enabled before reboot
    if (g_dhcpStatus != 0) {
        RegisterDhcpClientCallBack("eth0", &g_callback);
        RouterConfig config = {0};
        strcpy_s(config.ifname, sizeof(config.ifname), "eth0");
        int ret = StartDhcpClient(config);
        if (ret != DHCP_SUCCESS) {
            printf("Auto-start DHCP failed, ret = %d\n", ret);
            g_dhcpStatus = 0;
        }
    }

    TaskExecute();
    SetUIContent(rootView_);
}

void SettingDhcpAbilitySlice::OnInactive()
{
    AbilitySlice::OnInactive();
}

void SettingDhcpAbilitySlice::OnActive(const Want& want)
{
    AbilitySlice::OnActive(want);
}

void SettingDhcpAbilitySlice::OnBackground()
{
    AbilitySlice::OnBackground();
}

void SettingDhcpAbilitySlice::OnStop()
{
    AbilitySlice::OnStop();
}
} // namespace OHOS

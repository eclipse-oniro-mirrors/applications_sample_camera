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

#ifndef BUTTON_RM_CASE_VIEW_H
#define BUTTON_RM_CASE_VIEW_H

#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_view_group.h"
#include "graphic_config.h"
#include "rm_test_utils.h"

namespace OHOS {
#if GRAPHIC_ENABLE_BUTTON_FLAG

enum ButtonRmCaseType : uint8_t {
    BUTTON_CASE_DEMO,
    BUTTON_CASE_INTERRUPT,
    BUTTON_CASE_STRESS_CLICK,
    BUTTON_CASE_STRESS_MANY,
    BUTTON_CASE_STRESS_CONFIG,
    BUTTON_CASE_STRESS_ENABLE,
};

struct ButtonRmCase {
    const char* id;
    const char* name;
    const char* expect;
    ButtonRmCaseType type;
    bool isHotZone;
    bool adjacent;
    bool useDefaults;
    bool invalidEffect;
    uint16_t repeatCount;
    UIButton::ButtonAnimationEffect effect;
    int16_t expandL;
    int16_t expandT;
    int16_t expandR;
    int16_t expandB;
    bool disabled;
};

extern const ButtonRmCase g_buttonRmCases[];
extern const uint32_t g_buttonRmCaseNum;

/**
 * @brief Button RM 单个用例的视图构建与清理器。
 *
 * Build() 在 content 内部创建并返回用例容器；析构时先剥离监听器再删除容器子树。
 */
class ButtonRmCaseRunner {
public:
    explicit ButtonRmCaseRunner(const ButtonRmCase* testCase);
    ~ButtonRmCaseRunner();

    UIViewGroup* Build(UIViewGroup* content);

private:
    void ResetState();
    UILabelButton* CreateDemoButton();
    void ShowDemoCase();
    void ShowInterruptCase();
    void ShowStressCase();
    void ShowManyButtonsCase();
    void CreateDemoAdjacentButton();
    void CreateDemoCountLabel();
    void CreateManyButton(uint32_t index, uint32_t& passCount);
    void RunStressStep(UILabelButton* btn, RmStressDriver* driver, ButtonRmCaseType type,
                       UILabelButton* toggleBtn, uint32_t iter);
    void RunStressClickStep(UILabelButton* btn, RmStressDriver* driver, UILabelButton* toggleBtn,
                            uint32_t iter);
    void RunStressConfigStep(UILabelButton* btn, RmStressDriver* driver, UILabelButton* toggleBtn,
                             uint32_t iter);
    void RunStressEnableStep(UILabelButton* btn, RmStressDriver* driver, UILabelButton* toggleBtn,
                             uint32_t iter);
    void FinishStressClick(UILabelButton* btn, RmStressDriver* driver, UILabelButton* toggleBtn);
    void FinishStressConfig(UILabelButton* btn, RmStressDriver* driver, UILabelButton* toggleBtn);
    void FinishStressEnable(UILabelButton* btn, RmStressDriver* driver, UILabelButton* toggleBtn);
    void OnStressToggleClick(UILabelButton* btn, RmStressDriver* driver, ButtonRmCaseType type,
                             UILabelButton* toggleBtn);
    void AddClickListener(UIView* view, std::function<bool(UIView&, const ClickEvent&)> fn);
    void SetInfoText(const char* text);
    void RefreshCount();

    struct ListenerEntry {
        UIView* view;
        RmClickListener* listener;
    };
    static constexpr uint8_t MAX_LISTENERS = 128;

    const ButtonRmCase* case_;
    UIViewGroup* container_;
    UILabel* countLabel_;
    UILabel* infoLabel_;
    uint32_t demoClickCount_;
    uint32_t demoOutsideCount_;
    uint32_t adjacentClickCount_;
    uint32_t stressPassCount_;
    uint32_t stressFailCount_;
    uint32_t distinctHitCount_;
    bool manyHitFlags_[100];
    bool currentIsHotZone_;
    bool currentHasAdjacent_;
    ListenerEntry listeners_[MAX_LISTENERS];
    uint8_t listenerCount_;
};

#endif // GRAPHIC_ENABLE_BUTTON_FLAG
} // namespace OHOS
#endif // BUTTON_RM_CASE_VIEW_H

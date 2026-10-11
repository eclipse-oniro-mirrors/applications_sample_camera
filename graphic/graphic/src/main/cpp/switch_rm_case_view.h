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

#ifndef SWITCH_RM_CASE_VIEW_H
#define SWITCH_RM_CASE_VIEW_H

#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_toggle_button.h"
#include "components/ui_view_group.h"
#include "graphic_config.h"
#include "rm_test_utils.h"

namespace OHOS {
#if GRAPHIC_ENABLE_SWITCH_FLAG

enum SwitchRmCaseType : uint8_t {
    SWITCH_CASE_DEMO,
    SWITCH_CASE_VERIFY_GETTER,
    SWITCH_CASE_STRESS_TOGGLE,
    SWITCH_CASE_MANY,
    SWITCH_CASE_STRESS_STATE,
    SWITCH_CASE_STRESS_CONFIG,
};

struct SwitchRmCase {
    const char* id;
    const char* name;
    const char* expect;
    SwitchRmCaseType type;
    bool setOnSize;
    int16_t onSize;
    bool setOffSize;
    int16_t offSize;
    bool setOnThumb;
    uint32_t onThumb;
    bool setOffThumb;
    uint32_t offThumb;
    bool setOnBorder;
    uint32_t onBorder;
    bool setOffBorder;
    uint32_t offBorder;
    bool initialOn;
};

extern const SwitchRmCase g_switchRmCases[];
extern const uint32_t g_switchRmCaseNum;

/**
 * @brief Switch RM 单个用例的视图构建与清理器。
 *
 * Build() 在 content 内部创建并返回用例容器；析构时先剥离监听器再删除容器子树。
 */
class SwitchRmCaseRunner {
public:
    explicit SwitchRmCaseRunner(const SwitchRmCase* testCase);
    ~SwitchRmCaseRunner();

    UIViewGroup* Build(UIViewGroup* content);

private:
    void ResetState();
    UIToggleButton* CreateDemoToggle();
    void ShowDemoCase();
    void ShowVerifyCase();
    void ShowStressCase();
    void RunStressToggle(uint32_t iter, uint32_t done, UIToggleButton* toggle,
                         RmStressDriver* driver, UILabelButton* toggleBtn);
    void RunStressState(uint32_t iter, uint32_t done, UIToggleButton* toggle,
                        RmStressDriver* driver, UILabelButton* toggleBtn);
    void RunStressConfig(uint32_t iter, uint32_t done, UIToggleButton* toggle,
                         RmStressDriver* driver, UILabelButton* toggleBtn,
                         UILabel* setLabel, UILabel* stateLabel);
    void ReportStressConfig(uint32_t done, int16_t on, int16_t off,
                            uint32_t onC, uint32_t offC, uint32_t onB, uint32_t offB,
                            UIToggleButton* toggle, UILabel* setLabel, UILabel* stateLabel);
    void ShowManyCase();
    UILabelButton* CreateStressToggleButton();
    void CreateStressLabels(UIToggleButton* toggle, UILabel*& infoLabel,
                            UILabel*& stateLabel, UILabel*& setLabel);
    void BindStressStepHandler(RmStressDriver* driver, UIToggleButton* toggle,
                               SwitchRmCaseType type, UILabel* setLabel,
                               UILabel* stateLabel, UILabelButton* toggleBtn);
    void BindStressToggleClick(RmStressDriver* driver, UILabelButton* toggleBtn);
    void SetInfoText(const char* text);
    void AddClickListener(UIView* view, std::function<bool(UIView&, const ClickEvent&)> fn);
    void CreateTitleLabel();
    void CreateManySummaryLabels(uint32_t created, uint32_t colorPass, uint32_t sizePass);

    class SwitchStateListener;

    struct ListenerEntry {
        UIView* view;
        RmClickListener* listener;
    };
    static constexpr uint8_t MAX_LISTENERS = 128;

    const SwitchRmCase* case_;
    UIViewGroup* container_;
    UILabel* countLabel_;
    UILabel* infoLabel_;
    UIToggleButton* toggle_;
    SwitchStateListener* changeListener_;
    uint32_t changeCount_;
    uint32_t stressPassCount_;
    uint32_t stressFailCount_;
    ListenerEntry listeners_[MAX_LISTENERS];
    uint8_t listenerCount_;
};

#endif // GRAPHIC_ENABLE_SWITCH_FLAG
} // namespace OHOS
#endif // SWITCH_RM_CASE_VIEW_H

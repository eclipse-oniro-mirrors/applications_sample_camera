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

#ifndef SCROLLER_RM_CASE_VIEW_H
#define SCROLLER_RM_CASE_VIEW_H

#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_scroll_view.h"
#include "components/ui_view_group.h"
#include "components/ui_arc_scroll_bar.h"
#include "graphic_config.h"
#include "rm_test_utils.h"

namespace OHOS {
#if GRAPHIC_ENABLE_SCROLL_FLAG

enum ScrollerRmCaseType : uint8_t {
    SC_CASE_DEMO,
    SC_CASE_RESET,
    SC_CASE_LATE_VISIBLE,
    SC_CASE_UPDATE,
    SC_CASE_PLACEHOLDER,
    SC_CASE_MANY_ITEMS,
    SC_CASE_STRESS_UPDATE,
    SC_CASE_STRESS_SCROLL,
    SC_CASE_XY_SCROLL,
};

struct ScrollerRmCase {
    const char* id;
    const char* name;
    const char* expect;
    ScrollerRmCaseType type;
    bool wholeStyle;
    bool setWidth;
    uint16_t width;
    bool setColor;
    uint32_t colorRgb;
    bool setRadius;
    uint16_t radius;
    bool setMinLen;
    uint16_t minLen;
    bool setOpa;
    uint8_t opacity;
    bool longContent;
    bool smallViewport;
    bool hScroll;
};

extern const ScrollerRmCase g_scrollerRmCases[];
extern const uint32_t g_scrollerRmCaseNum;

/**
 * @brief 测试用 UIScrollView：暴露 GetAllChildRelativeRect 给 ArcScrollBarHostView 使用。
 */
class TestUIScrollView : public UIScrollView {
public:
    Rect GetAllChildRelativeRect() const
    {
        return UIViewGroup::GetAllChildRelativeRect();
    }
};

/**
 * @brief 老代码路径对照用 UIArcScrollBar：把受保护的轨道线宽暴露给测试侧。
 */
class LegacyTrackArcScrollBar : public UIArcScrollBar {
public:
    void SetTrackLineWidth(int16_t width)
    {
        backgroundStyle_->lineWidth_ = width;
    }
};

/**
 * @brief 矩形屏下承载 UIArcScrollBar 的宿主视图，并同步目标 UIScrollView 的滚动位置。
 */
class ArcScrollBarHostView : public UIView, public AnimatorCallback {
public:
    ArcScrollBarHostView();
    ~ArcScrollBarHostView() override;

    void InitArcScrollBar();
    void InitArcScrollBarLegacy();
    UIArcScrollBar* GetArcBar() const;
    void BindScrollView(TestUIScrollView* scroll);

    void Callback(UIView* view) override;

protected:
    void OnDraw(BufferInfo& gfxDstBuffer, const Rect& invalidatedArea) override;

private:
    UIArcScrollBar* arcBar_;
    TestUIScrollView* targetScroll_;
    Animator animator_;
};

/**
 * @brief Scroller RM 单个用例的视图构建与清理器。
 */
class ScrollerRmCaseRunner {
public:
    explicit ScrollerRmCaseRunner(const ScrollerRmCase* testCase);
    ~ScrollerRmCaseRunner();

    UIViewGroup* Build(UIViewGroup* content);

private:
    static constexpr uint32_t READBACK_LINES = 2;
    static constexpr uint32_t CFG_LINES = 2;

    UIScrollView* CreateDemoScroll();
    void CreateCompareScroll();
    void CreateConfigLabels();
    void CreateReadbackLabels();
    void RefreshReadback();
    void ApplyCaseStyle(UIScrollView* scroll);
    void SetStatusText(const char* text);
    void AddClickListener(UIView* view, std::function<bool(UIView&, const ClickEvent&)> fn);

    void ShowCase();
    void ShowResetCase();
    void ShowLateVisibleCase();
    void ShowUpdateCase();
    void ShowPlaceholderCase();
    void ShowStressUpdateCase();
    void ShowStressScrollCase();

    void ShowDemoLikeCase();
    void OnStressUpdateStep(uint32_t iter, UIScrollView* scroll, RmStressDriver* driver, UILabelButton* toggleBtn);
    void OnStressScrollStep(uint32_t iter, UIScrollView* scroll, RmStressDriver* driver, UILabelButton* toggleBtn);
    bool OnStressToggle(RmStressDriver* driver, UILabelButton* toggleBtn, UIView& view, const ClickEvent& event);
    void CreatePlaceholderInfoLabels();
    TestUIScrollView* CreatePlaceholderScroll(int16_t contentY, int16_t listW, int16_t hostH);
    void CreatePlaceholderReadback(ArcScrollBarHostView* testHost, int16_t bottomY);

    static constexpr uint8_t MAX_LISTENERS = 8;

    const ScrollerRmCase* case_;
    UIViewGroup* container_;
    UIScrollView* demoScroll_;
    UILabel* cfgLabels_[CFG_LINES];
    UILabel* readbackLabels_[READBACK_LINES];
    UILabel* statusLabel_;
    uint32_t updateCount_;

    struct ListenerEntry {
        UIView* view;
        RmClickListener* listener;
    };
    ListenerEntry listeners_[MAX_LISTENERS];
    uint8_t listenerCount_;
};

#endif // GRAPHIC_ENABLE_SCROLL_FLAG
} // namespace OHOS
#endif // SCROLLER_RM_CASE_VIEW_H

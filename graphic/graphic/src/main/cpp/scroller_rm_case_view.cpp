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

#include "scroller_rm_case_view.h"

#if GRAPHIC_ENABLE_SCROLL_FLAG
#include <cstdio>
#include <new>
#include "components/ui_view_group.h"
#include "events/click_event.h"
#include "graphic_utils.h"
#include "securec.h"

namespace OHOS {

namespace {
constexpr uint32_t SC_RGB_RED = 0xFF0000;
constexpr uint32_t SC_RGB_GREEN = 0x00C850;
constexpr uint32_t SC_RGB_BLUE = 0x0080FF;
constexpr uint32_t SC_RGB_YELLOW = 0xFFD700;
constexpr uint32_t SC_RGB_CYAN = 0x00C8C8;

constexpr int16_t CONT_X = 100;
constexpr int16_t CONT_Y = 0;
constexpr int16_t CONT_W = 760;
constexpr int16_t CONT_H = 400;
constexpr uint8_t CONT_RADIUS = 16;

constexpr uint8_t HINT_SIZE = 20;
constexpr int16_t HINT_X = 24;
constexpr int16_t HINT_Y = 340;
constexpr int16_t HINT_W = 712;
constexpr int16_t HINT_H = 44;

constexpr int16_t TITLE_X = 24;
constexpr int16_t TITLE_Y = 4;
constexpr int16_t TITLE_W = 712;
constexpr uint8_t TITLE_H = 26;
constexpr uint8_t TITLE_FONT = 20;
constexpr uint8_t ACTION_BTN_FONT = 22;

constexpr int16_t SC_VIEW_X = 24;
constexpr int16_t SC_TAG_Y = 52;
constexpr int16_t SC_VIEW_Y = 76;
constexpr int16_t SC_VIEW_W = 296;
constexpr int16_t SC_VIEW_H = 240;
constexpr int16_t SC_VIEW_SMALL_H = 120;
constexpr int16_t SC_CMP_X = 332;
constexpr int16_t SC_CMP_W = 124;
constexpr int16_t SC_ITEM_H = 30;
constexpr int16_t SC_ITEM_W = 280;
constexpr int16_t SC_CMP_ITEM_W = 112;
constexpr int16_t SC_ITEM_WIDE_W = 700;
constexpr int16_t SC_SIDE_X = 480;
constexpr int16_t SC_SIDE_W = 256;
constexpr int16_t SC_CFG_Y = 52;
constexpr int16_t SC_READBACK_Y = 108;
constexpr int16_t SC_LINE_GAP = 26;
constexpr int16_t SC_ACTION_X = 500;
constexpr int16_t SC_ACTION_Y = 210;
constexpr int16_t SC_ACTION_W = 150;
constexpr int16_t SC_ACTION_H = 44;
constexpr int16_t SC_STATUS_Y = 270;
constexpr int16_t SC_PLACE_TEXT_X = 40;

constexpr uint32_t SC_UPDATE_TARGET = 1000;
constexpr uint32_t SC_SCROLL_TARGET = 2000;
constexpr uint32_t SC_MANY_ITEMS = 1000;
constexpr uint32_t SC_LONG_ITEMS = 200;
constexpr uint32_t SC_NORMAL_ITEMS = 15;

constexpr uint8_t SC_RGB_RED_SHIFT = 16;
constexpr uint8_t SC_RGB_GREEN_SHIFT = 8;
constexpr uint16_t SC_ANIMATOR_INTERVAL = 16;
constexpr int16_t SC_LABEL_X = 24;
constexpr int16_t SC_LABEL_RIGHT_X = 390;
constexpr int16_t SC_LABEL_W = 350;
constexpr int16_t SC_ARC_ITEM_W = 280;
constexpr int16_t SC_STATUS_H = 60;
constexpr uint8_t SC_BTN_BORDER_RADIUS = 8;
constexpr uint8_t SC_ARC_BAR_WIDTH = 6;
constexpr uint16_t SC_ARC_BAR_MIN_LEN = 10;
constexpr uint8_t SC_OPA_OPAQUE = 255;
constexpr uint8_t SC_OPA_HALF = 128;
constexpr int16_t SC_ARC_HOST_MARGIN = 20;
constexpr uint8_t SC_HALF_HEIGHT_DIVISOR = 2;
constexpr uint8_t SC_PARITY_MOD = 2;
constexpr uint8_t SC_COLOR_COUNT = 3;
constexpr uint32_t SC_STRESS_STATUS_INTERVAL = 50;
constexpr uint16_t SC_UPDATE_INDICATOR_WIDTH = 10;
constexpr uint8_t SC_STRESS_WIDTH_MIN = 4;
constexpr uint16_t SC_STRESS_WIDTH_MAX = 10;
constexpr int16_t SC_PLACE_CONTENT_Y_OFFSET = 8;
constexpr int16_t SC_PLACE_TEXT_W = CONT_W - SC_PLACE_TEXT_X * 2;

ColorType RgbToColor(uint32_t rgb)
{
    return Color::GetColorFromRGB((rgb >> SC_RGB_RED_SHIFT) & 0xFF,
                                  (rgb >> SC_RGB_GREEN_SHIFT) & 0xFF,
                                  rgb & 0xFF);
}

void BuildCfgText(const ScrollerRmCase& testCase, char* line1, char* line2, uint32_t bufSize)
{
    line2[0] = '\0';
    if (!testCase.setWidth && !testCase.setColor && !testCase.setRadius && !testCase.setMinLen &&
        !testCase.setOpa) {
        (void)snprintf_s(line1, bufSize, bufSize - 1, "配置: 默认(不调新接口)");
        return;
    }
    int32_t len = snprintf_s(line1, bufSize, bufSize - 1, "配置");
    if (testCase.setWidth) {
        len += snprintf_s(line1 + len, bufSize - len, bufSize - len - 1, " w=%u", testCase.width);
    }
    if (testCase.setMinLen) {
        len += snprintf_s(line1 + len, bufSize - len, bufSize - len - 1, " min=%u", testCase.minLen);
    }
    if (testCase.setRadius) {
        len += snprintf_s(line1 + len, bufSize - len, bufSize - len - 1, " r=%u", testCase.radius);
    }
    int32_t len2 = 0;
    if (testCase.setOpa) {
        len2 += snprintf_s(line2 + len2, bufSize - len2, bufSize - len2 - 1, "opa=%u", testCase.opacity);
    }
    if (testCase.setColor) {
        len2 += snprintf_s(line2 + len2, bufSize - len2, bufSize - len2 - 1, "%s色=#%06X",
            (len2 > 0) ? " " : "", testCase.colorRgb);
    }
}
} // namespace

const ScrollerRmCase g_scrollerRmCases[] = {
    { "SC-001", "默认滚动条样式", "不配新接口:宽度/颜色/最小长度/透明度/淡入淡出与旧版一致",
      SC_CASE_DEMO, false, false, 0, false, 0, false, 0, false, 0, false, 0, false, false, false },
    { "SC-002", "整体SetIndicatorStyle", "width8/minLen30/radius4/绿/opa200整体生效;读回一致",
      SC_CASE_DEMO, true, true, 8, true, SC_RGB_GREEN, true, 4, true, 30, true, 200, false, false, false },
    { "SC-003", "width单项=8", "垂直/水平滚动条宽度均按8px显示",
      SC_CASE_DEMO, false, true, 8, false, 0, false, 0, false, 0, false, 0, false, false, true },
    { "SC-004", "color单项=红", "滑块显示红色;轨道背景颜色不被改变",
      SC_CASE_DEMO, false, false, 0, true, SC_RGB_RED, false, 0, false, 0, false, 0, false, false, false },
    { "SC-005", "borderRadius=4", "矩形滑块显示圆角;滚动和淡入淡出行为不变",
      SC_CASE_DEMO, false, false, 0, false, 0, true, 4, false, 0, false, 0, false, false, false },
    { "SC-006", "minLength=30长内容", "滑块长度不小于30px,且不超滚动条背景区域长度",
      SC_CASE_DEMO, false, false, 0, false, 0, false, 0, true, 30, false, 0, true, false, false },
    { "SC-007", "opacity=128", "滑块半透明;轨道背景透明度保持默认;无二次默认衰减",
      SC_CASE_DEMO, false, false, 0, false, 0, false, 0, false, 0, true, 128, false, false, false },
    { "SC-008", "ResetIndicatorStyle恢复默认", "先确认自定义样式生效;点重置后恢复默认(读回验证)",
      SC_CASE_RESET, true, true, 10, true, SC_RGB_YELLOW, true, 6, true, 40, true, 255, false, false, false },
    { "SC-009", "width=0边界", "恢复默认宽度(读回验证)+告警;滚动条不消失不崩溃",
      SC_CASE_DEMO, false, true, 0, false, 0, false, 0, false, 0, false, 0, false, false, false },
    { "SC-010", "minLength=0边界", "恢复默认最小长度(读回验证)+告警;滚动条正常绘制",
      SC_CASE_DEMO, false, false, 0, false, 0, false, 0, true, 0, false, 0, true, false, false },
    { "SC-011", "opacity=0边界", "滑块完全透明;轨道背景仍按默认透明度显示;滚动不受影响",
      SC_CASE_DEMO, false, false, 0, false, 0, false, 0, false, 0, true, 0, false, false, false },
    { "SC-012", "opacity=255边界", "滑块完全不透明;未发生默认前景透明度二次衰减",
      SC_CASE_DEMO, false, false, 0, false, 0, false, 0, false, 0, true, 255, false, false, false },
    { "SC-013", "minLength=999小视口", "滑块长度不超滚动条背景长度;无越界绘制",
      SC_CASE_DEMO, false, false, 0, false, 0, false, 0, true, 999, false, 0, false, true, false },
    { "SC-014", "矩形屏实例化弧形滚动条", "直接new UIArcScrollBar,红/宽6/opa255;与老路径(白/轨道同窄6)同屏对照",
      SC_CASE_PLACEHOLDER, false, true, 6, true, SC_RGB_RED, false, 0, true, 10, true, 255, false, false, false },
    { "SC-015", "滚动条创建前配样式", "隐藏时配样式;开启滚动条后自动同步,无需重复设置",
      SC_CASE_LATE_VISIBLE, false, true, 10, true, SC_RGB_YELLOW, false, 0, false, 0, true, 255,
      false, false, false },
    { "SC-016", "滚动条创建后更新样式", "先拖动观察;点更新后颜色/宽度/透明度立即生效,布局不变",
      SC_CASE_UPDATE, false, false, 0, false, 0, false, 0, false, 0, false, 0, false, false, false },
    { "SC-017", "非法组合w0+minLen0+opa0", "宽度/最小长度恢复默认(读回验证);透明度0生效;不崩溃",
      SC_CASE_DEMO, false, true, 0, false, 0, false, 0, true, 0, true, 0, true, false, false },
    { "SC-018", "1000子项滚动性能", "1000子项快速拖动;滚动条位置刷新正确;无明显卡顿",
      SC_CASE_MANY_ITEMS, true, true, 6, true, SC_RGB_CYAN, true, 0, true, 20, true, 200,
      true, false, false },
    { "SC-019", "高频样式更新x1000", "自动循环更新颜色/宽度/透明度1000次;稳定生效无异常",
      SC_CASE_STRESS_UPDATE, false, false, 0, false, 0, false, 0, false, 0, false, 0,
      false, false, false },
    { "SC-020", "长稳滚动淡入淡出", "opacity=128;自动往返滚动2000步(替代30分钟);淡入淡出无异常",
      SC_CASE_STRESS_SCROLL, false, false, 0, false, 0, false, 0, false, 0, true, 128,
      true, false, false },
    { "SC-021", "横纵滚动条组合", "X/Y滚动条同时开启;样式均正确;交替横纵拖动无样式串扰",
      SC_CASE_XY_SCROLL, true, true, 8, true, SC_RGB_GREEN, true, 4, true, 30, true, 220,
      false, false, true },
};
const uint32_t g_scrollerRmCaseNum = sizeof(g_scrollerRmCases) / sizeof(g_scrollerRmCases[0]);

// ArcScrollBarHostView
ArcScrollBarHostView::ArcScrollBarHostView()
    : arcBar_(nullptr), targetScroll_(nullptr), animator_(this, this, SC_ANIMATOR_INTERVAL, true) {}

ArcScrollBarHostView::~ArcScrollBarHostView()
{
    animator_.Stop();
    if (arcBar_ != nullptr) {
        delete arcBar_;
        arcBar_ = nullptr;
    }
}

void ArcScrollBarHostView::InitArcScrollBar()
{
    if (arcBar_ != nullptr) {
        delete arcBar_;
        arcBar_ = nullptr;
    }
    arcBar_ = new (std::nothrow) UIArcScrollBar();
    if (arcBar_ == nullptr) {
        return;
    }
    arcBar_->SetIndicatorWidth(SC_ARC_BAR_WIDTH);
    arcBar_->SetIndicatorColor(RgbToColor(SC_RGB_RED));
    arcBar_->SetIndicatorOpacity(SC_OPA_OPAQUE);
    arcBar_->SetIndicatorMinLength(SC_ARC_BAR_MIN_LEN);
}

void ArcScrollBarHostView::InitArcScrollBarLegacy()
{
    if (arcBar_ != nullptr) {
        delete arcBar_;
        arcBar_ = nullptr;
    }
    LegacyTrackArcScrollBar* bar = new (std::nothrow) LegacyTrackArcScrollBar();
    if (bar == nullptr) {
        return;
    }
    bar->SetTrackLineWidth(SC_ARC_BAR_WIDTH);
    arcBar_ = bar;
}

UIArcScrollBar* ArcScrollBarHostView::GetArcBar() const
{
    return arcBar_;
}

void ArcScrollBarHostView::BindScrollView(TestUIScrollView* scroll)
{
    targetScroll_ = scroll;
    if (targetScroll_ != nullptr) {
        animator_.Start();
    }
}

void ArcScrollBarHostView::Callback(UIView* view)
{
    (void)view;
    if (targetScroll_ == nullptr || arcBar_ == nullptr) {
        return;
    }
    Rect childrenRect = targetScroll_->GetAllChildRelativeRect();
    int16_t totalLen = childrenRect.GetHeight() + 2 * targetScroll_->GetScrollBlankSize();
    int16_t len = targetScroll_->GetHeight();
    if (totalLen > 0) {
        arcBar_->SetForegroundProportion(static_cast<float>(len) / totalLen);
        if (totalLen != len) {
            arcBar_->SetScrollProgress(static_cast<float>(targetScroll_->GetScrollBlankSize() - childrenRect.GetTop()) /
                                       (totalLen - len));
        }
    }
    Invalidate();
}

void ArcScrollBarHostView::OnDraw(BufferInfo& gfxDstBuffer, const Rect& invalidatedArea)
{
    UIView::OnDraw(gfxDstBuffer, invalidatedArea);
    if (arcBar_ != nullptr) {
        Rect rect = GetRect();
        arcBar_->SetPosition(rect.GetX() + SC_ARC_HOST_MARGIN,
                             rect.GetY() + rect.GetHeight() / SC_HALF_HEIGHT_DIVISOR,
                             SC_ARC_BAR_WIDTH,
                             rect.GetHeight() / SC_HALF_HEIGHT_DIVISOR - SC_ARC_HOST_MARGIN);
        arcBar_->OnDraw(gfxDstBuffer, invalidatedArea, GetMixOpaScale());
    }
}

// ScrollerRmCaseRunner
ScrollerRmCaseRunner::ScrollerRmCaseRunner(const ScrollerRmCase* testCase)
    : case_(testCase), container_(nullptr), demoScroll_(nullptr), statusLabel_(nullptr), updateCount_(0)
{
    for (uint32_t i = 0; i < READBACK_LINES; i++) {
        readbackLabels_[i] = nullptr;
    }
    for (uint32_t i = 0; i < CFG_LINES; i++) {
        cfgLabels_[i] = nullptr;
    }
    for (uint8_t i = 0; i < MAX_LISTENERS; i++) {
        listeners_[i].view = nullptr;
        listeners_[i].listener = nullptr;
    }
}

ScrollerRmCaseRunner::~ScrollerRmCaseRunner()
{
    for (uint8_t i = 0; i < listenerCount_; i++) {
        if (listeners_[i].view != nullptr) {
            listeners_[i].view->SetOnClickListener(nullptr);
        }
        delete listeners_[i].listener;
        listeners_[i].view = nullptr;
        listeners_[i].listener = nullptr;
    }
    listenerCount_ = 0;
    if (container_ != nullptr) {
        GraphicDeleteViewTree(container_);
        container_ = nullptr;
    }
    demoScroll_ = nullptr;
    statusLabel_ = nullptr;
    for (uint32_t i = 0; i < READBACK_LINES; i++) {
        readbackLabels_[i] = nullptr;
    }
    for (uint32_t i = 0; i < CFG_LINES; i++) {
        cfgLabels_[i] = nullptr;
    }
}

UIViewGroup* ScrollerRmCaseRunner::Build(UIViewGroup* content)
{
    if ((case_ == nullptr) || (container_ != nullptr) || (content == nullptr)) {
        return nullptr;
    }
    container_ = GraphicCreateView<UIViewGroup>(content);
    if (container_ == nullptr) {
        return nullptr;
    }
    container_->SetPosition(CONT_X, CONT_Y, CONT_W, CONT_H);
    container_->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x2A, 0x2A, 0x2A)));
    container_->SetStyle(STYLE_BORDER_RADIUS, CONT_RADIUS);
    container_->SetTouchable(true);

    demoScroll_ = nullptr;
    statusLabel_ = nullptr;
    for (uint32_t i = 0; i < READBACK_LINES; i++) {
        readbackLabels_[i] = nullptr;
    }
    for (uint32_t i = 0; i < CFG_LINES; i++) {
        cfgLabels_[i] = nullptr;
    }
    listenerCount_ = 0;
    updateCount_ = 0;

    ShowCase();

    char title[96];
    (void)snprintf_s(title, sizeof(title), sizeof(title) - 1, "%s %s", case_->id, case_->name);
    UILabel* titleLabel = GraphicCreateView<UILabel>(container_);
    if (titleLabel != nullptr) {
        titleLabel->SetPosition(TITLE_X, TITLE_Y, TITLE_W, TITLE_H);
        titleLabel->SetText(title);
        titleLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, TITLE_FONT);
        titleLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    }
    return container_;
}

void ScrollerRmCaseRunner::AddClickListener(UIView* view, std::function<bool(UIView&, const ClickEvent&)> fn)
{
    if ((view == nullptr) || (listenerCount_ >= MAX_LISTENERS)) {
        return;
    }
    RmClickListener* listener = new (std::nothrow) RmClickListener(std::move(fn));
    if (listener == nullptr) {
        return;
    }
    listeners_[listenerCount_].view = view;
    listeners_[listenerCount_].listener = listener;
    listenerCount_++;
    view->SetOnClickListener(listener);
}

void ScrollerRmCaseRunner::SetStatusText(const char* text)
{
    if (statusLabel_ != nullptr) {
        statusLabel_->SetText(text);
    }
}

UIScrollView* ScrollerRmCaseRunner::CreateDemoScroll()
{
    UILabel* tag = GraphicCreateView<UILabel>(container_);
    if (tag != nullptr) {
        tag->SetPosition(SC_VIEW_X, SC_TAG_Y, SC_VIEW_W, SC_LINE_GAP);
        tag->SetText("被测");
        tag->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        tag->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xCF, 0xCF, 0xCF)));
    }

    UIScrollView* scroll = GraphicCreateView<UIScrollView>(container_);
    if (scroll == nullptr) {
        return nullptr;
    }
    int16_t viewH = case_->smallViewport ? SC_VIEW_SMALL_H : SC_VIEW_H;
    scroll->SetPosition(SC_VIEW_X, SC_VIEW_Y, SC_VIEW_W, viewH);
    scroll->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x1A, 0x1A, 0x1A)));
    scroll->SetThrowDrag(true);

    uint32_t items = SC_NORMAL_ITEMS;
    if (case_->type == SC_CASE_MANY_ITEMS) {
        items = SC_MANY_ITEMS;
    } else if (case_->longContent) {
        items = SC_LONG_ITEMS;
    }
    int16_t itemW = case_->hScroll ? SC_ITEM_WIDE_W : SC_ITEM_W;
    for (uint32_t i = 0; i < items; i++) {
        UILabel* item = GraphicCreateView<UILabel>(scroll);
        if (item == nullptr) {
            continue;
        }
        item->SetPosition(0, static_cast<int16_t>(i * SC_ITEM_H), itemW, SC_ITEM_H);
        char text[32];
        (void)snprintf_s(text, sizeof(text), sizeof(text) - 1, "演示列表项 %04u", i + 1);
        item->SetText(text);
        item->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        item->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    }

    if (case_->type != SC_CASE_LATE_VISIBLE) {
        scroll->SetYScrollBarVisible(true);
        if (case_->hScroll) {
            scroll->SetXScrollBarVisible(true);
        }
    }
    demoScroll_ = scroll;
    return scroll;
}

void ScrollerRmCaseRunner::CreateCompareScroll()
{
    UILabel* tag = GraphicCreateView<UILabel>(container_);
    if (tag != nullptr) {
        tag->SetPosition(SC_CMP_X, SC_TAG_Y, SC_CMP_W, SC_LINE_GAP);
        tag->SetText("对照组");
        tag->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        tag->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xCF, 0xCF, 0xCF)));
    }

    UIScrollView* scroll = GraphicCreateView<UIScrollView>(container_);
    if (scroll == nullptr) {
        return;
    }
    int16_t viewH = case_->smallViewport ? SC_VIEW_SMALL_H : SC_VIEW_H;
    scroll->SetPosition(SC_CMP_X, SC_VIEW_Y, SC_CMP_W, viewH);
    scroll->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x1A, 0x1A, 0x1A)));
    scroll->SetThrowDrag(true);

    int16_t itemW = case_->hScroll ? SC_ITEM_WIDE_W : SC_CMP_ITEM_W;
    for (uint32_t i = 0; i < SC_NORMAL_ITEMS; i++) {
        UILabel* item = GraphicCreateView<UILabel>(scroll);
        if (item == nullptr) {
            continue;
        }
        item->SetPosition(0, static_cast<int16_t>(i * SC_ITEM_H), itemW, SC_ITEM_H);
        char text[16];
        (void)snprintf_s(text, sizeof(text), sizeof(text) - 1, "对照 %02u", i + 1);
        item->SetText(text);
        item->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        item->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    }
    scroll->SetYScrollBarVisible(true);
    if (case_->hScroll) {
        scroll->SetXScrollBarVisible(true);
    }
}

void ScrollerRmCaseRunner::CreateConfigLabels()
{
    char line1[96];
    char line2[96];
    if (case_->type == SC_CASE_STRESS_UPDATE) {
        (void)snprintf_s(line1, sizeof(line1), sizeof(line1) - 1, "配置: 压测循环改 色/宽/opa");
        line2[0] = '\0';
    } else {
        BuildCfgText(*case_, line1, line2, sizeof(line1));
    }
    const char* lines[CFG_LINES] = { line1, line2 };
    for (uint32_t i = 0; i < CFG_LINES; i++) {
        UILabel* line = GraphicCreateView<UILabel>(container_);
        if (line == nullptr) {
            continue;
        }
        line->SetPosition(SC_SIDE_X, SC_CFG_Y + i * SC_LINE_GAP, SC_SIDE_W, SC_LINE_GAP);
        line->SetText(lines[i]);
        line->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        line->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xCF, 0xCF, 0xCF)));
        cfgLabels_[i] = line;
    }
}

void ScrollerRmCaseRunner::ApplyCaseStyle(UIScrollView* scroll)
{
    if (case_->wholeStyle) {
        ScrollIndicatorStyle style = {};
        style.width = case_->width;
        style.minLength = case_->minLen;
        style.borderRadius = case_->radius;
        style.color = RgbToColor(case_->colorRgb);
        style.opacity = case_->opacity;
        scroll->SetIndicatorStyle(style);
        return;
    }
    if (case_->setWidth) {
        scroll->SetIndicatorWidth(case_->width);
    }
    if (case_->setColor) {
        scroll->SetIndicatorColor(RgbToColor(case_->colorRgb));
    }
    if (case_->setRadius) {
        scroll->SetIndicatorBorderRadius(case_->radius);
    }
    if (case_->setMinLen) {
        scroll->SetIndicatorMinLength(case_->minLen);
    }
    if (case_->setOpa) {
        scroll->SetIndicatorOpacity(case_->opacity);
    }
}

void ScrollerRmCaseRunner::CreateReadbackLabels()
{
    for (uint32_t i = 0; i < READBACK_LINES; i++) {
        UILabel* line = GraphicCreateView<UILabel>(container_);
        if (line == nullptr) {
            continue;
        }
        line->SetPosition(SC_SIDE_X, SC_READBACK_Y + i * SC_LINE_GAP, SC_SIDE_W, SC_LINE_GAP);
        line->SetText("-");
        line->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        line->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xFF, 0xD7, 0x00)));
        readbackLabels_[i] = line;
    }
}

void ScrollerRmCaseRunner::RefreshReadback()
{
    if (demoScroll_ == nullptr) {
        return;
    }
    ScrollIndicatorStyle cur = demoScroll_->GetIndicatorStyle();
    if (readbackLabels_[0] != nullptr) {
        char buf[64];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "读回 w=%u min=%u r=%u",
                         cur.width, cur.minLength, cur.borderRadius);
        readbackLabels_[0]->SetText(buf);
    }
    if (readbackLabels_[1] != nullptr) {
        char buf[48];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "opa=%u (色肉眼验)", cur.opacity);
        readbackLabels_[1]->SetText(buf);
    }
}

void ScrollerRmCaseRunner::ShowResetCase()
{
    UIScrollView* scroll = CreateDemoScroll();
    if (scroll == nullptr) {
        return;
    }
    ApplyCaseStyle(scroll);
    CreateCompareScroll();
    CreateConfigLabels();
    CreateReadbackLabels();
    RefreshReadback();

    UILabelButton* resetBtn = GraphicCreateView<UILabelButton>(container_);
    if (resetBtn == nullptr) {
        return;
    }
    resetBtn->SetPosition(SC_ACTION_X, SC_ACTION_Y, SC_ACTION_W, SC_ACTION_H);
    resetBtn->SetText("重置样式");
    resetBtn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, ACTION_BTN_FONT);
    resetBtn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    resetBtn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xC8, 0x50, 0x00)));
    resetBtn->SetStyle(STYLE_BORDER_RADIUS, SC_BTN_BORDER_RADIUS);
    resetBtn->SetTouchable(true);
    AddClickListener(resetBtn, [this, scroll](UIView& view, const ClickEvent& event) -> bool {
        (void)view;
        (void)event;
        scroll->ResetIndicatorStyle();
        RefreshReadback();
        if (cfgLabels_[0] != nullptr) {
            cfgLabels_[0]->SetText("配置: 已重置=默认");
        }
        if (cfgLabels_[1] != nullptr) {
            cfgLabels_[1]->SetText("");
        }
        SetStatusText("已重置: 恢复默认宽度/颜色/圆角/最小长度/透明度");
        return true;
    });
}

void ScrollerRmCaseRunner::ShowLateVisibleCase()
{
    UIScrollView* scroll = CreateDemoScroll();
    if (scroll == nullptr) {
        return;
    }
    ApplyCaseStyle(scroll);
    CreateCompareScroll();
    CreateConfigLabels();
    CreateReadbackLabels();
    RefreshReadback();

    UILabelButton* showBtn = GraphicCreateView<UILabelButton>(container_);
    if (showBtn == nullptr) {
        return;
    }
    showBtn->SetPosition(SC_ACTION_X, SC_ACTION_Y, SC_ACTION_W, SC_ACTION_H);
    showBtn->SetText("显示滚动条");
    showBtn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, ACTION_BTN_FONT);
    showBtn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    showBtn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x00, 0x80, 0xFF)));
    showBtn->SetStyle(STYLE_BORDER_RADIUS, SC_BTN_BORDER_RADIUS);
    showBtn->SetTouchable(true);
    AddClickListener(showBtn, [this, scroll](UIView& view, const ClickEvent& event) -> bool {
        (void)view;
        (void)event;
        scroll->SetYScrollBarVisible(true);
        scroll->Invalidate();
        SetStatusText("滚动条已创建: 样式应已自动同步,拖动观察");
        return true;
    });
}

void ScrollerRmCaseRunner::ShowUpdateCase()
{
    UIScrollView* scroll = CreateDemoScroll();
    if (scroll == nullptr) {
        return;
    }
    CreateCompareScroll();
    CreateConfigLabels();
    CreateReadbackLabels();
    RefreshReadback();

    UILabelButton* updateBtn = GraphicCreateView<UILabelButton>(container_);
    if (updateBtn == nullptr) {
        return;
    }
    updateBtn->SetPosition(SC_ACTION_X, SC_ACTION_Y, SC_ACTION_W, SC_ACTION_H);
    updateBtn->SetText("更新样式");
    updateBtn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, ACTION_BTN_FONT);
    updateBtn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    updateBtn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x00, 0x80, 0xFF)));
    updateBtn->SetStyle(STYLE_BORDER_RADIUS, SC_BTN_BORDER_RADIUS);
    updateBtn->SetTouchable(true);
    AddClickListener(updateBtn, [this, scroll](UIView& view, const ClickEvent& event) -> bool {
        (void)view;
        (void)event;
        scroll->SetIndicatorColor(RgbToColor(SC_RGB_GREEN));
        scroll->SetIndicatorWidth(SC_UPDATE_INDICATOR_WIDTH);
        scroll->SetIndicatorOpacity(SC_OPA_HALF);
        RefreshReadback();
        if (cfgLabels_[0] != nullptr) {
            char cfgText[64];
            (void)snprintf_s(cfgText, sizeof(cfgText), sizeof(cfgText) - 1, "配置 w=%u opa=%u",
                             SC_UPDATE_INDICATOR_WIDTH, SC_OPA_HALF);
            cfgLabels_[0]->SetText(cfgText);
        }
        if (cfgLabels_[1] != nullptr) {
            cfgLabels_[1]->SetText("色=#00C850(绿)");
        }
        char statusText[64];
        (void)snprintf_s(statusText, sizeof(statusText), sizeof(statusText) - 1, "已更新: 绿/宽%u/%s,立即重绘,布局不变",
                         SC_UPDATE_INDICATOR_WIDTH, "半透明");
        SetStatusText(statusText);
        return true;
    });
}

void ScrollerRmCaseRunner::CreatePlaceholderInfoLabels()
{
    const char* lines[] = {
        "SC-014 矩形屏实例化弧形滚动条(实时同步): 左侧拖动,右侧两个弧形同步变化。",
        "左=新API配置(红/宽6/opa255),右=老API默认样式(白/轨道同窄6),同屏对照显示。",
    };
    constexpr int16_t placeY = 34;
    for (uint32_t i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
        UILabel* line = GraphicCreateView<UILabel>(container_);
        if (line == nullptr) {
            continue;
        }
        line->SetPosition(SC_PLACE_TEXT_X, placeY + static_cast<int16_t>(i) * SC_LINE_GAP,
                          SC_PLACE_TEXT_W, SC_LINE_GAP);
        line->SetText(lines[i]);
        line->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        line->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xCF, 0xCF, 0xCF)));
    }
}

TestUIScrollView* ScrollerRmCaseRunner::CreatePlaceholderScroll(int16_t contentY, int16_t listW, int16_t hostH)
{
    TestUIScrollView* scroll = GraphicCreateView<TestUIScrollView>(container_);
    if (scroll == nullptr) {
        return nullptr;
    }
    scroll->SetPosition(SC_VIEW_X, contentY, listW, hostH);
    scroll->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x1A, 0x1A, 0x1A)));
    scroll->SetThrowDrag(true);
    scroll->SetYScrollBarVisible(false);
    scroll->SetDirection(UIAbstractScroll::VERTICAL);
    for (uint32_t i = 0; i < SC_LONG_ITEMS; i++) {
        UILabel* item = GraphicCreateView<UILabel>(scroll);
        if (item == nullptr) {
            continue;
        }
        item->SetPosition(0, static_cast<int16_t>(i * SC_ITEM_H), SC_ARC_ITEM_W, SC_ITEM_H);
        char text[32];
        (void)snprintf_s(text, sizeof(text), sizeof(text) - 1, "弧形滚动条演示项 %04u", i + 1);
        item->SetText(text);
        item->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        item->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    }
    return scroll;
}

void ScrollerRmCaseRunner::CreatePlaceholderReadback(ArcScrollBarHostView* testHost, int16_t bottomY)
{
    UIArcScrollBar* arcBar = testHost->GetArcBar();
    if (readbackLabels_[0] != nullptr && arcBar != nullptr) {
        char buf[64];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "读回 w=%u min=%u r=%u",
                         arcBar->GetIndicatorWidth(),
                         arcBar->GetIndicatorMinLength(),
                         arcBar->GetIndicatorBorderRadius());
        readbackLabels_[0]->SetText(buf);
        readbackLabels_[0]->SetPosition(SC_LABEL_X, bottomY + SC_LINE_GAP, SC_LABEL_W, SC_LINE_GAP);
    }
    if (readbackLabels_[1] != nullptr && arcBar != nullptr) {
        char buf[48];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "opa=%u (色肉眼验)", arcBar->GetIndicatorOpacity());
        readbackLabels_[1]->SetText(buf);
        readbackLabels_[1]->SetPosition(SC_LABEL_RIGHT_X, bottomY + SC_LINE_GAP, SC_LABEL_W, SC_LINE_GAP);
    }
}

void ScrollerRmCaseRunner::ShowPlaceholderCase()
{
    CreatePlaceholderInfoLabels();

    constexpr int16_t contentY = SC_VIEW_Y + SC_PLACE_CONTENT_Y_OFFSET;
    constexpr int16_t listW = 300;
    constexpr int16_t hostW = 100;
    constexpr int16_t hostGap = 10;
    constexpr int16_t hostH = SC_VIEW_H - 40;
    constexpr int16_t hostY = contentY;

    TestUIScrollView* scroll = CreatePlaceholderScroll(contentY, listW, hostH);
    if (scroll == nullptr) {
        return;
    }

    constexpr int16_t hostX = SC_SIDE_X;

    ArcScrollBarHostView* testHost = GraphicCreateView<ArcScrollBarHostView>(container_);
    if (testHost == nullptr) {
        return;
    }
    testHost->SetPosition(hostX, hostY, hostW, hostH);
    testHost->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x33, 0x33, 0x33)));
    testHost->SetTouchable(false);
    testHost->InitArcScrollBar();

    ArcScrollBarHostView* legacyHost = GraphicCreateView<ArcScrollBarHostView>(container_);
    if (legacyHost == nullptr) {
        return;
    }
    legacyHost->SetPosition(hostX + hostW + hostGap, hostY, hostW, hostH);
    legacyHost->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x33, 0x33, 0x33)));
    legacyHost->SetTouchable(false);
    legacyHost->InitArcScrollBarLegacy();

    CreateConfigLabels();
    CreateReadbackLabels();
    constexpr int16_t bottomY = 286;
    if (cfgLabels_[0] != nullptr) {
        cfgLabels_[0]->SetPosition(SC_LABEL_X, bottomY, SC_LABEL_W, SC_LINE_GAP);
    }
    if (cfgLabels_[1] != nullptr) {
        cfgLabels_[1]->SetPosition(SC_LABEL_RIGHT_X, bottomY, SC_LABEL_W, SC_LINE_GAP);
    }

    CreatePlaceholderReadback(testHost, bottomY);

    testHost->BindScrollView(scroll);
    legacyHost->BindScrollView(scroll);
}

void ScrollerRmCaseRunner::OnStressUpdateStep(uint32_t iter, UIScrollView* scroll,
                                              RmStressDriver* driver, UILabelButton* toggleBtn)
{
    static constexpr uint32_t kColors[] = { SC_RGB_RED, SC_RGB_GREEN, SC_RGB_BLUE };
    scroll->SetIndicatorColor(RgbToColor(kColors[iter % SC_COLOR_COUNT]));
    scroll->SetIndicatorWidth((iter % SC_PARITY_MOD == 0) ? SC_STRESS_WIDTH_MIN : SC_STRESS_WIDTH_MAX);
    scroll->SetIndicatorOpacity((iter % SC_PARITY_MOD == 0) ? SC_OPA_OPAQUE : SC_OPA_HALF);
    uint32_t done = iter + 1;
    updateCount_ = done;
    if ((done % SC_STRESS_STATUS_INTERVAL == 0) || (done >= SC_UPDATE_TARGET)) {
        char buf[64];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "已更新=%u 次", done);
        SetStatusText(buf);
        RefreshReadback();
    }
    if (done >= SC_UPDATE_TARGET) {
        driver->Stop();
        SetStatusText("完成1000次更新: 样式稳定生效,无异常");
        toggleBtn->SetText("开始压测");
        toggleBtn->Invalidate();
    }
}

void ScrollerRmCaseRunner::OnStressScrollStep(uint32_t iter, UIScrollView* scroll,
                                              RmStressDriver* driver, UILabelButton* toggleBtn)
{
    int16_t dy = ((iter / 10) % SC_PARITY_MOD == 0) ? 30 : -30;
    scroll->ScrollBy(0, dy);
    uint32_t done = iter + 1;
    if ((done % SC_STRESS_STATUS_INTERVAL == 0) || (done >= SC_SCROLL_TARGET)) {
        char buf[64];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "滚动步数=%u", done);
        SetStatusText(buf);
    }
    if (done >= SC_SCROLL_TARGET) {
        driver->Stop();
        SetStatusText("完成2000步往返滚动(降级替代30分钟长稳)");
        toggleBtn->SetText("开始压测");
        toggleBtn->Invalidate();
    }
}

bool ScrollerRmCaseRunner::OnStressToggle(RmStressDriver* driver, UILabelButton* toggleBtn,
                                          UIView& view, const ClickEvent& event)
{
    (void)view;
    (void)event;
    if (driver->IsRunning()) {
        driver->Stop();
        toggleBtn->SetText("开始压测");
    } else {
        driver->Start();
        toggleBtn->SetText("停止压测");
    }
    toggleBtn->Invalidate();
    return true;
}

void ScrollerRmCaseRunner::ShowStressUpdateCase()
{
    UIScrollView* scroll = CreateDemoScroll();
    if (scroll == nullptr) {
        return;
    }
    CreateConfigLabels();
    CreateReadbackLabels();
    RefreshReadback();
    updateCount_ = 0;

    RmStressDriver* driver = GraphicCreateView<RmStressDriver>(container_);
    if (driver == nullptr) {
        return;
    }
    driver->SetPosition(0, 0, 1, 1);
    driver->SetTouchable(false);

    UILabelButton* toggleBtn = GraphicCreateView<UILabelButton>(container_);
    if (toggleBtn == nullptr) {
        return;
    }
    toggleBtn->SetPosition(SC_ACTION_X, SC_ACTION_Y, SC_ACTION_W, SC_ACTION_H);
    toggleBtn->SetText("开始压测");
    toggleBtn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, ACTION_BTN_FONT);
    toggleBtn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    toggleBtn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x00, 0x80, 0xFF)));
    toggleBtn->SetStyle(STYLE_BORDER_RADIUS, SC_BTN_BORDER_RADIUS);
    toggleBtn->SetTouchable(true);

    driver->SetStepHandler([this, scroll, driver, toggleBtn](uint32_t iter) {
        OnStressUpdateStep(iter, scroll, driver, toggleBtn);
    });

    AddClickListener(toggleBtn, [this, driver, toggleBtn](UIView& view, const ClickEvent& event) -> bool {
        return OnStressToggle(driver, toggleBtn, view, event);
    });
}

void ScrollerRmCaseRunner::ShowStressScrollCase()
{
    UIScrollView* scroll = CreateDemoScroll();
    if (scroll == nullptr) {
        return;
    }
    ApplyCaseStyle(scroll);
    CreateConfigLabels();
    CreateReadbackLabels();
    RefreshReadback();

    RmStressDriver* driver = GraphicCreateView<RmStressDriver>(container_);
    if (driver == nullptr) {
        return;
    }
    driver->SetPosition(0, 0, 1, 1);
    driver->SetTouchable(false);

    UILabelButton* toggleBtn = GraphicCreateView<UILabelButton>(container_);
    if (toggleBtn == nullptr) {
        return;
    }
    toggleBtn->SetPosition(SC_ACTION_X, SC_ACTION_Y, SC_ACTION_W, SC_ACTION_H);
    toggleBtn->SetText("开始压测");
    toggleBtn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, ACTION_BTN_FONT);
    toggleBtn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    toggleBtn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x00, 0x80, 0xFF)));
    toggleBtn->SetStyle(STYLE_BORDER_RADIUS, SC_BTN_BORDER_RADIUS);
    toggleBtn->SetTouchable(true);

    driver->SetStepHandler([this, scroll, driver, toggleBtn](uint32_t iter) {
        OnStressScrollStep(iter, scroll, driver, toggleBtn);
    });

    AddClickListener(toggleBtn, [this, driver, toggleBtn](UIView& view, const ClickEvent& event) -> bool {
        return OnStressToggle(driver, toggleBtn, view, event);
    });
}

void ScrollerRmCaseRunner::ShowDemoLikeCase()
{
    UIScrollView* scroll = CreateDemoScroll();
    if (scroll != nullptr) {
        ApplyCaseStyle(scroll);
    }
    if (case_->type != SC_CASE_MANY_ITEMS) {
        CreateCompareScroll();
    }
    CreateConfigLabels();
    CreateReadbackLabels();
    RefreshReadback();
}

void ScrollerRmCaseRunner::ShowCase()
{
    switch (case_->type) {
        case SC_CASE_DEMO:
        case SC_CASE_MANY_ITEMS:
        case SC_CASE_XY_SCROLL:
            ShowDemoLikeCase();
            break;
        case SC_CASE_RESET:
            ShowResetCase();
            break;
        case SC_CASE_LATE_VISIBLE:
            ShowLateVisibleCase();
            break;
        case SC_CASE_UPDATE:
            ShowUpdateCase();
            break;
        case SC_CASE_PLACEHOLDER:
            ShowPlaceholderCase();
            break;
        case SC_CASE_STRESS_UPDATE:
            ShowStressUpdateCase();
            break;
        case SC_CASE_STRESS_SCROLL:
            ShowStressScrollCase();
            break;
        default:
            break;
    }

    if (case_->type != SC_CASE_PLACEHOLDER) {
        UILabel* statusLabel = GraphicCreateView<UILabel>(container_);
        if (statusLabel != nullptr) {
            statusLabel->SetPosition(SC_SIDE_X, SC_STATUS_Y, SC_SIDE_W, SC_STATUS_H);
            statusLabel->SetText("拖动左侧列表观察滚动条");
            statusLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
            statusLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
        }
        statusLabel_ = statusLabel;
    }

    UILabel* hint = GraphicCreateView<UILabel>(container_);
    if (hint != nullptr) {
        hint->SetPosition(HINT_X, HINT_Y, HINT_W, HINT_H);
        hint->SetText(case_->expect);
        hint->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        hint->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x9F, 0x9F, 0x9F)));
    }
}

} // namespace OHOS
#endif // GRAPHIC_ENABLE_SCROLL_FLAG

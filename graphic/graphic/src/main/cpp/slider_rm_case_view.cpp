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

#include "slider_rm_case_view.h"

#if GRAPHIC_ENABLE_SLIDER_FLAG
#include <cstdio>
#include <cstdlib>
#include <new>
#include "components/ui_edit_text.h"
#include "events/click_event.h"
#include "graphic_utils.h"
#include "securec.h"

namespace OHOS {

namespace {
const int32_t g_valsEven[] = { 0, 20, 40, 60, 80, 100 };
constexpr uint16_t g_valsEvenNum = 6;
const int32_t g_valsMessy[] = { 60, 20, 20, -10, 120, 100, 0 };
constexpr uint16_t g_valsMessyNum = 7;
const int32_t g_valsDense[] = { 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50,
                                55, 60, 65, 70, 75, 80, 85, 90, 95, 100 };
constexpr uint16_t g_valsDenseNum = 21;
const int32_t g_valsOverMax[] = { 0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30,
                                  33, 36, 39, 42, 45, 48, 51, 54, 57, 60, 63,
                                  66, 69, 72, 75, 78, 81, 84, 87, 90, 93, 96 };
constexpr uint16_t g_valsOverMaxNum = 33;

struct SliderColorScheme {
    ColorType background;
    ColorType foreground;
    ColorType knob;
};
const SliderColorScheme g_colorSchemes[] = {
    { Color::GetColorFromRGB(0x2E, 0x5A, 0x2E), Color::GetColorFromRGB(0x00, 0x7A, 0xFF),
      Color::GetColorFromRGB(0xFF, 0xA0, 0x00) },
    { Color::GetColorFromRGB(0x50, 0x30, 0x30), Color::GetColorFromRGB(0xD8, 0x30, 0x60),
      Color::GetColorFromRGB(0x30, 0xD8, 0xC0) },
};
constexpr uint32_t g_colorSchemeNum = sizeof(g_colorSchemes) / sizeof(g_colorSchemes[0]);

struct SliderGradient {
    const ColorType* bg;
    uint16_t bgCount;
    const ColorType* onTint;
    uint16_t onTintCount;
};
const ColorType g_gradBg0[] = { Color::GetColorFromRGB(0x30, 0x30, 0x30),
                                Color::GetColorFromRGB(0x90, 0x90, 0x90) };
const ColorType g_gradFg0[] = { Color::GetColorFromRGB(0x00, 0x7A, 0xFF),
                                Color::GetColorFromRGB(0x00, 0xD8, 0x60),
                                Color::GetColorFromRGB(0xFF, 0xD0, 0x00) };
const SliderGradient g_gradients[] = {
    { g_gradBg0, 2, g_gradFg0, 3 },
};

constexpr int16_t CONT_X = 100;
constexpr int16_t CONT_Y = 0;
constexpr int16_t CONT_W = 760;
constexpr int16_t CONT_H = 400;
constexpr uint8_t CONT_RADIUS = 16;

constexpr int16_t INFO_X = 24;
constexpr int16_t INFO_W = 712;
constexpr uint8_t INFO_SIZE = 22;
constexpr uint8_t HINT_SIZE = 20;
constexpr int16_t HINT_X = 24;
constexpr int16_t HINT_W = 712;
constexpr int16_t HINT_H = 44;

constexpr int16_t TITLE_X = 24;
constexpr int16_t TITLE_Y = 4;
constexpr int16_t TITLE_W = 712;
constexpr uint8_t TITLE_H = 26;
constexpr uint8_t TITLE_FONT = 20;

constexpr int16_t SL_H_W = 600;
constexpr int16_t SL_H_H = 92;
constexpr int16_t SL_H_Y = 64;
constexpr int16_t SL_MARK_TEXT_H = 132;
constexpr int16_t SL_EXTEND_H = 180;
constexpr int16_t SL_TRACK_H = 92;
constexpr int16_t SL_V_W = 60;
constexpr int16_t SL_V_H = 210;
constexpr int16_t SL_V_Y = 42;
constexpr int16_t SL_VAL_Y = 168;
constexpr int16_t SL_INPUT_Y = 205;
constexpr int16_t SL_CFG_Y = 258;
constexpr int16_t SL_CFG2_Y = 292;
constexpr int16_t SL_HINT_Y = 335;
constexpr int16_t SL_INPUT_W = 180;
constexpr int16_t SL_INPUT_H = 40;
constexpr int16_t SL_LABEL_H = 30;
constexpr int16_t SL_JUMP_BTN_W = 86;
constexpr int16_t SL_JUMP_BTN_H = 40;
constexpr int16_t SL_JUMP_BTN_X = INFO_X + SL_INPUT_W + 16;
constexpr int16_t SL_LOOP_BTN_W = SL_INPUT_W + 16 + SL_JUMP_BTN_W;
constexpr int16_t SL_EXTEND_HINT_Y = 184;
const uint32_t SL_MARK_TEXT_PANEL_COLOR = Color::ColorTo32(Color::GetColorFromRGB(0xFF, 0xF2, 0xB8));
const uint32_t SL_EXTEND_ZONE_COLOR = Color::ColorTo32(Color::GetColorFromRGB(0x00, 0xD8, 0x60));
constexpr uint8_t SL_EXTEND_ZONE_OPA = 170;
constexpr int16_t SL_KNOB_W = 25;
constexpr int16_t SL_CENTER_DIV = 2;

constexpr uint8_t BORDER_RADIUS = 6;
constexpr uint8_t VISUAL_PANEL_RADIUS = 6;
constexpr uint8_t INPUT_MAX_LENGTH = 6;
constexpr uint8_t FULL_OPACITY = 255;
constexpr int16_t MARK_TEXT_SLIDER_WIDTH = 150;
constexpr int16_t EXTEND_VALUE_Y = 205;
constexpr int16_t EXTEND_INPUT_Y = 238;
constexpr int16_t EXTEND_CFG_Y = 285;
constexpr int16_t EXTEND_CFG2_Y = 315;
constexpr int16_t EXTEND_HINT_Y = 350;
constexpr uint8_t MARK_TEXT_LOOP_COUNT = 50;
constexpr uint8_t DIRECTION_LOOP_COUNT = 8;
constexpr uint8_t DIRECTION_COUNT = 4;
constexpr uint8_t VERTICAL_DIR_MIN = 2;
constexpr uint8_t DIR_RIGHT_TO_LEFT = 1;
constexpr uint8_t DIR_TOP_TO_BOTTOM = 2;
constexpr uint8_t DIR_BOTTOM_TO_TOP = 3;
constexpr uint8_t KNOB_RADIUS_DIV = 2;
constexpr uint8_t TOGGLE_PARITY_MOD = 2;

UISlider::Direction MapDirection(uint8_t dir)
{
    switch (dir) {
        case DIR_RIGHT_TO_LEFT: return UISlider::Direction::DIR_RIGHT_TO_LEFT;
        case DIR_TOP_TO_BOTTOM: return UISlider::Direction::DIR_TOP_TO_BOTTOM;
        case DIR_BOTTOM_TO_TOP: return UISlider::Direction::DIR_BOTTOM_TO_TOP;
        default: return UISlider::Direction::DIR_LEFT_TO_RIGHT;
    }
}

bool IsVerticalDir(uint8_t dir)
{
    return dir >= VERTICAL_DIR_MIN;
}

int32_t ClampValue(const SliderRmCase& testCase, int32_t value)
{
    if (testCase.rangeMax < testCase.rangeMin) {
        return value;
    }
    if (value < testCase.rangeMin) {
        return testCase.rangeMin;
    }
    if (value > testCase.rangeMax) {
        return testCase.rangeMax;
    }
    return value;
}

int32_t ParseJumpValue(const char* text, int32_t fallback)
{
    if ((text == nullptr) || (text[0] == '\0')) {
        return fallback;
    }
    char* end = nullptr;
    long value = std::strtol(text, &end, 10);
    if (end == text) {
        return fallback;
    }
    return static_cast<int32_t>(value);
}

const char* BoolText(bool value)
{
    return value ? "1" : "0";
}

void ApplyColors(UISlider* slider, const SliderRmCase& testCase)
{
    if (slider == nullptr) {
        return;
    }
    if (testCase.colorScheme >= 0) {
        const SliderColorScheme& cs = g_colorSchemes[testCase.colorScheme];
        slider->SetSliderColor(cs.background, cs.foreground);
        slider->SetKnobColor(cs.knob);
        return;
    }
    if (testCase.enableMarkText) {
        slider->SetSliderColor(Color::GetColorFromRGB(0x40, 0x40, 0x40),
                               Color::GetColorFromRGB(0x00, 0x7A, 0xFF));
        slider->SetStyle(STYLE_BACKGROUND_OPA, 0);
    } else {
        slider->SetSliderColor(Color::GetColorFromRGB(0x68, 0x68, 0x68),
                               Color::GetColorFromRGB(0xFF, 0xFF, 0xFF));
    }
}

void AddVisualPanel(UIViewGroup* dialog, int16_t x, int16_t y, int16_t width, int16_t height, uint32_t color,
                    uint8_t opacity, int16_t radius)
{
    if (dialog == nullptr) {
        return;
    }
    UIView* panel = GraphicCreateView<UIView>(dialog);
    if (panel == nullptr) {
        return;
    }
    panel->SetPosition(x, y, width, height);
    panel->SetStyle(STYLE_BACKGROUND_COLOR, color);
    panel->SetStyle(STYLE_BACKGROUND_OPA, opacity);
    panel->SetStyle(STYLE_BORDER_RADIUS, radius);
    panel->SetTouchable(false);
}

} // namespace

class SliderRmValueListener : public UISlider::UISliderEventListener {
public:
    explicit SliderRmValueListener(UILabel* valueLabel) : valueLabel_(valueLabel) {}

    void OnChange(int32_t value) override
    {
        Refresh(value);
    }

    void Refresh(int32_t value)
    {
        if (valueLabel_ == nullptr) {
            return;
        }
        char buf[64];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "当前值: %d", value);
        valueLabel_->SetText(buf);
    }

private:
    UILabel* valueLabel_;
};

const SliderRmCase g_sliderRmCases[] = {
    { "SL-001", "默认(能力全关)", "无刻度/Toast,行为同旧版(SL-001)", 0, 100, 10, 30, 0,
      false, 0, 4, false, false, nullptr, 0, false, false, nullptr, false, -1, -1, 0 },
    { "SL-002", "值Toast EnableToast", "拖动/点击弹当前值Toast(新增RM014)", 0, 100, 10, 50, 0,
      false, 0, 4, false, false, nullptr, 0, false, false, nullptr, true, -1, -1, 0 },
    { "SL-003", "disabled Toast", "禁用后点击弹Toast,值不变(SL-002)", 0, 100, 10, 30, 0,
      false, 0, 4, false, false, nullptr, 0, false, true, "Current slider is disabled", false, -1, -1, 0 },
    { "SL-004", "自定义values吸附", "刻度按values,点近37吸附40(SL-003)", 0, 100, 10, 30, 0,
      true, 0, 6, false, false, g_valsEven, g_valsEvenNum, false, false, nullptr, false, -1, -1, 0 },
    { "SL-005", "线型刻度 LINE", "step=10线型刻度,size=6(SL-004)", 0, 100, 10, 40, 0,
      true, 0, 6, false, false, nullptr, 0, false, false, nullptr, false, -1, -1, 0 },
    { "SL-006", "点型刻度 DOT", "values各点显示点型标识(SL-005)", 0, 100, 10, 40, 0,
      true, 1, 8, false, false, g_valsEven, g_valsEvenNum, false, false, nullptr, false, -1, -1, 0 },
    { "SL-007", "刻度文本", "step=10显示0..100刻度值(SL-006,step映射)", 0, 100, 10, 40, 0,
      true, 0, 6, true, false, nullptr, 0, false, false, nullptr, false, -1, -1, 0 },
    { "SL-008", "渐变背景/前景", "背景/前景多色渐变(新增RM015)", 0, 100, 10, 50, 0,
      false, 0, 4, false, false, nullptr, 0, false, false, nullptr, false, -1, 0, 0 },
    { "SL-009", "扩展点击区 开", "点轨道外上下空白也响应(新增RM013)", 0, 100, 10, 50, 0,
      false, 0, 4, false, false, nullptr, 0, true, false, nullptr, false, -1, -1, 0 },
    { "SL-010", "扩展点击区 关", "仅轨道条内点击响应(对比)", 0, 100, 10, 50, 0,
      false, 0, 4, false, false, nullptr, 0, false, false, nullptr, false, -1, -1, 0 },
    { "SL-011", "三色独立(底/前景/滑块)", "三色各自生效;刻度色固定灰(SL-007)", 0, 100, 20, 40, 0,
      true, 0, 6, false, false, nullptr, 0, false, false, nullptr, false, 0, -1, 0 },
    { "SL-012", "values空回退step吸附", "刻度按step=10网格,点近44吸附40(SL-008)", 0, 100, 10, 30, 0,
      true, 0, 4, false, true, nullptr, 0, false, false, nullptr, false, -1, -1, 0 },
    { "SL-013", "values去重+越界过滤", "有效刻度0/20/60/100(SL-009)", 0, 100, 10, 30, 0,
      true, 0, 6, true, false, g_valsMessy, g_valsMessyNum, false, false, nullptr, false, -1, -1, 0 },
    { "SL-014", "刻度size=0回默认", "size<=0回退默认4(SL-010)", 0, 100, 20, 40, 0,
      true, 0, 0, false, false, nullptr, 0, false, false, nullptr, false, -1, -1, 0 },
    { "SL-015", "range max<min", "非法SetRange被拒,保持默认[0,100]不崩(SL-012)", 100, 0, 10, 0, 0,
      true, 0, 6, true, false, nullptr, 0, false, false, nullptr, false, -1, -1, 0 },
    { "SL-016", "方向 R2L 刻度", "右到左,刻度/吸附方向正确(SL-013)", 0, 100, 20, 40, 1,
      true, 0, 6, true, true, nullptr, 0, false, false, nullptr, false, -1, -1, 0 },
    { "SL-017", "方向 T2B 刻度", "上到下垂直,刻度与文本(SL-013)", 0, 100, 20, 40, 2,
      true, 0, 6, true, true, nullptr, 0, false, false, nullptr, false, -1, -1, 0 },
    { "SL-018", "方向 B2T 刻度", "下到上垂直,刻度与文本(SL-013)", 0, 100, 20, 40, 3,
      true, 0, 6, true, true, nullptr, 0, false, false, nullptr, false, -1, -1, 0 },
    { "SL-019", "disabled空Toast文案", "空文案不弹Toast,值不变(SL-014)", 0, 100, 10, 30, 0,
      false, 0, 4, false, false, nullptr, 0, false, true, "", false, -1, -1, 0 },
    { "SL-020", "非法MarkingsType", "强转非法值被忽略,保持线型(SL-015)", 0, 100, 20, 40, 0,
      true, 99, 6, false, false, nullptr, 0, false, false, nullptr, false, -1, -1, 0 },
    { "SL-021", "超长disabled Toast", "超长文案单行钳制不崩(SL-016)", 0, 100, 10, 30, 0,
      false, 0, 4, false, false, nullptr, 0, false, true,
      "This is a very long disabled toast message that exceeds the screen width", false, -1, -1, 0 },
    { "SL-022", "刻度文本抽稀(>20)", "21刻度值,文本抽稀显示(SL-018)", 0, 100, 10, 50, 0,
      true, 0, 6, true, false, g_valsDense, g_valsDenseNum, false, false, nullptr, false, -1, -1, 0 },
    { "SL-023", "多刻度值吸附(33截断)", "33值超上限截断32,触发截断LOGW,吸附最近刻度(SL-019)", 0, 100, 10, 50, 0,
      true, 0, 6, true, true, g_valsOverMax, g_valsOverMaxNum, false, false, nullptr, false, -1, -1, 0 },
    { "SL-024", "刻度/文本开关循环x50", "点按钮循环切换50次无残留(SL-020)", 0, 100, 20, 50, 0,
      true, 0, 6, true, false, nullptr, 0, false, false, nullptr, false, -1, -1, 1 },
    { "SL-025", "方向/颜色循环", "点按钮循环切换方向与颜色(SL-021)", 0, 100, 20, 50, 0,
      true, 0, 6, true, true, nullptr, 0, false, false, nullptr, false, 0, -1, 2 },
};
const uint32_t g_sliderRmCaseNum = sizeof(g_sliderRmCases) / sizeof(g_sliderRmCases[0]);

SliderRmCaseRunner::SliderRmCaseRunner(const SliderRmCase* testCase)
    : case_(testCase), container_(nullptr), slider_(nullptr), valueLabel_(nullptr),
      valueListener_(nullptr), listeners_{}, listenerCount_(0)
{
}

SliderRmCaseRunner::~SliderRmCaseRunner()
{
    if ((slider_ != nullptr) && (valueListener_ != nullptr)) {
        slider_->SetSliderEventListener(nullptr);
    }
    delete valueListener_;
    valueListener_ = nullptr;
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
    slider_ = nullptr;
    valueLabel_ = nullptr;
}

void SliderRmCaseRunner::ResetState()
{
    slider_ = nullptr;
    valueLabel_ = nullptr;
    valueListener_ = nullptr;
    listenerCount_ = 0;
}

UIViewGroup* SliderRmCaseRunner::Build(UIViewGroup* content)
{
    if ((case_ == nullptr) || (container_ != nullptr) || (content == nullptr)) {
        return nullptr;
    }
    ResetState();

    container_ = GraphicCreateView<UIViewGroup>(content);
    if (container_ == nullptr) {
        return nullptr;
    }
    container_->SetPosition(CONT_X, CONT_Y, CONT_W, CONT_H);
    container_->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x2A, 0x2A, 0x2A)));
    container_->SetStyle(STYLE_BORDER_RADIUS, CONT_RADIUS);
    container_->SetTouchable(true);

    ShowCase(*case_);

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

void SliderRmCaseRunner::AddClickListener(UIView* view, std::function<bool(UIView&, const ClickEvent&)> fn)
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

struct SliderRmCaseRunner::SliderLayout {
    int16_t sliderX;
    int16_t sliderY;
    int16_t sliderW;
    int16_t sliderH;
    int16_t validTrackW;
    int16_t validTrackH;
    int16_t valueY;
    int16_t inputY;
    int16_t cfgY;
    int16_t cfg2Y;
    int16_t hintY;
};

void SliderRmCaseRunner::ShowCase(const SliderRmCase& testCase)
{
    bool vertical = IsVerticalDir(testCase.direction);
    SliderLayout layout = ComputeSliderLayout(testCase, vertical);
    ApplyMarkTextLayout(layout, vertical, testCase);
    ApplyExtendClickLayout(layout, testCase);

    UISlider* slider = CreateAndConfigSlider(testCase, layout);
    if (slider == nullptr) {
        return;
    }
    slider_ = slider;
    CreateValueAndListener(testCase, layout, slider);
    CreateActionControls(testCase, layout);
    CreateInfoLabels(testCase, layout);
}

SliderRmCaseRunner::SliderLayout SliderRmCaseRunner::ComputeSliderLayout(const SliderRmCase& testCase, bool vertical)
{
    SliderLayout layout;
    layout.sliderW = vertical ? SL_V_W : SL_H_W;
    layout.sliderH = vertical ? SL_V_H : SL_H_H;
    layout.sliderX = static_cast<int16_t>((CONT_W - layout.sliderW) / SL_CENTER_DIV);
    layout.sliderY = vertical ? SL_V_Y : SL_H_Y;
    layout.validTrackW = layout.sliderW;
    layout.validTrackH = layout.sliderH;
    layout.valueY = SL_VAL_Y;
    layout.inputY = SL_INPUT_Y;
    layout.cfgY = SL_CFG_Y;
    layout.cfg2Y = SL_CFG2_Y;
    layout.hintY = SL_HINT_Y;
    return layout;
}

void SliderRmCaseRunner::ApplyMarkTextLayout(SliderLayout& layout, bool vertical, const SliderRmCase& testCase)
{
    if (!testCase.enableMarkText) {
        return;
    }
    if (vertical) {
        layout.sliderW = MARK_TEXT_SLIDER_WIDTH;
        layout.sliderX = static_cast<int16_t>((CONT_W - layout.sliderW) / SL_CENTER_DIV);
        layout.validTrackW = SL_V_W;
    } else {
        layout.sliderH = SL_MARK_TEXT_H;
        layout.validTrackH = SL_TRACK_H;
    }
    AddVisualPanel(container_, layout.sliderX, layout.sliderY, layout.sliderW, layout.sliderH,
                   SL_MARK_TEXT_PANEL_COLOR, FULL_OPACITY, VISUAL_PANEL_RADIUS);
}

void SliderRmCaseRunner::ApplyExtendClickLayout(SliderLayout& layout, const SliderRmCase& testCase)
{
    if (!testCase.expandClickArea || IsVerticalDir(testCase.direction)) {
        return;
    }
    layout.sliderH = SL_EXTEND_H;
    layout.sliderY = static_cast<int16_t>(SL_H_Y - ((SL_EXTEND_H - SL_H_H) / SL_CENTER_DIV));
    layout.validTrackH = SL_TRACK_H;
    layout.valueY = EXTEND_VALUE_Y;
    layout.inputY = EXTEND_INPUT_Y;
    layout.cfgY = EXTEND_CFG_Y;
    layout.cfg2Y = EXTEND_CFG2_Y;
    layout.hintY = EXTEND_HINT_Y;
    AddVisualPanel(container_, layout.sliderX, layout.sliderY, layout.sliderW, layout.sliderH,
                   SL_EXTEND_ZONE_COLOR, SL_EXTEND_ZONE_OPA, VISUAL_PANEL_RADIUS);

    UILabel* extendHint = GraphicCreateView<UILabel>(container_);
    if (extendHint != nullptr) {
        extendHint->SetPosition(INFO_X, SL_EXTEND_HINT_Y, INFO_W, SL_LABEL_H);
        extendHint->SetText("绿色区域=扩展点击区");
        extendHint->SetFont(DEFAULT_VECTOR_FONT_FILENAME, INFO_SIZE);
        extendHint->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x80, 0xFF, 0xA0)));
    }
}

UISlider* SliderRmCaseRunner::CreateAndConfigSlider(const SliderRmCase& testCase, const SliderLayout& layout)
{
    UISlider* slider = GraphicCreateView<UISlider>(container_);
    if (slider == nullptr) {
        return nullptr;
    }
    slider->SetPosition(layout.sliderX, layout.sliderY, layout.sliderW, layout.sliderH);
    slider->SetValidWidth(layout.validTrackW);
    slider->SetValidHeight(layout.validTrackH);
    slider->SetDirection(MapDirection(testCase.direction));
    slider->SetRange(testCase.rangeMax, testCase.rangeMin);
    slider->SetStep(testCase.step);
    slider->SetValue(testCase.initValue);
    ApplyColors(slider, testCase);
    slider->SetKnobWidth(SL_KNOB_W);
    slider->SetKnobRadius(SL_KNOB_W / KNOB_RADIUS_DIV);
    if ((testCase.values != nullptr) && (testCase.valuesCount > 0)) {
        slider->SetValues(testCase.values, testCase.valuesCount);
    }
    if (testCase.gradientScheme >= 0) {
        const SliderGradient& g = g_gradients[testCase.gradientScheme];
        slider->SetBgGradientColors(g.bg, g.bgCount);
        slider->SetOnTintGradientColors(g.onTint, g.onTintCount);
    }
    slider->EnableMarkings(testCase.enableMarkings);
    slider->SetMarkingsType(static_cast<UISlider::MarkingsType>(testCase.markingsType));
    slider->SetMarkingsSize(testCase.markingsSize);
    slider->EnableMarkText(testCase.enableMarkText);
    slider->EnableTicks(testCase.enableTicks);
    slider->SetExpandClickArea(testCase.expandClickArea);
    slider->EnableToast(testCase.enableToast);
    if (testCase.disabledToastMsg != nullptr) {
        slider->SetDisabledToastMsg(testCase.disabledToastMsg);
    }
    slider->SetDisabled(testCase.disabled);
    slider->SetTouchable(true);
    return slider;
}

void SliderRmCaseRunner::CreateValueAndListener(const SliderRmCase& testCase,
                                                const SliderLayout& layout,
                                                UISlider* slider)
{
    UILabel* valueLabel = GraphicCreateView<UILabel>(container_);
    if (valueLabel != nullptr) {
        valueLabel->SetPosition(INFO_X, layout.valueY, INFO_W, SL_LABEL_H);
        valueLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, INFO_SIZE);
        valueLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    }
    valueLabel_ = valueLabel;
    SliderRmValueListener* listener = new (std::nothrow) SliderRmValueListener(valueLabel);
    if (listener != nullptr) {
        slider->SetSliderEventListener(listener);
    }
    valueListener_ = listener;
    if (listener != nullptr) {
        listener->Refresh(testCase.initValue);
    }
}

void SliderRmCaseRunner::CreateActionControls(const SliderRmCase& testCase, const SliderLayout& layout)
{
    if (testCase.loopAction != 0) {
        CreateLoopButton(testCase, layout);
    } else {
        CreateInputAndJump(testCase, layout);
    }
}

void SliderRmCaseRunner::CreateLoopButton(const SliderRmCase& testCase, const SliderLayout& layout)
{
    UILabelButton* loopBtn = GraphicCreateView<UILabelButton>(container_);
    if (loopBtn == nullptr) {
        return;
    }
    loopBtn->SetPosition(INFO_X, layout.inputY, SL_LOOP_BTN_W, SL_JUMP_BTN_H);
    loopBtn->SetText(testCase.loopAction == 1 ? "循环切换刻度/文本 x50" : "循环切换方向/颜色");
    loopBtn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, INFO_SIZE);
    loopBtn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    loopBtn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x00, 0x80, 0xFF)));
    loopBtn->SetStyle(STYLE_BORDER_RADIUS, BORDER_RADIUS);
    loopBtn->SetTouchable(true);
    AddClickListener(loopBtn, [this](UIView& view, const ClickEvent& event) -> bool {
        (void)event;
        auto& btn = static_cast<UILabelButton&>(view);
        if (case_->loopAction == 1) {
            RunMarkTextLoop(btn);
        } else {
            RunDirectionColorLoop(btn);
        }
        int32_t farEnd = ((case_->initValue - case_->rangeMin) >= (case_->rangeMax - case_->initValue))
            ? case_->rangeMin : case_->rangeMax;
        slider_->SetValue(farEnd);
        slider_->SetValue(case_->initValue);
        if (valueListener_ != nullptr) {
            valueListener_->Refresh(case_->initValue);
        }
        slider_->Invalidate();
        return true;
    });
}

void SliderRmCaseRunner::RunMarkTextLoop(UILabelButton& btn)
{
    for (int i = 0; i < MARK_TEXT_LOOP_COUNT; i++) {
        bool on = (i % TOGGLE_PARITY_MOD) == 0;
        slider_->EnableMarkings(on);
        slider_->EnableMarkText(on);
        slider_->Invalidate();
    }
    slider_->EnableMarkings(true);
    slider_->EnableMarkText(true);
    btn.SetText("已循环50次,刻度/文本已恢复");
}

void SliderRmCaseRunner::RunDirectionColorLoop(UILabelButton& btn)
{
    for (int i = 0; i < DIRECTION_LOOP_COUNT; i++) {
        slider_->SetDirection(MapDirection(static_cast<uint8_t>(i % DIRECTION_COUNT)));
        const SliderColorScheme& cs = g_colorSchemes[i % g_colorSchemeNum];
        slider_->SetSliderColor(cs.background, cs.foreground);
        slider_->SetKnobColor(cs.knob);
        slider_->Invalidate();
    }
    slider_->SetDirection(MapDirection(case_->direction));
    ApplyColors(slider_, *case_);
    btn.SetText("已循环8次,方向/颜色已恢复");
}

void SliderRmCaseRunner::CreateInputAndJump(const SliderRmCase& testCase, const SliderLayout& layout)
{
    UIEditText* input = GraphicCreateView<UIEditText>(container_);
    if (input != nullptr) {
        input->SetPosition(INFO_X, layout.inputY, SL_INPUT_W, SL_INPUT_H);
        input->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x44, 0x44, 0x44)));
        input->SetStyle(STYLE_BORDER_RADIUS, BORDER_RADIUS);
        input->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
        input->SetStyle(STYLE_TEXT_OPA, FULL_OPACITY);
        input->SetTextColor(Color::White());
        input->SetPlaceholder("输入进度值");
        input->SetPlaceholderColor(Color::GetColorFromRGB(0xCF, 0xCF, 0xCF));
        input->SetFont(DEFAULT_VECTOR_FONT_FILENAME, INFO_SIZE);
        input->SetMaxLength(INPUT_MAX_LENGTH);
        input->SetTouchable(true);
    }

    UILabelButton* jumpBtn = GraphicCreateView<UILabelButton>(container_);
    if (jumpBtn != nullptr) {
        jumpBtn->SetPosition(SL_JUMP_BTN_X, layout.inputY, SL_JUMP_BTN_W, SL_JUMP_BTN_H);
        jumpBtn->SetText("跳转");
        jumpBtn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, INFO_SIZE);
        jumpBtn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
        jumpBtn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x00, 0x80, 0xFF)));
        jumpBtn->SetStyle(STYLE_BORDER_RADIUS, BORDER_RADIUS);
        jumpBtn->SetTouchable(true);
        AddClickListener(jumpBtn, [this, input](UIView& view, const ClickEvent& event) -> bool {
            (void)view;
            (void)event;
            int32_t value = ParseJumpValue(input->GetText(), case_->initValue);
            value = ClampValue(*case_, value);
            slider_->SetValue(value);
            slider_->Invalidate();
            if (valueListener_ != nullptr) {
                valueListener_->Refresh(value);
            }
            return true;
        });
    }
}

void SliderRmCaseRunner::CreateInfoLabels(const SliderRmCase& testCase, const SliderLayout& layout)
{
    char cfgBuf[160];
    if ((testCase.values != nullptr) && (testCase.valuesCount > 0)) {
        (void)snprintf_s(cfgBuf, sizeof(cfgBuf), sizeof(cfgBuf) - 1,
            "配置: range=[%d,%d] values=%u个(刻度按values) init=%d dir=%u",
            testCase.rangeMin, testCase.rangeMax, testCase.valuesCount, testCase.initValue, testCase.direction);
    } else {
        (void)snprintf_s(cfgBuf, sizeof(cfgBuf), sizeof(cfgBuf) - 1,
            "配置: range=[%d,%d] step=%u init=%d dir=%u",
            testCase.rangeMin, testCase.rangeMax, testCase.step, testCase.initValue, testCase.direction);
    }
    UILabel* cfgLabel = GraphicCreateView<UILabel>(container_);
    if (cfgLabel != nullptr) {
        cfgLabel->SetPosition(INFO_X, layout.cfgY, INFO_W, SL_LABEL_H);
        cfgLabel->SetText(cfgBuf);
        cfgLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, INFO_SIZE);
        cfgLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xCF, 0xCF, 0xCF)));
    }

    char cfgBuf2[200];
    (void)snprintf_s(cfgBuf2, sizeof(cfgBuf2), sizeof(cfgBuf2) - 1,
        "能力: mark=%s type=%u size=%d text=%s ticks=%s expand=%s dis=%s toast=%s",
        BoolText(testCase.enableMarkings), testCase.markingsType, testCase.markingsSize,
        BoolText(testCase.enableMarkText), BoolText(testCase.enableTicks),
        BoolText(testCase.expandClickArea), BoolText(testCase.disabled), BoolText(testCase.enableToast));
    UILabel* cfgLabel2 = GraphicCreateView<UILabel>(container_);
    if (cfgLabel2 != nullptr) {
        cfgLabel2->SetPosition(INFO_X, layout.cfg2Y, INFO_W, SL_LABEL_H);
        cfgLabel2->SetText(cfgBuf2);
        cfgLabel2->SetFont(DEFAULT_VECTOR_FONT_FILENAME, INFO_SIZE);
        cfgLabel2->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xCF, 0xCF, 0xCF)));
    }

    UILabel* hint = GraphicCreateView<UILabel>(container_);
    if (hint != nullptr) {
        hint->SetPosition(HINT_X, layout.hintY, HINT_W, HINT_H);
        hint->SetText(testCase.expect);
        hint->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        hint->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x9F, 0x9F, 0x9F)));
    }
}

} // namespace OHOS
#endif // GRAPHIC_ENABLE_SLIDER_FLAG

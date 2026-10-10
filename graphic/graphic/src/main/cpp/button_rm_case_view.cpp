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

#include "button_rm_case_view.h"

#if GRAPHIC_ENABLE_BUTTON_FLAG
#include <cstdio>
#include <cstring>
#include <new>
#include "components/ui_view_group.h"
#include "events/click_event.h"
#include "events/press_event.h"
#include "events/release_event.h"
#include "graphic_utils.h"
#include "securec.h"

namespace OHOS {

const ButtonRmCase g_buttonRmCases[] = {
    { "BT-001", "默认创建与显示", "不调用新增API:点击区=视觉区,点击回调,按住播缩放1次,无异常日志",
      BUTTON_CASE_DEMO, false, false, true, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, 0, 0, 0, 0, false },
    { "BT-002", "repeat count=1", "按住按钮:SCALE动画完整播放1次后停止,松开后恢复释放态",
      BUTTON_CASE_DEMO, false, false, false, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, 0, 0, 0, 0, false },
    { "BT-003", "effect=SCALE", "按住:缩放+按压态样式,释放恢复正常,过程无闪烁",
      BUTTON_CASE_DEMO, false, false, false, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, 0, 0, 0, 0, false },
    { "BT-004", "effect=NONE", "可正常响应点击;无缩放动画/无白色按压蒙层(按压态圆角变化属正常样式)",
      BUTTON_CASE_DEMO, false, false, false, false, 1,
      UIButton::BUTTON_ANIMATION_NONE, 0, 0, 0, 0, false },
    { "BT-005", "热区四向扩展(40,40,40,40)", "扩展区内点击命中;视觉大小/布局不变;回调正常",
      BUTTON_CASE_DEMO, true, false, false, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, 40, 40, 40, 40, false },
    { "BT-006", "组合:热区(30,20,30,20)+SCALE+repeat=2", "扩展区命中;按住动画播放2次;回调只1次;热区与动画无冲突",
      BUTTON_CASE_DEMO, true, false, false, false, 2,
      UIButton::BUTTON_ANIMATION_SCALE, 30, 20, 30, 20, false },
    { "BT-007", "repeat count=0", "不启动缩放动画和按压蒙层;点击回调仍正常触发",
      BUTTON_CASE_DEMO, false, false, false, false, 0,
      UIButton::BUTTON_ANIMATION_SCALE, 0, 0, 0, 0, false },
    { "BT-008", "repeat count=65535+中断", "配置值可保存(读回验证);需保持按住动画才持续;中断后停止复位可恢复",
      BUTTON_CASE_INTERRUPT, false, false, false, false, 65535,
      UIButton::BUTTON_ANIMATION_SCALE, 0, 0, 0, 0, false },
    { "BT-009", "热区 expand=0", "边界内点击有效;边界外1px无效;绘制区域不变化",
      BUTTON_CASE_DEMO, true, false, false, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, 0, 0, 0, 0, false },
    { "BT-010", "热区(100,50,100,50)+相邻控件", "扩展区可命中;相邻控件自身命中不被破坏;视觉矩形不扩大",
      BUTTON_CASE_DEMO, true, true, false, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, 100, 50, 100, 50, false },
    { "BT-011", "热区负值(-5,-1,-10,-20)", "四向恢复0(读回验证)+告警;界外点击不命中;不崩溃",
      BUTTON_CASE_DEMO, true, false, false, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, -5, -1, -10, -20, false },
    { "BT-012", "非法effect枚举(0xFF)", "恢复SCALE(读回验证)+告警;按压有缩放动画",
      BUTTON_CASE_DEMO, false, false, false, true, 1,
      UIButton::BUTTON_ANIMATION_NONE, 0, 0, 0, 0, false },
    { "BT-013", "Disable+热区(20,20,20,20)", "显示禁用态;视觉区/扩展区点击均无回调无动画",
      BUTTON_CASE_DEMO, true, false, false, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, 20, 20, 20, 20, true },
    { "BT-014", "高频点击压测x100", "自动按压/释放/点击100次;回调数与输入一致;无异常残留",
      BUTTON_CASE_STRESS_CLICK, false, false, false, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, 0, 0, 0, 0, false },
    { "BT-015", "100按钮热区命中", "100个按钮各设热区(4,4,4,4);自动校验热区+点击命中统计",
      BUTTON_CASE_STRESS_MANY, false, false, false, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, 0, 0, 0, 0, false },
    { "BT-016", "动效配置反复切换", "自动循环repeat(0/1/2/10)与effect(NONE/SCALE)并按压;停止后显示实时配置",
      BUTTON_CASE_STRESS_CONFIG, false, false, false, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, 0, 0, 0, 0, false },
    { "BT-017", "禁用/启用长稳切换", "自动循环Enable/Disable并校验touchable;启用恢复响应,无残留动画",
      BUTTON_CASE_STRESS_ENABLE, false, false, false, false, 1,
      UIButton::BUTTON_ANIMATION_SCALE, 40, 40, 40, 40, false },
};
const uint32_t g_buttonRmCaseNum = sizeof(g_buttonRmCases) / sizeof(g_buttonRmCases[0]);

namespace {
constexpr uint32_t STRESS_TARGET = 1000;
constexpr uint32_t STRESS_CLICK_TARGET = 100;
constexpr uint32_t MANY_BUTTON_NUM = 100;
constexpr int16_t MANY_EXPAND = 4;

constexpr int16_t CONT_X = 100;
constexpr int16_t CONT_Y = 0;
constexpr int16_t CONT_W = 760;
constexpr int16_t CONT_H = 400;
constexpr uint8_t CONT_RADIUS = 16;

constexpr int16_t DEMO_BTN_W = 220;
constexpr int16_t DEMO_BTN_H = 90;
constexpr int16_t DEMO_BTN_X = (CONT_W - DEMO_BTN_W) / 2;
constexpr int16_t DEMO_BTN_Y = 90;
constexpr uint8_t DEMO_BTN_RADIUS = 8;
constexpr uint8_t DEMO_BTN_FONT = 26;

constexpr int16_t ACTION_BTN_X = 530;
constexpr int16_t ACTION_BTN_Y = 115;
constexpr int16_t ACTION_BTN_W = 130;
constexpr int16_t ACTION_BTN_H = 44;
constexpr uint8_t ACTION_BTN_FONT = 22;
constexpr int16_t ADJ_BTN_X = 560;
constexpr int16_t ADJ_BTN_W = 140;
constexpr int16_t CFG_LABEL_Y = 200;
constexpr int16_t INFO_LABEL_Y = 236;
constexpr int16_t COUNT_LABEL_Y = 276;
constexpr int16_t MANY_GRID_X = 24;
constexpr int16_t MANY_GRID_Y = 116;
constexpr int16_t MANY_PITCH_X = 72;
constexpr int16_t MANY_PITCH_Y = 27;
constexpr int16_t MANY_BTN_W = 64;
constexpr int16_t MANY_BTN_H = 22;
constexpr uint32_t MANY_COLS = 10;

constexpr int16_t INFO_X = 24;
constexpr int16_t INFO_W = 712;
constexpr uint8_t INFO_SIZE = 22;
constexpr uint8_t HINT_SIZE = 20;
constexpr int16_t HINT_X = 24;
constexpr int16_t HINT_Y = 340;
constexpr int16_t HINT_W = 712;
constexpr int16_t HINT_H = 44;

constexpr uint8_t HOTZONE_OPA = 60;

constexpr int16_t TITLE_X = 24;
constexpr int16_t TITLE_Y = 4;
constexpr int16_t TITLE_W = 712;
constexpr uint8_t TITLE_H = 26;
constexpr uint8_t TITLE_FONT = 20;

constexpr int16_t LABEL_HEIGHT = 36;
constexpr int16_t COUNT_LABEL_HEIGHT = 40;
constexpr int16_t MANY_INFO_LABEL_Y = 56;
constexpr int16_t MANY_COUNT_LABEL_Y = 88;
constexpr uint8_t MANY_BTN_FONT = 16;
constexpr int16_t MANY_EXPAND_MULTIPLIER = 2;
constexpr uint32_t STRESS_REPORT_INTERVAL = 50;
constexpr uint32_t STRESS_CONFIG_REPORT_INTERVAL = 25;

const char* EffectName(UIButton::ButtonAnimationEffect effect)
{
    switch (effect) {
        case UIButton::BUTTON_ANIMATION_NONE: return "NONE";
        case UIButton::BUTTON_ANIMATION_SCALE: return "SCALE";
        default: return "?";
    }
}

void BuildReadBackText(UILabelButton* btn, char* buf, uint32_t bufSize)
{
    int16_t l = 0;
    int16_t t = 0;
    int16_t r = 0;
    int16_t b = 0;
    btn->GetTouchExpand(l, t, r, b);
#if defined(DEFAULT_ANIMATION) && DEFAULT_ANIMATION
    (void)snprintf_s(buf, bufSize, bufSize - 1, "读回: 热区(%d,%d,%d,%d) repeat=%u effect=%s", l, t, r, b,
                     static_cast<unsigned int>(btn->GetAnimationRepeatCount()),
                     EffectName(btn->GetAnimationEffect()));
#else
    (void)snprintf_s(buf, bufSize, bufSize - 1, "读回: 热区(%d,%d,%d,%d)", l, t, r, b);
#endif
}

UILabel* CreateLabel(UIViewGroup* container, int16_t x, int16_t y, int16_t w, int16_t h,
                     const char* text, uint8_t font, ColorType color)
{
    UILabel* label = GraphicCreateView<UILabel>(container);
    if (label != nullptr) {
        label->SetPosition(x, y, w, h);
        label->SetText(text);
        label->SetFont(DEFAULT_VECTOR_FONT_FILENAME, font);
        label->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(color));
    }
    return label;
}

UILabel* CreateReadBackLabel(UIViewGroup* container, UILabelButton* btn)
{
    char readBuf[160];
    BuildReadBackText(btn, readBuf, sizeof(readBuf));
    return CreateLabel(container, INFO_X, INFO_LABEL_Y, INFO_W, LABEL_HEIGHT, readBuf,
                       HINT_SIZE, Color::GetColorFromRGB(0xFF, 0xD7, 0x00));
}

UILabel* CreateTitleLabel(UIViewGroup* container, const ButtonRmCase* case_)
{
    char title[96];
    (void)snprintf_s(title, sizeof(title), sizeof(title) - 1, "%s %s", case_->id, case_->name);
    return CreateLabel(container, TITLE_X, TITLE_Y, TITLE_W, TITLE_H, title, TITLE_FONT, Color::White());
}

UIView* CreateHotZone(UIViewGroup* container, int16_t x, int16_t y, int16_t w, int16_t h,
                      int16_t l, int16_t t, int16_t r, int16_t b)
{
    UIView* zone = GraphicCreateView<UIView>(container);
    if (zone != nullptr) {
        zone->SetPosition(x - l, y - t, w + l + r, h + t + b);
        zone->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x00, 0xC8, 0x50)));
        zone->SetStyle(STYLE_BACKGROUND_OPA, HOTZONE_OPA);
        zone->SetStyle(STYLE_BORDER_RADIUS, DEMO_BTN_RADIUS);
        zone->SetTouchable(false);
    }
    return zone;
}

void CreateDemoHotZone(UIViewGroup* container, UILabelButton* btn)
{
    int16_t l = 0;
    int16_t t = 0;
    int16_t r = 0;
    int16_t b = 0;
    btn->GetTouchExpand(l, t, r, b);
    (void)CreateHotZone(container, DEMO_BTN_X, DEMO_BTN_Y, DEMO_BTN_W, DEMO_BTN_H, l, t, r, b);
    container->Remove(btn);
    container->Add(btn);
}

void CreateStressHotZone(UIViewGroup* container, UILabelButton* btn)
{
    int16_t hzL = 0;
    int16_t hzT = 0;
    int16_t hzR = 0;
    int16_t hzB = 0;
    btn->GetTouchExpand(hzL, hzT, hzR, hzB);
    if ((hzL != 0) || (hzT != 0) || (hzR != 0) || (hzB != 0)) {
        UIView* zone = CreateHotZone(container, DEMO_BTN_X, DEMO_BTN_Y,
                                     DEMO_BTN_W, DEMO_BTN_H, hzL, hzT, hzR, hzB);
        if (zone != nullptr) {
            container->Remove(btn);
            container->Add(btn);
        }
    }
}

UILabel* CreateCfgLabel(UIViewGroup* container, const ButtonRmCase* case_)
{
    char cfgBuf[160];
    if (case_->useDefaults) {
        (void)snprintf_s(cfgBuf, sizeof(cfgBuf), sizeof(cfgBuf) - 1, "配置: 不调用新增 API(全部默认)");
    } else if (case_->invalidEffect) {
        (void)snprintf_s(cfgBuf, sizeof(cfgBuf), sizeof(cfgBuf) - 1,
                         "配置: repeat=%u effect=0xFF(非法) 热区(%d,%d,%d,%d)",
                         static_cast<unsigned int>(case_->repeatCount),
                         case_->expandL, case_->expandT, case_->expandR, case_->expandB);
    } else {
        (void)snprintf_s(cfgBuf, sizeof(cfgBuf), sizeof(cfgBuf) - 1,
                         "配置: repeat=%u effect=%s 热区(%d,%d,%d,%d)%s",
                         static_cast<unsigned int>(case_->repeatCount), EffectName(case_->effect),
                         case_->expandL, case_->expandT, case_->expandR, case_->expandB,
                         case_->disabled ? " disabled" : "");
    }
    return CreateLabel(container, INFO_X, CFG_LABEL_Y, INFO_W, LABEL_HEIGHT, cfgBuf, HINT_SIZE,
                       Color::GetColorFromRGB(0xCF, 0xCF, 0xCF));
}

UILabelButton* CreateStressToggleButton(UIViewGroup* container)
{
    UILabelButton* toggleBtn = GraphicCreateView<UILabelButton>(container);
    if (toggleBtn != nullptr) {
        toggleBtn->SetPosition(ACTION_BTN_X, ACTION_BTN_Y, ACTION_BTN_W, ACTION_BTN_H);
        toggleBtn->SetText("开始压测");
        toggleBtn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, ACTION_BTN_FONT);
        toggleBtn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
        toggleBtn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x00, 0x80, 0xFF)));
        toggleBtn->SetStyle(STYLE_BORDER_RADIUS, DEMO_BTN_RADIUS);
        toggleBtn->SetTouchable(true);
    }
    return toggleBtn;
}

void CreateHintLabel(UIViewGroup* container, const ButtonRmCase* case_)
{
    (void)CreateLabel(container, HINT_X, HINT_Y, HINT_W, HINT_H, case_->expect, HINT_SIZE,
                      Color::GetColorFromRGB(0x9F, 0x9F, 0x9F));
}
} // namespace

ButtonRmCaseRunner::ButtonRmCaseRunner(const ButtonRmCase* testCase)
    : case_(testCase), container_(nullptr), countLabel_(nullptr), infoLabel_(nullptr),
      demoClickCount_(0), demoOutsideCount_(0), adjacentClickCount_(0), stressPassCount_(0),
      stressFailCount_(0), distinctHitCount_(0), manyHitFlags_{}, currentIsHotZone_(false),
      currentHasAdjacent_(false), listeners_{}, listenerCount_(0)
{
}

ButtonRmCaseRunner::~ButtonRmCaseRunner()
{
    // 先解除监听器与视图的绑定，再删除监听器，最后删除容器子树
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
    countLabel_ = nullptr;
    infoLabel_ = nullptr;
}

void ButtonRmCaseRunner::ResetState()
{
    currentIsHotZone_ = case_->isHotZone;
    currentHasAdjacent_ = case_->adjacent;
    demoClickCount_ = 0;
    demoOutsideCount_ = 0;
    adjacentClickCount_ = 0;
    stressPassCount_ = 0;
    stressFailCount_ = 0;
    distinctHitCount_ = 0;
    (void)memset_s(manyHitFlags_, sizeof(manyHitFlags_), 0, sizeof(manyHitFlags_));
    listenerCount_ = 0;
}

UIViewGroup* ButtonRmCaseRunner::Build(UIViewGroup* content)
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

    switch (case_->type) {
        case BUTTON_CASE_DEMO:
            ShowDemoCase();
            break;
        case BUTTON_CASE_INTERRUPT:
            ShowInterruptCase();
            break;
        case BUTTON_CASE_STRESS_CLICK:
        case BUTTON_CASE_STRESS_CONFIG:
        case BUTTON_CASE_STRESS_ENABLE:
            ShowStressCase();
            break;
        case BUTTON_CASE_STRESS_MANY:
            ShowManyButtonsCase();
            break;
        default:
            break;
    }

    if (case_->type != BUTTON_CASE_STRESS_MANY) {
        CreateHintLabel(container_, case_);
    }

    (void)CreateTitleLabel(container_, case_);
    return container_;
}

void ButtonRmCaseRunner::AddClickListener(UIView* view, std::function<bool(UIView&, const ClickEvent&)> fn)
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

void ButtonRmCaseRunner::SetInfoText(const char* text)
{
    if (infoLabel_ != nullptr) {
        infoLabel_->SetText(text);
    }
}

void ButtonRmCaseRunner::RefreshCount()
{
    if (countLabel_ == nullptr) {
        return;
    }
    char buf[96];
    if (currentIsHotZone_ && currentHasAdjacent_) {
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "点击=%u  相邻=%u  区外=%u",
                         demoClickCount_, adjacentClickCount_, demoOutsideCount_);
    } else if (currentIsHotZone_) {
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "点击=%u  区外=%u",
                         demoClickCount_, demoOutsideCount_);
    } else {
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "点击=%u", demoClickCount_);
    }
    countLabel_->SetText(buf);
}

UILabelButton* ButtonRmCaseRunner::CreateDemoButton()
{
    UILabelButton* btn = GraphicCreateView<UILabelButton>(container_);
    if (btn == nullptr) {
        return nullptr;
    }
    btn->SetPosition(DEMO_BTN_X, DEMO_BTN_Y, DEMO_BTN_W, DEMO_BTN_H);
    btn->SetText("测试按钮");
    btn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, DEMO_BTN_FONT);
    btn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    btn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x00, 0x80, 0xFF)));
    btn->SetStyle(STYLE_BORDER_RADIUS, DEMO_BTN_RADIUS);
    btn->SetTouchable(true);
    if (!case_->useDefaults) {
        btn->SetTouchExpand(case_->expandL, case_->expandT, case_->expandR, case_->expandB);
#if defined(DEFAULT_ANIMATION) && DEFAULT_ANIMATION
        btn->SetAnimationRepeatCount(case_->repeatCount);
        if (case_->invalidEffect) {
            btn->SetAnimationEffect(static_cast<UIButton::ButtonAnimationEffect>(0xFF));
        } else {
            btn->SetAnimationEffect(case_->effect);
        }
#endif
    }
    if (case_->disabled) {
        btn->Disable();
    }
    AddClickListener(btn, [this](UIView& view, const ClickEvent& event) -> bool {
        (void)view;
        (void)event;
        demoClickCount_++;
        RefreshCount();
        return true;
    });
    return btn;
}

void ButtonRmCaseRunner::CreateDemoAdjacentButton()
{
    UILabelButton* adj = GraphicCreateView<UILabelButton>(container_);
    if (adj == nullptr) {
        return;
    }
    adj->SetPosition(ADJ_BTN_X, DEMO_BTN_Y, ADJ_BTN_W, DEMO_BTN_H);
    adj->SetText("相邻控件");
    adj->SetFont(DEFAULT_VECTOR_FONT_FILENAME, DEMO_BTN_FONT);
    adj->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    adj->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x66, 0x66, 0x66)));
    adj->SetStyle(STYLE_BORDER_RADIUS, DEMO_BTN_RADIUS);
    adj->SetTouchable(true);
    AddClickListener(adj, [this](UIView& view, const ClickEvent& event) -> bool {
        (void)view;
        (void)event;
        adjacentClickCount_++;
        RefreshCount();
        return true;
    });
}

void ButtonRmCaseRunner::CreateDemoCountLabel()
{
    countLabel_ = CreateLabel(container_, INFO_X, COUNT_LABEL_Y, INFO_W, COUNT_LABEL_HEIGHT,
                              "点击=0", INFO_SIZE, Color::White());
}

void ButtonRmCaseRunner::ShowDemoCase()
{
    UILabelButton* btn = CreateDemoButton();
    if (btn == nullptr) {
        return;
    }

    if (case_->isHotZone) {
        CreateDemoHotZone(container_, btn);
    }

    if (case_->adjacent) {
        CreateDemoAdjacentButton();
    }

    (void)CreateCfgLabel(container_, case_);
    infoLabel_ = CreateReadBackLabel(container_, btn);
    CreateDemoCountLabel();
    RefreshCount();

    if (case_->isHotZone) {
        AddClickListener(container_, [this](UIView& view, const ClickEvent& event) -> bool {
            (void)view;
            (void)event;
            demoOutsideCount_++;
            RefreshCount();
            return true;
        });
    }
}

void ButtonRmCaseRunner::ShowInterruptCase()
{
    UILabelButton* btn = CreateDemoButton();
    if (btn == nullptr) {
        return;
    }

    infoLabel_ = CreateReadBackLabel(container_, btn);

    (void)CreateLabel(container_, INFO_X, CFG_LABEL_Y, INFO_W, LABEL_HEIGHT,
                      "需保持按住按钮,动画才持续循环播放;松开自动恢复。点\"中断动画\"停止并复位",
                      HINT_SIZE, Color::GetColorFromRGB(0xCF, 0xCF, 0xCF));

    UILabelButton* stopBtn = GraphicCreateView<UILabelButton>(container_);
    if (stopBtn != nullptr) {
        stopBtn->SetPosition(ACTION_BTN_X, ACTION_BTN_Y, ACTION_BTN_W, ACTION_BTN_H);
        stopBtn->SetText("中断动画");
        stopBtn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, ACTION_BTN_FONT);
        stopBtn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
        stopBtn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xC8, 0x50, 0x00)));
        stopBtn->SetStyle(STYLE_BORDER_RADIUS, DEMO_BTN_RADIUS);
        stopBtn->SetTouchable(true);
        AddClickListener(stopBtn, [this, btn](UIView& view, const ClickEvent& event) -> bool {
            (void)view;
            (void)event;
            btn->SetAnimationRepeatCount(0);
            SetInfoText("已中断: repeat=0,动画停止并复位,Button恢复正常");
            return true;
        });
    }
}

void ButtonRmCaseRunner::RunStressClickStep(UILabelButton* btn, RmStressDriver* driver,
                                            UILabelButton* toggleBtn, uint32_t iter)
{
    Point pos = { 10, 10 };
    uint32_t done = iter + 1;
    PressEvent press(pos);
    ReleaseEvent release(pos);
    ClickEvent click(pos);
    btn->OnPressEvent(press);
    btn->OnReleaseEvent(release);
    btn->OnClickEvent(click);
    if ((done % STRESS_REPORT_INTERVAL == 0) || (done >= STRESS_CLICK_TARGET)) {
        char buf[96];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                         "已执行=%u 回调=%u", done, demoClickCount_);
        SetInfoText(buf);
    }
    if (done >= STRESS_CLICK_TARGET) {
        FinishStressClick(btn, driver, toggleBtn);
    }
}

void ButtonRmCaseRunner::RunStressConfigStep(UILabelButton* btn, RmStressDriver* driver,
                                             UILabelButton* toggleBtn, uint32_t iter)
{
    Point pos = { 10, 10 };
    static constexpr uint16_t kRepeats[4] = { 0, 1, 2, 10 };
    uint16_t repeat = kRepeats[(iter / 2) % 4];
    UIButton::ButtonAnimationEffect effect = (iter % 2 == 0) ?
        UIButton::BUTTON_ANIMATION_SCALE : UIButton::BUTTON_ANIMATION_NONE;
    btn->SetAnimationEffect(UIButton::BUTTON_ANIMATION_NONE);
    btn->SetAnimationRepeatCount(repeat);
    btn->SetAnimationEffect(effect);
    PressEvent press(pos);
    ReleaseEvent release(pos);
    btn->OnPressEvent(press);
    btn->OnReleaseEvent(release);
    uint32_t done = iter + 1;
    if ((done % STRESS_CONFIG_REPORT_INTERVAL == 0) || (done >= STRESS_TARGET)) {
        char buf[96];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                         "轮次=%u 当前 repeat=%u effect=%s",
                         done, static_cast<unsigned int>(repeat), EffectName(effect));
        SetInfoText(buf);
    }
    if (done >= STRESS_TARGET) {
        FinishStressConfig(btn, driver, toggleBtn);
    }
}

void ButtonRmCaseRunner::RunStressEnableStep(UILabelButton* btn, RmStressDriver* driver,
                                             UILabelButton* toggleBtn, uint32_t iter)
{
    bool enable = (iter % 2 == 0);
    if (enable) {
        btn->Enable();
    } else {
        btn->Disable();
    }
    if (btn->IsTouchable() == enable) {
        stressPassCount_++;
    } else {
        stressFailCount_++;
    }
    uint32_t done = iter + 1;
    if ((done % STRESS_REPORT_INTERVAL == 0) || (done >= STRESS_TARGET)) {
        char buf[96];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                         "轮次=%u 通过=%u 异常=%u",
                         done, stressPassCount_, stressFailCount_);
        SetInfoText(buf);
    }
    if (done >= STRESS_TARGET) {
        FinishStressEnable(btn, driver, toggleBtn);
    }
}

void ButtonRmCaseRunner::FinishStressClick(UILabelButton* btn, RmStressDriver* driver,
                                           UILabelButton* toggleBtn)
{
    driver->Stop();
    btn->SetAnimationRepeatCount(0);
    btn->SetAnimationRepeatCount(1);
    toggleBtn->SetText("开始压测");
    toggleBtn->Invalidate();
    char buf[96];
    (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "完成%u次: 回调=%u %s",
                     STRESS_CLICK_TARGET, demoClickCount_,
                     (demoClickCount_ == STRESS_CLICK_TARGET) ? "(一致)" : "(不一致!)");
    SetInfoText(buf);
}

void ButtonRmCaseRunner::FinishStressConfig(UILabelButton* btn, RmStressDriver* driver,
                                            UILabelButton* toggleBtn)
{
    driver->Stop();
    char rb[160];
    BuildReadBackText(btn, rb, sizeof(rb));
    char buf[224];
    (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                     "完成%u轮,保持末次档位  %s", STRESS_TARGET, rb);
    SetInfoText(buf);
    toggleBtn->SetText("开始压测");
    toggleBtn->Invalidate();
}

void ButtonRmCaseRunner::FinishStressEnable(UILabelButton* btn, RmStressDriver* driver,
                                            UILabelButton* toggleBtn)
{
    driver->Stop();
    char buf[96];
    (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                     "完成%u轮: 通过=%u 异常=%u,保持当前%s",
                     STRESS_TARGET, stressPassCount_, stressFailCount_,
                     btn->IsTouchable() ? "启用" : "禁用");
    SetInfoText(buf);
    toggleBtn->SetText("开始压测");
    toggleBtn->Invalidate();
}

void ButtonRmCaseRunner::RunStressStep(UILabelButton* btn, RmStressDriver* driver,
                                       ButtonRmCaseType type, UILabelButton* toggleBtn,
                                       uint32_t iter)
{
    switch (type) {
        case BUTTON_CASE_STRESS_CLICK:
            RunStressClickStep(btn, driver, toggleBtn, iter);
            break;
        case BUTTON_CASE_STRESS_CONFIG:
            RunStressConfigStep(btn, driver, toggleBtn, iter);
            break;
        case BUTTON_CASE_STRESS_ENABLE:
            RunStressEnableStep(btn, driver, toggleBtn, iter);
            break;
        default:
            driver->Stop();
            break;
    }
}

void ButtonRmCaseRunner::OnStressToggleClick(UILabelButton* btn, RmStressDriver* driver,
                                             ButtonRmCaseType type, UILabelButton* toggleBtn)
{
    if (driver->IsRunning()) {
        driver->Stop();
        char rb[160];
        char buf[224];
        if (type == BUTTON_CASE_STRESS_CONFIG) {
            BuildReadBackText(btn, rb, sizeof(rb));
            (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                             "已停止,保持当前档位  %s", rb);
        } else if (type == BUTTON_CASE_STRESS_ENABLE) {
            BuildReadBackText(btn, rb, sizeof(rb));
            (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                             "已停止,保持当前%s  %s",
                             btn->IsTouchable() ? "启用" : "禁用", rb);
        } else {
            btn->SetAnimationRepeatCount(0);
            btn->SetAnimationEffect(UIButton::BUTTON_ANIMATION_SCALE);
            btn->SetAnimationRepeatCount(1);
            btn->Enable();
            BuildReadBackText(btn, rb, sizeof(rb));
            (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                             "已停止,实时配置  %s", rb);
        }
        SetInfoText(buf);
        toggleBtn->SetText("开始压测");
    } else {
        driver->Start();
        toggleBtn->SetText("停止压测");
    }
    toggleBtn->Invalidate();
}

void ButtonRmCaseRunner::ShowStressCase()
{
    UILabelButton* btn = CreateDemoButton();
    if (btn == nullptr) {
        return;
    }

    CreateStressHotZone(container_, btn);

    stressPassCount_ = 0;
    stressFailCount_ = 0;

    RmStressDriver* driver = GraphicCreateView<RmStressDriver>(container_);
    if (driver == nullptr) {
        return;
    }
    driver->SetPosition(0, 0, 1, 1);
    driver->SetTouchable(false);

    infoLabel_ = CreateLabel(container_, INFO_X, INFO_LABEL_Y, INFO_W, LABEL_HEIGHT,
                             "点\"开始压测\"启动自动循环", HINT_SIZE,
                             Color::GetColorFromRGB(0xFF, 0xD7, 0x00));
    countLabel_ = CreateLabel(container_, INFO_X, COUNT_LABEL_Y, INFO_W, COUNT_LABEL_HEIGHT,
                              "点击=0", INFO_SIZE, Color::White());

    ButtonRmCaseType type = case_->type;

    UILabelButton* toggleBtn = CreateStressToggleButton(container_);
    if (toggleBtn == nullptr) {
        return;
    }

    driver->SetStepHandler([this, btn, driver, type, toggleBtn](uint32_t iter) {
        RunStressStep(btn, driver, type, toggleBtn, iter);
    });

    AddClickListener(toggleBtn, [this, btn, driver, type, toggleBtn](UIView& view, const ClickEvent& event) -> bool {
        (void)view;
        (void)event;
        OnStressToggleClick(btn, driver, type, toggleBtn);
        return true;
    });
}

void ButtonRmCaseRunner::CreateManyButton(uint32_t i, uint32_t& passCount)
{
    UILabelButton* btn = GraphicCreateView<UILabelButton>(container_);
    if (btn == nullptr) {
        return;
    }
    int16_t x = MANY_GRID_X + static_cast<int16_t>(i % MANY_COLS) * MANY_PITCH_X;
    int16_t y = MANY_GRID_Y + static_cast<int16_t>(i / MANY_COLS) * MANY_PITCH_Y;
    btn->SetPosition(x, y, MANY_BTN_W, MANY_BTN_H);
    char text[8];
    (void)snprintf_s(text, sizeof(text), sizeof(text) - 1, "%u", i);
    btn->SetText(text);
    btn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, MANY_BTN_FONT);
    btn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    btn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x00, 0x80, 0xFF)));
    btn->SetStyle(STYLE_BORDER_RADIUS, DEMO_BTN_RADIUS);
    btn->SetTouchable(true);
    btn->SetTouchExpand(MANY_EXPAND, MANY_EXPAND, MANY_EXPAND, MANY_EXPAND);

    Rect visual = btn->GetRect();
    Rect touch = btn->GetTouchableRect();
    if ((touch.GetX() == visual.GetX() - MANY_EXPAND) && (touch.GetY() == visual.GetY() - MANY_EXPAND) &&
        (touch.GetWidth() == visual.GetWidth() + MANY_EXPAND * MANY_EXPAND_MULTIPLIER) &&
        (touch.GetHeight() == visual.GetHeight() + MANY_EXPAND * MANY_EXPAND_MULTIPLIER)) {
        passCount++;
    }

    AddClickListener(btn, [this, i](UIView& view, const ClickEvent& event) -> bool {
        (void)view;
        (void)event;
        demoClickCount_++;
        if (!manyHitFlags_[i]) {
            manyHitFlags_[i] = true;
            distinctHitCount_++;
        }
        if (countLabel_ != nullptr) {
            char buf[96];
            (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                             "点击=%u  命中不同按钮=%u",
                             demoClickCount_, distinctHitCount_);
            countLabel_->SetText(buf);
        }
        return true;
    });
}

void ButtonRmCaseRunner::ShowManyButtonsCase()
{
    (void)memset_s(manyHitFlags_, sizeof(manyHitFlags_), 0, sizeof(manyHitFlags_));
    distinctHitCount_ = 0;
    uint32_t passCount = 0;

    for (uint32_t i = 0; i < MANY_BUTTON_NUM; i++) {
        CreateManyButton(i, passCount);
    }

    char infoBuf[96];
    (void)snprintf_s(infoBuf, sizeof(infoBuf), sizeof(infoBuf) - 1,
                     "热区自动校验: %u/%u 通过(矩形四向各扩%dpx)",
                     passCount, MANY_BUTTON_NUM, MANY_EXPAND);
    infoLabel_ = CreateLabel(container_, INFO_X, MANY_INFO_LABEL_Y, INFO_W, LABEL_HEIGHT,
                             infoBuf, HINT_SIZE, Color::GetColorFromRGB(0xFF, 0xD7, 0x00));
    countLabel_ = CreateLabel(container_, INFO_X, MANY_COUNT_LABEL_Y, INFO_W, LABEL_HEIGHT,
                              "点击=0  命中不同按钮=0", HINT_SIZE, Color::White());
}

} // namespace OHOS
#endif // GRAPHIC_ENABLE_BUTTON_FLAG

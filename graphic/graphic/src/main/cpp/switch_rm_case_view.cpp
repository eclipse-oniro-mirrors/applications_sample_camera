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

#include "switch_rm_case_view.h"

#if GRAPHIC_ENABLE_SWITCH_FLAG
#include <cstdio>
#include <new>
#include "components/ui_view_group.h"
#include "events/click_event.h"
#include "graphic_utils.h"
#include "securec.h"

namespace OHOS {

const SwitchRmCase g_switchRmCases[] = {
    { "SW-001", "默认创建与状态切换", "不调新增API: 默认轨道/滑块/边框显示不变,状态切换正常",
      SWITCH_CASE_DEMO, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false },
    { "SW-002", "on/off滑块尺寸独立配置", "SELECTED用on=10,UNSELECTED用off=8,两态互不覆盖",
      SWITCH_CASE_DEMO, true, 10, true, 8, false, 0, false, 0, false, 0, false, 0, false },
    { "SW-003", "on/off滑块颜色独立配置", "选中态滑块白,非选中态灰,随状态切换",
      SWITCH_CASE_DEMO, false, 0, false, 0, true, 0xFFFFFF, true, 0x808080, false, 0, false, 0, false },
    { "SW-004", "on/off边框颜色配置", "选中态绿边框,非选中态红边框(宽1px恒不透明,代码无独立alpha)",
      SWITCH_CASE_DEMO, false, 0, false, 0, false, 0, false, 0, true, 0x00FF00, true, 0xFF0000, false },
    { "SW-005", "getter返回配置值", "6项getter逐项与setter入参比对,应全部一致",
      SWITCH_CASE_VERIFY_GETTER, true, 10, true, 8, true, 0xFFFFFF, true, 0x808080,
      true, 0x00FF00, true, 0xFF0000, false },
    { "SW-006", "尺寸+颜色+边框组合配置", "初始ON: 尺寸/滑块色/边框均按当前状态生效,组合无冲突",
      SWITCH_CASE_DEMO, true, 12, true, 8, true, 0xFFD700, true, 0x00C8C8,
      true, 0x00FF00, true, 0xFF0000, true },
    { "SW-007", "thumb size为0", "size=0 setter直接保存,绘制阶段回默认半径;读回0",
      SWITCH_CASE_DEMO, true, 0, true, 12, false, 0, false, 0, false, 0, false, 0, false },
    { "SW-008", "thumb size超轨道圆角999", "999 setter直接保存,绘制阶段回默认半径;读回999",
      SWITCH_CASE_DEMO, true, 999, true, 10, false, 0, false, 0, false, 0, false, 0, false },
    { "SW-009", "半径<=1时边框不绘制", "drawRadius<=边框宽1px: 不画边框,仅1px实心滑块(黑边框便于辨别)",
      SWITCH_CASE_DEMO, true, 1, false, 0, false, 0, false, 0, true, 0x000000, false, 0, true },
    { "SW-010", "未配置thumb color", "只配边框: 滑块保持默认白色,边框配置仍生效",
      SWITCH_CASE_DEMO, false, 0, false, 0, false, 0, false, 0, true, 0x00FF00, true, 0xFF0000, false },
    { "SW-011", "未配置border color", "只配滑块色: 不绘制边框,滑块色按配置生效",
      SWITCH_CASE_DEMO, false, 0, false, 0, true, 0xFFFFFF, true, 0x808080, false, 0, false, 0, false },
    { "SW-012", "高频状态切换x200", "自动切换ON/OFF 200次: 回调数与切换一致,无异常日志",
      SWITCH_CASE_STRESS_TOGGLE, true, 12, true, 8, true, 0xFFD700, true, 0x00C8C8,
      true, 0x00FF00, true, 0xFF0000, false },
    { "SW-013", "90个Switch批量配置", " 90个各配不同尺寸/滑块色,逐项读回防串扰",
      SWITCH_CASE_MANY, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false },
    { "SW-014", "长稳循环切换校验", "自动循环切换200轮: 每轮校验GetState一致,无残留",
      SWITCH_CASE_STRESS_STATE, true, 12, true, 8, true, 0xFFD700, true, 0x00C8C8,
      true, 0x00FF00, true, 0xFF0000, false },
    { "SW-015", "运行时反复覆盖配置", "自动循环覆盖6项配置1000轮: 每轮读回=末次配置,设置/读回同屏对照",
      SWITCH_CASE_STRESS_CONFIG, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false },
};
const uint32_t g_switchRmCaseNum = sizeof(g_switchRmCases) / sizeof(g_switchRmCases[0]);

namespace {
constexpr uint32_t STRESS_TARGET = 1000;
constexpr uint32_t STRESS_TOGGLE_TARGET = 200;
constexpr uint32_t MANY_GRID_SLOTS = 100;

constexpr int16_t CONT_X = 100;
constexpr int16_t CONT_Y = 0;
constexpr int16_t CONT_W = 760;
constexpr int16_t CONT_H = 400;
constexpr uint8_t CONT_RADIUS = 16;

constexpr int16_t SW_DEMO_W = 184;
constexpr int16_t SW_DEMO_H = 92;
constexpr int16_t SW_DEMO_X = (CONT_W - SW_DEMO_W) / 2;
constexpr int16_t SW_DEMO_Y = 56;
constexpr int16_t ACTION_BTN_X = 560;
constexpr int16_t ACTION_BTN_Y = 100;
constexpr int16_t ACTION_BTN_W = 130;
constexpr int16_t ACTION_BTN_H = 44;
constexpr uint8_t ACTION_BTN_FONT = 22;
constexpr int16_t CFG_LABEL_Y = 164;
constexpr int16_t READ_LABEL_Y = 196;
constexpr int16_t STATE_LABEL_Y = 228;
constexpr int16_t LABEL_LINE_H = 36;
constexpr int16_t MANY_GRID_X = 24;
constexpr int16_t MANY_GRID_Y = 88;
constexpr int16_t MANY_PITCH_X = 72;
constexpr int16_t MANY_PITCH_Y = 30;
constexpr int16_t MANY_BTN_W = 64;
constexpr int16_t MANY_BTN_H = 28;
constexpr uint32_t MANY_COLS = 10;

constexpr int16_t INFO_X = 24;
constexpr int16_t INFO_W = 712;
constexpr uint8_t INFO_SIZE = 22;
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

constexpr uint8_t ACTION_BTN_RADIUS = 8;
constexpr uint8_t TOGGLE_PARITY_MOD = 2;
constexpr uint8_t STRESS_REPORT_INTERVAL = 50;
constexpr uint8_t VERIFY_ITEM_COUNT = 6;
constexpr uint8_t RGB_SHIFT_R = 16;
constexpr uint8_t RGB_SHIFT_G = 8;
constexpr uint8_t RGB_MASK = 0xFF;
constexpr int16_t MANY_INFO_Y = 32;
constexpr int16_t MANY_TIP_Y = 64;
constexpr int16_t MANY_TIP_H = 24;

ColorType Rgb(uint32_t rgb)
{
    return Color::GetColorFromRGB((rgb >> RGB_SHIFT_R) & RGB_MASK,
                                  (rgb >> RGB_SHIFT_G) & RGB_MASK,
                                  rgb & RGB_MASK);
}

void BuildCfgText(const SwitchRmCase& testCase, char* buf, uint32_t bufSize)
{
    int32_t len = snprintf_s(buf, bufSize, bufSize - 1, "配置:");
    if (!testCase.setOnSize && !testCase.setOffSize && !testCase.setOnThumb && !testCase.setOffThumb &&
        !testCase.setOnBorder && !testCase.setOffBorder) {
        (void)snprintf_s(buf + len, bufSize - len, bufSize - len - 1, " 不调用新增 API(全部默认)");
        return;
    }
    if (testCase.setOnSize) {
        len += snprintf_s(buf + len, bufSize - len, bufSize - len - 1, " onSize=%d", testCase.onSize);
    }
    if (testCase.setOffSize) {
        len += snprintf_s(buf + len, bufSize - len, bufSize - len - 1, " offSize=%d", testCase.offSize);
    }
    if (testCase.setOnThumb) {
        len += snprintf_s(buf + len, bufSize - len, bufSize - len - 1, " onThumb=#%06X", testCase.onThumb);
    }
    if (testCase.setOffThumb) {
        len += snprintf_s(buf + len, bufSize - len, bufSize - len - 1, " offThumb=#%06X", testCase.offThumb);
    }
    if (testCase.setOnBorder) {
        len += snprintf_s(buf + len, bufSize - len, bufSize - len - 1, " onBorder=#%06X", testCase.onBorder);
    }
    if (testCase.setOffBorder) {
        len += snprintf_s(buf + len, bufSize - len, bufSize - len - 1, " offBorder=#%06X", testCase.offBorder);
    }
}
} // namespace

class SwitchRmCaseRunner::SwitchStateListener : public UICheckBox::OnChangeListener {
public:
    SwitchStateListener(UIToggleButton* toggle, UILabel* stateLabel, uint32_t* changeCount)
        : toggle_(toggle), stateLabel_(stateLabel), changeCount_(changeCount) {}

    bool OnChange(UICheckBox::UICheckBoxState state) override
    {
        if (changeCount_ != nullptr) {
            (*changeCount_)++;
        }
        Refresh(state);
        return true;
    }

    void Refresh(UICheckBox::UICheckBoxState state)
    {
        if (stateLabel_ == nullptr) {
            return;
        }
        bool isOn = (state == UICheckBox::SELECTED);
        int16_t cfg = isOn ? toggle_->GetOnThumbSize() : toggle_->GetOffThumbSize();
        char buf[96];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "状态: %s  该侧尺寸读回=%d  切换=%u",
                         isOn ? "ON" : "OFF", cfg,
                         (changeCount_ != nullptr) ? *changeCount_ : 0);
        stateLabel_->SetText(buf);
    }

private:
    UIToggleButton* toggle_;
    UILabel* stateLabel_;
    uint32_t* changeCount_;
};

SwitchRmCaseRunner::SwitchRmCaseRunner(const SwitchRmCase* testCase)
    : case_(testCase), container_(nullptr), countLabel_(nullptr), infoLabel_(nullptr),
      toggle_(nullptr), changeListener_(nullptr), changeCount_(0), stressPassCount_(0),
      stressFailCount_(0), listeners_{}, listenerCount_(0)
{
}

SwitchRmCaseRunner::~SwitchRmCaseRunner()
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
    if ((toggle_ != nullptr) && (changeListener_ != nullptr)) {
        toggle_->SetOnChangeListener(nullptr);
    }
    delete changeListener_;
    changeListener_ = nullptr;
    if (container_ != nullptr) {
        GraphicDeleteViewTree(container_);
        container_ = nullptr;
    }
    toggle_ = nullptr;
    countLabel_ = nullptr;
    infoLabel_ = nullptr;
}

void SwitchRmCaseRunner::ResetState()
{
    changeCount_ = 0;
    stressPassCount_ = 0;
    stressFailCount_ = 0;
    listenerCount_ = 0;
    changeListener_ = nullptr;
    toggle_ = nullptr;
}

UIViewGroup* SwitchRmCaseRunner::Build(UIViewGroup* content)
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
        case SWITCH_CASE_DEMO:
            ShowDemoCase();
            break;
        case SWITCH_CASE_VERIFY_GETTER:
            ShowVerifyCase();
            break;
        case SWITCH_CASE_STRESS_TOGGLE:
        case SWITCH_CASE_STRESS_STATE:
        case SWITCH_CASE_STRESS_CONFIG:
            ShowStressCase();
            break;
        case SWITCH_CASE_MANY:
            ShowManyCase();
            break;
        default:
            break;
    }

    if (case_->type != SWITCH_CASE_MANY) {
        UILabel* hint = GraphicCreateView<UILabel>(container_);
        if (hint != nullptr) {
            hint->SetPosition(HINT_X, HINT_Y, HINT_W, HINT_H);
            hint->SetText(case_->expect);
            hint->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
            hint->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x9F, 0x9F, 0x9F)));
        }
    }

    CreateTitleLabel();
    return container_;
}

void SwitchRmCaseRunner::CreateTitleLabel()
{
    char title[96];
    (void)snprintf_s(title, sizeof(title), sizeof(title) - 1, "%s %s", case_->id, case_->name);
    UILabel* titleLabel = GraphicCreateView<UILabel>(container_);
    if (titleLabel != nullptr) {
        titleLabel->SetPosition(TITLE_X, TITLE_Y, TITLE_W, TITLE_H);
        titleLabel->SetText(title);
        titleLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, TITLE_FONT);
        titleLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    }
}

void SwitchRmCaseRunner::AddClickListener(UIView* view, std::function<bool(UIView&, const ClickEvent&)> fn)
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

void SwitchRmCaseRunner::SetInfoText(const char* text)
{
    if (infoLabel_ != nullptr) {
        infoLabel_->SetText(text);
    }
}

UIToggleButton* SwitchRmCaseRunner::CreateDemoToggle()
{
    UIToggleButton* toggle = GraphicCreateView<UIToggleButton>(container_);
    if (toggle == nullptr) {
        return nullptr;
    }
    toggle->SetPosition(SW_DEMO_X, SW_DEMO_Y, SW_DEMO_W, SW_DEMO_H);
    toggle->SetTouchable(true);
    if (case_->setOnSize) {
        toggle->SetOnThumbSize(case_->onSize);
    }
    if (case_->setOffSize) {
        toggle->SetOffThumbSize(case_->offSize);
    }
    if (case_->setOnThumb) {
        toggle->SetOnThumbColor(Rgb(case_->onThumb));
    }
    if (case_->setOffThumb) {
        toggle->SetOffThumbColor(Rgb(case_->offThumb));
    }
    if (case_->setOnBorder) {
        toggle->SetOnBorderColor(Rgb(case_->onBorder));
    }
    if (case_->setOffBorder) {
        toggle->SetOffBorderColor(Rgb(case_->offBorder));
    }
    toggle->SetState(case_->initialOn);
    toggle_ = toggle;
    return toggle;
}

void SwitchRmCaseRunner::ShowDemoCase()
{
    UIToggleButton* toggle = CreateDemoToggle();
    if (toggle == nullptr) {
        return;
    }

    char cfgBuf[224];
    BuildCfgText(*case_, cfgBuf, sizeof(cfgBuf));
    UILabel* cfgLabel = GraphicCreateView<UILabel>(container_);
    if (cfgLabel != nullptr) {
        cfgLabel->SetPosition(INFO_X, CFG_LABEL_Y, INFO_W, LABEL_LINE_H);
        cfgLabel->SetText(cfgBuf);
        cfgLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        cfgLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xCF, 0xCF, 0xCF)));
    }

    char readBuf[160];
    (void)snprintf_s(readBuf, sizeof(readBuf), sizeof(readBuf) - 1,
                     "读回: on=%d off=%d (滑块色/边框肉眼验)",
                     toggle->GetOnThumbSize(), toggle->GetOffThumbSize());
    UILabel* infoLabel = GraphicCreateView<UILabel>(container_);
    if (infoLabel != nullptr) {
        infoLabel->SetPosition(INFO_X, READ_LABEL_Y, INFO_W, LABEL_LINE_H);
        infoLabel->SetText(readBuf);
        infoLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        infoLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xFF, 0xD7, 0x00)));
    }
    infoLabel_ = infoLabel;

    UILabel* stateLabel = GraphicCreateView<UILabel>(container_);
    if (stateLabel != nullptr) {
        stateLabel->SetPosition(INFO_X, STATE_LABEL_Y, INFO_W, LABEL_LINE_H);
        stateLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, INFO_SIZE);
        stateLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    }
    countLabel_ = stateLabel;
    SwitchStateListener* listener = new (std::nothrow) SwitchStateListener(toggle, stateLabel, &changeCount_);
    if (listener != nullptr) {
        changeListener_ = listener;
        toggle->SetOnChangeListener(listener);
        listener->Refresh(case_->initialOn ? UICheckBox::SELECTED : UICheckBox::UNSELECTED);
    }
}

void SwitchRmCaseRunner::ShowVerifyCase()
{
    UIToggleButton* toggle = CreateDemoToggle();
    if (toggle == nullptr) {
        return;
    }

    bool onSizeOk = (toggle->GetOnThumbSize() == case_->onSize);
    bool offSizeOk = (toggle->GetOffThumbSize() == case_->offSize);
    char line1[160];
    (void)snprintf_s(line1, sizeof(line1), sizeof(line1) - 1,
                     "尺寸: on 设%d读%d %s  off 设%d读%d %s",
                     case_->onSize, toggle->GetOnThumbSize(), onSizeOk ? "OK" : "X",
                     case_->offSize, toggle->GetOffThumbSize(), offSizeOk ? "OK" : "X");
    UILabel* sizeLabel = GraphicCreateView<UILabel>(container_);
    if (sizeLabel != nullptr) {
        sizeLabel->SetPosition(INFO_X, CFG_LABEL_Y, INFO_W, LABEL_LINE_H);
        sizeLabel->SetText(line1);
        sizeLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        sizeLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xFF, 0xD7, 0x00)));
    }

    bool onThumbOk = (toggle->GetOnThumbColor().full == Rgb(case_->onThumb).full);
    bool offThumbOk = (toggle->GetOffThumbColor().full == Rgb(case_->offThumb).full);
    bool onBorderOk = (toggle->GetOnBorderColor().full == Rgb(case_->onBorder).full);
    bool offBorderOk = (toggle->GetOffBorderColor().full == Rgb(case_->offBorder).full);
    char line2[160];
    (void)snprintf_s(line2, sizeof(line2), sizeof(line2) - 1,
                     "滑块色: on %s off %s  边框: on %s off %s",
                     onThumbOk ? "OK" : "X", offThumbOk ? "OK" : "X",
                     onBorderOk ? "OK" : "X", offBorderOk ? "OK" : "X");
    UILabel* colorLabel = GraphicCreateView<UILabel>(container_);
    if (colorLabel != nullptr) {
        colorLabel->SetPosition(INFO_X, READ_LABEL_Y, INFO_W, LABEL_LINE_H);
        colorLabel->SetText(line2);
        colorLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        colorLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xFF, 0xD7, 0x00)));
    }
    infoLabel_ = colorLabel;

    uint32_t pass = (onSizeOk ? 1 : 0) + (offSizeOk ? 1 : 0) + (onThumbOk ? 1 : 0) +
                    (offThumbOk ? 1 : 0) + (onBorderOk ? 1 : 0) + (offBorderOk ? 1 : 0);
    char sumBuf[96];
    (void)snprintf_s(sumBuf, sizeof(sumBuf), sizeof(sumBuf) - 1,
                     "比对一致 %u/%u 项", pass, VERIFY_ITEM_COUNT);
    UILabel* sumLabel = GraphicCreateView<UILabel>(container_);
    if (sumLabel != nullptr) {
        sumLabel->SetPosition(INFO_X, STATE_LABEL_Y, INFO_W, LABEL_LINE_H);
        sumLabel->SetText(sumBuf);
        sumLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, INFO_SIZE);
        sumLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    }
    countLabel_ = sumLabel;
}

void SwitchRmCaseRunner::ShowStressCase()
{
    UIToggleButton* toggle = CreateDemoToggle();
    if (toggle == nullptr) {
        return;
    }
    stressPassCount_ = 0;
    stressFailCount_ = 0;

    RmStressDriver* driver = GraphicCreateView<RmStressDriver>(container_);
    if (driver == nullptr) {
        return;
    }
    driver->SetPosition(0, 0, 1, 1);
    driver->SetTouchable(false);

    UILabel* infoLabel = nullptr;
    UILabel* stateLabel = nullptr;
    UILabel* setLabel = nullptr;
    CreateStressLabels(toggle, infoLabel, stateLabel, setLabel);

    SwitchRmCaseType type = case_->type;

    UILabelButton* toggleBtn = CreateStressToggleButton();
    if (toggleBtn == nullptr) {
        return;
    }

    BindStressStepHandler(driver, toggle, type, setLabel, stateLabel, toggleBtn);
    BindStressToggleClick(driver, toggleBtn);
}

void SwitchRmCaseRunner::CreateStressLabels(UIToggleButton* toggle, UILabel*& infoLabel,
                                            UILabel*& stateLabel, UILabel*& setLabel)
{
    char readBuf[160];
    (void)snprintf_s(readBuf, sizeof(readBuf), sizeof(readBuf) - 1,
                     "读回: on=%d off=%d,点\"开始压测\"启动",
                     toggle->GetOnThumbSize(), toggle->GetOffThumbSize());
    infoLabel = GraphicCreateView<UILabel>(container_);
    if (infoLabel != nullptr) {
        infoLabel->SetPosition(INFO_X, READ_LABEL_Y, INFO_W, LABEL_LINE_H);
        infoLabel->SetText(readBuf);
        infoLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        infoLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xFF, 0xD7, 0x00)));
    }
    infoLabel_ = infoLabel;

    stateLabel = GraphicCreateView<UILabel>(container_);
    if (stateLabel != nullptr) {
        stateLabel->SetPosition(INFO_X, STATE_LABEL_Y, INFO_W, LABEL_LINE_H);
        stateLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, INFO_SIZE);
        stateLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
    }
    countLabel_ = stateLabel;
    SwitchStateListener* listener = new (std::nothrow) SwitchStateListener(toggle, stateLabel, &changeCount_);
    if (listener != nullptr) {
        changeListener_ = listener;
        toggle->SetOnChangeListener(listener);
        listener->Refresh(case_->initialOn ? UICheckBox::SELECTED : UICheckBox::UNSELECTED);
    }

    if (case_->type != SWITCH_CASE_STRESS_CONFIG) {
        return;
    }
    setLabel = GraphicCreateView<UILabel>(container_);
    if (setLabel != nullptr) {
        setLabel->SetPosition(INFO_X, CFG_LABEL_Y, INFO_W, LABEL_LINE_H);
        setLabel->SetText("设置: (压测开始后显示本轮 6 项配置)");
        setLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        setLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xCF, 0xCF, 0xCF)));
    }
    if (infoLabel != nullptr) {
        infoLabel->SetText("读回: (压测开始后显示 getter 读回)");
    }
    if (stateLabel != nullptr) {
        stateLabel->SetText("轮次/通过/异常将在压测开始后显示");
    }
}

UILabelButton* SwitchRmCaseRunner::CreateStressToggleButton()
{
    UILabelButton* toggleBtn = GraphicCreateView<UILabelButton>(container_);
    if (toggleBtn != nullptr) {
        toggleBtn->SetPosition(ACTION_BTN_X, ACTION_BTN_Y, ACTION_BTN_W, ACTION_BTN_H);
        toggleBtn->SetText("开始压测");
        toggleBtn->SetFont(DEFAULT_VECTOR_FONT_FILENAME, ACTION_BTN_FONT);
        toggleBtn->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::White()));
        toggleBtn->SetStyle(STYLE_BACKGROUND_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0x00, 0x80, 0xFF)));
        toggleBtn->SetStyle(STYLE_BORDER_RADIUS, ACTION_BTN_RADIUS);
        toggleBtn->SetTouchable(true);
    }
    return toggleBtn;
}

void SwitchRmCaseRunner::BindStressStepHandler(RmStressDriver* driver, UIToggleButton* toggle,
                                               SwitchRmCaseType type, UILabel* setLabel,
                                               UILabel* stateLabel, UILabelButton* toggleBtn)
{
    driver->SetStepHandler([this, toggle, driver, type, setLabel, stateLabel, toggleBtn](uint32_t iter) {
        uint32_t done = iter + 1;
        switch (type) {
            case SWITCH_CASE_STRESS_TOGGLE:
                RunStressToggle(iter, done, toggle, driver, toggleBtn);
                break;
            case SWITCH_CASE_STRESS_STATE:
                RunStressState(iter, done, toggle, driver, toggleBtn);
                break;
            case SWITCH_CASE_STRESS_CONFIG:
                RunStressConfig(iter, done, toggle, driver, toggleBtn, setLabel, stateLabel);
                break;
            default:
                driver->Stop();
                break;
        }
    });
}

void SwitchRmCaseRunner::BindStressToggleClick(RmStressDriver* driver, UILabelButton* toggleBtn)
{
    AddClickListener(toggleBtn, [driver, toggleBtn](UIView& view, const ClickEvent& event) -> bool {
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
    });
}

void SwitchRmCaseRunner::RunStressToggle(uint32_t iter, uint32_t done, UIToggleButton* toggle,
                                         RmStressDriver* driver, UILabelButton* toggleBtn)
{
    toggle->SetState((iter % TOGGLE_PARITY_MOD) == 0);
    if ((done % STRESS_REPORT_INTERVAL == 0) || (done >= STRESS_TOGGLE_TARGET)) {
        char buf[96];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                         "已切换=%u 回调=%u", done, changeCount_);
        SetInfoText(buf);
    }
    if (done < STRESS_TOGGLE_TARGET) {
        return;
    }
    driver->Stop();
    char buf[96];
    (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                     "完成%u次切换: 回调=%u %s",
                     STRESS_TOGGLE_TARGET, changeCount_,
                     (changeCount_ == STRESS_TOGGLE_TARGET) ? "(一致)" : "(不一致!)");
    SetInfoText(buf);
    toggleBtn->SetText("开始压测");
    toggleBtn->Invalidate();
}

void SwitchRmCaseRunner::RunStressState(uint32_t iter, uint32_t done, UIToggleButton* toggle,
                                        RmStressDriver* driver, UILabelButton* toggleBtn)
{
    bool target = (iter % TOGGLE_PARITY_MOD) == 0;
    toggle->SetState(target);
    if (toggle->GetState() == target) {
        stressPassCount_++;
    } else {
        stressFailCount_++;
    }
    if ((done % STRESS_REPORT_INTERVAL == 0) || (done >= STRESS_TOGGLE_TARGET)) {
        char buf[96];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                         "轮次=%u 通过=%u 异常=%u",
                         done, stressPassCount_, stressFailCount_);
        SetInfoText(buf);
    }
    if (done < STRESS_TOGGLE_TARGET) {
        return;
    }
    driver->Stop();
    toggle->SetState(true);
    char buf[96];
    (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                     "完成%u轮: 通过=%u 异常=%u,已恢复ON态",
                     STRESS_TOGGLE_TARGET, stressPassCount_, stressFailCount_);
    SetInfoText(buf);
    toggleBtn->SetText("开始压测");
    toggleBtn->Invalidate();
}

void SwitchRmCaseRunner::RunStressConfig(uint32_t iter, uint32_t done, UIToggleButton* toggle,
                                         RmStressDriver* driver, UILabelButton* toggleBtn,
                                         UILabel* setLabel, UILabel* stateLabel)
{
    static constexpr int16_t kOnSizes[4] = { 10, 12, 14, 16 };
    static constexpr int16_t kOffSizes[4] = { 6, 8, 10, 12 };
    static constexpr uint32_t kThumbs[3] = { 0xFFD700, 0x00C8C8, 0xFFFFFF };
    static constexpr uint32_t kBorders[2] = { 0x00FF00, 0xFF0000 };
    int16_t on = kOnSizes[iter % 4];
    int16_t off = kOffSizes[iter % 4];
    uint32_t onC = kThumbs[iter % 3];
    uint32_t offC = kThumbs[(iter + 1) % 3];
    uint32_t onB = kBorders[iter % 2];
    uint32_t offB = kBorders[(iter + 1) % 2];
    toggle->SetOnThumbSize(on);
    toggle->SetOffThumbSize(off);
    toggle->SetOnThumbColor(Rgb(onC));
    toggle->SetOffThumbColor(Rgb(offC));
    toggle->SetOnBorderColor(Rgb(onB));
    toggle->SetOffBorderColor(Rgb(offB));
    bool ok = (toggle->GetOnThumbSize() == on) && (toggle->GetOffThumbSize() == off) &&
              (toggle->GetOnThumbColor().full == Rgb(onC).full) &&
              (toggle->GetOffThumbColor().full == Rgb(offC).full) &&
              (toggle->GetOnBorderColor().full == Rgb(onB).full) &&
              (toggle->GetOffBorderColor().full == Rgb(offB).full);
    if (ok) {
        stressPassCount_++;
    } else {
        stressFailCount_++;
    }
    if ((done % STRESS_REPORT_INTERVAL == 0) || (done >= STRESS_TARGET)) {
        ReportStressConfig(done, on, off, onC, offC, onB, offB, toggle, setLabel, stateLabel);
    }
    if (done < STRESS_TARGET) {
        return;
    }
    driver->Stop();
    if (stateLabel != nullptr) {
        char buf[96];
        (void)snprintf_s(buf, sizeof(buf), sizeof(buf) - 1,
                         "完成%u轮覆盖配置: 通过=%u 异常=%u",
                         STRESS_TARGET, stressPassCount_, stressFailCount_);
        stateLabel->SetText(buf);
    }
    toggleBtn->SetText("开始压测");
    toggleBtn->Invalidate();
}

void SwitchRmCaseRunner::ReportStressConfig(uint32_t done, int16_t on, int16_t off,
                                            uint32_t onC, uint32_t offC, uint32_t onB, uint32_t offB,
                                            UIToggleButton* toggle, UILabel* setLabel, UILabel* stateLabel)
{
    if (setLabel != nullptr) {
        char setBuf[160];
        (void)snprintf_s(setBuf, sizeof(setBuf), sizeof(setBuf) - 1,
                         "设置: on=%d off=%d 滑块#%06X/#%06X 边框#%06X/#%06X",
                         on, off, onC, offC, onB, offB);
        setLabel->SetText(setBuf);
    }
    char readBuf[160];
    (void)snprintf_s(readBuf, sizeof(readBuf), sizeof(readBuf) - 1,
                     "读回: on=%d off=%d 滑块#%06X/#%06X 边框#%06X/#%06X",
                     toggle->GetOnThumbSize(), toggle->GetOffThumbSize(),
                     toggle->GetOnThumbColor().full & 0xFFFFFF,
                     toggle->GetOffThumbColor().full & 0xFFFFFF,
                     toggle->GetOnBorderColor().full & 0xFFFFFF,
                     toggle->GetOffBorderColor().full & 0xFFFFFF);
    SetInfoText(readBuf);
    if (stateLabel != nullptr) {
        char cntBuf[96];
        (void)snprintf_s(cntBuf, sizeof(cntBuf), sizeof(cntBuf) - 1,
                         "轮次=%u 通过=%u 异常=%u",
                         done, stressPassCount_, stressFailCount_);
        stateLabel->SetText(cntBuf);
    }
}

void SwitchRmCaseRunner::ShowManyCase()
{
    static constexpr uint32_t kPalette[6] = { 0xFFD700, 0x00C8C8, 0xFFFFFF, 0xFF8000, 0x8080FF, 0x80FF80 };
    uint32_t colorPass = 0;
    uint32_t sizePass = 0;
    uint32_t created = 0;

    for (uint32_t i = 0; i < MANY_GRID_SLOTS; i++) {
        if ((i % MANY_COLS) == 0) {
            continue;
        }
        UIToggleButton* toggle = GraphicCreateView<UIToggleButton>(container_);
        if (toggle == nullptr) {
            continue;
        }
        int16_t x = MANY_GRID_X + static_cast<int16_t>(i % MANY_COLS) * MANY_PITCH_X;
        int16_t y = MANY_GRID_Y + static_cast<int16_t>(i / MANY_COLS) * MANY_PITCH_Y;
        toggle->SetPosition(x, y, MANY_BTN_W, MANY_BTN_H);
        toggle->SetTouchable(true);
        int16_t on = static_cast<int16_t>(i % 4) + 1;
        int16_t off = static_cast<int16_t>(i % 3) + 1;
        uint32_t onC = kPalette[i % 6];
        uint32_t offC = kPalette[(i + 3) % 6];
        toggle->SetOnThumbSize(on);
        toggle->SetOffThumbSize(off);
        toggle->SetOnThumbColor(Rgb(onC));
        toggle->SetOffThumbColor(Rgb(offC));
        toggle->SetState((i % TOGGLE_PARITY_MOD) == 0);
        created++;

        if ((toggle->GetOnThumbSize() == on) && (toggle->GetOffThumbSize() == off)) {
            sizePass++;
        }
        if ((toggle->GetOnThumbColor().full == Rgb(onC).full) &&
            (toggle->GetOffThumbColor().full == Rgb(offC).full)) {
            colorPass++;
        }
    }

    CreateManySummaryLabels(created, colorPass, sizePass);
}

void SwitchRmCaseRunner::CreateManySummaryLabels(uint32_t created, uint32_t colorPass, uint32_t sizePass)
{
    char infoBuf[160];
    (void)snprintf_s(infoBuf, sizeof(infoBuf), sizeof(infoBuf) - 1,
                     "%u个Switch已配置: 滑块色校验 %u/%u  尺寸校验 %u/%u",
                     created, colorPass, created, sizePass, created);
    UILabel* infoLabel = GraphicCreateView<UILabel>(container_);
    if (infoLabel != nullptr) {
        infoLabel->SetPosition(INFO_X, MANY_INFO_Y, INFO_W, LABEL_LINE_H);
        infoLabel->SetText(infoBuf);
        infoLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        infoLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xFF, 0xD7, 0x00)));
    }
    infoLabel_ = infoLabel;

    UILabel* tipLabel = GraphicCreateView<UILabel>(container_);
    if (tipLabel != nullptr) {
        tipLabel->SetPosition(INFO_X, MANY_TIP_Y, INFO_W, MANY_TIP_H);
        tipLabel->SetText("读回逐项与自身配置比对防串扰;任一 Switch 可点击交互");
        tipLabel->SetFont(DEFAULT_VECTOR_FONT_FILENAME, HINT_SIZE);
        tipLabel->SetStyle(STYLE_TEXT_COLOR, Color::ColorTo32(Color::GetColorFromRGB(0xCF, 0xCF, 0xCF)));
    }
}

} // namespace OHOS
#endif // GRAPHIC_ENABLE_SWITCH_FLAG

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

#include "rm_test_utils.h"
#include <cstdio>
#include <new>
#include "common/screen.h"
#include "graphic_utils.h"

namespace OHOS {

// RmClickListener
RmClickListener::RmClickListener(std::function<bool(UIView&, const ClickEvent&)> fn) : fn_(std::move(fn)) {}

RmClickListener::~RmClickListener() {}

bool RmClickListener::OnClick(UIView& view, const ClickEvent& event)
{
    return fn_(view, event);
}

// RmStressDriver
RmStressDriver::RmStressDriver() : animator_(this, this, stepPeriodMs, true) {}

RmStressDriver::~RmStressDriver()
{
    animator_.Stop();
}

void RmStressDriver::SetStepHandler(const std::function<void(uint32_t iter)>& handler)
{
    handler_ = handler;
}

void RmStressDriver::Start()
{
    iter_ = 0;
    animator_.Start();
}

void RmStressDriver::Stop()
{
    animator_.Stop();
}

bool RmStressDriver::IsRunning() const
{
    return animator_.GetState() == Animator::START;
}

void RmStressDriver::Callback(UIView* view)
{
    (void)view;
    if (handler_ != nullptr) {
        handler_(iter_++);
    }
}

// RmCaseListAdapter
RmCaseListAdapter::ItemClickListener::ItemClickListener(std::function<void(uint32_t)> cb, uint32_t index)
    : cb_(std::move(cb)), index_(index)
{
}

RmCaseListAdapter::ItemClickListener::~ItemClickListener() {}

bool RmCaseListAdapter::ItemClickListener::OnClick(UIView& view, const ClickEvent& event)
{
    (void)view;
    (void)event;
    if (cb_ != nullptr) {
        cb_(index_);
    }
    return true;
}

namespace {
constexpr int16_t GROUP_LIST_MARGIN = RM_GROUP_LIST_MARGIN;
constexpr int16_t GROUP_LIST_TOP = RM_GROUP_LIST_TOP;
constexpr uint16_t ITEM_HEIGHT = RM_ITEM_HEIGHT;
constexpr uint16_t ITEM_BORDER = RM_ITEM_BORDER;
constexpr uint16_t ITEM_RADIUS = RM_ITEM_RADIUS;
constexpr int16_t ITEM_TEXT_X = RM_ITEM_TEXT_X;
constexpr uint16_t ITEM_FONT_SIZE = RM_ITEM_FONT_SIZE;
constexpr int16_t CASE_LIST_H_MARGIN = GROUP_LIST_MARGIN + GROUP_LIST_MARGIN;
constexpr int16_t ITEM_H_BORDER = ITEM_BORDER + ITEM_BORDER;
constexpr int16_t ITEM_HEIGHT_HALF = ITEM_HEIGHT / 2;
constexpr int16_t ITEM_IMAGE_Y_ADJUST = 18;
} // namespace

RmCaseListAdapter::RmCaseListAdapter(uint32_t count, TitleProvider provider,
                                     std::function<void(uint32_t index)> onClick)
    : count_(count), provider_(std::move(provider)), onClick_(std::move(onClick)), titles_(nullptr),
      listeners_(nullptr), views_(nullptr)
{
    if (count_ == 0) {
        return;
    }

    titles_ = new (std::nothrow) char* [count_];
    if (titles_ == nullptr) {
        count_ = 0;
        return;
    }
    for (uint32_t i = 0; i < count_; i++) {
        titles_[i] = nullptr;
    }

    listeners_ = new (std::nothrow) ItemClickListener* [count_];
    if (listeners_ == nullptr) {
        count_ = 0;
        return;
    }
    for (uint32_t i = 0; i < count_; i++) {
        listeners_[i] = nullptr;
    }

    views_ = new (std::nothrow) UIView* [count_];
    if (views_ == nullptr) {
        count_ = 0;
        return;
    }
    for (uint32_t i = 0; i < count_; i++) {
        views_[i] = nullptr;
    }

    for (uint32_t i = 0; i < count_; i++) {
        titles_[i] = new (std::nothrow) char[titleBufSize];
        if (titles_[i] != nullptr) {
            provider_(i, titles_[i], titleBufSize);
        }
        listeners_[i] = new (std::nothrow) ItemClickListener(onClick_, i);
    }
}

RmCaseListAdapter::~RmCaseListAdapter()
{
    if (views_ != nullptr) {
        for (uint32_t i = 0; i < count_; i++) {
            if (views_[i] != nullptr) {
                views_[i]->SetOnClickListener(nullptr);
            }
        }
    }
    if (listeners_ != nullptr) {
        for (uint32_t i = 0; i < count_; i++) {
            delete listeners_[i];
            listeners_[i] = nullptr;
        }
        delete[] listeners_;
        listeners_ = nullptr;
    }
    if (views_ != nullptr) {
        delete[] views_;
        views_ = nullptr;
    }
    if (titles_ != nullptr) {
        for (uint32_t i = 0; i < count_; i++) {
            delete[] titles_[i];
            titles_[i] = nullptr;
        }
        delete[] titles_;
        titles_ = nullptr;
    }
}

uint16_t RmCaseListAdapter::GetCount()
{
    return static_cast<uint16_t>(count_);
}

UIView* RmCaseListAdapter::GetView(UIView* inView, int16_t index)
{
    if ((index < 0) || (index >= static_cast<int16_t>(count_))) {
        return nullptr;
    }
    UILabelButton* item = GetOrCreateItem(inView);
    if (item == nullptr) {
        return nullptr;
    }
    ConfigureItem(item, index);
    return item;
}

UILabelButton* RmCaseListAdapter::GetOrCreateItem(UIView* inView)
{
    if (inView == nullptr) {
        UILabelButton* item = new (std::nothrow) UILabelButton();
        if (item == nullptr) {
            return nullptr;
        }
        item->SetPosition(0, 0);
        item->SetStyleForState(STYLE_BORDER_WIDTH, ITEM_BORDER, UIButton::RELEASED);
        item->SetStyleForState(STYLE_BORDER_WIDTH, ITEM_BORDER, UIButton::PRESSED);
        item->SetStyleForState(STYLE_BORDER_WIDTH, ITEM_BORDER, UIButton::INACTIVE);
        item->SetStyleForState(STYLE_BORDER_OPA, 0, UIButton::RELEASED);
        item->SetStyleForState(STYLE_BORDER_OPA, 0, UIButton::PRESSED);
        item->SetStyleForState(STYLE_BORDER_OPA, 0, UIButton::INACTIVE);
        item->Resize(Screen::GetInstance().GetWidth() - CASE_LIST_H_MARGIN - ITEM_H_BORDER, ITEM_HEIGHT);
        return item;
    }
    UILabelButton* item = static_cast<UILabelButton*>(inView);
    ClearViewBinding(item);
    return item;
}

void RmCaseListAdapter::ClearViewBinding(UIView* view)
{
    if (views_ == nullptr) {
        return;
    }
    for (uint32_t i = 0; i < count_; i++) {
        if (views_[i] == view) {
            views_[i] = nullptr;
            break;
        }
    }
}

void RmCaseListAdapter::ConfigureItem(UILabelButton* item, int16_t index)
{
    if (listeners_[index] != nullptr) {
        item->SetOnClickListener(listeners_[index]);
    }
    if (titles_[index] != nullptr) {
        item->SetText(titles_[index]);
        item->SetViewId(titles_[index]);
    }
    item->SetFont(DEFAULT_VECTOR_FONT_FILENAME, ITEM_FONT_SIZE);
    item->SetViewIndex(index);
    item->SetAlign(TEXT_ALIGNMENT_LEFT);
    item->SetLabelPosition(ITEM_TEXT_X, 0);
    item->SetImageSrc(GRAPHIC_IMAGE_FORWARD, GRAPHIC_IMAGE_FORWARD);
    item->SetImagePosition(item->GetWidth() - RM_TEXT_DISTANCE_TO_LEFT_SIDE, ITEM_HEIGHT_HALF - ITEM_IMAGE_Y_ADJUST);
    item->SetStyleForState(STYLE_BORDER_RADIUS, ITEM_RADIUS, UIButton::RELEASED);
    item->SetStyleForState(STYLE_BORDER_RADIUS, ITEM_RADIUS, UIButton::PRESSED);
    item->SetStyleForState(STYLE_BORDER_RADIUS, ITEM_RADIUS, UIButton::INACTIVE);
    item->SetStyleForState(STYLE_BACKGROUND_COLOR, RM_BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::RELEASED);
    item->SetStyleForState(STYLE_BACKGROUND_COLOR, RM_BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::PRESSED);
    item->SetStyleForState(STYLE_BACKGROUND_COLOR, RM_BUTTON_STYLE_BACKGROUND_COLOR_VALUE, UIButton::INACTIVE);
    if (views_ != nullptr) {
        views_[index] = item;
    }
}

int16_t RmCaseListAdapter::GetItemWidthWithMargin(int16_t index)
{
    (void)index;
    return Screen::GetInstance().GetWidth() - CASE_LIST_H_MARGIN;
}

int16_t RmCaseListAdapter::GetItemHeightWithMargin(int16_t index)
{
    (void)index;
    return ITEM_HEIGHT + ITEM_H_BORDER;
}

} // namespace OHOS

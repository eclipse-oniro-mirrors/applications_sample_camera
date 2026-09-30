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

#ifndef RM_TEST_SLICE_BASE_H
#define RM_TEST_SLICE_BASE_H

#include "component_demo_slice.h"
#include "components/ui_list.h"
#include "components/ui_label_button.h"
#include "common/screen.h"
#include "graphic_utils.h"
#include "rm_test_utils.h"
#include "securec.h"
#include <cstdio>
#include <new>

namespace OHOS {

/**
 * @brief 共享的 RM 列表/用例/返回按钮模板基类。
 *
 * @tparam RunnerType 用例运行器类型（如 ButtonRmCaseRunner/ScrollerRmCaseRunner）
 * @tparam CaseType   用例配置类型（如 ButtonRmCase/ScrollerRmCase）
 * @tparam Cases      用例表全局数组指针
 * @tparam CaseCount  用例数全局变量指针
 */
template<typename RunnerType, typename CaseType, const CaseType* Cases, const uint32_t& CaseCount>
class RmTestSliceBase : public ComponentDemoSlice {
public:
    explicit RmTestSliceBase(const char* title);
    ~RmTestSliceBase() override;

protected:
    void SetupContent(UIViewGroup* content) override;

private:
    void EnterCase(uint32_t index);
    void BackToList();
    bool CreateCaseList(int16_t screenW, int16_t screenH);
    bool CreateBackButton(int16_t screenW);
    bool CreateBackListener();
    void SetBackBtnStyle(int16_t style, uint64_t value);

    static constexpr int16_t backBtnW = 88;
    static constexpr int16_t backBtnH = 56;
    static constexpr int16_t backBtnTop = 8;
    static constexpr int16_t backBtnRightMargin = 8;
    static constexpr uint16_t backBtnFontSize = 20;
    static constexpr int16_t caseListHMargin = RM_GROUP_LIST_MARGIN + RM_GROUP_LIST_MARGIN;
    static constexpr int16_t caseListVMargin = RM_GROUP_LIST_TOP + RM_GROUP_LIST_TOP;
    static constexpr uint16_t backBtnBorderRadius = 12;
    static constexpr uint16_t caseListReboundSize = 50;

    UIList* caseList_ = nullptr;
    RmCaseListAdapter* adapter_ = nullptr;
    UILabelButton* backToListBtn_ = nullptr;
    RunnerType* runner_ = nullptr;
    RmClickListener* backListener_ = nullptr;
    UIViewGroup* content_ = nullptr;
};

namespace internal {
inline void FormatCaseTitle(uint32_t index, char* buf, uint32_t bufSize,
                            const char* id, const char* name)
{
    if (bufSize > 0) {
        (void)snprintf_s(buf, bufSize, bufSize - 1, "%s %s", id, name);
    }
}
} // namespace internal

template<typename RunnerType, typename CaseType, const CaseType* Cases, const uint32_t& CaseCount>
RmTestSliceBase<RunnerType, CaseType, Cases, CaseCount>::RmTestSliceBase(const char* title)
    : ComponentDemoSlice(title) {}

template<typename RunnerType, typename CaseType, const CaseType* Cases, const uint32_t& CaseCount>
RmTestSliceBase<RunnerType, CaseType, Cases, CaseCount>::~RmTestSliceBase()
{
    if (runner_ != nullptr) {
        delete runner_;
        runner_ = nullptr;
    }
    if (backToListBtn_ != nullptr) {
        backToListBtn_->SetOnClickListener(nullptr);
    }
    delete backListener_;
    backListener_ = nullptr;
    if (adapter_ != nullptr) {
        delete adapter_;
        adapter_ = nullptr;
    }
    caseList_ = nullptr;
    backToListBtn_ = nullptr;
}

template<typename RunnerType, typename CaseType, const CaseType* Cases, const uint32_t& CaseCount>
void RmTestSliceBase<RunnerType, CaseType, Cases, CaseCount>::SetupContent(UIViewGroup* content)
{
    content_ = content;
    int16_t screenW = Screen::GetInstance().GetWidth();
    int16_t screenH = Screen::GetInstance().GetHeight();

    adapter_ = new (std::nothrow) RmCaseListAdapter(
        CaseCount,
        [](uint32_t index, char* buf, uint32_t bufSize) {
            internal::FormatCaseTitle(index, buf, bufSize, Cases[index].id, Cases[index].name);
        },
        [this](uint32_t index) { EnterCase(index); });
    if (adapter_ == nullptr) {
        printf("[RmTestSlice] create case list adapter failed\n");
        return;
    }

    if (!CreateCaseList(screenW, screenH)) {
        return;
    }
    if (!CreateBackButton(screenW)) {
        return;
    }
    if (!CreateBackListener()) {
        return;
    }
    backToListBtn_->SetOnClickListener(backListener_);
}

template<typename RunnerType, typename CaseType, const CaseType* Cases, const uint32_t& CaseCount>
bool RmTestSliceBase<RunnerType, CaseType, Cases, CaseCount>::CreateCaseList(int16_t screenW, int16_t screenH)
{
    caseList_ = GraphicCreateView<UIList>(content_);
    if (caseList_ == nullptr) {
        printf("[RmTestSlice] create case list failed\n");
        delete adapter_;
        adapter_ = nullptr;
        return false;
    }
    caseList_->SetPosition(RM_GROUP_LIST_MARGIN, RM_GROUP_LIST_TOP,
                           screenW - caseListHMargin,
                           screenH - headHeight - caseListVMargin);
    caseList_->SetThrowDrag(true);
    caseList_->SetReboundSize(caseListReboundSize);
    caseList_->SetYScrollBarVisible(true);
    caseList_->SetAdapter(adapter_);
    return true;
}

template<typename RunnerType, typename CaseType, const CaseType* Cases, const uint32_t& CaseCount>
bool RmTestSliceBase<RunnerType, CaseType, Cases, CaseCount>::CreateBackButton(int16_t screenW)
{
    backToListBtn_ = GraphicCreateView<UILabelButton>(content_);
    if (backToListBtn_ == nullptr) {
        printf("[RmTestSlice] create back button failed\n");
        GraphicDeleteViewTree(caseList_);
        caseList_ = nullptr;
        delete adapter_;
        adapter_ = nullptr;
        return false;
    }
    backToListBtn_->SetPosition(screenW - backBtnW - backBtnRightMargin, backBtnTop,
                                backBtnW, backBtnH);
    backToListBtn_->SetText("返回列表");
    backToListBtn_->SetFont(DEFAULT_VECTOR_FONT_FILENAME, backBtnFontSize);
    SetBackBtnStyle(STYLE_BORDER_RADIUS, backBtnBorderRadius);
    SetBackBtnStyle(STYLE_BACKGROUND_COLOR, RM_BUTTON_STYLE_BACKGROUND_COLOR_VALUE);
    backToListBtn_->SetVisible(false);
    return true;
}

template<typename RunnerType, typename CaseType, const CaseType* Cases, const uint32_t& CaseCount>
bool RmTestSliceBase<RunnerType, CaseType, Cases, CaseCount>::CreateBackListener()
{
    backListener_ = new (std::nothrow) RmClickListener(
        [this](UIView& view, const ClickEvent& event) -> bool {
            (void)view;
            (void)event;
            BackToList();
            return true;
        });
    if (backListener_ == nullptr) {
        printf("[RmTestSlice] create back listener failed\n");
        backToListBtn_->SetOnClickListener(nullptr);
        GraphicDeleteViewTree(caseList_);
        caseList_ = nullptr;
        backToListBtn_->SetOnClickListener(nullptr);
        GraphicDeleteViewTree(backToListBtn_);
        backToListBtn_ = nullptr;
        delete adapter_;
        adapter_ = nullptr;
        return false;
    }
    return true;
}

template<typename RunnerType, typename CaseType, const CaseType* Cases, const uint32_t& CaseCount>
void RmTestSliceBase<RunnerType, CaseType, Cases, CaseCount>::SetBackBtnStyle(int16_t style, uint64_t value)
{
    backToListBtn_->SetStyleForState(style, value, UIButton::RELEASED);
    backToListBtn_->SetStyleForState(style, value, UIButton::PRESSED);
    backToListBtn_->SetStyleForState(style, value, UIButton::INACTIVE);
}

template<typename RunnerType, typename CaseType, const CaseType* Cases, const uint32_t& CaseCount>
void RmTestSliceBase<RunnerType, CaseType, Cases, CaseCount>::EnterCase(uint32_t index)
{
    if ((caseList_ == nullptr) || (runner_ != nullptr) || (index >= CaseCount) || (content_ == nullptr)) {
        return;
    }
    caseList_->SetVisible(false);
    runner_ = new (std::nothrow) RunnerType(&Cases[index]);
    if (runner_ == nullptr) {
        printf("[RmTestSlice] create runner failed\n");
        caseList_->SetVisible(true);
        return;
    }
    runner_->Build(content_);
    backToListBtn_->SetVisible(true);
    content_->Invalidate();
}

template<typename RunnerType, typename CaseType, const CaseType* Cases, const uint32_t& CaseCount>
void RmTestSliceBase<RunnerType, CaseType, Cases, CaseCount>::BackToList()
{
    if ((runner_ == nullptr) || (caseList_ == nullptr) || (content_ == nullptr)) {
        return;
    }
    delete runner_;
    runner_ = nullptr;
    backToListBtn_->SetVisible(false);
    caseList_->SetVisible(true);
    content_->Invalidate();
}

} // namespace OHOS
#endif // RM_TEST_SLICE_BASE_H

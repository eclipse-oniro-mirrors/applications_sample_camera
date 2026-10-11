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

#ifndef RM_TEST_UTILS_H
#define RM_TEST_UTILS_H

#include <functional>
#include "components/ui_label_button.h"
#include "components/ui_list.h"
#include "components/abstract_adapter.h"
#include "animator/animator.h"

namespace OHOS {

/**
 * @brief 从 ui_test.h 抽取的 RM 验收页面通用常量。
 */
constexpr uint16_t RM_TITLE_LABEL_DEFAULT_HEIGHT = 29;
constexpr uint16_t RM_FONT_DEFAULT_SIZE = 20;
constexpr uint16_t RM_VIEW_DISTANCE_TO_LEFT_SIDE = 48;
constexpr uint16_t RM_VIEW_DISTANCE_TO_TOP_SIDE = 48;
constexpr uint16_t RM_VIEW_DISTANCE_TO_LEFT_SIDE2 = 24;
constexpr uint16_t RM_TEXT_DISTANCE_TO_LEFT_SIDE = 48;
constexpr uint16_t RM_TEXT_DISTANCE_TO_TOP_SIDE = 11;
constexpr uint16_t RM_HALF_OPA_OPAQUE = OPA_OPAQUE / 2;
constexpr uint16_t RM_VIEW_STYLE_BORDER_WIDTH = 2;
constexpr uint16_t RM_VIEW_STYLE_BORDER_RADIUS = 8;
constexpr uint16_t RM_BUTTON_LABEL_SIZE = 16;
constexpr uint8_t RM_BUTTON_STYLE_BORDER_RADIUS_VALUE = 20;
constexpr uint32_t RM_BUTTON_STYLE_BACKGROUND_COLOR_VALUE = 0xFF333333;
constexpr uint32_t RM_BUTTON_STYLE_BACKGROUND_COLOR_PRESS = 0xFF2D2D2D;
constexpr int16_t RM_BACK_BUTTON_HEIGHT = 64;

// 共享的用例列表布局常量
constexpr int16_t RM_GROUP_LIST_MARGIN = 24;
constexpr int16_t RM_GROUP_LIST_TOP = 8;
constexpr uint16_t RM_ITEM_HEIGHT = 64;
constexpr uint16_t RM_ITEM_BORDER = 4;
constexpr uint16_t RM_ITEM_RADIUS = 12;
constexpr int16_t RM_ITEM_TEXT_X = 24;
constexpr uint16_t RM_ITEM_FONT_SIZE = 24;

/**
 * @brief 将 std::function 包装为 UIView::OnClickListener。
 */
class RmClickListener : public UIView::OnClickListener {
public:
    explicit RmClickListener(std::function<bool(UIView&, const ClickEvent&)> fn);
    ~RmClickListener() override;
    bool OnClick(UIView& view, const ClickEvent& event) override;

private:
    std::function<bool(UIView&, const ClickEvent&)> fn_;
};

/**
 * @brief RM 验收压测驱动：挂在内容容器内的不可见 UIView，用 repeat Animator 每 16ms 推进一次压测步。
 *
 * 压测逻辑通过 SetStepHandler 注入；驱动随 DeleteChildren 一并析构，析构中停止 Animator，
 * 避免 AnimatorManager 残留。
 */
class RmStressDriver : public UIView, public AnimatorCallback {
public:
    static constexpr uint32_t stepPeriodMs = 16;

    RmStressDriver();
    ~RmStressDriver() override;

    void SetStepHandler(const std::function<void(uint32_t iter)>& handler);
    void Start();
    void Stop();
    bool IsRunning() const;

    void Callback(UIView* view) override;
    void OnStop(UIView& view) override {}

private:
    Animator animator_;
    std::function<void(uint32_t iter)> handler_;
    uint32_t iter_ = 0;
};

/**
 * @brief UIList 用例列表适配器：一行一个用例（id + name），点击回调进入对应用例。
 */
class RmCaseListAdapter : public AbstractAdapter {
public:
    using TitleProvider = std::function<void(uint32_t index, char* buf, uint32_t bufSize)>;

    RmCaseListAdapter(uint32_t count, TitleProvider provider, std::function<void(uint32_t index)> onClick);
    ~RmCaseListAdapter() override;

    uint16_t GetCount() override;
    UIView* GetView(UIView* inView, int16_t index) override;
    int16_t GetItemWidthWithMargin(int16_t index) override;
    int16_t GetItemHeightWithMargin(int16_t index) override;

private:
    class ItemClickListener : public UIView::OnClickListener {
    public:
        ItemClickListener(std::function<void(uint32_t)> cb, uint32_t index);
        ~ItemClickListener() override;
        bool OnClick(UIView& view, const ClickEvent& event) override;

    private:
        std::function<void(uint32_t)> cb_;
        uint32_t index_;
    };

    UILabelButton* GetOrCreateItem(UIView* inView);
    void ClearViewBinding(UIView* view);
    void ConfigureItem(UILabelButton* item, int16_t index);

    static constexpr uint32_t titleBufSize = 96;

    uint32_t count_;
    TitleProvider provider_;
    std::function<void(uint32_t index)> onClick_;
    char** titles_;
    ItemClickListener** listeners_;
    UIView** views_;
};

} // namespace OHOS
#endif // RM_TEST_UTILS_H

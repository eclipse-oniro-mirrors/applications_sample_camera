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

#ifndef OHOS_GRAPHIC_UTILS_H
#define OHOS_GRAPHIC_UTILS_H

#include <memory>
#include "gfx_utils/color.h"
#include "gfx_utils/style.h"
#include "components/ui_view_group.h"

namespace OHOS {
#define GRAPHIC_IMAGE_BACK \
    "/storage/app/run/com.ohos.graphicdemo/graphic/assets/graphic/resources/base/media/back.png"
#define GRAPHIC_IMAGE_FORWARD \
    "/storage/app/run/com.ohos.graphicdemo/graphic/assets/graphic/resources/base/media/forward.png"

#define GRAPHIC_HEAD_IMAGE_X 10
#define GRAPHIC_HEAD_IMAGE_Y 16
#define GRAPHIC_HEAD_IMAGE_WIDTH 48
#define GRAPHIC_HEAD_IMAGE_HEIGHT 48

/*
 * 删除以 view 为根的整棵子树（含 view 自身），从父节点摘除后释放。
 * 不影响 view 的兄弟节点。注意：UIViewGroup 析构不会删除子视图，
 * 删除视图子树必须使用本函数。实现见 graphic_utils.cpp。
 */
void GraphicDeleteViewTree(UIView* view);

/*
 * 创建视图并加入父节点。创建期所有权由 unique_ptr 管理：
 * 仅当父节点确认接管（Add 成功挂接）后才释放所有权移交视图树，
 * 创建或挂接失败时自动释放，防止中途返回导致泄漏。
 * 返回视图裸指针（归属父视图树，调用方仅用于属性设置）。
 */
template<typename T>
inline T* GraphicCreateView(UIViewGroup* parent)
{
    if (parent == nullptr) {
        return nullptr;
    }
    std::unique_ptr<T> view = std::make_unique<T>();
    parent->Add(view.get());
    if (view->GetParent() != parent) {
        return nullptr;
    }
    return view.release();
}
}
#endif // OHOS_GRAPHIC_UTILS_H

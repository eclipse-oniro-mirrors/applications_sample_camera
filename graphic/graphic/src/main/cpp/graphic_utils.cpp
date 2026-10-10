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

#include "graphic_utils.h"

namespace OHOS {
void GraphicDeleteViewTree(UIView* view)
{
    UIView* node = view;
    while (node != nullptr) {
        UIView* child = nullptr;
        if (node->IsViewGroup()) {
            child = static_cast<UIViewGroup*>(node)->GetChildrenHead();
        }
        if (child != nullptr) {
            // 下潜，优先删除子树
            node = child;
            continue;
        }
        // 叶子节点或无子容器：从父节点摘除后释放
        UIView* parent = node->GetParent();
        if (parent != nullptr) {
            static_cast<UIViewGroup*>(parent)->Remove(node);
        }
        bool isRoot = (node == view);
        delete node;
        if (isRoot) {
            break;
        }
        // 回溯到父节点，继续处理剩余子节点
        node = parent;
    }
}
} // namespace OHOS

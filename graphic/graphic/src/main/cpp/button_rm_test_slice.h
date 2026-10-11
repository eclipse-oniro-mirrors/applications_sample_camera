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

#ifndef BUTTON_RM_TEST_SLICE_H
#define BUTTON_RM_TEST_SLICE_H

#include "rm_test_slice_base.h"
#include "button_rm_case_view.h"

#if GRAPHIC_ENABLE_BUTTON_FLAG
namespace OHOS {
class ButtonRmTestSlice : public RmTestSliceBase<ButtonRmCaseRunner, ButtonRmCase,
                                                   g_buttonRmCases, g_buttonRmCaseNum> {
public:
    ButtonRmTestSlice();
};
} // namespace OHOS
#endif // GRAPHIC_ENABLE_BUTTON_FLAG
#endif // BUTTON_RM_TEST_SLICE_H

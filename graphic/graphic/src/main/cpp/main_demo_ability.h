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

#ifndef GRAPHIC_MAIN_DEMO_ABILITY_H
#define GRAPHIC_MAIN_DEMO_ABILITY_H

#include "ability.h"
#include "ability_slice.h"
#include "ability_loader.h"
#include "want.h"
#include "main_menu_ability_slice.h"

namespace OHOS {
class MainDemoAbility : public Ability {
public:
    MainDemoAbility() = default;
    ~MainDemoAbility() override = default;

    void OnStart(const Want& want) override;

protected:
    void OnStop() override
    {
        Ability::OnStop();
    }

    void OnActive(const Want& want) override
    {
        Ability::OnActive(want);
    }

    void OnInactive() override
    {
        Ability::OnInactive();
    }

    void OnBackground() override
    {
        Ability::OnBackground();
    }
};
} // namespace OHOS
#endif // GRAPHIC_MAIN_DEMO_ABILITY_H

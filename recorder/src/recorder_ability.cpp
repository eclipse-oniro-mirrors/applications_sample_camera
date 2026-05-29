/*
 * Copyright (c) 2026 RKH Corp.
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

#include "recorder_ability.h"
#include "recorder_log.h"

namespace OHOS {
REGISTER_AA(RecorderAbility)

void RecorderAbility::OnStart(const Want &want)
{
    LOGI("Recorder::OnStart");
    SetMainRoute("RecorderAbilityMainSlice");

    Ability::OnStart(want);
}

void RecorderAbility::OnInactive()
{
    LOGI("Recorder::OnInactive");
    Ability::OnInactive();
}

void RecorderAbility::OnActive(const Want &want)
{
    LOGI("Recorder::OnActive");
    Ability::OnActive(want);
}

void RecorderAbility::OnBackground()
{
    LOGI("Recorder::OnBackground");
    Ability::OnBackground();
}

void RecorderAbility::OnStop()
{
    LOGI("Recorder::OnStop");
    Ability::OnStop();
}
}
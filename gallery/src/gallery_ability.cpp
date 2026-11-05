/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

#include "gallery_ability.h"
#include "gallery_log.h"

namespace OHOS {
REGISTER_AA(GalleryAbility)

void GalleryAbility::OnStart(const Want &want)
{
    LOGI("GalleryAbility::OnStart");
    SetMainRoute("GalleryAbilitySlice");
    Ability::OnStart(want);
}

void GalleryAbility::OnInactive()
{
    LOGI("GalleryAbility::OnInactive");
    Ability::OnInactive();
}

void GalleryAbility::OnActive(const Want &want)
{
    LOGI("GalleryAbility::OnActive");
    Ability::OnActive(want);
}

void GalleryAbility::OnBackground()
{
    LOGI("GalleryAbility::OnBackground");
    Ability::OnBackground();
}

void GalleryAbility::OnStop()
{
    LOGI("GalleryAbility::OnStop");
    Ability::OnStop();
}
}
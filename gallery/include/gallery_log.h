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

#ifndef GALLERY_LOG_H
#define GALLERY_LOG_H

#ifdef HILOG_ENABLE

#ifndef LOG_DOMAIN
#define LOG_DOMAIN 0xD0000
#endif

#ifndef LOG_TAG
#define LOG_TAG "[GALLERY]"
#endif

#include <hilog/log.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FILE_NAME (strrchr((__FILE__), '/') ? strrchr((__FILE__), '/') + 1 : (__FILE__))

#define LOGD(fmt, ...) HILOG_DEBUG(LOG_APP, "[%s:%d] " fmt, FILE_NAME, __LINE__, ##__VA_ARGS__)
#define LOGI(fmt, ...) HILOG_INFO(LOG_APP, "[%s:%d] " fmt, FILE_NAME, __LINE__, ##__VA_ARGS__)
#define LOGW(fmt, ...) HILOG_WARN(LOG_APP, "[%s:%d] " fmt, FILE_NAME, __LINE__, ##__VA_ARGS__)
#define LOGE(fmt, ...) HILOG_ERROR(LOG_APP, "[%s:%d] " fmt, FILE_NAME, __LINE__, ##__VA_ARGS__)
#define LOGF(fmt, ...) HILOG_FATAL(LOG_APP, "[%s:%d] " fmt, FILE_NAME, __LINE__, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#else

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FILE_NAME (strrchr((__FILE__), '/') ? strrchr((__FILE__), '/') + 1 : (__FILE__))

#define LOGD(fmt, ...) printf("[D][GALLERY][%s:%d] " fmt "\n", FILE_NAME, __LINE__, ##__VA_ARGS__)
#define LOGI(fmt, ...) printf("[I][GALLERY][%s:%d] " fmt "\n", FILE_NAME, __LINE__, ##__VA_ARGS__)
#define LOGW(fmt, ...) printf("[W][GALLERY][%s:%d] " fmt "\n", FILE_NAME, __LINE__, ##__VA_ARGS__)
#define LOGE(fmt, ...) printf("[E][GALLERY][%s:%d] " fmt "\n", FILE_NAME, __LINE__, ##__VA_ARGS__)
#define LOGF(fmt, ...) printf("[F][GALLERY][%s:%d] " fmt "\n", FILE_NAME, __LINE__, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif

#endif /* GALLERY_LOG_H */

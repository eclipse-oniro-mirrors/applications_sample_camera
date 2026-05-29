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

#ifndef OHOS_RECORDER_UTILS_H
#define OHOS_RECORDER_UTILS_H

#include <sstream>
#include <iomanip>
#include <ctime>
#include <sys/stat.h>

#include "recorder_config.h"

namespace OHOS {
const uint32_t MS_PER_SECOND = 1000;
const long long MS_PER_MINUTE = 60 * MS_PER_SECOND;
const long long MS_PER_HOUR = 60 * MS_PER_MINUTE;

static std::string FormatDurationTime(uint32_t total_ms)
{
    if (total_ms == 0) {
        return "00:00:00";
    }
    uint32_t hours = static_cast<uint32_t>(total_ms / MS_PER_HOUR);
    total_ms %= MS_PER_HOUR;
    uint32_t minutes = static_cast<uint32_t>(total_ms / MS_PER_MINUTE);
    total_ms %= MS_PER_MINUTE;
    uint32_t seconds = static_cast<uint32_t>(total_ms / MS_PER_SECOND);

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(TIME_FIELD_WIDTH) << hours
        << ":"
        << std::setw(TIME_FIELD_WIDTH) << minutes
        << ":"
        << std::setw(TIME_FIELD_WIDTH) << seconds;
    return oss.str();
}

static std::string FormatTime(long timeMs, const char* format)
{
    std::time_t time = timeMs;
    std::tm* tm = std::localtime(&time);
    std::stringstream ss;
    ss << std::put_time(tm, format);
    return ss.str();
}

static long GetFileTime(const std::string& path)
{
    struct stat fileStat;
    if (stat(path.c_str(), &fileStat) == 0) {
        return fileStat.st_mtime;
    } else {
        LOGE("get file time failed, path:%s, errno:%d", path.c_str(), errno);
        return 0;
    }
}
}
#endif // OHOS_RECORDER_ABILITY_H

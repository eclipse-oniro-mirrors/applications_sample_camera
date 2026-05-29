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

#ifndef GALLERY_IMAGE_DECODER_H
#define GALLERY_IMAGE_DECODER_H

#include <memory>
#include <string>
#include <functional>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include <common/image.h>
#include <ability_event_handler.h>

namespace OHOS {

class ImageDecoder {
public:
    ImageDecoder(AbilityEventHandler* handler, size_t threadCount = 1);

    ~ImageDecoder();

    void DecodeImage(const std::string& imagePath, std::function<void(ImageInfo)> uiCallback);

    void Start();
    void Stop();
    bool IsRunning();

private:
    struct DecodeTask {
        std::string imagePath;
        std::function<void(ImageInfo)> callback;
    };

    void WorkerThread();
    bool TryGetTask(DecodeTask& task);
    void HandleTask(const DecodeTask& task);
    void NotifyCallback(const DecodeTask& task, const ImageInfo& imageInfo);

    ImageInfo DoDecode(const std::string& imagePath);

private:
    std::vector<std::thread> workerThreads_;   // 工作线程池
    std::queue<DecodeTask> taskQueue_;         // 任务队列
    std::mutex queueMutex_;                    // 队列互斥锁
    std::condition_variable taskCond_;         // 任务条件变量
    std::atomic<bool> isRunning_;              // 运行状态标记
    int maxThreadCount_;                       // 最大任务个数

    AbilityEventHandler *eventHandler_ = nullptr;
};

}
#endif // GALLERY_IMAGE_DECODER_H

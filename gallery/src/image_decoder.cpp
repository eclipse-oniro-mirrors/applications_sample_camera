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

#include <chrono>
#include <iostream>
#include <sstream>

#include <ability_event_handler.h>
#include <gfx_utils/file.h>

#if ENABLE_JPEG
#include "jpeglib.h"
#endif
#if ENABLE_PNG
#include "png.h"
#endif
#include <imgdecode/file_img_decoder.h>
#include <imgdecode/jpeg_img_decoder.h>
#include <imgdecode/png_img_decoder.h>

#include "image_decoder.h"
#include "gallery_log.h"

namespace OHOS {

enum GalleryImageType {
    IMG_PNG,
    IMG_JPEG,
    IMG_GIF,
    IMG_UNKNOWN,
};
const static uint8_t IMG_BYTES_TO_CHECK = 4; // 4: check 4 bytes of image file

GalleryImageType CheckImgType(const char* src)
{
    char buf[IMG_BYTES_TO_CHECK] = {0};
#ifdef _WIN32
    int32_t fd = open(src, O_RDONLY | O_BINARY);
#else
    int32_t fd = open(src, O_RDONLY);
#endif
    if (fd < 0) {
        LOGE("can't open %s\n", src);
        return IMG_UNKNOWN;
    }
    if (read(fd, buf, IMG_BYTES_TO_CHECK) != IMG_BYTES_TO_CHECK) {
        close(fd);
        return IMG_UNKNOWN;
    }
    close(fd);
#if ENABLE_PNG
    if (!png_sig_cmp(reinterpret_cast<png_const_bytep>(buf), 0, IMG_BYTES_TO_CHECK)) {
        return IMG_PNG;
    }
#endif
#if ENABLE_JPEG
    // 0xFF 0xD8: JPEG file's header
    if ((static_cast<uint8_t>(buf[0]) == 0xFF) && (static_cast<uint8_t>(buf[1]) == 0xD8)) {
        return IMG_JPEG;
    }
#endif
    if ((static_cast<uint8_t>(buf[0]) == 0x47) && (static_cast<uint8_t>(buf[1]) == 0x49) &&
          (static_cast<uint8_t>(buf[2]) == 0x46)) { // 2: array index of GIF file's header
        return IMG_GIF;
    }
    return IMG_UNKNOWN;
}

ImageDecoder::ImageDecoder(AbilityEventHandler* handler, size_t threadCount) : isRunning_(false),
    maxThreadCount_(threadCount),
    eventHandler_(handler)
{
}

ImageDecoder::~ImageDecoder()
{
    Stop();
}

void ImageDecoder::DecodeImage(const std::string& imagePath, std::function<void(ImageInfo)> uiCallback)
{
    std::lock_guard<std::mutex> lock(queueMutex_);
    taskQueue_.push({imagePath, uiCallback});
    taskCond_.notify_one();
}

void ImageDecoder::Start()
{
    isRunning_ = true;
    for (size_t i = 0; i < maxThreadCount_; ++i) {
        workerThreads_.emplace_back(&ImageDecoder::WorkerThread, this);
    }
}

void ImageDecoder::Stop()
{
    if (!isRunning_) return;

    isRunning_ = false;
    taskCond_.notify_all();

    for (auto& thread : workerThreads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    workerThreads_.clear();
}

bool ImageDecoder::IsRunning()
{
    return isRunning_;
}

bool ImageDecoder::TryGetTask(DecodeTask& task)
{
    std::unique_lock<std::mutex> lock(queueMutex_);
    taskCond_.wait(lock, [this]() {
        return !isRunning_ || !taskQueue_.empty();
    });

    if (isRunning_ && !taskQueue_.empty()) {
        task = std::move(taskQueue_.front());
        taskQueue_.pop();
        return true;
    }
    return false;
}

void ImageDecoder::HandleTask(const DecodeTask& task)
{
    if (!isRunning_) {
        return;
    }

    ImageInfo imageInfo = DoDecode(task.imagePath);
    NotifyCallback(task, imageInfo);
}

void ImageDecoder::NotifyCallback(const DecodeTask& task, const ImageInfo& imageInfo)
{
    if (eventHandler_) {
        eventHandler_->PostTask([task, imageInfo]() {
            task.callback(imageInfo);
        });
    }
}

void ImageDecoder::WorkerThread()
{
#ifndef __LITEOS_A__
    pid_t tid = gettid();
    LOGI("WorkerThread started, tid:%d", tid);
#endif
    while (isRunning_) {
        DecodeTask task;
        bool hasTask = TryGetTask(task);
        if (hasTask) {
            HandleTask(task);
        }
    }
#ifndef __LITEOS_A__
    LOGI("WorkerThread exit, tid: %d", tid);
#endif
}

ImageInfo ImageDecoder::DoDecode(const std::string& imagePath)
{
#ifndef __LITEOS_A__
    pid_t tid = gettid();
    LOGI("DoDecode start. path: %s (tid:%d)", imagePath.c_str(), tid);
#endif
    FileImgDecoder::ImgResDsc desc = {0};
    FileImgDecoder* decoder = nullptr;
    GalleryImageType type = CheckImgType(imagePath.c_str());
    if (type == IMG_PNG) {
        decoder = &(PngImgDecoder::GetInstance());
    } else if (type == IMG_JPEG) {
        decoder = &(JpegImgDecoder::GetInstance());
    } else {
        LOGE("DoDecode imageType(%d) not supported!", type);
        return desc.imgInfo;
    }

    if (decoder == nullptr) {
        LOGE("DoDecode decoder is null");
        return desc.imgInfo;
    }

    desc.path = imagePath.c_str();
    RetCode ret = decoder->Open(desc);
    if (ret != RetCode::OK) {
        LOGE("DoDecode decoder open failed");
        return desc.imgInfo;
    }

    ret = decoder->GetHeader(desc);
    if (ret != RetCode::OK) {
        LOGE("DoDecode decoder get header failed");
        decoder->Close(desc);
        return desc.imgInfo;
    }

    ret = decoder->ReadToCache(desc);
    if (ret != RetCode::OK) {
        LOGE("DoDecode decoder read to cache failed");
        decoder->Close(desc);
        return desc.imgInfo;
    }

#ifndef __LITEOS_A__
    LOGI("DoDecode end. path: %s (tid:%d) result:%d, imageInfo.data:%p", imagePath.c_str(),
         tid, ret, desc.imgInfo.data);
#endif
    return desc.imgInfo;
}
}


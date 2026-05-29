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

#ifndef OHOS_RECORDER_LIST_ADAPTER_H
#define OHOS_RECORDER_LIST_ADAPTER_H

#include <components/ui_view.h>
#include <components/ui_image_view.h>
#include <components/ui_label.h>
#include <components/abstract_adapter.h>
#include <event_listener.h>

#include <vector>
#include <functional>
#include <memory>

#include "recorder_config.h"

namespace OHOS {
struct RecordItem {
    std::string name;   // file name
    std::string path;   // file path
    std::string timeStr;
    long time;          // create time.
    bool started;       // play started status
    bool paused;        // paused status
};

class OnItemPlayListener : public HeapBase {
public:
    virtual void OnItemPlay(int16_t index, const RecordItem& item) = 0;
    virtual ~OnItemPlayListener() = default;
};

class OnItemDeleteListener : public HeapBase {
public:
    virtual void OnItemDelete(int16_t index, const RecordItem& item) = 0;
    virtual ~OnItemDeleteListener() = default;
};


using OnItemFunc = std::function<void(int16_t index, const RecordItem& item)>;

class RecorderListItemListener :
        public OnItemPlayListener,
        public OnItemDeleteListener {
public:
    RecorderListItemListener() = delete;
    ~RecorderListItemListener() override = default;

    RecorderListItemListener(OnItemFunc onPlay, OnItemFunc onDelete)
    {
        onPlay_ = std::move(onPlay);
        onDelete_ = std::move(onDelete);
    }

    void OnItemPlay(int16_t index, const RecordItem& item) override
    {
        if (!onPlay_) {
            return;
        }
        onPlay_(index, item);
    }

    void OnItemDelete(int16_t index, const RecordItem& item) override
    {
        if (!onDelete_) {
            return;
        }
        onDelete_(index, item);
    }

private:
    OnItemFunc onPlay_ {};
    OnItemFunc onDelete_ {};
};


class RecorderListAdapter : public AbstractAdapter {
public:
    RecorderListAdapter();
    ~RecorderListAdapter() override;
    uint16_t GetCount() override;
    UIView* GetView(UIView* inView, int16_t index) override;
    void Init();
    void SetOnItemPlayListener(OnItemPlayListener* listener);
    void SetOnItemDeleteListener(OnItemDeleteListener* listener);
    void SetItems(std::vector<RecordItem>& items);
    void AddItem(const RecordItem& item);
    void RemoveItem(int16_t index);
    void UpdateItem(int16_t index, const RecordItem& item);
    bool GetItem(int16_t index, RecordItem& item) const;
private:
    UIViewGroup* CreateItemView();
    UIImageView* CreateFileIcon();
    UILabel* CreateNameLabel();
    UILabel* CreateTimeLabel();
    UIImageView* CreatePlayButton();
    UIImageView* CreateDeleteButton();
    void BindItemView(UIViewGroup* root, int16_t index, RecordItem& item);
    void ResetItemListeners(UIImageView* playButton, UIImageView* deleteButton);
private:
    std::vector<RecordItem> items_;
    char fileIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
    char playIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
    char pauseIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
    char deleteIconAbsolutePath[MAX_PATH_LENGTH] = { 0 };
    OnItemPlayListener* onItemPlayListener_ { nullptr };
    OnItemDeleteListener* onItemDeleteListener_ { nullptr };
};

}
#endif // OHOS_RECORDER_LIST_ADAPTER_H

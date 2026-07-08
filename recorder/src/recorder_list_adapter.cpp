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

#include <ability_env.h>
#include <components/ui_image_view.h>
#include <components/ui_button.h>
#include <components/ui_label.h>

#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

#include "recorder_list_adapter.h"
#include "recorder_log.h"

#define VIEW_ID_ICON "ICON"
#define VIEW_ID_NAME "NAME"
#define VIEW_ID_TIME "TIME"
#define VIEW_ID_PLAY "PLAY"
#define VIEW_ID_DELETE "DELETE"

namespace OHOS {
RecorderListAdapter::RecorderListAdapter()
{
}

RecorderListAdapter::~RecorderListAdapter()
{
}

void RecorderListAdapter::Init()
{
    const char* pathHeader = GetSrcPath();
    if (sprintf_s(fileIconAbsolutePath, MAX_PATH_LENGTH, "%s%s", pathHeader, LIST_FILE_ICON_PATH) < 0) {
        LOGI("SimpleAdapter::Init | fileIconAbsolutePath error");
        return;
    }
    if (sprintf_s(playIconAbsolutePath, MAX_PATH_LENGTH, "%s%s", pathHeader, LIST_PLAY_ICON_PATH) < 0) {
        LOGI("SimpleAdapter::Init | playIconAbsolutePath error");
        return;
    }
    if (sprintf_s(pauseIconAbsolutePath, MAX_PATH_LENGTH, "%s%s", pathHeader, LIST_PAUSE_ICON_PATH) < 0) {
        LOGI("SimpleAdapter::Init | pauseIconAbsolutePath error");
        return;
    }
    if (sprintf_s(deleteIconAbsolutePath, MAX_PATH_LENGTH, "%s%s", pathHeader, LIST_DEL_ICON_PATH) < 0) {
        LOGI("SimpleAdapter::Init | deleteIconAbsolutePath error");
        return;
    }
    if (onItemPlayListener_ != nullptr) {
        delete onItemPlayListener_;
        onItemPlayListener_ = nullptr;
    }
    if (onItemDeleteListener_ != nullptr) {
        delete onItemDeleteListener_;
        onItemDeleteListener_ = nullptr;
    }
}

void RecorderListAdapter::SetOnItemPlayListener(OnItemPlayListener* listener)
{
    onItemPlayListener_ = listener;
}

void RecorderListAdapter::SetOnItemDeleteListener(OnItemDeleteListener* listener)
{
    onItemDeleteListener_ = listener;
}

void RecorderListAdapter::SetItems(std::vector<RecordItem>& items)
{
    items_ = items;
}

void RecorderListAdapter::AddItem(const RecordItem& item)
{
    items_.insert(items_.begin(), item);
}

void RecorderListAdapter::RemoveItem(int16_t index)
{
    items_.erase(items_.begin() + index);
}

void RecorderListAdapter::UpdateItem(int16_t index, const RecordItem& item)
{
    LOGI("UpdateItem index:%d", index);
    if (index >= 0 && index < items_.size()) {
        items_[index] = item;
    } else {
        LOGE("UpdateItem index out of range, index: %d, size: %zu", index, items_.size());
    }
}

bool RecorderListAdapter::GetItem(int16_t index, RecordItem& item) const
{
    if (index >= 0 && index < items_.size()) {
        item = items_[index];
        return true;
    } else {
        LOGE("GetItem index out of range, index: %d, size: %zu", index, items_.size());
        return false;
    }
}

uint16_t RecorderListAdapter::GetCount()
{
    LOGI("GetCount items size: %zu", items_.size());
    return (uint16_t)items_.size();
}

UIViewGroup* RecorderListAdapter::CreateItemView()
{
    UIViewGroup* item = new UIViewGroup();
    item->SetPosition(0, 0, LIST_ITEM_WIDTH(), LIST_ITEM_HEIGHT());
    item->SetStyle(STYLE_BORDER_RADIUS, LIST_ITEM_BORDER_RADIUS);
    item->SetStyle(STYLE_BORDER_WIDTH, 0);
    item->SetStyle(STYLE_BACKGROUND_COLOR, Color::White().full);
    item->SetStyle(STYLE_BACKGROUND_OPA, OPA_OPAQUE);
    item->SetStyle(STYLE_MARGIN_BOTTOM, LIST_DIVIDER_HEIGHT);

    item->Add(CreateFileIcon());
    item->Add(CreateNameLabel());
    item->Add(CreateTimeLabel());
    item->Add(CreatePlayButton());
    item->Add(CreateDeleteButton());
    return item;
}

UIImageView* RecorderListAdapter::CreateFileIcon()
{
    UIImageView* fileIcon = new UIImageView();
    fileIcon->SetViewId(VIEW_ID_ICON);
    fileIcon->SetPosition(
        LIST_ITEM_FILE_ICON_X(),
        LIST_ITEM_FILE_ICON_Y(),
        LIST_ITEM_FILE_ICON_WIDTH(),
        LIST_ITEM_FILE_ICON_HEIGHT());
    fileIcon->SetAutoEnable(false);
    fileIcon->SetResizeMode(UIImageView::CONTAIN);
    fileIcon->SetSrc(fileIconAbsolutePath);
    fileIcon->SetTouchable(false);
    return fileIcon;
}

UILabel* RecorderListAdapter::CreateNameLabel()
{
    UILabel* nameLabel = new UILabel();
    nameLabel->SetViewId(VIEW_ID_NAME);
    nameLabel->SetPosition(
        LIST_ITEM_NAME_LABEL_X(),
        LIST_ITEM_NAME_LABEL_Y(),
        LIST_ITEM_NAME_LABEL_WIDTH(),
        LIST_ITEM_NAME_LABEL_HEIGHT());
    nameLabel->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_LEFT, UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
    nameLabel->SetFont(FONT_NAME, LIST_ITEM_NAME_LABEL_FONT_SIZE());
    nameLabel->SetStyle(STYLE_TEXT_COLOR, Color::Black().full);
    nameLabel->SetStyle(STYLE_TEXT_OPA, OPA_OPAQUE);
    return nameLabel;
}

UILabel* RecorderListAdapter::CreateTimeLabel()
{
    UILabel* timeLabel = new UILabel();
    timeLabel->SetViewId(VIEW_ID_TIME);
    timeLabel->SetPosition(
        LIST_ITEM_TIME_LABEL_X(),
        LIST_ITEM_TIME_LABEL_Y(),
        LIST_ITEM_TIME_LABEL_WIDTH(),
        LIST_ITEM_TIME_LABEL_HEIGHT());
    timeLabel->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_LEFT, UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
    timeLabel->SetFont(FONT_NAME, LIST_ITEM_TIME_LABEL_FONT_SIZE());
    timeLabel->SetStyle(STYLE_TEXT_COLOR, Color::Gray().full);
    timeLabel->SetStyle(STYLE_TEXT_OPA, OPA_OPAQUE);
    return timeLabel;
}

UIImageView* RecorderListAdapter::CreatePlayButton()
{
    UIImageView* playButton = new UIImageView();
    playButton->SetViewId(VIEW_ID_PLAY);
    playButton->SetPosition(
        LIST_ITEM_PLAY_BUTTON_X(),
        LIST_ITEM_PLAY_BUTTON_Y(),
        LIST_ITEM_PLAY_BUTTON_WIDTH(),
        LIST_ITEM_PLAY_BUTTON_HEIGHT());
    playButton->SetAutoEnable(false);
    playButton->SetResizeMode(UIImageView::CONTAIN);
    playButton->SetTouchable(true);
    return playButton;
}

UIImageView* RecorderListAdapter::CreateDeleteButton()
{
    UIImageView* deleteButton = new UIImageView();
    deleteButton->SetViewId(VIEW_ID_DELETE);
    deleteButton->SetPosition(
        LIST_ITEM_DEL_BUTTON_X(),
        LIST_ITEM_DEL_BUTTON_Y(),
        LIST_ITEM_DEL_BUTTON_WIDTH(),
        LIST_ITEM_DEL_BUTTON_HEIGHT());
    deleteButton->SetAutoEnable(false);
    deleteButton->SetResizeMode(UIImageView::CONTAIN);
    deleteButton->SetSrc(deleteIconAbsolutePath);
    deleteButton->SetTouchable(true);
    return deleteButton;
}

UIView* RecorderListAdapter::GetView(UIView* inView, int16_t index)
{
    LOGI("GetView inView:%p, index:%d", inView, index);
    if (items_.size() == 0) {
        return nullptr;
    }
    if ((index >= items_.size()) || (index < 0)) {
        return nullptr;
    }
    UIViewGroup* root = nullptr;
    if (inView == nullptr) {
        root = CreateItemView();
    } else {
        root = static_cast<UIViewGroup*>(inView);
    }
    root->SetViewIndex(index);
    BindItemView(root, index, items_[index]);
    return root;
}

void RecorderListAdapter::BindItemView(UIViewGroup* root, int16_t index, RecordItem& item)
{
    UILabel* nameLabel = nullptr;
    UILabel* timeLabel = nullptr;
    UIImageView* playButton = nullptr;
    UIImageView* deleteButton = nullptr;
    nameLabel = static_cast<UILabel*>(root->GetChildById(VIEW_ID_NAME));
    timeLabel = static_cast<UILabel*>(root->GetChildById(VIEW_ID_TIME));
    playButton = static_cast<UIImageView*>(root->GetChildById(VIEW_ID_PLAY));
    deleteButton = static_cast<UIImageView*>(root->GetChildById(VIEW_ID_DELETE));

    nameLabel->SetText(item.name.c_str());
    timeLabel->SetText(item.timeStr.c_str());
    if (item.started && !item.paused) {
        playButton->SetSrc(pauseIconAbsolutePath);
    } else {
        playButton->SetSrc(playIconAbsolutePath);
    }
    ResetItemListeners(playButton, deleteButton);

    UIView::OnClickListener* playButtonListener = new EventListener(
        [this, index, &item] (UIView& view, const Event& event) -> bool {
            LOGI("play/pause button on click");
            if (onItemPlayListener_) {
                onItemPlayListener_->OnItemPlay(index, item);
            }
            return true;
        }, nullptr);

    UIView::OnClickListener* deleteButtonListener = new EventListener(
        [this, index, &item] (UIView& view, const Event& event) -> bool {
            LOGI("delete button on click");
            if (onItemDeleteListener_) {
                onItemDeleteListener_->OnItemDelete(index, item);
            }
            return true;
        }, nullptr);

    playButton->SetOnClickListener(playButtonListener);
    deleteButton->SetOnClickListener(deleteButtonListener);
}

void RecorderListAdapter::ResetItemListeners(UIImageView* playButton, UIImageView* deleteButton)
{
    UIView::OnClickListener* playButtonlistener = playButton->GetOnClickListener();
    if (playButtonlistener != nullptr) {
        delete playButtonlistener;
    }
    UIView::OnClickListener* deleteButtonlistener = deleteButton->GetOnClickListener();
    if (deleteButtonlistener != nullptr) {
        delete deleteButtonlistener;
    }
}

}
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

#include "gallery_ability_slice.h"
#include "ability_env.h"
#include "ability_manager.h"
#include <ability_event_handler.h>
#include "picture_ability_slice.h"

#include "gfx_utils/file.h"
#include "gfx_utils/mem_api.h"
#include "securec.h"

#include "gallery_log.h"
#include "image_decoder.h"

namespace OHOS {
REGISTER_AS(GalleryAbilitySlice)

GalleryAbilitySlice::~GalleryAbilitySlice()
{
    LOGI("~GalleryAbilitySlice() | start");
    Clear();
    LOGI("~GalleryAbilitySlice() | end");
}

void GalleryAbilitySlice::Clear()
{
    LOGI("GalleryAbilitySlice::Clear() | start");
    if (backIcon_ != nullptr) {
        delete backIcon_;
        backIcon_ = nullptr;
    }
    if (backIconListener_ != nullptr) {
        delete backIconListener_;
        backIconListener_ = nullptr;
    }
    if (deleteClickListener_ != nullptr) {
        delete deleteClickListener_;
        deleteClickListener_ = nullptr;
    }
    if (backArea_ != nullptr) {
        delete backArea_;
        backArea_ = nullptr;
    }
    if (titleLabel_ != nullptr) {
        delete titleLabel_;
        titleLabel_ = nullptr;
    }
    if (deleteLabel_ != nullptr) {
        delete deleteLabel_;
        deleteLabel_ = nullptr;
    }
    if (imageDecoder_ != nullptr) {
        delete imageDecoder_;
        imageDecoder_ = nullptr;
    }

    ClearThumb();

    if (rootView_ != nullptr) {
        RootView::DestroyWindowRootView(rootView_);
        rootView_ = nullptr;
    }
    LOGI("GalleryAbilitySlice::Clear() | end");
}

void GalleryAbilitySlice::ClearThumb()
{
    LOGI("GalleryAbilitySlice::ClearThumb() | start");
    if (picContainer_ != nullptr) {
        delete picContainer_;
        picContainer_ = nullptr;
    }
    if (picList_ != nullptr) {
        ClearPictureList(picList_);
        delete picList_;
        picList_ = nullptr;
    }
    for (uint16_t i = 0; i < pictureCount_; i++) {
        if (pictureName_[i] != nullptr) {
            delete[] pictureName_[i];
            pictureName_[i] = nullptr;
        }
    }
    for (uint16_t i = 0; i < pictureOnClickListenerCount_; i++) {
        if (pictureOnClickListener_[i] != nullptr) {
            delete pictureOnClickListener_[i];
            pictureOnClickListener_[i] = nullptr;
        }
    }
    pictureCount_ = 0;
    pictureOnClickListenerCount_ = 0;
    LOGI("GalleryAbilitySlice::ClearThumb() | end");
}

void GalleryAbilitySlice::ClearPictureList(const UIView* view)
{
    LOGI("GalleryAbilitySlice::ClearPictureList() | start");
    if (view == nullptr || !(view->IsViewGroup())) {
        return;
    }
    UIView* child = static_cast<const UIViewGroup*>(view)->GetChildrenHead();
    UIView* childNext = nullptr;
    while (child != nullptr) {
        childNext = child->GetNextSibling();
        if (child->IsViewGroup()) {
            ClearPictureList(child);
        }
        delete child;
        child = childNext;
    }
    LOGI("GalleryAbilitySlice::ClearPictureList() | end");
}

void GalleryAbilitySlice::InitTitle()
{
    LOGI("GalleryAbilitySlice::InitTitle | start");
    InitTitleBackArea();
    InitTitleLabels();
}

void GalleryAbilitySlice::InitTitleBackArea()
{
    backIcon_ = new UIImageView();
    backIcon_->SetAutoEnable(false);
    backIcon_->SetResizeMode(UIImageView::ImageResizeMode::CONTAIN);
    backIcon_->SetPosition(BACK_ICON_POSITION_X(), BACK_ICON_POSITION_Y(), BACK_ICON_WIDTH(), BACK_ICON_HEIGHT());
    backIcon_->SetSrc(backIconAbsolutePath);
    backIcon_->SetTouchable(true);

    backArea_ = new UIViewGroup();
    backArea_->SetPosition(0, 0, LABEL_POSITION_X(), LABEL_HEIGHT());
    backArea_->SetStyle(STYLE_BACKGROUND_OPA, 0);
    backArea_->SetTouchable(true);

    auto onClick = [this] (UIView& view, const Event& event) -> bool {
        LOGI("############  Next AS enter   #############");
        TerminateAbility();
        LOGI("############  Next AS exit   #############");
        return true;
    };
    backIconListener_ = new EventListener(onClick, nullptr);
    backIcon_->SetOnClickListener(backIconListener_);
    backArea_->SetOnClickListener(backIconListener_);

    backArea_->Add(backIcon_);
    rootView_->Add(backArea_);
}

void GalleryAbilitySlice::InitTitleLabels()
{
    titleLabel_ = new UILabel();
    titleLabel_->SetPosition(LABEL_POSITION_X(), LABEL_POSITION_Y, LABEL_WIDTH(), LABEL_HEIGHT());
    titleLabel_->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_LEFT, UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
    titleLabel_->SetFont(FONT_NAME, GALLERY_FONT_SIZE());
    titleLabel_->SetStyle(STYLE_TEXT_COLOR, Color::Black().full);
    titleLabel_->SetStyle(STYLE_TEXT_OPA, OPA_OPAQUE);
    titleLabel_->SetText("照片");

    deleteLabel_ = new UILabel();
    deleteLabel_->SetPosition(ROOT_VIEW_WIDTH() - DELETE_LABEL_WIDTH(), LABEL_POSITION_Y,
                              DELETE_LABEL_WIDTH(), LABEL_HEIGHT());
    deleteLabel_->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_LEFT,
                           UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
    deleteLabel_->SetFont(FONT_NAME, GALLERY_DELETE_FONT_SIZE());
    deleteLabel_->SetStyle(STYLE_TEXT_COLOR, Color::Black().full);
    deleteLabel_->SetStyle(STYLE_TEXT_OPA, OPA_OPAQUE);
    deleteLabel_->SetText("全部删除");
    deleteLabel_->SetTouchable(true);
    auto deleteClick = [this] (UIView& view, const Event& event) -> bool {
        LOGI("############  DeleteAllData click enter #############");
        DeleteAllData();
        LOGI("############  DeleteAllData click exit  #############");
        return true;
    };
    deleteClickListener_ = new EventListener(deleteClick, nullptr);
    deleteLabel_->SetOnClickListener(deleteClickListener_);

    rootView_->Add(titleLabel_);
    rootView_->Add(deleteLabel_);
}

void GalleryAbilitySlice::InitPictureList()
{
    LOGI("GalleryAbilitySlice::InitPictureList | start");
    picContainer_ = new UIScrollView();
    picContainer_->SetPosition(0, LABEL_POSITION_Y + LABEL_HEIGHT());
    picContainer_->Resize(ROOT_VIEW_WIDTH(), ROOT_VIEW_HEIGHT() - (LABEL_POSITION_Y + LABEL_HEIGHT()));
    picContainer_->SetStyle(STYLE_BACKGROUND_OPA, 0);
    picContainer_->SetStyle(STYLE_BACKGROUND_COLOR, Color::Silver().full);
    rootView_->Add(picContainer_);

    picList_ = new UIViewGroup();
    picList_->SetPosition(0, 0, ROOT_VIEW_WIDTH(), ROOT_VIEW_HEIGHT());
    picList_->SetStyle(STYLE_BACKGROUND_OPA, 0);

    int16_t numInLine = (ROOT_VIEW_WIDTH() + THUMBNAIL_SPACE) / (THUMBNAIL_RESOLUTION_X() + THUMBNAIL_SPACE);
    int16_t offset = ((ROOT_VIEW_WIDTH() + THUMBNAIL_SPACE) %
        (THUMBNAIL_RESOLUTION_X() + THUMBNAIL_SPACE)) / 2; // 2: half
    AddAllPictures(Point { offset, 0 }, numInLine);

    int16_t totalHeight = (pictureCount_ / numInLine) * (THUMBNAIL_RESOLUTION_Y() + THUMBNAIL_SPACE);
    if ((pictureCount_ % numInLine) != 0) {
        totalHeight += THUMBNAIL_RESOLUTION_Y() + THUMBNAIL_SPACE;
    }
    picList_->Resize(ROOT_VIEW_WIDTH(), totalHeight);
    LOGI("------------ totalHeight : %d ------------", totalHeight);
    picContainer_->Add(picList_);
}

void GalleryAbilitySlice::AddAllPictures(const Point& pos, int16_t numInLine)
{
    LOGI("GalleryAbilitySlice::AddAllPictures | start | %d", numInLine);
    Point imagePos = pos;
    LOGI("opendir: %s", PHOTO_DIRECTORY);
    DIR* drip = opendir(PHOTO_DIRECTORY);
    if (drip == nullptr) {
        return;
    }
    struct dirent* info = nullptr;
    while ((info = readdir(drip)) != nullptr  && pictureCount_ < MAX_PICTURE_COUNT) {
        LOGI("readdir for: %s", info->d_name);
        uint16_t imageNameLen = static_cast<uint16_t>(strlen(info->d_name));
        if (imageNameLen > MAX_PATH_LENGTH || (strcmp(info->d_name, ".") == 0) || (strcmp(info->d_name, "..") == 0)) {
            LOGW("GalleryAbilitySlice::AddAllPictures | imageNameLen > MAX_PATH_LENGTH | %d", imageNameLen);
            continue;
        }
        char* imageName = new char[imageNameLen + 1]();
        memcpy_s(imageName, imageNameLen + 1, info->d_name, imageNameLen + 1);
        pictureName_[pictureCount_] = imageName;
        pictureCount_++;

        uint16_t pathLen = static_cast<uint16_t>(strlen(PHOTO_DIRECTORY)) + imageNameLen + 1;
        if (pathLen > MAX_PATH_LENGTH) {
            LOGW("GalleryAbilitySlice::AddAllPictures | pathLen > MAX_PATH_LENGTH | %d", pathLen);
            continue;
        }
        char* imagePath = new char[pathLen + 1]();
        if (sprintf_s(imagePath, pathLen + 1, "%s/%s", PHOTO_DIRECTORY, info->d_name) < 0) {
            LOGE("GalleryAbilitySlice::AddAllPictures | sprintf_s error");
            delete[] imagePath;
            continue;
        }

        LOGI("add image: pos:[%d, %d], name:%s, path:%s", imagePos.x, imagePos.y, imageName, imagePath);
        picList_->Add(CreateImageItem(imagePos, imageName, imagePath));
        delete[] imagePath;

        if ((pictureCount_ % numInLine) == 0) {
            imagePos.x = pos.x;
            imagePos.y += THUMBNAIL_RESOLUTION_Y() + THUMBNAIL_SPACE;
        } else {
            imagePos.x += THUMBNAIL_RESOLUTION_X() + THUMBNAIL_SPACE;
        }
    }
    delete info;
    closedir(drip);
}

UIView* GalleryAbilitySlice::CreateImageItem(const Point& pos, const char* imageName, const char* imagePath)
{
    UIImageView* imageView = new UIImageView();
    imageView->SetAutoEnable(false);
    imageView->Resize(THUMBNAIL_RESOLUTION_X(), THUMBNAIL_RESOLUTION_Y());
    pictureOnClickListener_[pictureOnClickListenerCount_] = GetImageClickListener(imageName);
    imageView->SetOnClickListener(pictureOnClickListener_[pictureOnClickListenerCount_++]);
    imageView->SetTouchable(true);
    imageView->SetResizeMode(UIImageView::FILL);
    imageView->SetPosition(0, 0);

    UIViewGroup* imageItem = new UIViewGroup();
    imageItem->SetStyle(STYLE_BACKGROUND_OPA, 0);
    imageItem->SetPosition(pos.x, pos.y, THUMBNAIL_RESOLUTION_X(), THUMBNAIL_RESOLUTION_Y());
    imageItem->SetTouchable(true);
    imageItem->SetOnClickListener(imageView->GetOnClickListener());
    imageItem->Add(imageView);

    std::string filePath(imagePath);
    if (filePath.find("mp4") != std::string::npos) {
        UIImageView* videoTag = new UIImageView();
        std::string videoTagFielPath = videoTagIconAbsolutePath;
        videoTag->SetPosition(VIDEO_TAG_POSITION_X(), VIDEO_TAG_POSITION_Y(), VIDEO_TAG_WIDTH(), VIDEO_TAG_HEIGHT());
        videoTag->SetTouchable(true);
        videoTag->SetOnClickListener(imageView->GetOnClickListener());
        imageDecoder_->DecodeImage(videoTagFielPath, [videoTag, videoTagFielPath](ImageInfo imageInfo) {
            LOGI("do SetSrc for img, filePath:%s, dataSize:%u", videoTagFielPath.c_str(), imageInfo.dataSize);
            videoTag->SetSrc(&imageInfo);
        });

        UILabel* labelView = new UILabel();
        labelView->SetPosition(0, 0, THUMBNAIL_RESOLUTION_X(), THUMBNAIL_RESOLUTION_Y());
        labelView->SetAlign(UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER,
                            UITextLanguageAlignment::TEXT_ALIGNMENT_CENTER);
        labelView->SetLineBreakMode(UILabel::LineBreakMode::LINE_BREAK_ELLIPSIS);
        labelView->SetFont(FONT_NAME, GALLERY_FONT_SIZE());
        labelView->SetStyle(STYLE_TEXT_COLOR, Color::White().full);
        labelView->SetStyle(STYLE_TEXT_OPA, OPA_OPAQUE);
        labelView->SetText(imageName);

        imageItem->SetStyle(STYLE_BACKGROUND_COLOR, Color::Black().full);
        imageItem->SetStyle(STYLE_BACKGROUND_OPA, OPA_OPAQUE);
        imageItem->Add(videoTag);
        imageItem->Add(labelView);
    } else {
        std::string fileName = imageName;
        std::string filePath = imagePath;
        static int num = 0;
        imageDecoder_->DecodeImage(filePath, [imageView, filePath](ImageInfo imageInfo) {
            LOGI("do SetSrc for img, filePath:%s, dataSize:%u", filePath.c_str(), imageInfo.dataSize);
            imageView->SetSrc(&imageInfo);
        });
    }

    return imageItem;
}

EventListener* GalleryAbilitySlice::GetImageClickListener(const char* path)
{
    auto onClick = [this, path] (UIView& view, const Event& event) -> bool {
        LOGI("############  Next AS enter   #############");
        Want wantData = { nullptr };
        LOGI("------- imagePath: %s ", path);
        bool ret = SetWantData(&wantData, path, strlen(path) + 1);
        if (!ret) {
            LOGE("############  SetWantData error   #############");
            return ret;
        }
        AbilitySlice* nextSlice = nullptr;
        std::string filePath(path);
        if (filePath.find("jpg") != std::string::npos) {
            LOGI("--------- enter PictureAbilitySlice");
            nextSlice = AbilityLoader::GetInstance().GetAbilitySliceByName("PictureAbilitySlice");
        } else {
            LOGI("--------- enter PlayerAbilitySlice");
            nextSlice = AbilityLoader::GetInstance().GetAbilitySliceByName("PlayerAbilitySlice");
        }
        if (nextSlice == nullptr) {
            LOGW("undefined nextSlice");
        } else {
            Present(*nextSlice, wantData);
        }
        LOGI("############  Next AS exit   #############");
        return true;
    };
    return new EventListener(onClick, nullptr);
}

void GalleryAbilitySlice::DeleteAllData()
{
    picContainer_->Invalidate();
    rootView_->Remove(picContainer_);
    ClearThumb();

    DeleteAllFilesInDir(THUMBNAIL_DIRECTORY);
    DeleteAllFilesInDir(PHOTO_DIRECTORY);
    DeleteAllFilesInDir(VIDEO_SOURCE_DIRECTORY);

    InitPictureList();
}

void GalleryAbilitySlice::DeleteAllFilesInDir(const char* path)
{
    DIR* drip = opendir(path);
    if (drip == nullptr) {
        return;
    }
    struct dirent* info = nullptr;
    while ((info = readdir(drip)) != nullptr) {
        uint16_t fileNameLen = static_cast<uint16_t>(strlen(info->d_name));
        uint16_t pathLen = static_cast<uint16_t>(strlen(path)) + fileNameLen + 1;
        if (pathLen > MAX_PATH_LENGTH) {
            LOGW("GalleryAbilitySlice::AddAllPictures | pathLen > MAX_PATH_LENGTH | %d", pathLen);
            continue;
        }
        char* filePath = new char[pathLen + 1]();
        if (sprintf_s(filePath, pathLen + 1, "%s/%s", path, info->d_name) < 0) {
            LOGE("GalleryAbilitySlice::AddAllPictures | sprintf_s error");
            delete[] filePath;
            continue;
        }
        if (unlink(filePath) != 0) {
            LOGE("unlink file error | %s", filePath);
        }
        delete[] filePath;
    }
    delete info;
    closedir(drip);
    LOGI("GalleryAbilitySlice::DeleteAllFilesInDir() | success | %s", path);
}

void GalleryAbilitySlice::OnStart(const Want &want)
{
    AbilitySlice::OnStart(want);

    rootView_ = RootView::GetWindowRootView();
    rootView_->SetPosition(ROOT_VIEW_POSITION_X, ROOT_VIEW_POSITION_Y);
    rootView_->Resize(ROOT_VIEW_WIDTH(), ROOT_VIEW_HEIGHT());
    rootView_->SetStyle(STYLE_BACKGROUND_COLOR, Color::White().full);

    const char* pathHeader = GetSrcPath();
    if (sprintf_s(backIconAbsolutePath, MAX_PATH_LENGTH, "%s%s", pathHeader, BACK_ICON_PATH) < 0) {
        LOGE("GalleryAbilitySlice::OnStart | backIconAbsolutePath error");
        return;
    }
    if (sprintf_s(videoTagIconAbsolutePath, MAX_PATH_LENGTH, "%s%s", pathHeader, VIDEO_TAG_ICON_PATH) < 0) {
        LOGE("GalleryAbilitySlice::OnStart | videoTagIconAbsolutePath error");
        return;
    }

    imageDecoder_ = new ImageDecoder(AbilityEventHandler::GetCurrentHandler(), 1);

    InitTitle();
    InitPictureList();
    SetUIContent(rootView_);
}

void GalleryAbilitySlice::OnInactive()
{
    LOGI("GalleryAbilitySlice::OnInactive");
    AbilitySlice::OnInactive();
}

void GalleryAbilitySlice::OnActive(const Want &want)
{
    LOGI("GalleryAbilitySlice::OnActive");
    AbilitySlice::OnActive(want);
    if (!imageDecoder_->IsRunning()) {
        imageDecoder_->Start();
    }
}

void GalleryAbilitySlice::OnBackground()
{
    LOGI("GalleryAbilitySlice::OnBackground");
    AbilitySlice::OnBackground();
}

void GalleryAbilitySlice::OnStop()
{
    LOGI("GalleryAbilitySlice::OnStop");
    AbilitySlice::OnStop();
    Clear();
}
}
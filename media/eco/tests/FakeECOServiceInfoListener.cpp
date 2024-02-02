/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "FakeFakeECOServiceInfoListener"

#include "FakeECOServiceInfoListener.h"

#include <android-base/unique_fd.h>
#include <binder/Parcel.h>
#include <binder/Parcelable.h>
#include <cutils/ashmem.h>
#include <gtest/gtest.h>
#include <math.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <utils/Log.h>

namespace android {
namespace media {
namespace eco {

FakeECOServiceInfoListener::FakeECOServiceInfoListener(int32_t width, int32_t height,
                                                       bool isCameraRecording,
                                                       android::sp<IECOSession> session)
      : mWidth(width),
        mHeight(height),
        mIsCameraRecording(isCameraRecording),
        mECOSession(session) {
    ALOGD("FakeECOServiceInfoListener construct with w: %d, h: %d, isCameraRecording: %d", mWidth,
          mHeight, mIsCameraRecording);
}

FakeECOServiceInfoListener::FakeECOServiceInfoListener(int32_t width, int32_t height,
                                                       bool isCameraRecording)
      : mWidth(width), mHeight(height), mIsCameraRecording(isCameraRecording) {
    ALOGD("FakeECOServiceInfoListener construct with w: %d, h: %d, isCameraRecording: %d", mWidth,
          mHeight, mIsCameraRecording);
}

FakeECOServiceInfoListener::~FakeECOServiceInfoListener() {
    ALOGD("FakeECOServiceInfoListener destructor");
}

Status FakeECOServiceInfoListener::getType(int32_t* /*_aidl_return*/) {
    return binder::Status::ok();
}

Status FakeECOServiceInfoListener::getName(::android::String16* _aidl_return) {
    *_aidl_return = String16("FakeECOServiceInfoListener");
    return binder::Status::ok();
}

Status FakeECOServiceInfoListener::getECOSession(sp<::android::IBinder>* _aidl_return) {
    *_aidl_return = IInterface::asBinder(mECOSession);
    return binder::Status::ok();
}

Status FakeECOServiceInfoListener::onNewInfo(const ::android::media::eco::ECOData& newInfo) {
    ALOGD("FakeECOServiceInfoListener get new info");
    mInfoAvaiableCallback(newInfo);
    return binder::Status::ok();
}

// IBinder::DeathRecipient implementation
void FakeECOServiceInfoListener::binderDied(const wp<IBinder>& /*who*/) {}

}  // namespace eco
}  // namespace media
}  // namespace android

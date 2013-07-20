/*
 * Copyright (C) 2010 The Android Open Source Project
 * Copyright (C) 2012, The Linux Foundation. All rights reserved.
 *
 * Not a Contribution, Apache license notifications and license are
 * retained for attribution purposes only.

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

#ifndef HWC_EXTERNAL_DISPLAY_H
#define HWC_EXTERNAL_DISPLAY_H

#include <utils/threads.h>
#include <linux/fb.h>

struct hwc_context_t;

/* Video formates supported by the HDMI Standard */
/* Indicates the resolution, pix clock and the aspect ratio */
#define m640x480p60_4_3         1
#define m720x480p60_4_3         2
#define m720x480p60_16_9        3
#define m1280x720p60_16_9       4
#define m1920x1080i60_16_9      5
#define m1440x480i60_4_3        6
#define m1440x480i60_16_9       7
#define m1920x1080p60_16_9      16
#define m720x576p50_4_3         17
#define m720x576p50_16_9        18
#define m1280x720p50_16_9       19
#define m1440x576i50_4_3        21
#define m1440x576i50_16_9       22
#define m1920x1080p50_16_9      31
#define m1920x1080p24_16_9      32
#define m1920x1080p25_16_9      33
#define m1920x1080p30_16_9      34

namespace qhwc {

//Type of scanning of EDID(Video Capability Data Block)
enum external_scansupport_type {
    EXT_SCAN_NOT_SUPPORTED      = 0,
    EXT_SCAN_ALWAYS_OVERSCANED  = 1,
    EXT_SCAN_ALWAYS_UNDERSCANED = 2,
    EXT_SCAN_BOTH_SUPPORTED     = 3
};

enum mode_state {
    EXT_MODE_CHANGED = 1,
    EXT_MODE_RESET   = 2,
};

class ExternalDisplay
{
public:
    ExternalDisplay(hwc_context_t* ctx);
    ~ExternalDisplay();
    int getModeCount() const;
    void getEDIDModes(int *out) const;
    bool isCEUnderscanSupported() { return mUnderscanSupported; }
    void setExternalDisplay(bool connected, int extFbNum = 0);
    bool isExternalConnected() { return mConnected;};
    void  setExtDpyNum(int extDpyNum) { mExtDpyNum = extDpyNum;};
    int  getExternalType() {return mConnectedFbNum;};
    bool isWFDActive() {return (mConnectedFbNum == mWfdFbNum);};
    bool isHDMIPrimary() {return mHdmiPrimary;};
    void setHPD(uint32_t startEnd);
    void setEDIDMode(int resMode);
    void setActionSafeDimension(int w, int h);
    void setCustomMode(int mode) {mNewMode = mode; mCustomMode = mode;}
    void setNewMode(int mode) {mNewMode = mode;}
    int getCustomMode() {return mCustomMode;};
    int ignoreRequest(const char *str);
    int  configureHDMIDisplay(int mode = -1);
    int  getNewMode();
    int  getCurMode();
    int  configureWFDDisplay();
    int  teardownHDMIDisplay();
    int  teardownWFDDisplay();
    int  setHdmiPrimaryMode();
    bool isHdmiPrimary() { return mHdmiPrimary; }
    bool hasResolutionChanged() { return mHdmiPrimaryResChanged;}
    bool readResolution();
    bool isValidMode(int ID);
    bool isInterlacedMode(int mode);

private:
    void readCEUnderscanInfo();
    int  parseResolution(char* edidStr, int* edidModes);
    void setResolution(int ID);
    bool openFrameBuffer(int fbNum);
    bool closeFrameBuffer();
    bool writeHPDOption(int userOption) const;
    void handleUEvent(char* str, int len);
    int  getModeOrder(int mode);
    int  getUserMode();
    int  getBestMode();
    void resetInfo();
    void setDpyHdmiAttr();
    void setDpyWfdAttr();
    void getAttrForMode(int& width, int& height, int& fps);
    void updateExtDispDevFbIndex();
    int  getExtFbNum(int &fbNum);

    mutable android::Mutex mExtDispLock;
    int mFd;
    int mCurrentMode;
    int mConnected;
    int mConnectedFbNum;
    int mResolutionMode;
    char mEDIDs[128];
    int mEDIDModes[64];
    int mModeCount;
    bool mUnderscanSupported;
    hwc_context_t *mHwcContext;
    fb_var_screeninfo mVInfo;
    int mHdmiFbNum;
    int mWfdFbNum;
    int mExtDpyNum;
    bool mHdmiPrimary;
    bool mHdmiPrimaryResChanged;
    int mCustomMode;
    int mCurMode;
    int mNewMode;
};

}; //qhwc
// ---------------------------------------------------------------------------
#endif //HWC_EXTERNAL_DISPLAY_H

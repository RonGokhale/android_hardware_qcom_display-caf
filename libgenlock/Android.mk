LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := qcom/display
LOCAL_COPY_HEADERS := genlock.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)
LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_C_INCLUDES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_C_INCLUDES += $(TARGET_OUT_HEADERS)/qcom/display
LOCAL_ADDITIONAL_DEPENDENCIES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr
LOCAL_SRC_FILES := genlock.cpp
LOCAL_CFLAGS:= -DLOG_TAG=\"libgenlock\"
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libgenlock
include $(BUILD_SHARED_LIBRARY)

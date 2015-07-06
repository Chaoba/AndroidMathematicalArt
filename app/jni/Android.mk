LOCAL_PATH := $(call my-dir)

#bitmap operations module
include $(CLEAR_VARS)

LOCAL_MODULE    := MathematicalArtLibrary
LOCAL_SRC_FILES := MathematicalArtLibrary.cpp
LOCAL_LDLIBS := -llog
LOCAL_LDFLAGS += -ljnigraphics
#LOCAL_C_INCLUDES := D:/software/android-ndk-r10e/sources/cxx-stl/stlport/stlport


include $(BUILD_SHARED_LIBRARY)
APP_OPTIM := debug
LOCAL_CFLAGS := -g

#if you need to add more module, do the same as the one we started with (the one with the CLEAR_VARS)
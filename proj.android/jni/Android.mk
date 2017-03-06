LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES_JNI_PREFIXED := \
    $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp) \
    $(wildcard $(LOCAL_PATH)/../../Classes/**/*.cpp) \
    $(wildcard $(LOCAL_PATH)/../../Classes/**/**/*.cpp) \
    $(wildcard $(LOCAL_PATH)/../../Classes/**/**/**/*.cpp)

LOCAL_SRC_FILES_JNI_UNPREFIXED := $(subst jni/,, $(LOCAL_SRC_FILES_JNI_PREFIXED))

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   $(LOCAL_SRC_FILES_JNI_UNPREFIXED)

$(info $(LOCAL_SRC_FILES))


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/Manager \
					$(LOCAL_PATH)/../../Classes/Object \
					$(LOCAL_PATH)/../../Classes/puzzle \
					$(LOCAL_PATH)/../../Classes/Scene \

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

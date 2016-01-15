LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Desert_home.cpp \
                   ../../Classes/Desert_level.cpp \
                   ../../Classes/Desert_help.cpp \
                   ../../Classes/TooslFunction.cpp \
                   ../../Classes/MainUI.cpp \
                   ../../Classes/AudioManage.cpp \
                   ../../Classes/Btn_QuestionSelect.cpp \
                   ../../Classes/Exit.cpp \
                   ../../Classes/guaiwu_js.cpp \
                   ../../Classes/Level_1.cpp \
                   ../../Classes/Level_2.cpp \
                   ../../Classes/Level_3.cpp \
                   ../../Classes/Level_4.cpp \
                   ../../Classes/Level_5.cpp \
                   ../../Classes/Level_6.cpp \
                   ../../Classes/Level_7.cpp \
                   ../../Classes/Level_8.cpp \
                   ../../Classes/Level_9.cpp \
                   ../../Classes/Level_10.cpp \
                   ../../Classes/MainCar_R.cpp \
                   ../../Classes/objSpring.cpp \
                   ../../Classes/other_level_1.cpp \
                   ../../Classes/other_level_2.cpp \
                   ../../Classes/SpriteTweenBase.cpp \
                   ../../Classes/Archery.cpp \
                   ../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

      

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static


# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)



# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

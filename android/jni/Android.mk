LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := helloworld_shared

LOCAL_MODULE_FILENAME := libhelloworld

LOCAL_SRC_FILES := helloworld/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/LoginScene.cpp	\
                   ../../Classes/Component/Bullet.cpp \
                   ../../Classes/Component/Cannon.cpp \
                   ../../Classes/Component/ControllPanel.cpp \
                   ../../Classes/Component/GamingLayer.cpp \
                   ../../Classes/Component/PauseLayer.cpp \
                   ../../Classes/Component/ResulitLayer.cpp \
                   ../../Classes/Config/BaseConfig.cpp \
                   ../../Classes/Config/NotificationNameConfig.cpp \
                   ../../Classes/CsvReader/CsvReader.cpp \
                   ../../Classes/GameData/MonsterData.cpp \
                   ../../Classes/GameData/MonsterMrg.cpp \
                   ../../Classes/GameData/PlayerData.cpp \
                   ../../Classes/GameData/PlayerMrg.cpp \
                   ../../Classes/XmlReader/XmlReader.cpp 



LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)
$(call import-add-path, D:/projects/cocos2d-1.0.1-x-0.13.0-beta)
$(call import-add-path, D:/projects/cocos2d-1.0.1-x-0.13.0-beta/cocos2dx/platform/third_party/android/prebuilt)
$(call import-module,cocos2dx)

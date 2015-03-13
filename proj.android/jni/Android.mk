LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/controllers/GameController.cpp
                   ../../Classes/controllers/MainController.cpp
                   ../../Classes/models/GameModel.cpp
                   ../../Classes/services/RemoteService.cpp
                   ../../Classes/services/WSService.cpp
                   ../../Classes/ui/sprites/DSprite.cpp
                   ../../Classes/ui/sprites/TSprite.cpp
                   ../../Classes/utils/poker_eval_lib/mtrand.cpp
                   ../../Classes/utils/poker_eval_lib/pokerlib.cpp
                   ../../Classes/utils/GameUtils.cpp
                   ../../Classes/utils/PixelCollision.cpp
                   ../../Classes/views/comps/DragSampleView.cpp
                   ../../Classes/views/comps/VideoSampleView.cpp
                   ../../Classes/views/MainView.cpp                   
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

#pragma once

#include "capi/config.h"

typedef enum EPluginMsgType {
    ELuaOnReady = 11,
    EFrameUpdate = 12,
    EOnPause = 15,
    EOnResume = 16,
    EOnExit = 30,
    EThreadLuaOnReady = 31,
} EPluginMsgType;

extern "C" {
    typedef int(*PluginProc)(int, void*);
    void addPlugin(PluginProc proc,const char* name);

#if defined(ANDROID)
    #include <jni.h>
    JNIEnv* getEnv();
    jclass findClass(JNIEnv* env, const char* className);
#endif
}


#if (TARGET_PLATFORM == PLATFORM_IOS)
#define BABE_PLUGIN_ENTRY(name) \
extern "C" { \
    int name##_plugin_proc(EPluginMsgType eMsgType, void* param1) { \
        return name(eMsgType, param1); \
    } \
}
#elif (TARGET_PLATFORM == PLATFORM_WIN32)
    #define BABE_PLUGIN_ENTRY(name) \
    extern "C" {  \
        __declspec(dllexport) int plugin_proc(EPluginMsgType eMsgType, void* param1); \
        int plugin_proc(EPluginMsgType eMsgType, void* param1) { \
            return name(eMsgType, param1); \
        } \
    }
#else
#define BABE_PLUGIN_ENTRY(name) \
DLL_EXPORT extern "C" { \
    int plugin_proc(EPluginMsgType eMsgType, void* param1) { \
        return name(eMsgType, param1); \
    } \
}
#endif





//
//  config.h
//  ghost
//
//  Created by VicentGong on 14-3-6.
//  Copyright (c) 2014 VicentGong. All rights reserved.
//
#pragma once

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#elif ANDROID
#define DLL_EXPORT __attribute__((visibility("default")))
#else
#define DLL_EXPORT 
#endif

#define PLATFORM_UNKNOWN 0
#define PLATFORM_IOS     1
#define PLATFORM_ANDROID 2
#define PLATFORM_WIN32   3
#define PLATFORM_WP8	 4
#define PLATFORM_WIN10	 5
#define PLATFORM_LINUX   6

#include "lua/include.h"
#include "LuaIntf/LuaIntf.h"


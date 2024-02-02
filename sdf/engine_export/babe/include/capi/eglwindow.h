#pragma once

#include "capi/config.h"

#ifdef __cplusplus
extern "C" {
#endif
	DLL_EXPORT void* eglwindow_create_external_context();
	DLL_EXPORT void eglwindow_destory_external_context(void* context);
	DLL_EXPORT bool eglwindow_make_current_context(void* context);
	DLL_EXPORT void* eglwindow_get_gl_load_proc();
	DLL_EXPORT void* eglwindow_get_handler();

#ifdef __cplusplus
}
#endif
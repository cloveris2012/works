/* 插件导出c接口
* @Author: YuchengMo
* @Date:   2021-09-09 10:42:14
* @Last Modified by:   YuchengMo
* @Last Modified time: 2021-09-09 10:45:05
*/
#include "capi/config.h"

#ifdef __cplusplus
extern "C" {
#endif
	DLL_EXPORT bool is_main_thread();
	DLL_EXPORT bool is_render_thread();
	DLL_EXPORT void run_in_main_thread(void (*fn)(void*), void* ud);
	DLL_EXPORT void run_in_render_thread(void (*fn)(void*), void* ud);

	// fixme 需要移走 不属于runloop 只是临时放这里
	DLL_EXPORT void lua_err(lua_State* L);

#ifdef __cplusplus
}
#endif

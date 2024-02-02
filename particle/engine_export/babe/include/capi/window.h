/* window导出c接口
* @Author: YuchengMo
* @Date:   2021-09-09 10:42:14
* @Last Modified by:   YuchengMo
* @Last Modified time: 2021-09-09 10:45:05
*/

#include "capi/config.h"
#ifdef __cplusplus
extern "C" {
#endif
	DLL_EXPORT int window_capture_begin_read(long win, int* width, int* height);
	DLL_EXPORT void window_capture_end_read(long win);
#ifdef __cplusplus
}
#endif

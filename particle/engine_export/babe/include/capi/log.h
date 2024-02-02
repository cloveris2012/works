/* 日志导出c接口
* @Author: YuchengMo
* @Date:   2021-09-09 10:42:14
* @Last Modified by:   YuchengMo
* @Last Modified time: 2021-09-09 10:45:05
*/
#include "capi/config.h"

typedef void(*LogHandler)(const char* typestr, const char* tag, const char* content, unsigned int color);

#ifdef __cplusplus
extern "C" {
#endif
	DLL_EXPORT void add_log_handler(LogHandler handler);

	DLL_EXPORT void remove_log_handler(LogHandler handler);
	DLL_EXPORT void clear_log_handlers();
	DLL_EXPORT void log_i(const char* tag, const char* format, va_list vlist);
	DLL_EXPORT void log_w(const char* tag, const char* format, va_list vlist);
	DLL_EXPORT void log_e(const char* tag, const char* format, va_list vlist);
#ifdef __cplusplus
}
#endif

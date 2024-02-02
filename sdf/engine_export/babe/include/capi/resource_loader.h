/* 资源加载导出c接口
* @Author: YuchengMo
* @Date:   2021-09-09 10:42:14
* @Last Modified by:   YuchengMo
* @Last Modified time: 2021-09-09 10:45:05
*/

#include "capi/config.h"

#ifdef __cplusplus
extern "C" {
#endif
	DLL_EXPORT void* load_to_stream(const char* name, int type);
	DLL_EXPORT int istream_tellg(void* s);
	DLL_EXPORT void istream_seekg(void* s, int pos, int direction);
	DLL_EXPORT void istream_read(void* s, char* c, int size);
	DLL_EXPORT int istream_gcount(void* s);
	DLL_EXPORT bool isteam_good(void* s);
	DLL_EXPORT bool istream_eof(void* s);
	DLL_EXPORT void istream_clear(void* s);
	DLL_EXPORT void release_istream(void* s);

	DLL_EXPORT void* create_loader(const char* path);
	DLL_EXPORT void release_loader(void* zip_loader);
	DLL_EXPORT int loader_get_entry_count(void* zip_loader);
	DLL_EXPORT const char* loader_get_entry_name(void* zip_loader, int i);
	DLL_EXPORT void* loader_load_entry_as_loader(void* loader, const char* name);
	DLL_EXPORT char* loader_load_entry(void* zip_loader, const char* name, int* psize);
	DLL_EXPORT void loader_release_entry(void* zip_loader, char* pdata);

#ifdef __cplusplus
}
#endif

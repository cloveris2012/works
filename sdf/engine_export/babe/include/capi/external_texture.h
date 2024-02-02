/* external_texture 导出c接口
* @Author: YuchengMo
* @Date:   2021-09-09 10:42:14
* @Last Modified by:   YuchengMo
* @Last Modified time: 2021-09-09 10:45:05
*/

#include "capi/config.h"

#ifdef __cplusplus
extern "C" {
#endif
	DLL_EXPORT int external_texture_create(unsigned int width, unsigned int height, unsigned int t1, unsigned int t2, unsigned int t3);
	DLL_EXPORT void external_texture_release(int handler);
	DLL_EXPORT void external_texture_set_size(int handler, unsigned int width, unsigned int height);
	DLL_EXPORT unsigned int external_texture_begin_write(int handler);
	DLL_EXPORT void external_texture_end_write(int handler);
#ifdef __cplusplus
}
#endif
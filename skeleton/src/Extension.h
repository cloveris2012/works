#ifndef Skel_Extension_h
#define Skel_Extension_h


#include <stdlib.h>
#include "utils/dll.h"

#define SP_UNUSED(x) (void)(x)

namespace skel {
class String;

class SK_API SkelExtension {
public:
	template<typename T>
	static T *alloc(size_t num, const char *file, int line) {
		return (T *) getInstance()->_alloc(sizeof(T) * num, file, line);
	}

	template<typename T>
	static T *calloc(size_t num, const char *file, int line) {
		return (T *) getInstance()->_calloc(sizeof(T) * num, file, line);
	}

	template<typename T>
	static T *realloc(T *ptr, size_t num, const char *file, int line) {
		return (T *) getInstance()->_realloc(ptr, sizeof(T) * num, file, line);
	}

	template<typename T>
	static void free(T *ptr, const char *file, int line) {
		getInstance()->_free((void *) ptr, file, line);
	}

	template<typename T>
	static void beforeFree(T *ptr) {
		getInstance()->_beforeFree((void *) ptr);
	}
	
	static char *readFile(const String &path, int *length) {
		return getInstance()->_readFile(path, length);
	}

	static void setInstance(SkelExtension *inSkelExtension);

	static SkelExtension *getInstance();

	virtual ~SkelExtension();

	/// Implement this function to use your own memory allocator
	virtual void *_alloc(size_t size, const char *file, int line) = 0;

	virtual void *_calloc(size_t size, const char *file, int line) = 0;

	virtual void *_realloc(void *ptr, size_t size, const char *file, int line) = 0;

	/// If you provide a skelAllocFunc, you should also provide a skelFreeFunc
	virtual void _free(void *mem, const char *file, int line) = 0;

	virtual char *_readFile(const String &path, int *length) = 0;

	virtual void _beforeFree(void *ptr) { SP_UNUSED(ptr); }

protected:
	SkelExtension();

private:
	static SkelExtension *_instance;
};

class SK_API DefaultSkelExtension : public SkelExtension {
public:
	DefaultSkelExtension();

	virtual ~DefaultSkelExtension();

protected:
	virtual void *_alloc(size_t size, const char *file, int line);

	virtual void *_calloc(size_t size, const char *file, int line);

	virtual void *_realloc(void *ptr, size_t size, const char *file, int line);

	virtual void _free(void *mem, const char *file, int line);

	virtual char *_readFile(const String &path, int *length);
};

}

#endif /* Skel_Extension_h */

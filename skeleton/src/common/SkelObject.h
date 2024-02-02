#ifndef Skel_Object_h
#define Skel_Object_h

#include <new>
#include <stddef.h>

#include "utils/dll.h"

namespace skel {
class String;

class SK_API SkelObject {
public:
	void *operator new(size_t sz);

	void *operator new(size_t sz, const char *file, int line);

	void *operator new(size_t sz, void *ptr);

	void operator delete(void *p, const char *file, int line);

	void operator delete(void *p, void *mem);

	void operator delete(void *p);

	virtual ~SkelObject();
};
}

#endif

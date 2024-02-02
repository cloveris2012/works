#include "common/SkelObject.h"
#include "Extension.h"

using namespace skel;

void *SkelObject::operator new(size_t sz) {
	return SkelExtension::getInstance()->_calloc(sz, __FILE__, __LINE__);
}

void *SkelObject::operator new(size_t sz, const char *file, int line) {
	return SkelExtension::getInstance()->_calloc(sz, file, line);
}

void *SkelObject::operator new(size_t sz, void *ptr) {
	SP_UNUSED(sz);
	return ptr;
}

void SkelObject::operator delete(void *p, const char *file, int line) {
	SkelExtension::free(p, file, line);
}

void SkelObject::operator delete(void *p, void *mem) {
	SP_UNUSED(mem);
	SkelExtension::free(p, __FILE__, __LINE__);
}

void SkelObject::operator delete(void *p) {
	SkelExtension::free(p, __FILE__, __LINE__);
}

SkelObject::~SkelObject() {
	SkelExtension::beforeFree(this);
}

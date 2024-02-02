#include "Extension.h"
#include "common/SkelString.h"

#include <assert.h>

using namespace skel;

SkelExtension *SkelExtension::_instance = NULL;

void SkelExtension::setInstance(SkelExtension *inValue) {
	assert(inValue);

	_instance = inValue;
}

SkelExtension *SkelExtension::getInstance() {
	if (!_instance) _instance = new DefaultSkelExtension;
	assert(_instance);

	return _instance;

	/*static DefaultSkelExtension instance;
	return &instance;*/
}

SkelExtension::~SkelExtension() {
}

SkelExtension::SkelExtension() {
}

DefaultSkelExtension::~DefaultSkelExtension() {
}

void *DefaultSkelExtension::_alloc(size_t size, const char *file, int line) {
	SP_UNUSED(file);
	SP_UNUSED(line);

	if (size == 0)
		return 0;
	void *ptr = ::malloc(size);
	return ptr;
}

void *DefaultSkelExtension::_calloc(size_t size, const char *file, int line) {
	SP_UNUSED(file);
	SP_UNUSED(line);

	if (size == 0)
		return 0;

	void *ptr = ::malloc(size);
	if (ptr) {
		memset(ptr, 0, size);
	}
	return ptr;
}

void *DefaultSkelExtension::_realloc(void *ptr, size_t size, const char *file, int line) {
	SP_UNUSED(file);
	SP_UNUSED(line);

	void *mem = NULL;
	if (size == 0)
		return 0;
	if (ptr == NULL)
		mem = ::malloc(size);
	else
		mem = ::realloc(ptr, size);
	return mem;
}

void DefaultSkelExtension::_free(void *mem, const char *file, int line) {
	SP_UNUSED(file);
	SP_UNUSED(line);

	::free(mem);
}

char *DefaultSkelExtension::_readFile(const String &path, int *length) {
	char *data;
	FILE *file = fopen(path.buffer(), "rb");
	if (!file) return 0;

	fseek(file, 0, SEEK_END);
	*length = (int) ftell(file);
	fseek(file, 0, SEEK_SET);

	data = SkelExtension::alloc<char>(*length, __FILE__, __LINE__);
	fread(data, 1, *length, file);
	fclose(file);

	return data;
}

DefaultSkelExtension::DefaultSkelExtension() : SkelExtension() {
}

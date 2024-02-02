#ifndef SKEL_STRING_H
#define SKEL_STRING_H

#include "common/SkelObject.h"
#include "../Extension.h"

#include <string.h>
#include <stdio.h>

// Required for sprintf on MSVC
#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif

namespace skel {
class SK_API String : public SkelObject {
public:
	String() : _length(0), _buffer(NULL) {
	}

	String(const char *chars, bool own = false) {
		if (!chars) {
			_length = 0;
			_buffer = NULL;
		} else {
			_length = strlen(chars);
			if (!own) {
				_buffer = SkelExtension::calloc<char>(_length + 1, __FILE__, __LINE__);
				memcpy((void *) _buffer, chars, _length + 1);
			} else {
				_buffer = (char *) chars;
			}
		}
	}

	String(const String &other) {
		if (!other._buffer) {
			_length = 0;
			_buffer = NULL;
		} else {
			_length = other._length;
			_buffer = SkelExtension::calloc<char>(other._length + 1, __FILE__, __LINE__);
			memcpy((void *) _buffer, other._buffer, other._length + 1);
		}
	}

	size_t length() const {
		return _length;
	}

	bool isEmpty() const {
		return _length == 0;
	}

	const char *buffer() const {
		return _buffer;
	}

	void own(const String &other) {
		if (this == &other) return;
		if (_buffer) {
			SkelExtension::free(_buffer, __FILE__, __LINE__);
		}
		_length = other._length;
		_buffer = other._buffer;
		other._length = 0;
		other._buffer = NULL;
	}

	void own(const char *chars) {
		if (_buffer == chars) return;
		if (_buffer) {
			SkelExtension::free(_buffer, __FILE__, __LINE__);
		}

		if (!chars) {
			_length = 0;
			_buffer = NULL;
		} else {
			_length = strlen(chars);
			_buffer = (char *) chars;
		}
	}

	void unown() {
		_length = 0;
		_buffer = NULL;
	}

	String &operator=(const String &other) {
		if (this == &other) return *this;
		if (_buffer) {
			SkelExtension::free(_buffer, __FILE__, __LINE__);
		}
		if (!other._buffer) {
			_length = 0;
			_buffer = NULL;
		} else {
			_length = other._length;
			_buffer = SkelExtension::calloc<char>(other._length + 1, __FILE__, __LINE__);
			memcpy((void *) _buffer, other._buffer, other._length + 1);
		}
		return *this;
	}

	String &operator=(const char *chars) {
		if (_buffer == chars) return *this;
		if (_buffer) {
			SkelExtension::free(_buffer, __FILE__, __LINE__);
		}
		if (!chars) {
			_length = 0;
			_buffer = NULL;
		} else {
			_length = strlen(chars);
			_buffer = SkelExtension::calloc<char>(_length + 1, __FILE__, __LINE__);
			memcpy((void *) _buffer, chars, _length + 1);
		}
		return *this;
	}

	String &append(const char *chars) {
		size_t len = strlen(chars);
		size_t thisLen = _length;
		_length = _length + len;
		bool same = chars == _buffer;
		_buffer = SkelExtension::realloc(_buffer, _length + 1, __FILE__, __LINE__);
		memcpy((void *) (_buffer + thisLen), (void *) (same ? _buffer : chars), len + 1);
		return *this;
	}

	String &append(const String &other) {
		size_t len = other.length();
		size_t thisLen = _length;
		_length = _length + len;
		bool same = other._buffer == _buffer;
		_buffer = SkelExtension::realloc(_buffer, _length + 1, __FILE__, __LINE__);
		memcpy((void *) (_buffer + thisLen), (void *) (same ? _buffer : other._buffer), len + 1);
		return *this;
	}

	String &append(int other) {
		char str[100];
		sprintf(str, "%i", other);
		append(str);
		return *this;
	}

	String &append(float other) {
		char str[100];
		sprintf(str, "%f", other);
		append(str);
		return *this;
	}

	friend bool operator==(const String &a, const String &b) {
		if (a._buffer == b._buffer) return true;
		if (a._length != b._length) return false;
		if (a._buffer && b._buffer) {
			return strcmp(a._buffer, b._buffer) == 0;
		} else {
			return false;
		}
	}

	friend bool operator!=(const String &a, const String &b) {
		return !(a == b);
	}

	~String() {
		if (_buffer) {
			SkelExtension::free(_buffer, __FILE__, __LINE__);
		}
	}

private:
	mutable size_t _length;
	mutable char *_buffer;
};
}


#endif //SKEL_STRING_H

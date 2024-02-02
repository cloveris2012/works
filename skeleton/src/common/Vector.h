#ifndef Skel_Vector_h
#define Skel_Vector_h

#include "../Extension.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"
#include <assert.h>

namespace skel {
template<typename T>
class SK_API Vector : public SkelObject {
public:
	Vector() : _size(0), _capacity(0), _buffer(NULL) {
	}

	Vector(const Vector &inVector) : _size(inVector._size), _capacity(inVector._capacity), _buffer(NULL) {
		if (_capacity > 0) {
			_buffer = allocate(_capacity);
			for (size_t i = 0; i < _size; ++i) {
				construct(_buffer + i, inVector._buffer[i]);
			}
		}
	}

	~Vector() {
		clear();
		deallocate(_buffer);
	}

	inline void clear() {
		for (size_t i = 0; i < _size; ++i) {
			destroy(_buffer + (_size - 1 - i));
		}

		_size = 0;
	}

	inline size_t getCapacity() const {
		return _capacity;
	}

	inline size_t size() const {
		return _size;
	}

	inline void setSize(size_t newSize, const T &defaultValue) {
		assert(newSize >= 0);
		size_t oldSize = _size;
		_size = newSize;
		if (_capacity < newSize) {
			_capacity = (int) (_size * 1.75f);
			if (_capacity < 8) _capacity = 8;
			_buffer = skel::SkelExtension::realloc<T>(_buffer, _capacity, __FILE__, __LINE__);
		}
		if (oldSize < _size) {
			for (size_t i = oldSize; i < _size; i++) {
				construct(_buffer + i, defaultValue);
			}
		}
	}

	inline void ensureCapacity(size_t newCapacity = 0) {
		if (_capacity >= newCapacity) return;
		_capacity = newCapacity;
		_buffer = SkelExtension::realloc<T>(_buffer, newCapacity, __FILE__, __LINE__);
	}

	inline void add(const T &inValue) {
		if (_size == _capacity) {
			// inValue might reference an element in this buffer
			// When we reallocate, the reference becomes invalid.
			// We thus need to create a defensive copy before
			// reallocating.
			T valueCopy = inValue;
			_capacity = (int) (_size * 1.75f);
			if (_capacity < 8) _capacity = 8;
			_buffer = skel::SkelExtension::realloc<T>(_buffer, _capacity, __FILE__, __LINE__);
			construct(_buffer + _size++, valueCopy);
		} else {
			construct(_buffer + _size++, inValue);
		}
	}

	inline void addAt(const T &inValue, int inIndex) {
		assert(inIndex >= 0 && inIndex <= _size);
		add(inValue);
		if (inIndex != _size && _size > 1) {
			T tmp(_buffer[_size - 1]);
			for (int i = _size - 2; i >= inIndex; --i) {
				_buffer[i + 1] = _buffer[i];
			}
			_buffer[inIndex] = tmp;
		}
	}

	inline void addAll(Vector<T> &inValue) {
		ensureCapacity(this->size() + inValue.size());
		for (size_t i = 0; i < inValue.size(); i++) {
			add(inValue[i]);
		}
	}

	inline void clearAndAddAll(Vector<T> &inValue) {
		this->clear();
		this->addAll(inValue);
	}

	inline void removeAt(size_t inIndex) {
		assert(inIndex < _size);

		--_size;

		if (inIndex != _size) {
			for (size_t i = inIndex; i < _size; ++i) {
				T tmp(_buffer[i]);
				_buffer[i] = _buffer[i + 1];
				_buffer[i + 1] = tmp;
			}
		}

		destroy(_buffer + _size);
	}

	inline void remove(const T &inValue) {
		int index = indexOf(inValue);
		assert(index != -1);
		removeAt(index);
	}

	inline bool contains(const T &inValue) {
		for (size_t i = 0; i < _size; ++i) {
			if (_buffer[i] == inValue) {
				return true;
			}
		}

		return false;
	}

	inline int indexOf(const T &inValue) {
		for (size_t i = 0; i < _size; ++i) {
			if (_buffer[i] == inValue) {
				return (int)i;
			}
		}

		return -1;
	}

	inline T &operator[](size_t inIndex) {
		assert(inIndex < _size);

		return _buffer[inIndex];
	}

	inline friend bool operator==(Vector<T> &lhs, Vector<T> &rhs) {
		if (lhs.size() != rhs.size()) {
			return false;
		}

		for (size_t i = 0, n = lhs.size(); i < n; ++i) {
			if (lhs[i] != rhs[i]) {
				return false;
			}
		}

		return true;
	}

	inline friend bool operator!=(Vector<T> &lhs, Vector<T> &rhs) {
		return !(lhs == rhs);
	}

	inline T *buffer() {
		return _buffer;
	}

private:
	size_t _size;
	size_t _capacity;
	T *_buffer;

	inline T *allocate(size_t n) {
		assert(n > 0);

		T *ptr = SkelExtension::calloc<T>(n, __FILE__, __LINE__);

		assert(ptr);

		return ptr;
	}

	inline void deallocate(T *buffer) {
		if (_buffer) {
			SkelExtension::free(buffer, __FILE__, __LINE__);
		}
	}

	inline void construct(T *buffer, const T &val) {
		new(buffer) T(val);
	}

	inline void destroy(T *buffer) {
		buffer->~T();
	}

	// Vector &operator=(const Vector &inVector) {};
};
}

#endif /* Skel_Vector_h */

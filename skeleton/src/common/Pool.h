#ifndef Skel_Pool_h
#define Skel_Pool_h

#include "../Extension.h"
#include "common/Vector.h"
#include "utils/ContainerUtil.h"
#include "common/SkelObject.h"

namespace skel {
template<typename T>
class SK_API Pool : public SkelObject {
public:
	Pool() {
	}

	~Pool() {
		ContainerUtil::cleanUpVectorOfPointers(_objects);
	}

	T *obtain() {
		if (_objects.size() > 0) {
			T **object = &_objects[_objects.size() - 1];
			T *ret = *object;
			_objects.removeAt(_objects.size() - 1);

			return ret;
		} else {
			T *ret = new(__FILE__, __LINE__) T();

			return ret;
		}
	}

	void free(T *object) {
		if (!_objects.contains(object)) {
			_objects.add(object);
		}
	}

private:
	Vector<T *> _objects;
};
}

#endif /* Skel_Pool_h */

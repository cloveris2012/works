#ifndef Skel_LinkedMesh_h
#define Skel_LinkedMesh_h

#include "common/SkelObject.h"
#include "common/SkelString.h"

namespace skel {
class MeshAttachment;

class SK_API LinkedMesh : public SkelObject {
	friend class SkeletonBinary;

	friend class SkeletonJson;

public:
	LinkedMesh(MeshAttachment *mesh, const String &skin, size_t slotIndex, const String &parent, bool inheritDeform);

private:
	MeshAttachment *_mesh;
	String _skin;
	size_t _slotIndex;
	String _parent;
	bool _inheritDeform;
};
}

#endif /* Skel_LinkedMesh_h */

#include "LinkedMesh.h"

#include "MeshAttachment.h"

using namespace skel;

LinkedMesh::LinkedMesh(MeshAttachment *mesh, const String &skin, size_t slotIndex, const String &parent, bool inheritDeform) :
		_mesh(mesh),
		_skin(skin),
		_slotIndex(slotIndex),
		_parent(parent),
		_inheritDeform(inheritDeform) {
}

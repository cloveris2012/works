#include "BoundingBoxAttachment.h"

using namespace skel;

RTTI_IMPL(BoundingBoxAttachment, VertexAttachment)

BoundingBoxAttachment::BoundingBoxAttachment(const String &name) : VertexAttachment(name) {
}

Attachment* BoundingBoxAttachment::copy() {
	BoundingBoxAttachment* copy = new (__FILE__, __LINE__) BoundingBoxAttachment(getName());
	copyTo(copy);
	return copy;
}

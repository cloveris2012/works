#include "ClippingAttachment.h"

#include "../../data/SlotData.h"

using namespace skel;

RTTI_IMPL(ClippingAttachment, VertexAttachment)

ClippingAttachment::ClippingAttachment(const String &name) : VertexAttachment(name), _endSlot(NULL) {
}

SlotData *ClippingAttachment::getEndSlot() {
	return _endSlot;
}

void ClippingAttachment::setEndSlot(SlotData *inValue) {
	_endSlot = inValue;
}

Attachment* ClippingAttachment::copy() {
	ClippingAttachment* copy = new (__FILE__, __LINE__) ClippingAttachment(getName());
	copyTo(copy);
	copy->_endSlot = _endSlot;
	return copy;
}

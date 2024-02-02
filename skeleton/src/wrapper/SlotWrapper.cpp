#include "SlotWrapper.h"
#include <iostream>
using namespace skel;

SlotWrapper::SlotWrapper(SlotData &data,  Bone &bone) : Slot(data, bone) {

}


void SlotWrapper::clearAttachment() {
	setAttachment(nullptr);
	getData().setAttachmentName("");
}

std::string SlotWrapper::getAttachmentName() {
	auto attachment = getAttachment();
	if (attachment != nullptr) {
		return attachment->getName().buffer();
	}
	return "";
}
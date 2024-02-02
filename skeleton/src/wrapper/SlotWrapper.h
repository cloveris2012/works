#pragma once

#include "common/skel.h"

class SlotWrapper : public skel::Slot {
public:
	SlotWrapper(skel::SlotData &data, skel::Bone &bone);
	void clearAttachment();
	//static SlotWrapper *create(SkeletonWrapper *skeleton);
	std::string getAttachmentName();
};


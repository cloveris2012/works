#ifndef SLOT_DATA_WRAPPER_H
#define SLOT_DATA_WRAPPER_H

#include "data/SlotData.h"
#include "common/skel.h"
#include "common/SkelString.h"
#include "BoneDataWrapper.h"
using namespace skel;

class SlotDataWrapper : public SlotData {
public:
	SlotDataWrapper(int index, const String &name, BoneData &boneData);

	std::string getSlotName();
	void setSlotName(const char * name);
	BoneDataWrapper * getBoneDataWrapper();
	std::string getAttachmentNameWrapper();
	void setAttachmentNameWrapper(const char * name);
};

#endif
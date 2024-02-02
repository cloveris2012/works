#include "SlotDataWrapper.h"
#include <iostream>
using namespace skel;

SlotDataWrapper::SlotDataWrapper(int index, const String &name, BoneData &boneData) : SlotData(index, name, boneData) {

}

std::string SlotDataWrapper::getSlotName()
{
	std::string name = getName().buffer();//ֱ不能直接返回
	return name;
}

void SlotDataWrapper::setSlotName(const char* name) {
	skel::String str(name);
	_name = str;
}

BoneDataWrapper * SlotDataWrapper::getBoneDataWrapper(){
	auto data = &getBoneData(); 
	return dynamic_cast<BoneDataWrapper*>(data);
}

std::string SlotDataWrapper::getAttachmentNameWrapper()
{
	auto aname = getAttachmentName();
	if (aname.isEmpty()) return "";

	std::string name = aname.buffer();
	return name;
}

void SlotDataWrapper::setAttachmentNameWrapper(const char* name) {
	skel::String str(name);
	setAttachmentName(str);
}

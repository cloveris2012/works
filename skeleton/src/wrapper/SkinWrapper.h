#pragma once

#include "common/skel.h"
#include "RegionAttachmentWrapper.h"
#include "MeshAttachmentWrapper.h"

//#include "LuaIntf/LuaIntf.h"
class SkinWrapper : public skel::Skin {
public:
	SkinWrapper(const skel::String &name);
	//static SlotWrapper *create(SkeletonWrapper *skeleton);
	std::string getSkinName();
	LuaIntf::LuaRef getAttachmentWrappers(lua_State* L);
	void addAttachmentWrapper(int slotIndex, const char * name, skel::Attachment *atta);
	void removeAttachmentWrapper(int slotIndex, const char * name);
	void addSlot(int slotIndex);
	void removeSlot(int slotIndex);
	void copySkin(SkinWrapper *skin);
	void addSkin(SkinWrapper *skin);
};
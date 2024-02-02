#pragma once

#include "common/skel.h"
#include "LuaIntf/LuaIntf.h"
#include "BoneWrapper.h"

class RegionAttachmentWrapper : public skel::RegionAttachment {
public:
	RegionAttachmentWrapper(const skel::String &name);

	std::string getTag();
	std::string getName2();
	LuaIntf::LuaRef computeWorldVerticesWrapper(lua_State* L, BoneWrapper bone);
	LuaIntf::LuaRef getUVsWrapper(lua_State* L);
	LuaIntf::LuaRef getOffsetWrapper(lua_State* L);

	void setPath(std::string path);
	std::string getPath();
private:
	std::string _tag;
};

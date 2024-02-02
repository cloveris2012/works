#pragma once
#include "SlotWrapper.h"
#include "common/skel.h"

class MeshAttachmentWrapper : public skel::MeshAttachment {
public:
	MeshAttachmentWrapper(const skel::String &name);

	std::string getTag();
	std::string getName2();
	LuaIntf::LuaRef computeWorldVerticesWrapper(lua_State* L, SlotWrapper slot);
	//LuaIntf::LuaRef getUVsWrapper(lua_State* L);
	//LuaIntf::LuaRef getTrianglesWrapper(lua_State* L);
	//LuaIntf::LuaRef getEdgesWrapper(lua_State* L);

	LuaIntf::LuaRef verticesGetter(lua_State* L);
	void verticesSetter(LuaIntf::LuaRef vectices);

	LuaIntf::LuaRef trianglesGetter(lua_State* L);
	void trianglesSetter(LuaIntf::LuaRef triangles);

	LuaIntf::LuaRef uvsGetter(lua_State* L);
	void uvsSetter(LuaIntf::LuaRef uvs);

	LuaIntf::LuaRef edgesGetter(lua_State* L);
	void edgesSetter(LuaIntf::LuaRef uvs);

	LuaIntf::LuaRef regionUVsGetter(lua_State* L);
	void regionUVsSetter(LuaIntf::LuaRef uvs);

	LuaIntf::LuaRef bonesGetter(lua_State* L);

	void bonesSetter(LuaIntf::LuaRef uvs);

	void setPath(std::string path);
	std::string getPath();

private:
	std::string _tag;
};


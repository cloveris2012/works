#include "RegionAttachmentWrapper.h"

using namespace skel;

RegionAttachmentWrapper::RegionAttachmentWrapper(const String &name) : RegionAttachment(name) {
	_tag = "region";
}

std::string RegionAttachmentWrapper::getTag()
{	
	return _tag;
}

std::string RegionAttachmentWrapper::getName2() {
	std::string name = getName().buffer();
	return name;
}

LuaIntf::LuaRef RegionAttachmentWrapper::computeWorldVerticesWrapper(lua_State* L, BoneWrapper bone) {
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef vertices(L, -1);
	LS.pop();

	Vector<float> worldVertices;
	worldVertices.setSize(8, 8);
	computeWorldVertices(bone, worldVertices, 0);

	size_t index = 0;
	while (index < worldVertices.size())
	{
		vertices.set<int, float>(index + 1, worldVertices[index]);
		index++;
	}

	return vertices;
}

LuaIntf::LuaRef RegionAttachmentWrapper::getUVsWrapper(lua_State* L)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef uvs(L, -1);
	LS.pop();

	size_t index = 0;
	auto uvsVec = getUVs();
	while (index < uvsVec.size())
	{
		uvs.set<int, float>(index + 1, uvsVec[index]);
		index++;
	}
	return uvs;
}

LuaIntf::LuaRef RegionAttachmentWrapper::getOffsetWrapper(lua_State* L)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef offset(L, -1);
	LS.pop();

	size_t index = 0;
	auto offsetVec = getOffset();
	while (index < offsetVec.size())
	{
		offset.set<int, float>(index + 1, offsetVec[index]);
		index++;
	}
	return offset;
}

void RegionAttachmentWrapper::setPath(std::string path) {
	RegionAttachment::setPath(path.c_str());
}

std::string RegionAttachmentWrapper::getPath() {
	return RegionAttachment::getPath().buffer();
}

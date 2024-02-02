#include "BoneWrapper.h"
#include "utils/LuaEx.h"
#include <iostream>
using namespace skel;

BoneWrapper::BoneWrapper(BoneData &data, Skeleton &skeleton, Bone *parent) : Bone(data, skeleton, parent) {

}


void BoneWrapper::updateWorldTransformWrpper() {
	updateWorldTransform();
}

void BoneWrapper::updateWorldTransformWith(float x, float y, float rotation, float scaleX, float scaleY, float shearX, float shearY) {
	updateWorldTransform( x,  y, rotation,  scaleX, scaleY, shearX,shearY);
}

LuaIntf::LuaRef BoneWrapper::worldToLocalWrapper(lua_State* L, float x, float y)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();
	float dx, dy;
	worldToLocal(x, y, dx, dy);
	ref.set<int, float>(1, dx);
	ref.set<int, float>(2, dy);
	return ref;
}

LuaIntf::LuaRef BoneWrapper::localToWorldWrapper(lua_State* L, float x, float y)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();
	float dx, dy;
	localToWorld(x, y, dx, dy);
	ref.set<int, float>(1, dx);
	ref.set<int, float>(2, dy);
	return ref;
}

void BoneWrapper::add(BoneWrapper * bone)
{
	bone->_parent = this;
	bone->_data.setParent(&_data);
}

void BoneWrapper::remove(BoneWrapper * bone)
{
	bone->_parent = nullptr;
	bone->_data.setParent(nullptr);
}


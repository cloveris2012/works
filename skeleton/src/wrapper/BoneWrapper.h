#pragma once

//#include "SkeletonWrapper.h"
#include "common/skel.h"
#include "LuaIntf/LuaIntf.h"

class BoneWrapper : public skel::Bone {
public:
	BoneWrapper(skel::BoneData &data, skel::Skeleton &skeleton, skel::Bone *parent);

	void updateWorldTransformWrpper();

	void updateWorldTransformWith(float x, float y, float rotation, float scaleX, float scaleY, float shearX, float shearY);

	LuaIntf::LuaRef worldToLocalWrapper(lua_State* L, float x,float y);

	LuaIntf::LuaRef localToWorldWrapper(lua_State* L, float x, float y);

	void add(BoneWrapper *bone);
	void remove(BoneWrapper * bone);
};
#pragma once

#include "common/skel.h"
#include "common/SkelString.h"
#include "LuaIntf/LuaIntf.h"
#include "wrapper/data/SkeletonDataWrapper.h"

class EventTimelineWrapper : public skel::EventTimeline {
public:
	EventTimelineWrapper(int frameCount);
	LuaIntf::LuaRef getFrameData(lua_State* L, size_t frameIndex);
	void setToSetupPose(LuaIntf::LuaRef &data, SkeletonDataWrapper *skeletonData);
};

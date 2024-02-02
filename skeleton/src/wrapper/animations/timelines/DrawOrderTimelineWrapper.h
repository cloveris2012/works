#pragma once

#include "common/skel.h"
#include "wrapper/data/CurveDataWrapper.h"
#include "wrapper/data/SkeletonDataWrapper.h"
#include "LuaIntf/LuaIntf.h"
#include "common/Vector.h"

using skel::Vector;

class DrawOrderTimelineWrapper : public skel::DrawOrderTimeline {
public:
	DrawOrderTimelineWrapper(int frameCount);

	LuaIntf::LuaRef getFrameData(lua_State* L, size_t frameIndex);

	Vector<Vector<int> > &getOrigionalOffsets();
	Vector<Vector<std::string> > &getOrigionalSlotNames();

	void setToSetupPose(LuaIntf::LuaRef &data, SkeletonDataWrapper *skeletonData);
private:
	Vector< Vector<int> > _origionalOffsets;
	Vector< Vector<std::string> > _origionalSlotNames;
};

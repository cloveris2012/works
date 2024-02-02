#pragma once

#include "common/skel.h"
#include "common/SkelString.h"
#include "wrapper/data/CurveDataWrapper.h"
#include "LuaIntf/LuaIntf.h"

class IkConstraintTimelineWrapper : public skel::IkConstraintTimeline {
public:
	IkConstraintTimelineWrapper(int frameCount);

	int getIkConstraintIndex();
	void setIkConstraintIndex(int index);

	void setStepped(size_t frameIndex) override;
	void setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) override;

	size_t getFrameCount();

	LuaIntf::LuaRef getFrameData(lua_State* L, size_t frameIndex);
private:
	CurveDataWrapper data;
};

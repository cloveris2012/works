#pragma once

#include "common/skel.h"
#include "common/SkelString.h"
#include "wrapper/data/CurveDataWrapper.h"
#include "LuaIntf/LuaIntf.h"

class ColorTimelineWrapper : public skel::ColorTimeline {
public:
	ColorTimelineWrapper(int frameCount);
	void setStepped(size_t frameIndex) override;
	void setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) override;

	size_t getFrameCount();

	LuaIntf::LuaRef getFrameData(lua_State* L, size_t frameIndex);

	int getSlotIndex();
	void setSlotIndex(int index);

	void setToSetupPose(LuaIntf::LuaRef &data);
private:
	CurveDataWrapper data;
};

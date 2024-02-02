#pragma once

#include "common/skel.h"
#include "wrapper/data/CurveDataWrapper.h"
#include "LuaIntf/LuaIntf.h"
#include "common/Vector.h"

class DeformTimelineWrapper : public skel::DeformTimeline {
public:
	DeformTimelineWrapper(int frameCount);
	skel::Vector< skel::Vector<float> >& getOrigionalVertices();
	skel::Vector<int> &getOrigionalOffsets();

	void setStepped(size_t frameIndex) override;
	void setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) override;

	size_t getFrameCount();

	LuaIntf::LuaRef getFrameData(lua_State* L, size_t frameIndex);

	int getSlotIndex();
	void setSlotIndex(int index);

	std::string getAttachmentName();

	void setToSetupPose(LuaIntf::LuaRef &data);
private:
	CurveDataWrapper data;
	skel::Vector< skel::Vector<float> > _origionalVertices;
	skel::Vector<int> _origionalOffsets;
};

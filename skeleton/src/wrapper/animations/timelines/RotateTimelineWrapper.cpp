#include "RotateTimelineWrapper.h"
#include <iostream>
using namespace skel;

RotateTimelineWrapper::RotateTimelineWrapper(int frameCount) : RotateTimeline(frameCount) {

}

void RotateTimelineWrapper::setStepped(size_t frameIndex) {
	data.setStepped(frameIndex);
	RotateTimeline::setStepped(frameIndex);
}

void RotateTimelineWrapper::setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) {
	data.setCurve(frameIndex, cx1, cy1, cx2, cy2);
	RotateTimeline::setCurve(frameIndex, cx1, cy1, cx2, cy2);
}

size_t RotateTimelineWrapper::getFrameCount() {
	return getFrames().size() / ENTRIES;
}

LuaIntf::LuaRef RotateTimelineWrapper::getFrameData(lua_State* L, size_t frameIndex)
{

	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();

	data.fillCurveData(frameIndex, ref);

	size_t index = frameIndex * ENTRIES;
	auto &frames = getFrames();
	ref.set<std::string, float>("time", frames[index]);
	ref.set<std::string, float>("angle", frames[index + ROTATION]);

	return ref;
}

void RotateTimelineWrapper::setToSetupPose(LuaIntf::LuaRef &data) {
	int frameCount = data.len();

	_frames.ensureCapacity(frameCount * ENTRIES);
	_frames.setSize(frameCount * ENTRIES, 0);
	resetCurves(frameCount);

	size_t frameIndex = 0;
	for (auto beg = data.begin(), end = data.end(); beg != end; ++beg, ++frameIndex) {
		float timelineScale = 1;

		setFrame(frameIndex, beg.value().get("time").toValue<float>(),
			beg.value().get("angle").toValue<float>() * timelineScale);
		this->data.readCurveData(beg, this, frameIndex);
	}
}

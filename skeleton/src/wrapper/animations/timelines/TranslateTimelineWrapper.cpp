#include "TranslateTimelineWrapper.h"
#include <iostream>
using namespace skel;

TranslateTimelineWrapper::TranslateTimelineWrapper(int frameCount) : TranslateTimeline(frameCount) {

}

void TranslateTimelineWrapper::setStepped(size_t frameIndex) {
	data.setStepped(frameIndex);
	TranslateTimeline::setStepped(frameIndex);
}

void TranslateTimelineWrapper::setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) {
	data.setCurve(frameIndex, cx1, cy1, cx2, cy2);
	TranslateTimeline::setCurve(frameIndex, cx1, cy1, cx2, cy2);
}

size_t TranslateTimelineWrapper::getFrameCount() {
	return _frames.size() / ENTRIES;
}

LuaIntf::LuaRef TranslateTimelineWrapper::getFrameData(lua_State* L, size_t frameIndex)
{

	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();

	data.fillCurveData(frameIndex, ref);

	size_t index = frameIndex * ENTRIES;
	ref.set<std::string, float>("time", _frames[index]);
	ref.set<std::string, float>("x", _frames[index + X]);
	ref.set<std::string, float>("y", _frames[index + Y]);

	return ref;
}

int TranslateTimelineWrapper::getBoneIndex() {
	return _boneIndex;
}

void TranslateTimelineWrapper::setBoneIndex(int index) {
	_boneIndex = index;
}

void TranslateTimelineWrapper::setToSetupPose(LuaIntf::LuaRef &data) {
	int frameCount = data.len();

	_frames.ensureCapacity(frameCount * ENTRIES);
	_frames.setSize(frameCount * ENTRIES, 0);
	resetCurves(frameCount);

	size_t frameIndex = 0;
	for(auto beg = data.begin(), end = data.end(); beg != end; ++ beg, ++ frameIndex) {
		float timelineScale = 1;

		setFrame(frameIndex, beg.value().get("time").toValue<float>(),
			beg.value().get("x").toValue<float>() * timelineScale,
			beg.value().get("y").toValue<float>() * timelineScale);
		this->data.readCurveData(beg, this, frameIndex);
	}
}

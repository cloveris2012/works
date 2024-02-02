#include "TwoColorTimelineWrapper.h"
#include <iostream>
using namespace skel;

TwoColorTimelineWrapper::TwoColorTimelineWrapper(int frameCount) : TwoColorTimeline(frameCount) {

}

void TwoColorTimelineWrapper::setStepped(size_t frameIndex) {
	data.setStepped(frameIndex);
	TwoColorTimeline::setStepped(frameIndex);
}

void TwoColorTimelineWrapper::setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) {
	data.setCurve(frameIndex, cx1, cy1, cx2, cy2);
	TwoColorTimeline::setCurve(frameIndex, cx1, cy1, cx2, cy2);
}

size_t TwoColorTimelineWrapper::getFrameCount() {
	return _frames.size() / ENTRIES;
}

LuaIntf::LuaRef TwoColorTimelineWrapper::getFrameData(lua_State* L, size_t frameIndex)
{

	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();

	data.fillCurveData(frameIndex, ref);

	size_t index = frameIndex * ENTRIES;
	ref.set<std::string, float>("time", _frames[index]);
	ref.set<std::string, float>("r", _frames[index + R]);
	ref.set<std::string, float>("g", _frames[index + G]);
	ref.set<std::string, float>("b", _frames[index + B]);
	ref.set<std::string, float>("a", _frames[index + A]);

	ref.set<std::string, float>("r2", _frames[index + R2]);
	ref.set<std::string, float>("g2", _frames[index + G2]);
	ref.set<std::string, float>("b2", _frames[index + B2]);

	return ref;
}

int TwoColorTimelineWrapper::getSlotIndex() {
	return _slotIndex;
}

void TwoColorTimelineWrapper::setSlotIndex(int index) {
	_slotIndex = index;
}
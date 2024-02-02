#include "IkConstraintTimelineWrapper.h"
#include <iostream>
using namespace skel;

IkConstraintTimelineWrapper::IkConstraintTimelineWrapper(int frameCount) : IkConstraintTimeline(frameCount) {

}

int IkConstraintTimelineWrapper::getIkConstraintIndex() {
	return _ikConstraintIndex;
}

void IkConstraintTimelineWrapper::setIkConstraintIndex(int index) {
	_ikConstraintIndex = index;
}

void IkConstraintTimelineWrapper::setStepped(size_t frameIndex) {
	data.setStepped(frameIndex);
	IkConstraintTimeline::setStepped(frameIndex);
}

void IkConstraintTimelineWrapper::setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) {
	data.setCurve(frameIndex, cx1, cy1, cx2, cy2);
	IkConstraintTimeline::setCurve(frameIndex, cx1, cy1, cx2, cy2);
}

size_t IkConstraintTimelineWrapper::getFrameCount() {
	return _frames.size() / ENTRIES;
}

LuaIntf::LuaRef IkConstraintTimelineWrapper::getFrameData(lua_State* L, size_t frameIndex)
{

	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();

	data.fillCurveData(frameIndex, ref);

	size_t index = frameIndex * ENTRIES;
	ref.set<std::string, float>("time", _frames[index]);
	ref.set<std::string, float>("mix", _frames[index + MIX]);
	ref.set<std::string, float>("softness", _frames[index + SOFTNESS]);
	ref.set<std::string, float>("bendPositive", _frames[index + BEND_DIRECTION]);
	ref.set<std::string, bool>("compress", _frames[index + COMPRESS]);
	ref.set<std::string, bool>("stretch", _frames[index + STRETCH]);

	return ref;
}

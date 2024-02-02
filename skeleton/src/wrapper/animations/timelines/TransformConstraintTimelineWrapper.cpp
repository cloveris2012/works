#include "TransformConstraintTimelineWrapper.h"
#include <iostream>
using namespace skel;

TransformConstraintTimelineWrapper::TransformConstraintTimelineWrapper(int frameCount) : TransformConstraintTimeline(frameCount) {

}

int TransformConstraintTimelineWrapper::getTransformConstraintIndex() {
	return _transformConstraintIndex;
}

void TransformConstraintTimelineWrapper::setTransformConstraintIndex(int index) {
	_transformConstraintIndex = index;
}

void TransformConstraintTimelineWrapper::setStepped(size_t frameIndex) {
	data.setStepped(frameIndex);
	TransformConstraintTimeline::setStepped(frameIndex);
}

void TransformConstraintTimelineWrapper::setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) {
	data.setCurve(frameIndex, cx1, cy1, cx2, cy2);
	TransformConstraintTimeline::setCurve(frameIndex, cx1, cy1, cx2, cy2);
}

size_t TransformConstraintTimelineWrapper::getFrameCount() {
	return _frames.size() / ENTRIES;
}

LuaIntf::LuaRef TransformConstraintTimelineWrapper::getFrameData(lua_State* L, size_t frameIndex)
{

	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();

	data.fillCurveData(frameIndex, ref);

	size_t index = frameIndex * ENTRIES;
	ref.set<std::string, float>("time", _frames[index]);
	ref.set<std::string, float>("rotateMix", _frames[index + ROTATE]);
	ref.set<std::string, float>("translateMix", _frames[index + TRANSLATE]);
	ref.set<std::string, float>("scaleMix", _frames[index + SCALE]);
	ref.set<std::string, float>("shearMix", _frames[index + SHEAR]);
	return ref;
}

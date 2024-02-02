#include "ColorTimelineWrapper.h"
#include "common/Color.h"
#include <iostream>
using namespace skel;

ColorTimelineWrapper::ColorTimelineWrapper(int frameCount) : ColorTimeline(frameCount) {

}

void ColorTimelineWrapper::setStepped(size_t frameIndex) {
	data.setStepped(frameIndex);
	ColorTimeline::setStepped(frameIndex);
}

void ColorTimelineWrapper::setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) {
	data.setCurve(frameIndex, cx1, cy1, cx2, cy2);
	ColorTimeline::setCurve(frameIndex, cx1, cy1, cx2, cy2);
}

size_t ColorTimelineWrapper::getFrameCount() {
	return getFrames().size() / ENTRIES;
}

LuaIntf::LuaRef ColorTimelineWrapper::getFrameData(lua_State* L, size_t frameIndex)
{

	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();

	data.fillCurveData(frameIndex, ref);

	size_t index = frameIndex * ENTRIES;
	auto &frames = getFrames();
	ref.set<std::string, float>("time", frames[index]);
	ref.set<std::string, float>("r", frames[index + R]);
	ref.set<std::string, float>("g", frames[index + G]);
	ref.set<std::string, float>("b", frames[index + B]);
	ref.set<std::string, float>("a", frames[index + A]);

	return ref;
}

int ColorTimelineWrapper::getSlotIndex() {
	return _slotIndex;
}

void ColorTimelineWrapper::setSlotIndex(int index) {
	_slotIndex = index;
}

void ColorTimelineWrapper::setToSetupPose(LuaIntf::LuaRef &data) {
	int frameCount = data.len();

	_frames.ensureCapacity(frameCount * ENTRIES);
	_frames.setSize(frameCount * ENTRIES, 0);
	resetCurves(frameCount);

	size_t frameIndex = 0;
	for (auto beg = data.begin(), end = data.end(); beg != end; ++beg, ++frameIndex) {
		auto color = beg.value().get("color").toValue<std::string>();
		setFrame(frameIndex, beg.value().get("time").toValue<float>(),
			Color::toColor(color.c_str(), 0), Color::toColor(color.c_str(), 1), Color::toColor(color.c_str(), 2), Color::toColor(color.c_str(), 3));
		this->data.readCurveData(beg, this, frameIndex);
	}
}
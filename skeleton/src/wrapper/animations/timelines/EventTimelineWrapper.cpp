#include "EventTimelineWrapper.h"
#include "utils/SkeletonWrapperCreator.h"
#include <iostream>
using namespace skel;

EventTimelineWrapper::EventTimelineWrapper(int frameCount) : EventTimeline(frameCount) {

}

LuaIntf::LuaRef EventTimelineWrapper::getFrameData(lua_State* L, size_t frameIndex)
{

	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();

	auto &frames = getFrames();
	auto &events = getEvents();
	ref.set<std::string, float>("time", frames[frameIndex]);
	ref.set<std::string, std::string>("name", events[frameIndex]->getData().getName().buffer());

	return ref;
}

void EventTimelineWrapper::setToSetupPose(LuaIntf::LuaRef &data, SkeletonDataWrapper *skeletonData) {
	int frameCount = data.len();

	_frames.setSize(frameCount, 0);
	_events.setSize(frameCount, NULL);

	size_t frameIndex = 0;
	for (auto beg = data.begin(), end = data.end(); beg != end; ++beg, ++frameIndex) {
		Event *event;
		auto name = beg.value().get("name").toValue<std::string>();
		EventData *eventData = skeletonData->findEvent(name.c_str());
		if (!eventData) {
			return;
		}
		SkeletonWrapperCreator creator;
		event = creator.createEvent(beg.value().get("time").toValue<float>(), *eventData);
		
		event->setIntValue(beg.value().has("int") ? beg.value().get("int").toValue<int>() : eventData->getIntValue());
		event->setFloatValue(beg.value().has("float") ? beg.value().get("float").toValue<float>() : eventData->getFloatValue());
		event->setStringValue(beg.value().has("string") ? beg.value().get("string").toValue<std::string>().c_str() : eventData->getStringValue().buffer());
		if (!eventData->getAudioPath().isEmpty()) {
			event->setVolume(beg.value().has("volume") ? beg.value().get("volume").toValue<float>() : 1);
			event->setBalance(beg.value().has("balance") ? beg.value().get("balance").toValue<float>() : 1);
		}
		setFrame(frameIndex, event);
	}
}

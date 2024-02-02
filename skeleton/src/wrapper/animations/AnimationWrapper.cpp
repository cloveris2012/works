#include "AnimationWrapper.h"
#include <iostream>
using namespace skel;

AnimationWrapper::AnimationWrapper(const String &name, Vector<Timeline *> &timelines, float duration) : Animation(name, timelines, duration) {

}

void AnimationWrapper::setName(const char *name) {
	_name = name;
}

const char *AnimationWrapper::getName() {
	return _name.buffer();
}

size_t AnimationWrapper::getTimelineCount() {
	return _timelines.size();
}

std::string AnimationWrapper::getTimelineClassName(size_t index) {
	std::string name = typeid(*_timelines[index]).name();
	return name.substr(strlen("class "), name.size() - strlen("class ") - strlen("Wrapper"));
}

void AnimationWrapper::addTimeline(Timeline *timeline, int index) {
	_timelines.addAt(timeline, index);
	_timelineIds.put(timeline->getPropertyId(), true);
	// 仅添加了一个空的timeline，无需更新duration
}

void AnimationWrapper::removeTimeline(Timeline *timeline) {
	_timelines.removeAt(_timelines.indexOf(timeline));
	_timelineIds.put(timeline->getPropertyId(), false);
}

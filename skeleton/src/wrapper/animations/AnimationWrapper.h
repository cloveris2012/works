#pragma once

#include "common/skel.h"
#include "common/SkelString.h"
#include "common/Vector.h"

class AnimationWrapper : public skel::Animation {
public:
	AnimationWrapper(const skel::String &name, skel::Vector<skel::Timeline *> &timelines, float duration);
	void setName(const char *name);
	const char *getName();

	size_t getTimelineCount();

	template <typename T>
	T *getTimeline(size_t index) {
		return dynamic_cast<T*>(_timelines[index]);
	}
	std::string getTimelineClassName(size_t index);

	void addTimeline(skel::Timeline *timeline, int index);
	void removeTimeline(skel::Timeline *timeline);
};


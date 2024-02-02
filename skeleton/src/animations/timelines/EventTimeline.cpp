#include "EventTimeline.h"

#include "../../Skeleton.h"
#include "../../entities/Event.h"

#include "../Animation.h"
#include "../../config/TimelineType.h"
#include "../../entities/Slot.h"
#include "../../data/SlotData.h"
#include "../../data/EventData.h"
#include "../../utils/ContainerUtil.h"

#include <float.h>

using namespace skel;

RTTI_IMPL(EventTimeline, Timeline)

EventTimeline::EventTimeline(int frameCount) : Timeline() {
	_frames.setSize(frameCount, 0);
	_events.setSize(frameCount, NULL);
}

EventTimeline::~EventTimeline() {
	ContainerUtil::cleanUpVectorOfPointers(_events);
}

void EventTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
	MixBlend blend, MixDirection direction
) {
	if (pEvents == NULL) return;

	Vector<Event *> &events = *pEvents;

	size_t frameCount = _frames.size();

	if (lastTime > time) {
		// Fire events after last time for looped animations.
		apply(skeleton, lastTime, FLT_MAX, pEvents, alpha, blend, direction);
		lastTime = -1.0f;
	} else if (lastTime >= _frames[frameCount - 1]) {
		// Last time is after last frame.
		return;
	}

	if (time < _frames[0]) return; // Time is before first frame.

	int frame;
	if (lastTime < _frames[0]) {
		frame = 0;
	} else {
		frame = Animation::binarySearch(_frames, lastTime);
		float frameTime = _frames[frame];
		while (frame > 0) {
			// Fire multiple events with the same frame.
			if (_frames[frame - 1] != frameTime) break;
			frame--;
		}
	}

	for (; (size_t)frame < frameCount && time >= _frames[frame]; ++frame)
		events.add(_events[frame]);
}

int EventTimeline::getPropertyId() {
	return ((int) TimelineType_Event << 24);
}

void EventTimeline::setFrame(size_t frameIndex, Event *event) {
	_frames[frameIndex] = event->getTime();
	_events[frameIndex] = event;
}

Vector<float> &EventTimeline::getFrames() { return _frames; }

Vector<Event *> &EventTimeline::getEvents() { return _events; }

size_t EventTimeline::getFrameCount() { return _frames.size(); }

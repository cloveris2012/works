#ifndef Skel_EventTimeline_h
#define Skel_EventTimeline_h

#include "Timeline.h"

namespace skel {
	class SK_API EventTimeline : public Timeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		explicit EventTimeline(int frameCount);

		~EventTimeline();

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();

		/// Sets the time and value of the specified keyframe.
		void setFrame(size_t frameIndex, Event* event);

		Vector<float>& getFrames();
		Vector<Event*>& getEvents();
		size_t getFrameCount();

	protected:
		Vector<float> _frames;
		Vector<Event*> _events;
	};
}

#endif /* Skel_EventTimeline_h */

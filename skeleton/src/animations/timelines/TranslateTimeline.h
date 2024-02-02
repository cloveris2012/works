#ifndef Skel_TranslateTimeline_h
#define Skel_TranslateTimeline_h

#include "CurveTimeline.h"

#include "animations/Animation.h"
#include "config/TimelineType.h"

namespace skel {

	class SK_API TranslateTimeline : public CurveTimeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		static const int ENTRIES;

		explicit TranslateTimeline(int frameCount);

		virtual ~TranslateTimeline();

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();

		/// Sets the time and value of the specified keyframe.
		void setFrame(int frameIndex, float time, float x, float y);

	protected:
		static const int PREV_TIME;
		static const int PREV_X;
		static const int PREV_Y;
		static const int X;
		static const int Y;

		Vector<float> _frames;
		int _boneIndex;
	};
}

#endif /* Skel_TranslateTimeline_h */

#ifndef Skel_PathConstraintMixTimeline_h
#define Skel_PathConstraintMixTimeline_h

#include "CurveTimeline.h"

namespace skel {
#define SP_PATHCONSTRAINTMIXTIMELINE_ENTRIES 5

	class SK_API PathConstraintMixTimeline : public CurveTimeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		static const int ENTRIES;

		explicit PathConstraintMixTimeline(int frameCount);

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();

	private:
		static const int PREV_TIME;
		static const int PREV_ROTATE;
		static const int PREV_TRANSLATE;
		static const int ROTATE;
		static const int TRANSLATE;

		Vector<float> _frames;
		int _pathConstraintIndex;

		/// Sets the time and mixes of the specified keyframe.
		void setFrame(int frameIndex, float time, float rotateMix, float translateMix);
	};
}

#endif /* Skel_PathConstraintMixTimeline_h */

#ifndef Skel_PathConstraintSpacingTimeline_h
#define Skel_PathConstraintSpacingTimeline_h

#include "PathConstraintPositionTimeline.h"

namespace skel {
	class SK_API PathConstraintSpacingTimeline : public PathConstraintPositionTimeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		explicit PathConstraintSpacingTimeline(int frameCount);

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();
	};
}

#endif /* Skel_PathConstraintSpacingTimeline_h */

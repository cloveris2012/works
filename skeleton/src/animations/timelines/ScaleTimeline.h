#ifndef Skel_ScaleTimeline_h
#define Skel_ScaleTimeline_h

#include "TranslateTimeline.h"

namespace skel {
	class SK_API ScaleTimeline : public TranslateTimeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		explicit ScaleTimeline(int frameCount);

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();
	};
}

#endif /* Skel_ScaleTimeline_h */

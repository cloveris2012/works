#ifndef Skel_ShearTimeline_h
#define Skel_ShearTimeline_h

#include "TranslateTimeline.h"

namespace skel {
	class SK_API ShearTimeline : public TranslateTimeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		explicit ShearTimeline(int frameCount);

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();
	};
}

#endif /* Skel_ShearTimeline_h */

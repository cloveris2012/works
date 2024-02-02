#ifndef Skel_RotateTimeline_h
#define Skel_RotateTimeline_h

#include "CurveTimeline.h"

namespace skel {
	class SK_API RotateTimeline : public CurveTimeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;
		friend class AnimationState;

		RTTI_DECL

	public:
		static const int ENTRIES = 2;

		explicit RotateTimeline(int frameCount);

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();

		/// Sets the time and value of the specified keyframe.
		void setFrame(int frameIndex, float time, float degrees);

		int getBoneIndex();
		void setBoneIndex(int inValue);

		Vector<float>& getFrames();

	protected:
		static const int PREV_TIME = -2;
		static const int PREV_ROTATION = -1;
		static const int ROTATION = 1;

		int _boneIndex;
		Vector<float> _frames; // time, angle, ...
	};
}

#endif /* Skel_RotateTimeline_h */

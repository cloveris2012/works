#ifndef Skel_TwoColorTimeline_h
#define Skel_TwoColorTimeline_h

#include "CurveTimeline.h"

namespace skel {

	class SK_API TwoColorTimeline : public CurveTimeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		static const int ENTRIES;

		explicit TwoColorTimeline(int frameCount);

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();

		/// Sets the time and value of the specified keyframe.
		void setFrame(int frameIndex, float time, float r, float g, float b, float a, float r2, float g2, float b2);

		int getSlotIndex();
		void setSlotIndex(int inValue);

	protected:
		static const int PREV_TIME;
		static const int PREV_R;
		static const int PREV_G;
		static const int PREV_B;
		static const int PREV_A;
		static const int PREV_R2;
		static const int PREV_G2;
		static const int PREV_B2;
		static const int R;
		static const int G;
		static const int B;
		static const int A;
		static const int R2;
		static const int G2;
		static const int B2;

		Vector<float> _frames; // time, r, g, b, a, r2, g2, b2, ...
		int _slotIndex;
	};
}

#endif /* Skel_TwoColorTimeline_h */

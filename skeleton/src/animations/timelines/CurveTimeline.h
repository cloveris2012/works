#ifndef Skel_CurveTimeline_h
#define Skel_CurveTimeline_h

#include "Timeline.h"
#include "common/Vector.h"

namespace skel {
	/// Base class for frames that use an interpolation bezier curve.
	class SK_API CurveTimeline : public Timeline {
		RTTI_DECL

	public:
		explicit CurveTimeline(int frameCount);

		virtual ~CurveTimeline();

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction) = 0;

		virtual int getPropertyId() = 0;

		void resetCurves(int frameCount);

		size_t getFrameCount();

		void setLinear(size_t frameIndex);

		virtual void setStepped(size_t frameIndex);

		/// Sets the control handle positions for an interpolation bezier curve used to transition from this keyframe to the next.
		/// cx1 and cx2 are from 0 to 1, representing the percent of time between the two keyframes. cy1 and cy2 are the percent of
		/// the difference between the keyframe's values.
		virtual void setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2);

		float getCurvePercent(size_t frameIndex, float percent);

		float getCurveType(size_t frameIndex);

	protected:
		static const float LINEAR;
		static const float STEPPED;
		static const float BEZIER;
		static const int BEZIER_SIZE;

	private:
		Vector<float> _curves; // type, x, y, ...
	};
}

#endif /* Skel_CurveTimeline_h */

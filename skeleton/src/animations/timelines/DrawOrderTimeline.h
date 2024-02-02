#ifndef Skel_DrawOrderTimeline_h
#define Skel_DrawOrderTimeline_h

#include "Timeline.h"

namespace skel {
	class SK_API DrawOrderTimeline : public Timeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		explicit DrawOrderTimeline(int frameCount);

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();

		/// Sets the time and value of the specified keyframe.
		/// @param drawOrder May be NULL to use bind pose draw order
		void setFrame(size_t frameIndex, float time, Vector<int>& drawOrder);

		Vector<float>& getFrames();
		Vector< Vector<int> >& getDrawOrders();
		size_t getFrameCount();

	protected:
		Vector<float> _frames;
		Vector< Vector<int> > _drawOrders;
	};
}

#endif /* Skel_DrawOrderTimeline_h */

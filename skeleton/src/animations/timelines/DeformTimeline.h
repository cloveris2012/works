#ifndef Skel_DeformTimeline_h
#define Skel_DeformTimeline_h

#include "CurveTimeline.h"

namespace skel {
	class VertexAttachment;

	class SK_API DeformTimeline : public CurveTimeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		explicit DeformTimeline(int frameCount);

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();

		/// Sets the time and value of the specified keyframe.
		void setFrame(int frameIndex, float time, Vector<float>& vertices);

		int getSlotIndex();
		void setSlotIndex(int inValue);
		Vector<float>& getFrames();
		Vector< Vector<float> >& getVertices();
		VertexAttachment* getAttachment();
		void setAttachment(VertexAttachment* inValue);

	protected:
		int _slotIndex;
		Vector<float> _frames;
		Vector< Vector<float> > _frameVertices;
		VertexAttachment* _attachment;
	};
}

#endif /* Skel_DeformTimeline_h */

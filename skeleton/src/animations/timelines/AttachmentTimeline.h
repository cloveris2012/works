#ifndef Skel_AttachmentTimeline_h
#define Skel_AttachmentTimeline_h

#include "Timeline.h"
#include "common/SkelObject.h"
#include "common/Vector.h"
#include "config/MixBlend.h"
#include "config/MixDirection.h"
#include "common/SkelString.h"

namespace skel {

	class Skeleton;
	class Slot;
	class Event;

	class SK_API AttachmentTimeline : public Timeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		explicit AttachmentTimeline(int frameCount);

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();

		/// Sets the time and value of the specified keyframe.
		void setFrame(int frameIndex, float time, const String& attachmentName);

		size_t getSlotIndex();
		void setSlotIndex(size_t inValue);
		Vector<float>& getFrames();
		Vector<String>& getAttachmentNames();
		size_t getFrameCount();
	protected:
		size_t _slotIndex;
		Vector<float> _frames;
		Vector<String> _attachmentNames;

        void setAttachment(Skeleton& skeleton, Slot& slot, String* attachmentName);
    };
}

#endif /* Skel_AttachmentTimeline_h */

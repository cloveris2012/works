#ifndef Skel_ClippingAttachment_h
#define Skel_ClippingAttachment_h

#include "VertexAttachment.h"

namespace skel {
	class SlotData;

	class SK_API ClippingAttachment : public VertexAttachment {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		friend class SkeletonClipping;

		RTTI_DECL

	public:
		explicit ClippingAttachment(const String& name);

		SlotData* getEndSlot();
		void setEndSlot(SlotData* inValue);

		virtual Attachment* copy();

	private:
		SlotData* _endSlot;
	};
}

#endif /* Skel_ClippingAttachment_h */

#ifndef Skel_BoundingBoxAttachment_h
#define Skel_BoundingBoxAttachment_h

#include "VertexAttachment.h"
#include "common/SkelObject.h"

namespace skel {
	/// Attachment that has a polygon for bounds checking.
	class SK_API BoundingBoxAttachment : public VertexAttachment {
		RTTI_DECL

		explicit BoundingBoxAttachment(const String& name);

		virtual Attachment* copy();
	};
}

#endif /* Skel_BoundingBoxAttachment_h */

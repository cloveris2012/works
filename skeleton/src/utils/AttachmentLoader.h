#ifndef Skel_AttachmentLoader_h
#define Skel_AttachmentLoader_h

#include "common/RTTI.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"

namespace skel {
	class Skin;
	class Attachment;
	class RegionAttachment;
	class MeshAttachment;
	class BoundingBoxAttachment;
	class PathAttachment;
	class PointAttachment;
	class ClippingAttachment;
	class SkeletonObjectCreator;

	class SK_API AttachmentLoader : public SkelObject {
	public:
		RTTI_DECL

		AttachmentLoader();

		virtual ~AttachmentLoader();

		/// @return May be NULL to not load any attachment.
		virtual RegionAttachment* newRegionAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name, const String& path) = 0;

		/// @return May be NULL to not load any attachment.
		virtual MeshAttachment* newMeshAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name, const String& path) = 0;

		/// @return May be NULL to not load any attachment.
		virtual BoundingBoxAttachment* newBoundingBoxAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name) = 0;

		/// @return May be NULL to not load any attachment
		virtual PathAttachment* newPathAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name) = 0;

		virtual PointAttachment* newPointAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name) = 0;

		virtual ClippingAttachment* newClippingAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name) = 0;

		virtual void configureAttachment(Attachment* attachment) = 0;
	};
}

#endif /* Skel_AttachmentLoader_h */

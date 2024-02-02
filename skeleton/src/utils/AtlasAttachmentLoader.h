#ifndef Skel_AtlasAttachmentLoader_h
#define Skel_AtlasAttachmentLoader_h

#include "AttachmentLoader.h"
#include "common/Vector.h"
#include "common/SkelString.h"

namespace skel {
	class Atlas;
	class AtlasRegion;
	class SkeletonObjectCreator;

	/// An AttachmentLoader that configures attachments using texture regions from an Atlas.
	/// See http://esotericsoftware.com/skel-loading-skeleton-data#JSON-and-binary-data about Loading Skeleton Data in the Skel Runtimes Guide.
	class SK_API AtlasAttachmentLoader : public AttachmentLoader {
	public:
		RTTI_DECL

		explicit AtlasAttachmentLoader(Atlas* atlas);

		virtual RegionAttachment* newRegionAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name, const String& path);

		virtual MeshAttachment* newMeshAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name, const String& path);

		virtual BoundingBoxAttachment* newBoundingBoxAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name);

		virtual PathAttachment* newPathAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name);

		virtual PointAttachment* newPointAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name);

		virtual ClippingAttachment* newClippingAttachment(SkeletonObjectCreator &creator, Skin& skin, const String& name);

		virtual void configureAttachment(Attachment* attachment);

		AtlasRegion* findRegion(const String& name);

	private:
		Atlas* _atlas;
	};
}

#endif /* Skel_AtlasAttachmentLoader_h */

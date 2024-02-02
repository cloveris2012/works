#include "AtlasAttachmentLoader.h"
#include "../entities/Skin.h"
#include "../entities/attachments/RegionAttachment.h"
#include "../entities/attachments/MeshAttachment.h"
#include "../entities/attachments/BoundingBoxAttachment.h"
#include "../entities/attachments/PathAttachment.h"
#include "../entities/attachments/PointAttachment.h"
#include "../entities/attachments/ClippingAttachment.h"
#include "common/Atlas.h"
#include "utils/SkeletonObjectCreator.h"

namespace skel {
RTTI_IMPL(AtlasAttachmentLoader, AttachmentLoader)

AtlasAttachmentLoader::AtlasAttachmentLoader(Atlas *atlas) : AttachmentLoader(), _atlas(atlas){
}

RegionAttachment *AtlasAttachmentLoader::newRegionAttachment(SkeletonObjectCreator &creator, Skin &skin, const String &name, const String &path) {
	SP_UNUSED(skin);

	AtlasRegion *regionP = findRegion(path);
	if (!regionP) return NULL;

	AtlasRegion &region = *regionP;

	RegionAttachment *attachmentP = creator.createRegionAttachment(name);

	RegionAttachment &attachment = *attachmentP;
	attachment.setRendererObject(regionP);
	attachment.setUVs(region.u, region.v, region.u2, region.v2, region.rotate);
	attachment._regionOffsetX = region.offsetX;
	attachment._regionOffsetY = region.offsetY;
	attachment._regionWidth = (float)region.width;
	attachment._regionHeight = (float)region.height;
	attachment._regionOriginalWidth = (float)region.originalWidth;
	attachment._regionOriginalHeight = (float)region.originalHeight;
	attachment._texName = region.texName;
	return attachmentP;
}

MeshAttachment *AtlasAttachmentLoader::newMeshAttachment(SkeletonObjectCreator &creator, Skin &skin, const String &name, const String &path) {
	SP_UNUSED(skin);

	AtlasRegion *regionP = findRegion(path);
	if (!regionP) return NULL;

	AtlasRegion &region = *regionP;

	MeshAttachment *attachmentP = creator.createMeshAttachment(name);

	MeshAttachment &attachment = *attachmentP;
	attachment.setRendererObject(regionP);
	attachment._regionU = region.u;
	attachment._regionV = region.v;
	attachment._regionU2 = region.u2;
	attachment._regionV2 = region.v2;
	attachment._regionRotate = region.rotate;
	attachment._regionDegrees = region.degrees;
	attachment._regionOffsetX = region.offsetX;
	attachment._regionOffsetY = region.offsetY;
	attachment._regionWidth = (float)region.width;
	attachment._regionHeight = (float)region.height;
	attachment._regionOriginalWidth = (float)region.originalWidth;
	attachment._regionOriginalHeight = (float)region.originalHeight;
	attachment._texName = region.texName;

	return attachmentP;
}

BoundingBoxAttachment *AtlasAttachmentLoader::newBoundingBoxAttachment(SkeletonObjectCreator &creator, Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return creator.createBoundingBoxAttachment(name);
}

PathAttachment *AtlasAttachmentLoader::newPathAttachment(SkeletonObjectCreator &creator, Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return creator.createPathAttachment(name);
}

PointAttachment *AtlasAttachmentLoader::newPointAttachment(SkeletonObjectCreator &creator, Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return creator.createPointAttachment(name);
}

ClippingAttachment *AtlasAttachmentLoader::newClippingAttachment(SkeletonObjectCreator &creator, Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return creator.createClippingAttachment(name);
}

void AtlasAttachmentLoader::configureAttachment(Attachment* attachment) {
	SP_UNUSED(attachment);
}

AtlasRegion *AtlasAttachmentLoader::findRegion(const String &name) {
	return _atlas->findRegion(name);
}

}

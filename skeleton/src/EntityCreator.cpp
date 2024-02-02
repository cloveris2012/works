#include "EntityCreator.h"

BoneDataWrapper* EntityCreator::createBoneData(int index, const std::string & name)
{
	const skel::String skelName = name.c_str();
	auto bonedata = new BoneDataWrapper(index, skelName,nullptr);
	return bonedata;
}

BoneWrapper * EntityCreator::createBone(BoneDataWrapper * bonedata, SkeletonExtend * skeleton)
{
	auto bone = new BoneWrapper(*bonedata, *skeleton, nullptr);
	return bone;
}

Color * EntityCreator::createColor(float r, float g, float b, float a)
{
	auto color = new Color(r, g, b, a);
	return color;
}

SlotDataWrapper * EntityCreator::createSlotData(int index, const std::string & name,BoneDataWrapper *bonedata)
{
	const skel::String skelName = name.c_str();
	auto slotdata = new SlotDataWrapper(index, skelName, *bonedata);
	return slotdata;
}

SlotWrapper * EntityCreator::createSlot(SlotDataWrapper *slotdata, BoneWrapper *bone)
{
	auto slot = new SlotWrapper(*slotdata, *bone);
	return slot;
}

RegionAttachmentWrapper * EntityCreator::createRegionAttachment(const std::string &name, const std::string &path,SkeletonExtend* skeleton)
{
	const skel::String skelName = name.c_str();
	const skel::String skelPath = path.c_str();

	Atlas atlas(skeleton->unitdata);
	auto atlasRegion = atlas.findRegion(skelPath);

	auto region = new RegionAttachmentWrapper(skelName);
	region->setRendererObject(atlasRegion);
	region->setUVs(atlasRegion->u, atlasRegion->v, atlasRegion->u2, atlasRegion->v2, atlasRegion->rotate);
	region->setRegionOffsetX(atlasRegion->offsetX);
	region->setRegionOffsetY(atlasRegion->offsetY);
	region->setRegionWidth(atlasRegion->width) ;
	region->setRegionHeight(atlasRegion->height);
	if (atlasRegion->rotate) {
		region->setWidth(atlasRegion->height);
		region->setHeight(atlasRegion->width);
	}
	else {
		region->setWidth(atlasRegion->width);
		region->setHeight(atlasRegion->height);
	}
	region->setRegionOriginalWidth(atlasRegion->originalWidth);
	region->setRegionOriginalHeight(atlasRegion->originalHeight);
	region->updateOffset();
	return region;
}

MeshAttachmentWrapper * EntityCreator::createMeshAttachment(const std::string & name, const std::string &path, SkeletonExtend* skeleton)
{
	const skel::String skelName = name.c_str();
	const skel::String skelPath = path.c_str();

	Atlas atlas(skeleton->unitdata);
	auto atlasRegion = atlas.findRegion(skelPath);

	auto mesh = new MeshAttachmentWrapper(skelName);
	mesh->setRendererObject(atlasRegion);

	mesh->setRegionV(atlasRegion->v);
	mesh->setRegionV2(atlasRegion->v2);
	mesh->setRegionU(atlasRegion->u);
	mesh->setRegionU2(atlasRegion->u2);
	mesh->setRegionRotate(atlasRegion->rotate);
	if (atlasRegion->rotate) {
		mesh->setRegionDegrees(90);
	}
	mesh->setRegionOffsetX(atlasRegion->offsetX);
	mesh->setRegionOffsetY(atlasRegion->offsetY);
	mesh->setRegionWidth(atlasRegion->width);
	mesh->setRegionHeight(atlasRegion->height);
	mesh->setRegionOriginalWidth(atlasRegion->originalWidth);
	mesh->setRegionOriginalHeight(atlasRegion->originalHeight);
	return mesh;
}

EventDataWrapper * EntityCreator::createEventData(const std::string & name)
{
	auto eventData = new EventDataWrapper(name.c_str());
	return eventData;
}

SkinWrapper * EntityCreator::createSkin(const std::string & name)
{
	auto skin = new SkinWrapper(name.c_str());
	return skin;
}

SkeletonDataWrapper * EntityCreator::createSkeletonData()
{
	auto skeletonData = new SkeletonDataWrapper();
	return skeletonData;
}


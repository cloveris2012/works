#pragma once
#include "common/skel.h"
#include "wrapper/data/BoneDataWrapper.h"
#include "wrapper/data/EventDataWrapper.h"
#include "wrapper/BoneWrapper.h"
#include "wrapper/data/SlotDataWrapper.h"
#include "wrapper/SlotWrapper.h"
#include "wrapper/RegionAttachmentWrapper.h"
#include "wrapper/MeshAttachmentWrapper.h"
#include "wrapper/SkinWrapper.h"
#include "wrapper/data/SkeletonDataWrapper.h"

class EntityCreator {

public:
	static BoneDataWrapper * createBoneData(int index, const std::string &name);
	static BoneWrapper * createBone(BoneDataWrapper *bonedata,SkeletonExtend *skeleton);
	static Color* createColor(float r, float g, float b, float a);

	static SlotDataWrapper * createSlotData(int index, const std::string &name,BoneDataWrapper *bonedata);
	static SlotWrapper * createSlot(SlotDataWrapper *slotdata,BoneWrapper *bone);

	static RegionAttachmentWrapper * createRegionAttachment(const std::string &name, const std::string &path, SkeletonExtend *skeleton);

	static MeshAttachmentWrapper * createMeshAttachment(const std::string &name, const std::string &path, SkeletonExtend *skeleton);

	static EventDataWrapper * createEventData(const std::string &name);

	static SkinWrapper * createSkin(const std::string &name);

	static SkeletonDataWrapper * createSkeletonData();
};
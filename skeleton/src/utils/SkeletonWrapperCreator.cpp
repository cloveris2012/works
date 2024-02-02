#include "SkeletonWrapperCreator.h"
#include "wrapper/data/SkeletonDataWrapper.h"
#include "wrapper/data/BoneDataWrapper.h"
#include "wrapper/data/EventDataWrapper.h"
#include "wrapper/SkeletonWrapper.h"
#include "wrapper/AnimationStateWrapper.h"
#include "wrapper/RegionAttachmentWrapper.h"
#include "wrapper/MeshAttachmentWrapper.h"
#include "wrapper/SkinWrapper.h"
#include "wrapper/data/PathConstraintDataWrapper.h"
#include "wrapper/data/IkConstraintDataWrapper.h"
#include "wrapper/data/TransformConstraintDataWrapper.h"
#include "wrapper/data/AnimationStateDataWrapper.h"

#include "wrapper/animations/timelines/AttachmentTimelineWrapper.h"
#include "wrapper/animations/timelines/ColorTimelineWrapper.h"
#include "wrapper/animations/timelines/DeformTimelineWrapper.h"
#include "wrapper/animations/timelines/DrawOrderTimelineWrapper.h"
#include "wrapper/animations/timelines/EventTimelineWrapper.h"
#include "wrapper/animations/timelines/IkConstraintTimelineWrapper.h"
#include "wrapper/animations/timelines/PathConstraintMixTimelineWrapper.h"
#include "wrapper/animations/timelines/PathConstraintPositionTimelineWrapper.h"
#include "wrapper/animations/timelines/PathConstraintSpacingTimelineWrapper.h"
#include "wrapper/animations/timelines/RotateTimelineWrapper.h"
#include "wrapper/animations/timelines/ScaleTimelineWrapper.h"
#include "wrapper/animations/timelines/ShearTimelineWrapper.h"
#include "wrapper/animations/timelines/TransformConstraintTimelineWrapper.h"
#include "wrapper/animations/timelines/TranslateTimelineWrapper.h"
#include "wrapper/animations/timelines/TwoColorTimelineWrapper.h"

using namespace skel;

SkeletonWrapperCreator::SkeletonWrapperCreator() {
}

SkeletonWrapperCreator::~SkeletonWrapperCreator() {
}

// data

SkeletonData *SkeletonWrapperCreator::createSkeletonData() {
	return new(__FILE__, __LINE__) SkeletonDataWrapper();
}

BoneData *SkeletonWrapperCreator::createBoneData(int index, const String &name, BoneData *parent, Json *map) {
	BoneDataWrapper *boneData = new(__FILE__, __LINE__) BoneDataWrapper(index, name, parent);
	const char *color = Json::getString(map, "color", 0);
	if (color) {
		Color &c = boneData->getColor();
		c.r = Color::toColor(color, 0);
		c.g = Color::toColor(color, 1);
		c.b = Color::toColor(color, 2);
		c.a = Color::toColor(color, 3);
	}
	return boneData;
}

SlotData *SkeletonWrapperCreator::createSlotData(int index, const String &name, BoneData &boneData) {
	return new(__FILE__, __LINE__) SlotDataWrapper(index, name, boneData);
}

EventData *SkeletonWrapperCreator::createEventData(const skel::String &name) {
	return new(__FILE__, __LINE__) EventDataWrapper(name);
}

IkConstraintData *SkeletonWrapperCreator::createIkConstraintData(const String &name) {
	return new(__FILE__, __LINE__) IkConstraintDataWrapper(name);
}

TransformConstraintData *SkeletonWrapperCreator::createTransformConstraintData(const String &name) {
	return new(__FILE__, __LINE__) TransformConstraintDataWrapper(name);
}

PathConstraintData *SkeletonWrapperCreator::createPathConstraintData(const String& name) {
	return new(__FILE__, __LINE__) PathConstraintDataWrapper(name);
}

AnimationStateData *SkeletonWrapperCreator::createAnimationStateData(SkeletonData *skeletonData) {
	return new (__FILE__, __LINE__) AnimationStateDataWrapper(skeletonData);
}

// entity

SkeletonExtend *SkeletonWrapperCreator::createSkeleton(SkeletonData *skeletonData) {
	return new (__FILE__, __LINE__) SkeletonWrapper(skeletonData, *this);
}

Bone* skel::SkeletonWrapperCreator::createBone(BoneData &data, Skeleton &skeleton, Bone *parent) {
	return new (__FILE__, __LINE__) BoneWrapper(data, skeleton,parent);
}

Slot* skel::SkeletonWrapperCreator::createSlot(SlotData & data, Bone & bone)
{
	return new (__FILE__, __LINE__) SlotWrapper(data, bone);
}

RegionAttachment * skel::SkeletonWrapperCreator::createRegionAttachment(const String & name)
{
	return new (__FILE__, __LINE__) RegionAttachmentWrapper(name);
}

MeshAttachment * skel::SkeletonWrapperCreator::createMeshAttachment(const String & name)
{
	return new (__FILE__, __LINE__) MeshAttachmentWrapper(name);
}

Skin* SkeletonWrapperCreator::createSkin(const String &name) {
	return new(__FILE__, __LINE__) SkinWrapper(name);
}

// animation

AnimationStateExtend *SkeletonWrapperCreator::createAnimationState(AnimationStateData *data) {
	return new (__FILE__, __LINE__) AnimationStateWrapper(data);
}

Animation *SkeletonWrapperCreator::createAnimation(const String &name, Vector<Timeline *> &timelines, float duration) {
	return new(__FILE__, __LINE__) AnimationWrapper(name, timelines, duration);
}

AttachmentTimeline *SkeletonWrapperCreator::createAttachmentTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) AttachmentTimelineWrapper(frameCount);
}

ColorTimeline *SkeletonWrapperCreator::createColorTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) ColorTimelineWrapper(frameCount);
}

TwoColorTimeline *SkeletonWrapperCreator::createTwoColorTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) TwoColorTimelineWrapper(frameCount);
}

RotateTimeline *SkeletonWrapperCreator::createRotateTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) RotateTimelineWrapper(frameCount);
}

ScaleTimeline *SkeletonWrapperCreator::createScaleTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) ScaleTimelineWrapper(frameCount);
}

TranslateTimeline *SkeletonWrapperCreator::createTranslateTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) TranslateTimelineWrapper(frameCount);
}

ShearTimeline *SkeletonWrapperCreator::createShearTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) ShearTimelineWrapper(frameCount);
}

IkConstraintTimeline *SkeletonWrapperCreator::createIkConstraintTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) IkConstraintTimelineWrapper(frameCount);
}

TransformConstraintTimeline *SkeletonWrapperCreator::createTransformConstraintTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) TransformConstraintTimelineWrapper(frameCount);
}

PathConstraintSpacingTimeline *SkeletonWrapperCreator::createPathConstraintSpacingTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) PathConstraintSpacingTimelineWrapper(frameCount);
}

PathConstraintPositionTimeline *SkeletonWrapperCreator::createPathConstraintPositionTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) PathConstraintPositionTimelineWrapper(frameCount);
}

PathConstraintMixTimeline *SkeletonWrapperCreator::createPathConstraintMixTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) PathConstraintMixTimelineWrapper(frameCount);
}

DeformTimeline *SkeletonWrapperCreator::createDeformTimeline(int frameCount, Json *map) {
	DeformTimelineWrapper *timeline = new(__FILE__, __LINE__) DeformTimelineWrapper(frameCount);
	size_t frameIndex;
	Json *valueMap;
	auto &origionalVertices = timeline->getOrigionalVertices();
	auto &origionalOffsets = timeline->getOrigionalOffsets();
	for (valueMap = map->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
		
		int offset = Json::getInt(valueMap, "offset", 0);
		origionalOffsets[frameIndex] = offset;
		Json *vertices = Json::getItem(valueMap, "vertices");
		if (vertices) {
			origionalVertices[frameIndex].clear();
			Json *vertex;
			for (vertex = vertices->_child; vertex; vertex = vertex->_next) {
				origionalVertices[frameIndex].add(vertex->_valueFloat);
			}
		}
	}

	return timeline;
}

DrawOrderTimeline *SkeletonWrapperCreator::createDrawOrderTimeline(int frameCount, Json *map) {
	DrawOrderTimelineWrapper *timeline = new(__FILE__, __LINE__) DrawOrderTimelineWrapper(frameCount);
	size_t frameIndex;
	Json *valueMap;
	auto &origionalOffsets = timeline->getOrigionalOffsets();
	auto &origionalSlotNames = timeline->getOrigionalSlotNames();
	for (valueMap = map->_child, frameIndex = 0; valueMap; valueMap = valueMap->_next, ++frameIndex) {
		Vector<int> drawOrder2;
		Json *offsets = Json::getItem(valueMap, "offsets");
		if (offsets) {
			origionalOffsets[frameIndex].clear();
			origionalSlotNames[frameIndex].clear();
			Json *offsetMap;
			for (offsetMap = offsets->_child; offsetMap; offsetMap = offsetMap->_next) {
				origionalOffsets[frameIndex].add(Json::getInt(offsetMap, "offset", 0));
				origionalSlotNames[frameIndex].add(Json::getString(offsetMap, "slot", 0));
			}
		}
	}

	return timeline;
}

EventTimeline *SkeletonWrapperCreator::createEventTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) EventTimelineWrapper(frameCount);
}

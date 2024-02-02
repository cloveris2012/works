#include "SkeletonObjectCreator.h"
using namespace skel;

SkeletonObjectCreator::SkeletonObjectCreator() {
}

SkeletonObjectCreator::~SkeletonObjectCreator() {
}

// data

SkeletonData *SkeletonObjectCreator::createSkeletonData() {
	return new(__FILE__, __LINE__) SkeletonData();
}

BoneData *SkeletonObjectCreator::createBoneData(int index, const String &name, BoneData *parent, Json *map) {
	return new(__FILE__, __LINE__) BoneData(index, name, parent);
}

SlotData *SkeletonObjectCreator::createSlotData(int index, const String &name, BoneData &boneData) {
	return new(__FILE__, __LINE__) SlotData(index, name, boneData);
}

IkConstraintData *SkeletonObjectCreator::createIkConstraintData(const String &name) {
	return new(__FILE__, __LINE__) IkConstraintData(name);
}

TransformConstraintData *SkeletonObjectCreator::createTransformConstraintData(const String &name) {
	return new(__FILE__, __LINE__) TransformConstraintData(name);
}

PathConstraintData *SkeletonObjectCreator::createPathConstraintData(const String& name) {
	return new(__FILE__, __LINE__) PathConstraintData(name);
}

EventData *SkeletonObjectCreator::createEventData(const skel::String &name) {
	return new(__FILE__, __LINE__) EventData(name);
}

AnimationStateData *SkeletonObjectCreator::createAnimationStateData(SkeletonData *skeletonData) {
	return new (__FILE__, __LINE__) AnimationStateData(skeletonData);
}

// entity

SkeletonExtend *SkeletonObjectCreator::createSkeleton(SkeletonData *skeletonData) {
	return new (__FILE__, __LINE__) SkeletonExtend(skeletonData, *this);
}

AnimationStateExtend *SkeletonObjectCreator::createAnimationState(AnimationStateData *data) {
	return new (__FILE__, __LINE__) AnimationStateExtend(data);
}

Bone *SkeletonObjectCreator::createBone(BoneData &data, Skeleton &skeleton, Bone *parent) {
	return new(__FILE__, __LINE__) Bone(data, skeleton, parent);
}

Slot *SkeletonObjectCreator::createSlot(SlotData &data, Bone &bone) {
	return new(__FILE__, __LINE__) Slot(data, bone);
}

IkConstraint *SkeletonObjectCreator::createIkConstraint(IkConstraintData &data, Skeleton &skeleton) {
	return new(__FILE__, __LINE__) IkConstraint(data, skeleton);
}

TransformConstraint *SkeletonObjectCreator::createTransformConstraint(TransformConstraintData &data, Skeleton &skeleton) {
	return new(__FILE__, __LINE__) TransformConstraint(data, skeleton);
}

PathConstraint *SkeletonObjectCreator::createPathConstraint(PathConstraintData &data, Skeleton &skeleton) {
	return new(__FILE__, __LINE__) PathConstraint(data, skeleton);
}

Skin* SkeletonObjectCreator::createSkin(const String &name) {
	return new(__FILE__, __LINE__) Skin(name);
}

LinkedMesh* SkeletonObjectCreator::createLinkedMesh(MeshAttachment *mesh, const String &skin, size_t slotIndex, const String &parent, bool inheritDeform) {
	return new(__FILE__, __LINE__) LinkedMesh(mesh, skin, slotIndex, parent, inheritDeform);
}

Event *SkeletonObjectCreator::createEvent(float time, const skel::EventData &data) {
	return new(__FILE__, __LINE__) Event(time, data);
}

RegionAttachment *SkeletonObjectCreator::createRegionAttachment(const String &name) {
	return new(__FILE__, __LINE__) RegionAttachment(name);
}

MeshAttachment *SkeletonObjectCreator::createMeshAttachment(const String &name) {
	return new(__FILE__, __LINE__) MeshAttachment(name);
}

BoundingBoxAttachment *SkeletonObjectCreator::createBoundingBoxAttachment(const String &name) {
	return new(__FILE__, __LINE__) BoundingBoxAttachment(name);
}

PathAttachment *SkeletonObjectCreator::createPathAttachment(const String &name) {
	return new(__FILE__, __LINE__) PathAttachment(name);
}

PointAttachment *SkeletonObjectCreator::createPointAttachment(const String &name) {
	return new(__FILE__, __LINE__) PointAttachment(name);
}

ClippingAttachment *SkeletonObjectCreator::createClippingAttachment(const String &name) {
	return new(__FILE__, __LINE__) ClippingAttachment(name);
}

// animation

Animation *SkeletonObjectCreator::createAnimation(const String &name, Vector<Timeline *> &timelines, float duration) {
	return new(__FILE__, __LINE__) Animation(name, timelines, duration);
}

AttachmentTimeline *SkeletonObjectCreator::createAttachmentTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) AttachmentTimeline(frameCount);
}

ColorTimeline *SkeletonObjectCreator::createColorTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) ColorTimeline(frameCount);
}

TwoColorTimeline *SkeletonObjectCreator::createTwoColorTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) TwoColorTimeline(frameCount);
}

RotateTimeline *SkeletonObjectCreator::createRotateTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) RotateTimeline(frameCount);
}

ScaleTimeline *SkeletonObjectCreator::createScaleTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) ScaleTimeline(frameCount);
}

TranslateTimeline *SkeletonObjectCreator::createTranslateTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) TranslateTimeline(frameCount);
}

ShearTimeline *SkeletonObjectCreator::createShearTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) ShearTimeline(frameCount);
}

IkConstraintTimeline *SkeletonObjectCreator::createIkConstraintTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) IkConstraintTimeline(frameCount);
}

TransformConstraintTimeline *SkeletonObjectCreator::createTransformConstraintTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) TransformConstraintTimeline(frameCount);
}

PathConstraintSpacingTimeline *SkeletonObjectCreator::createPathConstraintSpacingTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) PathConstraintSpacingTimeline(frameCount);
}

PathConstraintPositionTimeline *SkeletonObjectCreator::createPathConstraintPositionTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) PathConstraintPositionTimeline(frameCount);
}

PathConstraintMixTimeline *SkeletonObjectCreator::createPathConstraintMixTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) PathConstraintMixTimeline(frameCount);
}

DeformTimeline *SkeletonObjectCreator::createDeformTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) DeformTimeline(frameCount);
}

DrawOrderTimeline *SkeletonObjectCreator::createDrawOrderTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) DrawOrderTimeline(frameCount);
}

EventTimeline *SkeletonObjectCreator::createEventTimeline(int frameCount, Json *map) {
	return new(__FILE__, __LINE__) EventTimeline(frameCount);
}
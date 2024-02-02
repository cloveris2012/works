#include "SkeletonDataWrapper.h"
#include <iostream>
using namespace skel;

size_t SkeletonDataWrapper::getBoneDataCount() {
	return _bones.size();
}

size_t SkeletonDataWrapper::getSlotDataCount() {
	return _slots.size();
}

size_t SkeletonDataWrapper::getSkinCount() {
	return _skins.size();
}

size_t SkeletonDataWrapper::getEventDataCount() {
	return _events.size();
}

size_t SkeletonDataWrapper::getAnimationCount() {
	return _animations.size();
}

size_t SkeletonDataWrapper::getIkConstraintDataCount() {
	return _ikConstraints.size();
}

size_t SkeletonDataWrapper::getTransformConstraintDataCount() {
	return _transformConstraints.size();
}

size_t SkeletonDataWrapper::getPathConstraintDataCount() {
	return _pathConstraints.size();
}

BoneDataWrapper *SkeletonDataWrapper::getBoneData(size_t index) {
	return dynamic_cast<BoneDataWrapper*>(_bones[index]);
}

SlotDataWrapper *SkeletonDataWrapper::getSlotData(size_t index) {
	return dynamic_cast<SlotDataWrapper*>(_slots[index]);
}

SkinWrapper * SkeletonDataWrapper::getSkin(size_t index)
{
	return dynamic_cast<SkinWrapper*>(_skins[index]);
}

SkinWrapper * SkeletonDataWrapper::getDefaultSkinWrapper() {
	return dynamic_cast<SkinWrapper*>(getDefaultSkin());
}


EventDataWrapper *SkeletonDataWrapper::getEventData(size_t index) {
	return dynamic_cast<EventDataWrapper*>(_events[index]);
}

AnimationWrapper *SkeletonDataWrapper::getAnimation(size_t index) {
	return dynamic_cast<AnimationWrapper*>(_animations[index]);
}

IkConstraintDataWrapper *SkeletonDataWrapper::getIkConstraintData(size_t index) {
	return dynamic_cast<IkConstraintDataWrapper*>(_ikConstraints[index]);
}

TransformConstraintDataWrapper *SkeletonDataWrapper::getTransformConstraintData(size_t index) {
	return dynamic_cast<TransformConstraintDataWrapper*>(_transformConstraints[index]);
}

PathConstraintDataWrapper *SkeletonDataWrapper::getPathConstraintData(size_t index) {
	return dynamic_cast<PathConstraintDataWrapper*>(_pathConstraints[index]);
}

BoneDataWrapper *SkeletonDataWrapper::findBoneLua(const char *boneName)
{
	return dynamic_cast<BoneDataWrapper*>(findBone(boneName));
}

int SkeletonDataWrapper::findBoneIndexLua(const char * boneName)
{
	return findBoneIndex(boneName);
}

SlotDataWrapper *SkeletonDataWrapper::findSlotLua(const char *slotName)
{
	return dynamic_cast<SlotDataWrapper*>(findSlot(slotName));
}

int SkeletonDataWrapper::findSlotIndexLua(const char *slotName)
{
	return findSlotIndex(slotName);
}

SkinWrapper *SkeletonDataWrapper::findSkinLua(const char *skinName)
{
	return dynamic_cast<SkinWrapper*>(findSkin(skinName));
}

AnimationWrapper *SkeletonDataWrapper::findAnimationLua(const char *animationName)
{
	return dynamic_cast<AnimationWrapper*>(findAnimation(animationName));
}

void SkeletonDataWrapper::insertBone(BoneData *boneData) {
	_bones.add(boneData);
}

void SkeletonDataWrapper::removeAnimation(skel::Animation* animation) {
	_animations.remove(animation);
}

void SkeletonDataWrapper::addAnimation(skel::Animation* animation, int index) {
	_animations.addAt(animation, index);
}

void SkeletonDataWrapper::removeEvent(skel::EventData* event) {
	_events.remove(event);
}

void SkeletonDataWrapper::addEvent(skel::EventData* event, int index) {
	_events.addAt(event, index);
}

void SkeletonDataWrapper::copy(SkeletonData * skeletonData)
{
	_name = skeletonData->getName();
	_bones.clearAndAddAll(skeletonData->getBones());
	_slots.clearAndAddAll(skeletonData->getSlots());
	_skins.clearAndAddAll(skeletonData->getSkins());
	setDefaultSkin(skeletonData->getDefaultSkin());
	_events.clearAndAddAll(skeletonData->getEvents());
	_animations.clearAndAddAll(skeletonData->getAnimations());
	_ikConstraints.clearAndAddAll(skeletonData->getIkConstraints());
	_transformConstraints.clearAndAddAll(skeletonData->getTransformConstraints());
	_pathConstraints.clearAndAddAll(skeletonData->getPathConstraints());
	_x = skeletonData->getX();
	_y = skeletonData->getY();
	_width = skeletonData->getWidth();
	_height = skeletonData->getHeight();
	_version = skeletonData->getVersion();
	_hash = skeletonData->getHash();
	_fps = skeletonData->getFps();
	_imagesPath = skeletonData->getImagesPath();
	_audioPath = skeletonData->getAudioPath();
}

#ifndef SKELETON_DATA_WRAPPER_H
#define SKELETON_DATA_WRAPPER_H

#include "data/BoneData.h"
#include "common/skel.h"
#include "BoneDataWrapper.h"
#include "SlotDataWrapper.h"
#include "EventDataWrapper.h"
#include "wrapper/SkinWrapper.h"
#include "IkConstraintDataWrapper.h"
#include "TransformConstraintDataWrapper.h"
#include "PathConstraintDataWrapper.h"
#include "wrapper/animations/AnimationWrapper.h"

class SkeletonDataWrapper : public skel::SkeletonData {
public:

	size_t getBoneDataCount();
	size_t getSlotDataCount();
	size_t getSkinCount();
	size_t getEventDataCount();
	size_t getAnimationCount();
	size_t getIkConstraintDataCount();
	size_t getTransformConstraintDataCount();
	size_t getPathConstraintDataCount();

	BoneDataWrapper *getBoneData(size_t index);
	SlotDataWrapper *getSlotData(size_t index);
	SkinWrapper *getSkin(size_t index);
	SkinWrapper *getDefaultSkinWrapper();
	EventDataWrapper *getEventData(size_t index);
	AnimationWrapper *getAnimation(size_t index);
	IkConstraintDataWrapper *getIkConstraintData(size_t index);
	TransformConstraintDataWrapper *getTransformConstraintData(size_t index);
	PathConstraintDataWrapper *getPathConstraintData(size_t index);
	BoneDataWrapper *findBoneLua(const char* boneName);
	int findBoneIndexLua(const char* boneName);
	SlotDataWrapper *findSlotLua(const char* slotName);
	int findSlotIndexLua(const char* slotName);
	SkinWrapper *findSkinLua(const char* skinName);
	AnimationWrapper *findAnimationLua(const char* animationName);

	void removeAnimation(skel::Animation* animation);
	void addAnimation(skel::Animation* animation, int index);

	void removeEvent(skel::EventData* event);
	void addEvent(skel::EventData* event, int index);

	void insertBone(skel::BoneData *);

	void copy(SkeletonData* skeletonData);
};

#endif
#ifndef SKELETON_REG_H
#define SKELETON_REG_H

//#include <vector>
#include "common/skel.h"
#include "utils/SkeletonObjectCreator.h"

#include "data/SkeletonDataWrapper.h"
#include "BoneWrapper.h"
#include "SlotWrapper.h"
#include "RegionAttachmentWrapper.h"
#include "MeshAttachmentWrapper.h"
#include "SkinWrapper.h"

class SkeletonWrapper : public skel::SkeletonExtend {
public:
	SkeletonWrapper(skel::SkeletonData *skeletonData, skel::SkeletonObjectCreator &creator);
	~SkeletonWrapper();
	SlotWrapper* getSlotByIndex(size_t index);

	void setData(SkeletonDataWrapper *skeletonData);
	SkeletonDataWrapper *getData();
	SkinWrapper *getSkinWrapper();

	BoneWrapper* getBoneByIndex(size_t index);

	// edit
public:
	void addBone(Bone *bone, int index);
	void removeBone( int index);
	void addSlot(Slot * slot, int index);
	void removeSlot(int index);
	void updateBonesOrder();
	void changeDrawOrder(int src, int dst);
	void setSkinBySkin(SkinWrapper *skin);

private:
	bool _customData;
};

#endif
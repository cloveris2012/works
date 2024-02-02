#include "SkeletonWrapper.h"
#include <iostream>
#include "utils/LuaEx.h"


using namespace std;
using namespace skel;

SkeletonWrapper::SkeletonWrapper(SkeletonData *skeletonData, SkeletonObjectCreator &creator) : SkeletonExtend(skeletonData, creator) {
	_customData = false;
}

SkeletonWrapper::~SkeletonWrapper()
{
	if (_customData == true)
	{
		delete _data;
	}
}

void SkeletonWrapper::setData(SkeletonDataWrapper * skeletonData)
{
	_data = skeletonData;
	_customData = true;
}

SkeletonDataWrapper *SkeletonWrapper::getData() {
	return dynamic_cast<SkeletonDataWrapper*>(Skeleton::getData());
}

BoneWrapper* SkeletonWrapper::getBoneByIndex(size_t index)
{
	auto bones = getBones();
	if (index < 0 || index >= bones.size()) {
		return nullptr;
	}
	auto wrapper = dynamic_cast<BoneWrapper*>(bones[index]);
	return  wrapper;
}

SlotWrapper* SkeletonWrapper::getSlotByIndex(size_t index)
{
	auto slots = getSlots();
	if (index < 0 || index >= slots.size()) {
		return nullptr;
	}
	return  dynamic_cast<SlotWrapper *>(slots[index]);
}

SkinWrapper *SkeletonWrapper::getSkinWrapper() {
	return dynamic_cast<SkinWrapper*>(getSkin());
}

void SkeletonWrapper::addBone(Bone * bone, int index)
{
	auto &bones = getBones();
	if (index > bones.size()) {
		printf("addBone error index is not legal!");
		return;
	}
	else if (index == bones.size()) {
		bones.add(bone);
		//添加到skeletonData
		getData()->getBones().add(&bone->getData());
		bone->getData()._index = index;
	}
	else {
		//在数组中间添加bone
		auto tmp = bones[index];
		auto tmp_data = getData()->getBones()[index];
		bones[index] = bone;
		getData()->getBones()[index] = &bone->getData();
		index++;
		while (index < bones.size()) {
			auto tmp2 = bones[index];
			auto tmp_data2 = getData()->getBones()[index];
			bones[index] = tmp;
			getData()->getBones()[index] = tmp_data;
			tmp_data->_index = index;
			tmp = tmp2;
			tmp_data = tmp_data2;
			index++;
		}
		bones.add(tmp);
		getData()->getBones().add(tmp_data);
		tmp_data->_index = index;
	}
}

void SkeletonWrapper::removeBone( int index)
{
	auto &bones = getBones();
	if (index >= bones.size()) {
		printf("removeBone error index is not legal!");
		return;
	}
	else {

		bones.removeAt(index);
		getData()->getBones().removeAt(index);
		
		// update index
		while (index < bones.size()) {
			bones[index]->setIndex(index);
			bones[index]->getData()._index = index;
			index++;
		}
		
	}
}

void SkeletonWrapper::addSlot(Slot * slot, int index) {
	auto &slots = getSlots();
	if (index > slots.size()) {
		printf("addSlot error,index is not legal!");
		return;
	}
	else if (index == slots.size()) {
		slots.add(slot);
		getData()->getSlots().add(&slot->getData());
		slot->getData()._index = index;
		//add to draworder
		getDrawOrder().add(slot);
	}
	else {
		auto &drawOrder = getDrawOrder();

		auto tmp = slots[index];
		auto tmp_data = getData()->getSlots()[index];
		auto tmp_draw = drawOrder[index];
		slots[index] = slot;
		drawOrder[index] = slot;
		getData()->getSlots()[index] = &slot->getData();
		index++;
		while (index < slots.size()) {
			auto tmp2 = slots[index];
			auto tmp_data2 = getData()->getSlots()[index];
			auto tmp_draw2 = drawOrder[index];
			slots[index] = tmp;
			drawOrder[index] = tmp;
			getData()->getSlots()[index] = tmp_data;
			tmp_data->_index = index;
			tmp = tmp2;
			tmp_data = tmp_data2;
			tmp_draw = tmp_draw2;
			index++;
		}
		slots.add(tmp);
		getData()->getSlots().add(tmp_data);
		tmp_data->_index = index;
		drawOrder.add(tmp_draw);
	}
}

void SkeletonWrapper::removeSlot( int index) {
	auto &slots = getSlots();
	if (index >= slots.size()) {
		printf("removeBone error index is not legal!");
		return;
	}
	else {
		slots.removeAt(index);
		getData()->getSlots().removeAt(index);
		getDrawOrder().removeAt(index);
		// update index
		while (index < slots.size()) {
			slots[index]->getData()._index = index;
			index++;
		}
	}
}

void SkeletonWrapper::updateBonesOrder() {
	updateCache();
	auto &list = getUpdateCacheList();
	//通过updateCachelist的顺序，来处理新的bones列表

	auto &realBones = getBones();
	auto &realDatas = getData()->getBones();
	realBones.clear();
	realDatas.clear();
	for (int index = 0; index < list.size(); index++) {
		auto update = list[index];
		if (update->getRTTI().isExactly(Bone::rtti)) {
			auto bone = dynamic_cast<BoneWrapper*>(update);
			bone->setIndex(index);
			bone->getData()._index = index;
			realBones.add(bone);
			realDatas.add(&bone->getData());
		}
	}
}

void SkeletonWrapper::changeDrawOrder(int src, int dst) {
	auto &slots = getSlots();
	
	if (src > slots.size() || dst > slots.size()) {
		printf("changeDrawOrder error,out of index");
		return;
	}
	if (src > dst) {
		auto tmp = slots[dst];
		slots[dst] = slots[src];
		int index = dst + 1;
		while (index < slots.size())
		{
			auto tmp2 = slots[index];
			slots[index] = tmp;
			tmp = tmp2;
			index++;
		}
	}
	else
	{
		auto tmp = slots[dst];
		slots[dst] = slots[src];
		int index = src;
		while (index < dst - 1) {
			slots[index] = slots[index + 1];
			index++;
		}
		slots[index] = tmp;
	}
	getDrawOrder().clear();
	getData()->getSlots().clear();
	int start = 0;
	while (start < slots.size()) {
		auto slot = slots[start];
		getDrawOrder().add(slot);
		getData()->getSlots().add(&slot->getData());
		slot->getData()._index = start;
		start++;
	}
}

void SkeletonWrapper::setSkinBySkin(SkinWrapper * skin)
{
	return SkeletonExtend::setSkinBySkin(dynamic_cast<Skin*>(skin));
}

#include "DrawOrderTimelineWrapper.h"
#include <iostream>
using namespace skel;

DrawOrderTimelineWrapper::DrawOrderTimelineWrapper(int frameCount) : DrawOrderTimeline(frameCount) {
	_origionalOffsets.ensureCapacity(frameCount);
	_origionalSlotNames.ensureCapacity(frameCount);

	for (int i = 0; i < frameCount; ++i) {
		Vector<int> vec;
		_origionalOffsets.add(vec);
		Vector<std::string> vec2;
		_origionalSlotNames.add(vec2);
	}
}

Vector<Vector<int> > &DrawOrderTimelineWrapper::getOrigionalOffsets() {
	return _origionalOffsets;
}

Vector<Vector<std::string> > &DrawOrderTimelineWrapper::getOrigionalSlotNames() {
	return _origionalSlotNames;
}

LuaIntf::LuaRef DrawOrderTimelineWrapper::getFrameData(lua_State* L, size_t frameIndex)
{

	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();

	auto &frames = getFrames();
	ref.set<std::string, float>("time", frames[frameIndex]);


	LS.newTable();
	LuaIntf::LuaRef oRef(L, -1);
	LS.pop();
	ref.set<std::string, LuaIntf::LuaRef>("offsets", oRef);

	auto &offsets = _origionalOffsets[frameIndex];
	auto &slotNames = _origionalSlotNames[frameIndex];
	for (size_t i = 0; i < offsets.size(); i++) {

		LS.newTable();
		LuaIntf::LuaRef tRef(L, -1);
		LS.pop();
		oRef.set<int, LuaIntf::LuaRef>(i + 1, tRef);

		tRef.set<std::string, float>("offset", offsets[i]);
		tRef.set<std::string, std::string>("slot", slotNames[i]);
	}

	return ref;
}

void DrawOrderTimelineWrapper::setToSetupPose(LuaIntf::LuaRef &data, SkeletonDataWrapper *skeletonData) {
	int frameCount = data.len();

	_frames.ensureCapacity(frameCount);
	_drawOrders.ensureCapacity(frameCount);

	_frames.setSize(frameCount, 0);

	for (int i = 0; i < frameCount; ++i) {
		Vector<int> vec;
		_drawOrders.add(vec);
	}

	size_t frameIndex = 0;
	for (auto beg = data.begin(), end = data.end(); beg != end; ++beg, ++frameIndex) {
		auto offsets = beg.value().get("offsets");
		Vector<int> drawOrder2;

		Vector<int> unchanged;
		size_t slotSize = skeletonData->getSlots().size();
		unchanged.ensureCapacity(slotSize - offsets.len());
		unchanged.setSize(slotSize - offsets.len(), 0);
		size_t originalIndex = 0, unchangedIndex = 0;

		drawOrder2.ensureCapacity(slotSize);
		drawOrder2.setSize(slotSize, 0);
		int ii;
		for (ii = (int)slotSize - 1; ii >= 0; --ii)
			drawOrder2[ii] = -1;

		for (auto beg2 = offsets.begin(), end2 = offsets.end(); beg2 != end2; ++beg2) {
			auto slotName = beg2.value().get("slot").toValue<std::string>();
			int slotIndex = skeletonData->findSlotIndex(slotName.c_str());
			assert(slotIndex != -1);
			/* Collect unchanged items. */
			while (originalIndex != (size_t)slotIndex)
				unchanged[unchangedIndex++] = originalIndex++;
			/* Set changed items. */
			drawOrder2[originalIndex + beg2.value().get("offset").toValue<int>()] = originalIndex;
			originalIndex++;
		}
		/* Collect remaining unchanged items. */
		while (originalIndex < slotSize)
			unchanged[unchangedIndex++] = originalIndex++;
		/* Fill in unchanged items. */
		for (ii = (int)slotSize - 1; ii >= 0; ii--)
			if (drawOrder2[ii] == -1) drawOrder2[ii] = unchanged[--unchangedIndex];

		setFrame(frameIndex, beg.value().get("time").toValue<float>(),drawOrder2);
	}
}

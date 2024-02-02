#include "AttachmentTimelineWrapper.h"
#include <iostream>
using namespace skel;

AttachmentTimelineWrapper::AttachmentTimelineWrapper(int frameCount) : AttachmentTimeline(frameCount) {

}

float AttachmentTimelineWrapper::getFrame(size_t index) {
	auto &frames = getFrames();
	return frames[index];
}

const char *AttachmentTimelineWrapper::getAttachmentName(size_t index) {
	auto &names = getAttachmentNames();
	return names[index].buffer();
}

int AttachmentTimelineWrapper::getSlotIndex() {
	return _slotIndex;
}

void AttachmentTimelineWrapper::setSlotIndex(int index) {
	_slotIndex = index;
}

void AttachmentTimelineWrapper::setToSetupPose(LuaIntf::LuaRef &data) {
	int frameCount = data.len();

	_frames.ensureCapacity(frameCount);
	_frames.setSize(frameCount, 0);

	_attachmentNames.ensureCapacity(frameCount);
	for (int i = 0; i < frameCount; ++i) {
		_attachmentNames.add(String());
	}

	size_t frameIndex = 0;
	for (auto beg = data.begin(), end = data.end(); beg != end; ++beg, ++frameIndex) {

		std::string name = "";
		if (beg.value().has("name"))
			name = beg.value().get("name").toValue<std::string>();

		setFrame(frameIndex, beg.value().get("time").toValue<float>(), name.c_str());
	}
}

void AttachmentTimelineWrapper::setFrameLua(int frameIndex, float time, const char *attachmentName) {
	setFrame(frameIndex, time, attachmentName);
}
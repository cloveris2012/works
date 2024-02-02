#pragma once

#include "common/skel.h"
#include "common/SkelString.h"

class AttachmentTimelineWrapper : public skel::AttachmentTimeline {
public:
	AttachmentTimelineWrapper(int frameCount);
	float getFrame(size_t index);
	const char *getAttachmentName(size_t index);
	int getSlotIndex();
	void setSlotIndex(int index);
	void setToSetupPose(LuaIntf::LuaRef &data);
	void setFrameLua(int frameIndex, float time, const char *attachmentName);
};

#include "AnimationCreator.h"
#include "common/Vector.h"

AnimationWrapper *AnimationCreator::createAnimation(std::string name, float duration)
{
	skel::Vector<Timeline *> timelines;
	AnimationWrapper *animation = new(__FILE__, __LINE__) AnimationWrapper(name.c_str(), timelines, duration);
	return animation;
}

AttachmentTimelineWrapper *AnimationCreator::createAttachmentTimeline(int slotIndex, int frameCount)
{
	AttachmentTimelineWrapper *timeline = new(__FILE__, __LINE__) AttachmentTimelineWrapper(frameCount);
	timeline->setSlotIndex(slotIndex);
	return timeline;
}

ColorTimelineWrapper *AnimationCreator::createColorTimeline(int slotIndex, int frameCount)
{
	ColorTimelineWrapper *timeline = new(__FILE__, __LINE__) ColorTimelineWrapper(frameCount);
	timeline->setSlotIndex(slotIndex);
	return timeline;
}

DeformTimelineWrapper *AnimationCreator::createDeformTimeline(int slotIndex, skel::VertexAttachment *inValue, int frameCount)
{
	DeformTimelineWrapper *timeline = new(__FILE__, __LINE__) DeformTimelineWrapper(frameCount);
	timeline->setSlotIndex(slotIndex);
	timeline->setAttachment(inValue);
	return timeline;
}

DrawOrderTimelineWrapper *AnimationCreator::createDrawOrderTimeline(int frameCount)
{
	DrawOrderTimelineWrapper *timeline = new(__FILE__, __LINE__) DrawOrderTimelineWrapper(frameCount);
	return timeline;
}

EventTimelineWrapper *AnimationCreator::createEventTimeline(int frameCount)
{
	EventTimelineWrapper *timeline = new(__FILE__, __LINE__) EventTimelineWrapper(frameCount);
	return timeline;
}

IkConstraintTimelineWrapper *AnimationCreator::createIkConstraintTimeline(int frameCount)
{
	IkConstraintTimelineWrapper *timeline = new(__FILE__, __LINE__) IkConstraintTimelineWrapper(frameCount);
	return timeline;
}

PathConstraintMixTimelineWrapper *AnimationCreator::createPathConstraintMixTimeline(int frameCount)
{
	PathConstraintMixTimelineWrapper *timeline = new(__FILE__, __LINE__) PathConstraintMixTimelineWrapper(frameCount);
	return timeline;
}

PathConstraintPositionTimelineWrapper *AnimationCreator::createPathConstraintPositionTimeline(int frameCount)
{
	PathConstraintPositionTimelineWrapper *timeline = new(__FILE__, __LINE__) PathConstraintPositionTimelineWrapper(frameCount);
	return timeline;
}

PathConstraintSpacingTimelineWrapper *AnimationCreator::createPathConstraintSpacingTimeline(int frameCount)
{
	PathConstraintSpacingTimelineWrapper *timeline = new(__FILE__, __LINE__) PathConstraintSpacingTimelineWrapper(frameCount);
	return timeline;
}

RotateTimelineWrapper *AnimationCreator::createRotateTimeline(int boneIndex, int frameCount)
{
	RotateTimelineWrapper *timeline = new(__FILE__, __LINE__) RotateTimelineWrapper(frameCount);
	timeline->setBoneIndex(boneIndex);
	return timeline;
}

ScaleTimelineWrapper *AnimationCreator::createScaleTimeline(int boneIndex, int frameCount)
{
	ScaleTimelineWrapper *timeline = new(__FILE__, __LINE__) ScaleTimelineWrapper(frameCount);
	timeline->setBoneIndex(boneIndex);
	return timeline;
}

ShearTimelineWrapper *AnimationCreator::createShearTimeline(int boneIndex, int frameCount)
{
	ShearTimelineWrapper *timeline = new(__FILE__, __LINE__) ShearTimelineWrapper(frameCount);
	timeline->setBoneIndex(boneIndex);
	return timeline;
}

TransformConstraintTimelineWrapper *AnimationCreator::createTransformConstraintTimeline(int frameCount)
{
	TransformConstraintTimelineWrapper *timeline = new(__FILE__, __LINE__) TransformConstraintTimelineWrapper(frameCount);
	return timeline;
}

TranslateTimelineWrapper *AnimationCreator::createTranslateTimeline(int boneIndex, int frameCount)
{
	TranslateTimelineWrapper *timeline = new(__FILE__, __LINE__) TranslateTimelineWrapper(frameCount);
	timeline->setBoneIndex(boneIndex);
	return timeline;
}

TwoColorTimelineWrapper *AnimationCreator::createTwoColorTimeline(int slotIndex, int frameCount)
{
	TwoColorTimelineWrapper *timeline = new(__FILE__, __LINE__) TwoColorTimelineWrapper(frameCount);
	timeline->setSlotIndex(slotIndex);
	return timeline;
}




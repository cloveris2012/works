#pragma once
#include "common/skel.h"
#include "wrapper/animations/AnimationWrapper.h"
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

class AnimationCreator {

public:
	static AnimationWrapper *createAnimation(std::string name, float duration);
	static AttachmentTimelineWrapper *createAttachmentTimeline(int slotIndex, int frameCount);
	static ColorTimelineWrapper *createColorTimeline(int slotIndex, int frameCount);
	static DeformTimelineWrapper *createDeformTimeline(int slotIndex, skel::VertexAttachment *inValue, int frameCount);
	static DrawOrderTimelineWrapper *createDrawOrderTimeline(int frameCount);
	static EventTimelineWrapper *createEventTimeline(int frameCount);
	static IkConstraintTimelineWrapper *createIkConstraintTimeline(int frameCount);
	static PathConstraintMixTimelineWrapper *createPathConstraintMixTimeline(int frameCount);
	static PathConstraintPositionTimelineWrapper *createPathConstraintPositionTimeline(int frameCount);
	static PathConstraintSpacingTimelineWrapper *createPathConstraintSpacingTimeline(int frameCount);
	static RotateTimelineWrapper *createRotateTimeline(int boneIndex, int frameCount);
	static ScaleTimelineWrapper *createScaleTimeline(int boneIndex, int frameCount);
	static ShearTimelineWrapper *createShearTimeline(int boneIndex, int frameCount);
	static TransformConstraintTimelineWrapper *createTransformConstraintTimeline(int frameCount);
	static TranslateTimelineWrapper *createTranslateTimeline(int boneIndex, int frameCount);
	static TwoColorTimelineWrapper *createTwoColorTimeline(int slotIndex, int frameCount);
};
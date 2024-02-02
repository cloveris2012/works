#include "PathConstraintSpacingTimeline.h"

#include "../../Skeleton.h"
#include "../../entities/Event.h"

#include "../Animation.h"
#include "../../config/TimelineType.h"
#include "../../entities/Slot.h"
#include "../../data/SlotData.h"
#include "../../entities/PathConstraint.h"
#include "../../data/PathConstraintData.h"

using namespace skel;

RTTI_IMPL(PathConstraintSpacingTimeline, PathConstraintPositionTimeline)

PathConstraintSpacingTimeline::PathConstraintSpacingTimeline(int frameCount) : PathConstraintPositionTimeline(
		frameCount) {
}

void PathConstraintSpacingTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents,
	float alpha, MixBlend blend, MixDirection direction
) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);
	SP_UNUSED(direction);

	PathConstraint *constraintP = skeleton._pathConstraints[_pathConstraintIndex];
	PathConstraint &constraint = *constraintP;
	if (!constraint.isActive()) return;

	if (time < _frames[0]) {
		switch (blend) {
		case MixBlend_Setup:
			constraint._spacing = constraint._data._spacing;
			return;
		case MixBlend_First:
			constraint._spacing += (constraint._data._spacing - constraint._spacing) * alpha;
			return;
		default:
			return;
		}
	}

	float spacing;
	if (time >= _frames[_frames.size() - ENTRIES]) {
		// Time is after last frame.
		spacing = _frames[_frames.size() + PREV_VALUE];
	} else {
		// Interpolate between the previous frame and the current frame.
		int frame = Animation::binarySearch(_frames, time, ENTRIES);
		spacing = _frames[frame + PREV_VALUE];
		float frameTime = _frames[frame];
		float percent = getCurvePercent(frame / ENTRIES - 1,
			1 - (time - frameTime) / (_frames[frame + PREV_TIME] - frameTime));

		spacing += (_frames[frame + VALUE] - spacing) * percent;
	}

	if (blend == MixBlend_Setup)
		constraint._spacing = constraint._data._spacing + (spacing - constraint._data._spacing) * alpha;
	else
		constraint._spacing += (spacing - constraint._spacing) * alpha;
}

int PathConstraintSpacingTimeline::getPropertyId() {
	return ((int) TimelineType_PathConstraintSpacing << 24) + _pathConstraintIndex;
}

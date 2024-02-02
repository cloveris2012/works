#pragma once

#include "common/skel.h"
#include "common/SkelString.h"

class PathConstraintSpacingTimelineWrapper : public skel::PathConstraintSpacingTimeline {
public:
	PathConstraintSpacingTimelineWrapper(int frameCount);
};

#pragma once

#include "common/skel.h"
#include "common/SkelString.h"

class PathConstraintPositionTimelineWrapper : public skel::PathConstraintPositionTimeline {
public:
	PathConstraintPositionTimelineWrapper(int frameCount);
};

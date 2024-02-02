#pragma once

#include "common/skel.h"
#include "common/SkelString.h"

class CurveTimelineWrapper : public skel::CurveTimeline {
public:
	CurveTimelineWrapper(int frameCount);
};

#ifndef ANIMATION_STATE_DATA_WRAPPER_H
#define ANIMATION_STATE_DATA_WRAPPER_H

#include "data/AnimationStateData.h"
#include "common/skel.h"
#include "common/SkelString.h"
using namespace skel;

class AnimationStateDataWrapper : public AnimationStateData {
public:
	AnimationStateDataWrapper(SkeletonData* skeletonData);
};

#endif
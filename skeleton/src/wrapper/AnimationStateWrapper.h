#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H

#include "SkeletonWrapper.h"
#include "common/skel.h"

class AnimationStateWrapper : public skel::AnimationStateExtend {
public:
	AnimationStateWrapper(skel::AnimationStateData *data);
	TrackEntry *setAnimationByName(size_t trackIndex, const char *animationName, int loopCount);
};

#endif
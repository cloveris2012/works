#include "AnimationStateWrapper.h"
#include "utils/LuaEx.h"
#include <iostream>
using namespace skel;

AnimationStateWrapper::AnimationStateWrapper(AnimationStateData *data) : AnimationStateExtend(data) {

}

TrackEntry *AnimationStateWrapper::setAnimationByName(size_t trackIndex, const char *animationName, int loopCount) {
	return AnimationState::setAnimation(trackIndex, animationName, loopCount);
}
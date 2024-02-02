#include "AnimationStateExtend.h"
#include "wrapper/SkeletonWrapper.h"
#include <iostream>
using namespace skel;

AnimationStateExtend::AnimationStateExtend(AnimationStateData *data) : AnimationState(data) {

}

TrackEntry * AnimationStateExtend::setAnimationByName(size_t trackIndex, const char *animationName, int loopCount) {
	return setAnimation(trackIndex, animationName, loopCount);
}

TrackEntry * AnimationStateExtend::addAnimationByName(size_t trackIndex, const char *animationName, int loopCount,float delay) {
	return addAnimation(trackIndex, animationName, loopCount, delay);
}

void AnimationStateExtend::setListener(LuaIntf::LuaRef listener) {

	AnimationStateListenerObjectWrapper *object = new AnimationStateListenerObjectWrapper(listener);
	object->_listener.retainInMainThread();
	AnimationState::setListener(object);
}

int AnimationStateExtend::getAnimationStateId()
{
	return id;
}

bool AnimationStateExtend::apply(SkeletonWrapper *skeleton)
{   
	return AnimationState::apply(*dynamic_cast<Skeleton *>(skeleton));
}


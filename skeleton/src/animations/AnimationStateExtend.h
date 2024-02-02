#ifndef ANIMATION_STATE_EXTEND_H
#define ANIMATION_STATE_EXTEND_H

#include "common/skel.h"
#include "LuaIntf/LuaIntf.h"

class SkeletonWrapper;

namespace skel {

	class AnimationStateListenerObjectWrapper : public AnimationStateListenerObject {
	public:
		AnimationStateListenerObjectWrapper(LuaIntf::LuaRef listener) : _listener(listener) { };
		virtual void callback(AnimationState* state, EventType type, TrackEntry* entry, Event* event) {
			if (_listener != nullptr) {
				_listener.call(type, entry, event);
			}
		}
	public:
		LuaIntf::LuaRef _listener;
	};

	class AnimationStateExtend : public AnimationState {
	public:
		AnimationStateExtend(AnimationStateData *data);
		TrackEntry * setAnimationByName(size_t trackIndex, const char *animationName, int loopCount);
		TrackEntry * addAnimationByName(size_t trackIndex, const char * animationName, int loopCount, float delay);
		std::size_t id = 0;
		void setListener(LuaIntf::LuaRef listener);
		int getAnimationStateId();
		bool apply(SkeletonWrapper *skeleton);
	};

}

#endif
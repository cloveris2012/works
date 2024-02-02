#ifndef Skel_Timeline_h
#define Skel_Timeline_h

#include "common/RTTI.h"
#include "common/Vector.h"
#include "config/MixBlend.h"
#include "config/MixDirection.h"
#include "common/SkelObject.h"

namespace skel {
class Skeleton;

class Event;

class SK_API Timeline : public SkelObject {
RTTI_DECL

public:
	Timeline();

	virtual ~Timeline();

	/// Sets the value(s) for the specified time.
	/// @param skeleton The skeleton the timeline is being applied to. This provides access to the bones, slots, and other skeleton components the timeline may change.
	/// @param lastTime lastTime The time this timeline was last applied. Timelines such as EventTimeline trigger only at specific times rather than every frame. In that case, the timeline triggers everything between lastTime (exclusive) and time (inclusive).
	/// @param time The time within the animation. Most timelines find the key before and the key after this time so they can interpolate between the keys.
	/// @param pEvents If any events are fired, they are added to this array. Can be NULL to ignore firing events or if the timeline does not fire events. May be NULL.
	/// @param alpha alpha 0 applies the current or setup pose value (depending on pose parameter). 1 applies the timeline
	///	value. Between 0 and 1 applies a value between the current or setup pose and the timeline value. By adjusting alpha over
	///	time, an animation can be mixed in or out. alpha can also be useful to apply animations on top of each other (layered).
	/// @param blend Controls how mixing is applied when alpha is than 1.
	/// @param direction Indicates whether the timeline is mixing in or out. Used by timelines which perform instant transitions such as DrawOrderTimeline and AttachmentTimeline.
	virtual void
	apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha, MixBlend blend,
		MixDirection direction) = 0;

	virtual int getPropertyId() = 0;
};
}

#endif /* Skel_Timeline_h */

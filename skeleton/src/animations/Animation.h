#ifndef Skel_Animation_h
#define Skel_Animation_h

#include "common/Vector.h"
#include "common/HashMap.h"
#include "config/MixBlend.h"
#include "config/MixDirection.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"

namespace skel {
class Timeline;

class Skeleton;

class Event;

class SK_API Animation : public SkelObject {
	friend class AnimationState;

	friend class TrackEntry;

	friend class AnimationStateData;

	friend class AttachmentTimeline;

	friend class ColorTimeline;

	friend class DeformTimeline;

	friend class DrawOrderTimeline;

	friend class EventTimeline;

	friend class IkConstraintTimeline;

	friend class PathConstraintMixTimeline;

	friend class PathConstraintPositionTimeline;

	friend class PathConstraintSpacingTimeline;

	friend class RotateTimeline;

	friend class ScaleTimeline;

	friend class ShearTimeline;

	friend class TransformConstraintTimeline;

	friend class TranslateTimeline;

	friend class TwoColorTimeline;

public:
	Animation(const String &name, Vector<Timeline *> &timelines, float duration);

	~Animation();

	/// Applies all the animation's timelines to the specified skeleton.
	/// See also Timeline::apply(Skeleton&, float, float, Vector, float, MixPose, MixDirection)
	void apply(Skeleton &skeleton, float lastTime, float time, bool loop, Vector<Event *> *pEvents, float alpha,
		MixBlend blend, MixDirection direction);

	const String &getName();

	Vector<Timeline *> &getTimelines();

	bool hasTimeline(int id);

	float getDuration();

	void setDuration(float inValue);



protected:
	Vector<Timeline *> _timelines;
	HashMap<int, bool> _timelineIds;
	float _duration;
	String _name;

	/// @param target After the first and before the last entry.
	static int binarySearch(Vector<float> &values, float target, int step);

	/// @param target After the first and before the last entry.
	static int binarySearch(Vector<float> &values, float target);

	static int linearSearch(Vector<float> &values, float target, int step);
};
}

#endif /* Skel_Animation_h */

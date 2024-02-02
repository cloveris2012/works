#ifndef Skel_Event_h
#define Skel_Event_h

#include "common/SkelObject.h"
#include "common/SkelString.h"

namespace skel {
class EventData;

/// Stores the current pose values for an Event.
class SK_API Event : public SkelObject {
	friend class SkeletonBinary;

	friend class SkeletonJson;

	friend class AnimationState;

public:
	Event(float time, const EventData &data);

	const EventData &getData();

	/// The animation time this event was keyed.
	float getTime();

	int getIntValue();

	void setIntValue(int inValue);

	float getFloatValue();

	void setFloatValue(float inValue);

	const String &getStringValue();

	void setStringValue(const String &inValue);

	float getVolume();

	void setVolume(float inValue);

	float getBalance();

	void setBalance(float inValue);

private:
	const EventData &_data;
	const float _time;
	int _intValue;
	float _floatValue;
	String _stringValue;
	float _volume;
	float _balance;
};
}

#endif /* Skel_Event_h */

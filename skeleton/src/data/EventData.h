#ifndef Skel_EventData_h
#define Skel_EventData_h

#include "common/SkelObject.h"
#include "common/SkelString.h"

namespace skel {
/// Stores the setup pose values for an Event.
class SK_API EventData : public SkelObject {
	friend class SkeletonBinary;

	friend class SkeletonJson;

	friend class Event;

public:
	explicit EventData(const String &name);

	/// The name of the event, which is unique within the skeleton.
	const String &getName() const;

	int getIntValue() const;

	void setIntValue(int inValue);

	float getFloatValue()  const;

	void setFloatValue(float inValue);

	const String &getStringValue()  const;

	void setStringValue(const String &inValue);

	const String &getAudioPath()  const;

	void setAudioPath(const String &inValue);

	float getVolume() const;

	void setVolume(float inValue);

	float getBalance() const;

	void setBalance(float inValue);

protected:
	String _name;
	int _intValue;
	float _floatValue;
	String _stringValue;
	String _audioPath;
	float _volume;
	float _balance;
};
}

#endif /* Skel_EventData_h */

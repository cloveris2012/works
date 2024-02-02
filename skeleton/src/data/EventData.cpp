#include "EventData.h"

#include <assert.h>

skel::EventData::EventData(const skel::String &name) :
		_name(name),
		_intValue(0),
		_floatValue(0),
		_stringValue(),
		_audioPath(),
		_volume(1),
		_balance(0) {
	assert(_name.length() > 0);
}

/// The name of the event, which is unique within the skeleton.
const skel::String &skel::EventData::getName() const {
	return _name;
}

int skel::EventData::getIntValue() const {
	return _intValue;
}

void skel::EventData::setIntValue(int inValue) {
	_intValue = inValue;
}

float skel::EventData::getFloatValue() const {
	return _floatValue;
}

void skel::EventData::setFloatValue(float inValue) {
	_floatValue = inValue;
}

const skel::String &skel::EventData::getStringValue() const {
	return _stringValue;
}

void skel::EventData::setStringValue(const skel::String &inValue) {
	this->_stringValue = inValue;
}

const skel::String &skel::EventData::getAudioPath() const {
	return _audioPath;
}

void skel::EventData::setAudioPath(const skel::String &inValue) {
	_audioPath = inValue;
}


float skel::EventData::getVolume() const {
	return _volume;
}

void skel::EventData::setVolume(float inValue) {
	_volume = inValue;
}

float skel::EventData::getBalance() const {
	return _balance;
}

void skel::EventData::setBalance(float inValue) {
	_balance = inValue;
}

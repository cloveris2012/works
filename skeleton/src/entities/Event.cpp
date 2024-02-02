#include "Event.h"

#include "../data/EventData.h"

skel::Event::Event(float time, const skel::EventData &data) :
		_data(data),
		_time(time),
		_intValue(0),
		_floatValue(0),
		_stringValue(),
		_volume(1),
		_balance(0) {
}

const skel::EventData &skel::Event::getData() {
	return _data;
}

float skel::Event::getTime() {
	return _time;
}

int skel::Event::getIntValue() {
	return _intValue;
}

void skel::Event::setIntValue(int inValue) {
	_intValue = inValue;
}

float skel::Event::getFloatValue() {
	return _floatValue;
}

void skel::Event::setFloatValue(float inValue) {
	_floatValue = inValue;
}

const skel::String &skel::Event::getStringValue() {
	return _stringValue;
}

void skel::Event::setStringValue(const skel::String &inValue) {
	_stringValue = inValue;
}


float skel::Event::getVolume() {
	return _volume;
}

void skel::Event::setVolume(float inValue) {
	_volume = inValue;
}

float skel::Event::getBalance() {
	return _balance;
}

void skel::Event::setBalance(float inValue) {
	_balance = inValue;
}

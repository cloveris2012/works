#include "EventDataWrapper.h"
#include <iostream>
using namespace skel;

EventDataWrapper::EventDataWrapper(const String &name) : EventData(name) {

}

std::string EventDataWrapper::getName() {
	return _name.buffer();
}

void EventDataWrapper::setName(std::string name) {
	_name = name.data();
}

const std::string EventDataWrapper::getStringValue() const {
	if (_stringValue == nullptr)
		return "";
	return _stringValue.buffer();
}

void EventDataWrapper::setStringValue(const std::string &inValue) {
	_stringValue = inValue.data();
}

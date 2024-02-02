#ifndef EVENT_DATA_WRAPPER_H
#define EVENT_DATA_WRAPPER_H

#include "data/EventData.h"
#include "common/skel.h"
#include "common/SkelString.h"
using namespace skel;

class EventDataWrapper : public EventData {
public:
	EventDataWrapper(const String &name);
	std::string getName();
	void setName(std::string name);
	const std::string getStringValue()  const;
	void setStringValue(const std::string &inValue);
};

#endif
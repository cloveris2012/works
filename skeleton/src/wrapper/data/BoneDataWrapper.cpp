#include "BoneDataWrapper.h"
#include <iostream>
using namespace skel;

BoneDataWrapper::BoneDataWrapper(int index, const String &name, BoneData *parent) : BoneData(index, name, parent) {

}

Color &BoneDataWrapper::getColor() {
	return _color;
}

std::string BoneDataWrapper::getParentName(){
	auto parent = getParent();
	if (parent) {
		std::string pname = parent->getName().buffer();
		return pname;
	}
	return "";
}

std::string BoneDataWrapper::getWrapperName(){
    std::string name = getName().buffer();
    return name;
}

void BoneDataWrapper::setName(const char* name) {
	skel::String str(name);
	_name = str;
}
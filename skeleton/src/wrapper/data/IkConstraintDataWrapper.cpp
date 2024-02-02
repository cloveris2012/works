#include "IkConstraintDataWrapper.h"
#include <iostream>
using namespace skel;

IkConstraintDataWrapper::IkConstraintDataWrapper(const String& name) : IkConstraintData(name) {

}

std::string IkConstraintDataWrapper::getName() {
	return IkConstraintData::getName().buffer();
}


size_t IkConstraintDataWrapper::getBoneDataCount() {
	return _bones.size();
}

BoneDataWrapper *IkConstraintDataWrapper::getBoneData(size_t index) {
	return dynamic_cast<BoneDataWrapper*>(_bones[index]);
}

BoneDataWrapper *IkConstraintDataWrapper::getTarget() {
	return dynamic_cast<BoneDataWrapper*>(_target);
}
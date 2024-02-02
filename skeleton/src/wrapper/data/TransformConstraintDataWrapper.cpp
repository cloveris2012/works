#include "TransformConstraintDataWrapper.h"
#include <iostream>
using namespace skel;

TransformConstraintDataWrapper::TransformConstraintDataWrapper(const String& name) : TransformConstraintData(name) {

}

std::string TransformConstraintDataWrapper::getName() {
	return TransformConstraintData::getName().buffer();
}


size_t TransformConstraintDataWrapper::getBoneDataCount() {
	return _bones.size();
}

BoneDataWrapper *TransformConstraintDataWrapper::getBoneData(size_t index) {
	return dynamic_cast<BoneDataWrapper*>(_bones[index]);
}

BoneDataWrapper *TransformConstraintDataWrapper::getTarget() {
	return dynamic_cast<BoneDataWrapper*>(_target);
}

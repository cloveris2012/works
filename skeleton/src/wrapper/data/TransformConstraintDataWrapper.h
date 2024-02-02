#ifndef TRANSFORM_CONSTRAINT_DATA_WRAPPER_H
#define TRANSFORM_CONSTRAINT_DATA_WRAPPER_H

#include "data/TransformConstraintData.h"
#include "common/skel.h"
#include "common/SkelString.h"
#include "BoneDataWrapper.h"
using namespace skel;

class TransformConstraintDataWrapper : public TransformConstraintData {
public:
	TransformConstraintDataWrapper(const String& name);
	std::string getName();
	size_t getBoneDataCount();
	BoneDataWrapper *getBoneData(size_t index);
	BoneDataWrapper* getTarget();
};

#endif
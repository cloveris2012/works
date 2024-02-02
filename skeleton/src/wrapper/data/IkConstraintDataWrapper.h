#ifndef IK_CONSTRAINT_DATA_WRAPPER_H
#define IK_CONSTRAINT_DATA_WRAPPER_H

#include "data/IkConstraintData.h"
#include "common/skel.h"
#include "common/SkelString.h"
#include "BoneDataWrapper.h"
using namespace skel;

class IkConstraintDataWrapper : public IkConstraintData {
public:
	IkConstraintDataWrapper(const String& name);
	std::string getName();
	size_t getBoneDataCount();
	BoneDataWrapper *getBoneData(size_t index);
	BoneDataWrapper* getTarget();
};

#endif
#ifndef PATH_CONSTRAINT_DATA_WRAPPER_H
#define PATH_CONSTRAINT_DATA_WRAPPER_H

#include "data/PathConstraintData.h"
#include "common/skel.h"
#include "common/SkelString.h"
using namespace skel;

class PathConstraintDataWrapper : public PathConstraintData {
public:
	PathConstraintDataWrapper(const String& name);
};

#endif
#ifndef BONE_DATA_WRAPPER_H
#define BONE_DATA_WRAPPER_H

#include "data/BoneData.h"
#include "common/skel.h"
#include "common/SkelString.h"
using namespace skel;

class BoneDataWrapper : public BoneData {
public:
	BoneDataWrapper(int index, const String &name, BoneData *parent = NULL);

	std::string getParentName();
	std::string getWrapperName();
	void setName(const char * name);
	Color &getColor();

private:
	Color _color;
	
};

#endif
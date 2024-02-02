#pragma once

#include "common/skel.h"
#include "common/SkelString.h"
#include "LuaIntf/LuaIntf.h"
#include <map>

class CurveData {
public:
	// -1表示未定义
	float curve = -1;
	float c2 = -1;
	float c3 = -1;
	float c4 = -1;
	short stepped = -1;
};

class CurveDataWrapper {
public:
	void setStepped(size_t frameIndex);
	void setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2);
	void fillCurveData(size_t index, LuaIntf::LuaRef &ref);
	void readCurveData(LuaIntf::LuaTableIterator iter, skel::CurveTimeline *timeline, size_t frameIndex);
protected:
	std::map<size_t, CurveData> _curveDatas;
};



#include "CurveDataWrapper.h"
#include <iostream>

void CurveDataWrapper::setStepped(size_t frameIndex) {
	CurveData data;
	data.stepped = 1;
	_curveDatas[frameIndex] = data;
}

void CurveDataWrapper::setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) {
	CurveData data;
	data.curve = cx1;
	data.c2 = cy1;
	data.c3 = cx2;
	data.c4 = cy2;
	_curveDatas[frameIndex] = data;
}

void CurveDataWrapper::fillCurveData(size_t index, LuaIntf::LuaRef &ref) {
	auto iter = _curveDatas.find(index);
	if (iter != _curveDatas.end()) {
		auto &data = iter->second;

		if (data.stepped != -1)
			ref.set<std::string, std::string>("curve", "stepped");

		if (data.curve != -1)
			ref.set<std::string, float>("curve", data.curve);

		if (data.c2 != -1)
			ref.set<std::string, float>("c2", data.c2);

		if (data.c3 != -1)
			ref.set<std::string, float>("c3", data.c3);

		if (data.c4 != -1)
			ref.set<std::string, float>("c4", data.c4);
	}
	
}

void CurveDataWrapper::readCurveData(LuaIntf::LuaTableIterator iter, skel::CurveTimeline *timeline, size_t frameIndex) {
	const auto &curve = iter.value().get("curve");
	if (!curve) return;
	if ((strcmp(curve.typeName(), "string") == 0) && (curve.toValue<std::string>().compare("stepped") == 0))
		timeline->setStepped(frameIndex);
	else {
		float c1 = curve.toValue<float>();  // 0
		float c2 = iter.value().get("c2").toValue<float>(); // 0
		float c3 = iter.value().get("c3").toValue<float>(); // 1
		float c4 = iter.value().get("c4").toValue<float>(); // 1
		timeline->setCurve(frameIndex, c1, c2, c3, c4);
	}
}

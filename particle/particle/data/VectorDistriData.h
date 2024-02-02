#pragma once
#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "Configs.h"

using vec3 = glm::vec3;

typedef struct VectorConstantCurveData
{
	int m_title;
	float m_inVal;
	vec3 m_outVal;
	vec3 m_arriveTan;
	vec3 m_leaveTan;
	int m_mode;

	VectorConstantCurveData(int title, float inVal, vec3 outVal, vec3 arriveTan, vec3 leaveTan, int mode)
		: m_title(title)
		, m_inVal(inVal)
		, m_outVal(outVal)
		, m_arriveTan(arriveTan)
		, m_leaveTan(leaveTan)
		, m_mode(mode)
	{}

} VectorConstantCurveData;

typedef struct VectorUniformCurveData
{
	int m_title;
	float m_inVal;
	vec3 m_outVal1;
	vec3 m_outVal2;
	vec3 m_arriveTan1;
	vec3 m_arriveTan2;
	vec3 m_leaveTan1;
	vec3 m_leaveTan2;
	int m_mode;

	VectorUniformCurveData(int title, float inVal, vec3 outVal1, vec3 outVal2, vec3 arriveTan1, vec3 arriveTan2, vec3 leaveTan1, vec3 leaveTan2, int mode)
		: m_title(title)
		, m_inVal(inVal)
		, m_outVal1(outVal1)
		, m_outVal2(outVal2)
		, m_arriveTan1(arriveTan1)
		, m_arriveTan2(arriveTan2)
		, m_leaveTan1(leaveTan1)
		, m_leaveTan2(leaveTan2)
		, m_mode(mode)
	{}
} VectorUniformCurveData;


typedef struct VectorDistriData
{
	VectorDistriData(std::string attriName = "---", int flags = 0, vec3 cons = vec3(), vec3 min = vec3(), vec3 max = vec3(), int type = 0, int distriType = 0, bool isLoop = false, bool isBaked = false)
		: m_flags(flags)
		, m_cons(cons)
		, m_min(min)
		, m_max(max)
		, m_type(type)
		, m_distriType(distriType)
		, m_loop(isLoop)
		, m_baked(isBaked)
	{}

	std::string m_attriName;
	int m_flags;
	vec3 m_cons;
	vec3 m_min;
	vec3 m_max;
	int m_type;
	int m_distriType;
	bool m_loop;
	bool m_baked;
	std::vector<VectorConstantCurveData*> m_curveList;
	std::vector<VectorUniformCurveData*> m_uniformCurveList;

} VectorDistriData;


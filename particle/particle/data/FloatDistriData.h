#pragma once
#include <iostream>
#include <vector>

#include "Configs.h"

typedef struct FloatConstantCurveData
{
	int m_title;
	float m_inVal;
	float m_outVal;
	float m_arriveTan;
	float m_leaveTan;
	int m_mode;

	FloatConstantCurveData(int title, float inVal, float outVal, float arriveTan, float leaveTan, int mode)
		: m_title(title)
		, m_inVal(inVal)
		, m_outVal(outVal)
		, m_arriveTan(arriveTan)
		, m_leaveTan(leaveTan)
		, m_mode(mode)
	{}

} FloatConstantCurveData;

typedef struct FloatUniformCurveData
{
	int m_title;
	float m_inVal;
	float m_outVal1;
	float m_outVal2;
	float m_arriveTan1;
	float m_arriveTan2;
	float m_leaveTan1;
	float m_leaveTan2;
	int m_mode;

	FloatUniformCurveData(int title, float inVal, float outVal1, float outVal2, float arriveTan1, float arriveTan2, float leaveTan1, float leaveTan2, int mode)
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

} FloatUniformCurveData;

typedef struct FloatDistriData
{
	FloatDistriData(std::string attriName = "---", int flags = 0, float cons = 0, float min = 0, float max = 0, int type = 0, int distriType = 0, bool isLoop = false, bool isBaked = false)
		: m_attriName(attriName)
		, m_flags(flags)
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
	float m_cons;
	float m_min;
	float m_max;
	int m_type;
	int m_distriType;
	bool m_loop;
	bool m_baked;
	std::vector<FloatConstantCurveData*> m_curveList;
	std::vector<FloatUniformCurveData*> m_uniformCurveList;

} FloatDistriData;


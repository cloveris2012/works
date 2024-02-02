#include "FloatUniformCurve.h"
//using json = nlohmann::json;

FloatUniformCurve::FloatUniformCurve(int title, 
	                                 float inVal, 
	                                 float outVal1, float outVal2, 
	                                 float arriveTan1, float arriveTan2, 
	                                 float leaveTan1, float leaveTan2, 
	                                 int mode)
	: m_title(title)
	, m_inVal(inVal)
	, m_outVal1(outVal1)
	, m_outVal2(outVal2)
	, m_arriveTan1(arriveTan1)
	, m_arriveTan2(arriveTan2)
	, m_leaveTan1(leaveTan1)
	, m_leaveTan2(leaveTan2)
	, m_mode(mode)
{
}

int FloatUniformCurve::title()
{
	return m_title;
}

void FloatUniformCurve::setTitle(int title)
{
	m_title = title;
}

float FloatUniformCurve::inVal()
{
	return m_inVal;
}

void FloatUniformCurve::setInVal(float inVal)
{
	m_inVal = inVal;
}

float FloatUniformCurve::outVal1()
{
	return m_outVal1;
}

void FloatUniformCurve::setOutVal1(float outVal1)
{
	m_outVal1 = outVal1;
}

float FloatUniformCurve::outVal2()
{
	return m_outVal2;
}

void FloatUniformCurve::setOutVal2(float outVal2)
{
	m_outVal2 = outVal2;
}

float FloatUniformCurve::arriveTan1()
{
	return m_arriveTan1;
}

void FloatUniformCurve::setArriveTan1(float arriveTan1)
{
	m_arriveTan1 = arriveTan1;
}

float FloatUniformCurve::arriveTan2()
{
	return m_arriveTan2;
}

void FloatUniformCurve::setArriveTan2(float arriveTan2)
{
	m_arriveTan2 = arriveTan2;
}

float FloatUniformCurve::leaveTan1()
{
	return m_leaveTan1;
}

void FloatUniformCurve::setLeaveTan1(float leaveTan1)
{
	m_leaveTan1 = leaveTan1;
}

float FloatUniformCurve::leaveTan2()
{
	return m_leaveTan2;
}

void FloatUniformCurve::setLeaveTan2(float leaveTan2)
{
	m_leaveTan2 = leaveTan2;
}

int FloatUniformCurve::mode()
{
	return m_mode;
}

void FloatUniformCurve::setMode(int mode)
{
	m_mode = mode;
}

//void FloatUniformCurve::setData(json data)
//{
//	m_title = data[0];
//	m_inVal = data[1];
//	m_outVal1 = data[2];
//	m_outVal2 = data[3];
//	m_arriveTan1 = data[4];
//	m_arriveTan2 = data[5];
//	m_leaveTan1 = data[6];
//	m_leaveTan2 = data[7];
//	m_mode = data[8];
//}
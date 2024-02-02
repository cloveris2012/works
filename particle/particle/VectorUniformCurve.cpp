#include "VectorUniformCurve.h"

//using json = nlohmann::json;
using vec3 = glm::vec3;

VectorUniformCurve::VectorUniformCurve(int title, 
	                                   float inVal, 
	                                   vec3 outVal1, vec3 outVal2, 
	                                   vec3 arriveTan1, vec3 arriveTan2, 
	                                   vec3 leaveTan1, vec3 leaveTan2, 
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

int VectorUniformCurve::title()
{
	return m_title;
}

void VectorUniformCurve::setTitle(int title)
{
	m_title = title;
}

float VectorUniformCurve::inVal()
{
	return m_inVal;
}

void VectorUniformCurve::setInVal(float inVal)
{
		m_inVal = inVal;
}

vec3 VectorUniformCurve::outVal1()
{
	return m_outVal1;
}

void VectorUniformCurve::setOutVal1(vec3 outVal1)
{
	m_outVal1 = outVal1;
}

vec3 VectorUniformCurve::outVal2()
{
	return m_outVal2;
}

void VectorUniformCurve::setOutVal2(vec3 outVal2)
{
	m_outVal2 = outVal2;
}

vec3 VectorUniformCurve::arriveTan1()
{
	return m_arriveTan1;
}

void VectorUniformCurve::setArriveTan1(vec3 arriveTan1)
{
	m_arriveTan1 = arriveTan1;
}

vec3 VectorUniformCurve::arriveTan2()
{
	return m_arriveTan2;
}

void VectorUniformCurve::setArriveTan2(vec3 arriveTan2)
{
	m_arriveTan2 = arriveTan2;
}

vec3 VectorUniformCurve::leaveTan1()
{
	return m_leaveTan1;
}

void VectorUniformCurve::setLeaveTan1(vec3 leaveTan1)
{
	m_leaveTan1 = leaveTan1;
}

vec3 VectorUniformCurve::leaveTan2()
{
	return m_leaveTan2;
}

void VectorUniformCurve::setLeaveTan2(vec3 leaveTan2)
{
	m_leaveTan2 = leaveTan2;
}

int VectorUniformCurve::mode()
{
	return m_mode;
}

void VectorUniformCurve::setMode(int mode)
{
	m_mode = mode;
}

//void VectorUniformCurve::setData(json data)
//{
//	m_title = data[0];
//	m_inVal = data[1];
//
//	json outVal1 = data[2];
//    m_outVal1 = vec3(outVal1[0], outVal1[1], outVal1[2]);
//	json outVal2 = data[3];
//	m_outVal2 = vec3(outVal2[0], outVal2[1], outVal2[2]);
//	json arriveTan1 = data[4];
//	m_arriveTan1 = vec3(arriveTan1[0], arriveTan1[1], arriveTan1[2]);
//	json arriveTan2 = data[5];
//	m_arriveTan2 = vec3(arriveTan2[0], arriveTan2[1], arriveTan2[2]);
//	json leaveTan1 = data[6];
//	m_leaveTan1 = vec3(leaveTan1[0], leaveTan1[1], leaveTan1[2]);
//	json leaveTan2 = data[7];
//	m_leaveTan2 = vec3(leaveTan2[0], leaveTan2[1], leaveTan2[2]);
//	m_mode = data[8];
//}
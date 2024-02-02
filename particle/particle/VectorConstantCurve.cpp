#include "VectorConstantCurve.h"

//using json = nlohmann::json;
using vec3 = glm::vec3;

VectorConstantCurve::VectorConstantCurve(int title, float inVal, vec3 outVal, vec3 arriveTan, vec3 leaveTan, int mode)
	: m_title(title)
	, m_inVal(inVal)
	, m_outVal(outVal)
	, m_arriveTan(arriveTan)
	, m_leaveTan(leaveTan)
	, m_mode(mode)
{

}

int VectorConstantCurve::title()
{
	return m_title;
}

float VectorConstantCurve::inVal()
{
	return m_inVal;
}

vec3 VectorConstantCurve::outVal()
{
	return m_outVal;
}
vec3 VectorConstantCurve::arriveTan()
{
	return m_arriveTan;
}

vec3 VectorConstantCurve::leaveTan()
{
	return m_leaveTan;
}

int VectorConstantCurve::mode()
{
	return m_mode;
}

void VectorConstantCurve::setTitle(int title)
{
	m_title = title;
}

void VectorConstantCurve::setInVal(float inVal)
{
	m_inVal = inVal;
}

void VectorConstantCurve::setOutVal(vec3 outVal)
{
	m_outVal = outVal;
}

void VectorConstantCurve::setArriveTan(vec3 arriveTan)
{
	m_arriveTan = arriveTan;
}

void VectorConstantCurve::setLeaveTan(vec3 leaveTan)
{
	m_leaveTan = leaveTan;
}

void VectorConstantCurve::setMode(int mode)
{
	m_mode = mode;
}

//void VectorConstantCurve::setData(json data)
//{
//	m_title = data[0];
//	m_inVal = data[1];
//
//    json outVal = data[2];
//	m_outVal = vec3(outVal[0], outVal[1], outVal[2]);
//	json arriveTan = data[3];
//	m_arriveTan = vec3(arriveTan[0], arriveTan[1], arriveTan[2]);
//	json leaveTan = data[4];
//	m_arriveTan = vec3(leaveTan[0], leaveTan[1], leaveTan[2]);
//
//	m_mode = data[5];
//}
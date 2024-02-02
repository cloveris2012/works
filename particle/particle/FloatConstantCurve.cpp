#include "FloatConstantCurve.h"

//using json = nlohmann::json;

FloatConstantCurve::FloatConstantCurve(int title, float inVal, float outVal, float arriveTan, float leaveTan, int mode)
	: m_title(title)
	, m_inVal(inVal)
	, m_outVal(outVal)
	, m_arriveTan(arriveTan)
	, m_leaveTan(leaveTan)
	, m_mode(mode)
{

}

int FloatConstantCurve::title()
{
	return m_title;
}

float FloatConstantCurve::inVal()
{
	return m_inVal;
}

float FloatConstantCurve::outVal()
{
	return m_outVal;
}

float FloatConstantCurve::arriveTan()
{
	return m_arriveTan;
}

float FloatConstantCurve::leaveTan()
{
	return m_leaveTan;
}

int FloatConstantCurve::mode()
{
	return m_mode;
}

void FloatConstantCurve::setTitle(int title)
{
	m_title = title;
}

void FloatConstantCurve::setInVal(float inVal)
{
	m_inVal = inVal;
}

void FloatConstantCurve::setOutVal(float outVal)
{
	m_outVal = outVal;
}

void FloatConstantCurve::setArriveTan(float arriveTan)
{
	m_arriveTan = arriveTan;
}

void FloatConstantCurve::setLeaveTan(float leaveTan)
{
	m_leaveTan = leaveTan;
}

void FloatConstantCurve::setMode(int mode)
{
	m_mode = mode;
}

//void FloatConstantCurve::setData(json data)
//{
//	m_title = data[0];
//	m_inVal = data[1];
//	m_outVal = data[2];
//	m_arriveTan = data[3];
//	m_leaveTan = data[4];
//	m_mode = data[5];
//}
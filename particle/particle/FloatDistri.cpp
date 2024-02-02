#include "FloatDistri.h"
#include <math.h>
#include <limits>

//using json = nlohmann::json;
using jsonDoc = rapidjson::Document;
using jsonVal = rapidjson::Value;

FloatDistri::FloatDistri(std::string attriName, int flags, float cons, float min, float max, int type, bool isLoop, bool isBaked)
	: m_attriName(attriName),
	m_flags(flags),
	m_cons(cons),
	m_min(min),
	m_max(max),
	m_type(type),
	m_loop(isLoop),
	m_baked(isBaked)
{
	m_bakedData.SetArray();
}

FloatDistri::~FloatDistri()
{
	for (int i = 0; i < m_curveList.size(); i++)
	{
		auto curve = m_curveList[i];

		delete curve;
	}

	for (int i = 0; i < m_uniformCurveList.size(); i++)
	{
		auto curve = m_uniformCurveList[i];

		delete curve;
	}
}

std::string FloatDistri::attriName()
{
	return m_attriName;
}

float FloatDistri::cons()
{
	return m_cons;
}

float FloatDistri::min()
{
	return m_min;
}

float FloatDistri::max()
{
	return m_max;
}

int FloatDistri::dataType()
{
	return m_type;
}

int FloatDistri::flags()
{
	return m_flags;
}

bool FloatDistri::isLoop()
{
	return m_loop;
}

bool FloatDistri::isBaked()
{
	return m_baked;
}

int FloatDistri::distriType()
{
	return m_distriType;
}

std::vector<FloatConstantCurve*> FloatDistri::curveList()
{
	return m_curveList;
}

std::vector<FloatUniformCurve*> FloatDistri::uniformCurveList()
{
	return m_uniformCurveList;
}

void FloatDistri::setAttriName(std::string name)
{
	m_attriName = name;
}

void FloatDistri::setCons(float cons)
{
	m_cons = cons;
}

void FloatDistri::setMin(float min)
{
	m_min = min;
}

void FloatDistri::setMax(float max)
{
	m_max = max;
}

void FloatDistri::setDataType(int index)
{
	m_type = index;
}

void FloatDistri::setFlags(int flags)
{
	m_flags = flags;
}

void FloatDistri::setIsLoop(bool loop)
{
	m_loop = loop;
}

void FloatDistri::setIsBaked(bool baked)
{
	m_baked = baked;
}

void FloatDistri::setDistriType(int type)
{
	m_distriType = type;
}

float FloatDistri::getMaxValue()
{
	float max = std::numeric_limits<float>::min();

	if (m_type == FloatDistri::CONSTANT)
		max = cons();
	else if (m_type == FloatDistri::UNIFORM)
		max = this->max();
	else if (m_type == FloatDistri::CONSCURVE)
	{
		if (this->isBaked())
		{
			for (int i = 0; i < this->m_bakedData.Size(); i++)
			{
				max = max > m_bakedData[i].GetFloat() ? max : m_bakedData[i].GetFloat();
			}
		}
		else
		{
			if (m_curveList.size() == 0)
				return 0;
			for (int i = 0; i <m_curveList.size(); i++)
			{
				float indexOutVal = m_curveList[i]->outVal();
				max = max > indexOutVal ? max : indexOutVal;
			}
		}

	}
	else if (m_type == FloatDistri::UNIFORMCURVE)
	{
		if (this->isBaked())
		{
			for (int i = 0; i < this->m_bakedData.Size(); i++)
			{
				max = max > m_bakedData[i].GetFloat() ? max : m_bakedData[i].GetFloat();
			}
		}
		else
		{
			if (m_uniformCurveList.size() == 0)
				return 0;
			for (int i = 0; i < m_uniformCurveList.size(); i++)
			{
				float indexOutVal = m_uniformCurveList[i]->outVal1();
				max = max > indexOutVal ? max : indexOutVal;

				indexOutVal = m_uniformCurveList[i]->outVal2();
				max = max > indexOutVal ? max : indexOutVal;
			}
		}
	}

	return max;
}

void FloatDistri::resetData()
{
	m_cons = 0;
	m_min = 0;
	m_max = 0;
	m_curveList.clear();
	m_uniformCurveList.clear();
	m_loop = false;
	m_baked = false;
	m_bakedData.Clear();
}

void FloatDistri::appendList()
{
	m_curveList.push_back(new FloatConstantCurve(m_curveList.size(), 0, 0, 0, 0, 4));
}

void FloatDistri::appendList(FloatConstantCurve * obj)
{
	m_curveList.push_back(obj);
}

void FloatDistri::appendUniformList()
{
	
	m_uniformCurveList.push_back(new FloatUniformCurve(m_uniformCurveList.size(), 0, 0, 0, 0, 0, 0, 0, 4));
}

void FloatDistri::appendUniformList(FloatUniformCurve * obj)
{
	m_uniformCurveList.push_back(obj);
}

void FloatDistri::removeList()
{
	if (!m_curveList.empty())
		m_curveList.pop_back();
}

void FloatDistri::removeUniformList()
{
	if (!m_uniformCurveList.empty())
		m_uniformCurveList.pop_back();
}

float FloatDistri::updateCurve(float val)
{
	if (m_curveList.size() == 0)
		return 0;
	else if (m_curveList.size() == 1)
		return m_curveList[0]->outVal();
	else if (val < m_curveList[0]->inVal())
	    return m_curveList[0]->outVal();
	else if (!m_loop)
	{
		if (val > m_curveList.back()->inVal())
		{
			return m_curveList.back()->outVal();
		}
		else
		{
			for (int i = 0; i < m_curveList.size() - 1; ++i)
			{
				FloatConstantCurve *curve = m_curveList[i];
				FloatConstantCurve *curve1 = m_curveList[i + 1];
				if (curve->inVal() <= val && val <= curve1->inVal())
				{
					float diff = (float)curve1->inVal() - (float)curve->inVal();
					float alpha = (val - (float)curve->inVal()) / diff;

					if (curve->mode() == FloatConstantCurve::ConstantMode)
						return curve->outVal();
					else if (curve->mode() == FloatConstantCurve::LinearMode)
						return this->lerpFloat((float)curve->outVal(), (float)curve1->outVal(), alpha);
					else if (curve->mode() < FloatConstantCurve::LinearMode && curve->mode() >= FloatConstantCurve::AutoMode)
						return this->cubicInterpFloat((float)curve->outVal(), (float)curve->leaveTan(), (float)curve1->outVal(), (float)curve1->arriveTan(), alpha);
				}
			}
		}
	}
	else if(m_loop)
	{
		float length = abs(m_curveList.back()->inVal() - m_curveList.front()->inVal());

		float offset = m_curveList.front()->inVal();

		int step = floor((val - offset) / length);

		float pos = val - (float)step * length;

		for (int i = 0; i < m_curveList.size() - 1; ++i)
		{
			FloatConstantCurve *curve = m_curveList[i];
			FloatConstantCurve *curve1 = m_curveList[i + 1];
			if (curve->inVal() <= pos && pos<= curve1->inVal())
			{
				float diff = (float)curve1->inVal() - (float)curve->inVal();
				float alpha = (pos - (float)curve->inVal()) / diff;

				if (curve->mode() == FloatConstantCurve::ConstantMode)
					return curve->outVal();
				else if (curve->mode() == FloatConstantCurve::LinearMode)
					return this->lerpFloat((float)curve->outVal(), (float)curve1->outVal(), alpha);
				else if (curve->mode() < FloatConstantCurve::LinearMode && curve->mode() >= FloatConstantCurve::AutoMode)
					return this->cubicInterpFloat((float)curve->outVal(), (float)curve->leaveTan(), (float)curve1->outVal(), (float)curve1->arriveTan(), alpha);
			}
		}
	}
}

float FloatDistri::updateUniformCurve(float val)
{
	float v1 = 0;
	float v2 = 0;

	if (m_uniformCurveList.size() == 0)
		return 0;
	else if (m_uniformCurveList.size() == 1)
	{
		v1 = m_uniformCurveList[0]->outVal1();
		v2 = m_uniformCurveList[0]->outVal2();
	}
	else if (val < m_uniformCurveList[0]->inVal())
	{
		v1 = m_uniformCurveList[0]->outVal1();
		v2 = m_uniformCurveList[0]->outVal2();
	}
	else if (!m_loop)
	{
		if (val > m_uniformCurveList.back()->inVal())
		{
			v1 = m_uniformCurveList.back()->outVal1();
			v2 = m_uniformCurveList.back()->outVal2();
		}
		else
		{
			for (int i = 0; i < m_uniformCurveList.size() - 1; ++i)
			{
				if (i < m_uniformCurveList.size() - 1)
				{
					FloatUniformCurve *curve = m_uniformCurveList[i];
					FloatUniformCurve *curve1 = m_uniformCurveList[i + 1];
					if (curve->inVal() <= val && val <= curve1->inVal())
					{
						float diff = (float)curve1->inVal() - (float)curve->inVal();
						float alpha = (val - (float)curve->inVal()) / diff;

						if (curve->mode() == FloatUniformCurve::ConstantMode)
						{
							v1 = curve->outVal1();
							v2 = curve->outVal2();
						}
						else if (curve->mode() == FloatUniformCurve::LinearMode)
						{
							v1 = this->lerpFloat((float)curve->outVal1(), (float)curve1->outVal1(), alpha);
							v2 = this->lerpFloat((float)curve->outVal2(), (float)curve1->outVal2(), alpha);
						}
						else if (curve->mode() < FloatUniformCurve::LinearMode && curve->mode() >= FloatUniformCurve::AutoMode)
						{
							v1 = this->cubicInterpFloat((float)curve->outVal1(), (float)curve->leaveTan1(), (float)curve1->outVal1(), (float)curve1->arriveTan1(), alpha);
							v2 = this->cubicInterpFloat((float)curve->outVal2(), (float)curve->leaveTan2(), (float)curve1->outVal2(), (float)curve1->arriveTan2(), alpha);
						}
					}
				}
			}
		}
	}
	else if (m_loop)
	{
		float length = abs(m_uniformCurveList.back()->inVal() - m_uniformCurveList.front()->inVal());

		float offset = m_uniformCurveList.front()->inVal();

		int step = floor((val - offset) / length);

		float pos = val - (float)step * length;

		for (int i = 0; i < m_uniformCurveList.size() - 1; ++i)
		{
			if (i < m_uniformCurveList.size() - 1)
			{
				FloatUniformCurve *curve = m_uniformCurveList[i];
				FloatUniformCurve *curve1 = m_uniformCurveList[i + 1];
				if (curve->inVal() <= pos && pos <= curve1->inVal())
				{
					float diff = (float)curve1->inVal() - (float)curve->inVal();
					float alpha = (pos - (float)curve->inVal()) / diff;

					if (curve->mode() == FloatUniformCurve::ConstantMode)
					{
						v1 = curve->outVal1();
						v2 = curve->outVal2();
					}
					else if (curve->mode() == FloatUniformCurve::LinearMode)
					{
						v1 = this->lerpFloat((float)curve->outVal1(), (float)curve1->outVal1(), alpha);
						v2 = this->lerpFloat((float)curve->outVal2(), (float)curve1->outVal2(), alpha);
					}
					else if (curve->mode() < FloatUniformCurve::LinearMode && curve->mode() >= FloatUniformCurve::AutoMode)
					{
						v1 = this->cubicInterpFloat((float)curve->outVal1(), (float)curve->leaveTan1(), (float)curve1->outVal1(), (float)curve1->arriveTan1(), alpha);
						v2 = this->cubicInterpFloat((float)curve->outVal2(), (float)curve->leaveTan2(), (float)curve1->outVal2(), (float)curve1->arriveTan2(), alpha);
					}
				}

			}
		}
	}

	m_currentUniformCurveMax = v1;
	m_currentUniformCurveMin = v2;
	return v1 + Random::Instance()->OneFloat() * (v2 - v1);
}


float FloatDistri::lerpFloat(float out0, float out1, float alpha)
{
	return out0 + alpha * (out1 - out0);
}

float FloatDistri::cubicInterpFloat(float out0, float leaveTan, float out1, float arriveTan, float alpha)
{
	const float A2 = alpha * alpha;
	const float A3 = A2 * alpha;

	return (((2 * A3) - (3 * A2) + 1)*out0) + ((A3 - (2 * A2) + alpha) * leaveTan * (out1 - out0)) + ((A3 - A2) * arriveTan * (out1 - out0)) + (((-2 * A3) + (3 * A2))*out1);
}

void FloatDistri::setBakedData(jsonVal &bakedData)
{
	m_bakedData = bakedData;
}

//jsonVal FloatDistri::getBakedData()
//{
//	return m_bakedData;
//}

float FloatDistri::getCurveBaked(float val)
{
	if (m_bakedData.Capacity() == 0)
		return 0;
	int index = floor(val * 60);

	if (this->dataType() == FloatDistri::CONSCURVE)
	{
		if (!m_bakedData[index].IsNumber())
			return m_bakedData[m_bakedData.Size() - 1].GetFloat();

		return m_bakedData[index].GetFloat();
	}
	else if (this->dataType() == FloatDistri::UNIFORMCURVE)
	{	
		float min = m_bakedData[index * 2].GetFloat();
		float max = m_bakedData[index * 2 + 1].GetFloat();

		if (!m_bakedData[index * 2].IsNumber())
			min = m_bakedData[0].GetFloat();
		else
			min = m_bakedData[index * 2].GetFloat();


		if (!m_bakedData[index * 2 + 1].IsNumber())
			max = m_bakedData[m_bakedData.Size() - 1].GetFloat();
		else
			max = m_bakedData[index * 2 + 1].GetFloat();

		return min + Random::Instance()->OneFloat() * (max - min);
	}
}


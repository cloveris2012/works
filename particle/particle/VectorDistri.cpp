#include "VectorDistri.h"
#include <math.h>

using vec3 = glm::vec3;
//using json = nlohmann::json;
using jsonDoc = rapidjson::Document;
using jsonVal = rapidjson::Value;

VectorDistri::VectorDistri(std::string attriName, int flags, vec3 cons, vec3 min, vec3 max, int type, bool isLoop, bool isBaked)
	:m_flags(flags)
	, m_cons(cons)
	, m_min(min)
	, m_max(max)
	, m_type(type)
	, m_loop(isLoop)
	, m_baked(isBaked)
{
	m_bakedData.SetArray();
}

VectorDistri::~VectorDistri()
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

std::string VectorDistri::attriName()
{
	return m_attriName;
}

int VectorDistri::distriType()
{
	return m_distriType;
}

vec3 VectorDistri::cons()
{
	return m_cons;
}

vec3 VectorDistri::min()
{
	return m_min;
}
vec3 VectorDistri::max()
{
	return m_max;
}
int VectorDistri::dataType()
{
	return m_type;
}

int VectorDistri::flags()
{
	return m_flags;
}

bool VectorDistri::isLoop()
{
	return m_loop;
}

bool VectorDistri::isBaked()
{
	return m_baked;
}

std::vector<VectorConstantCurve*> VectorDistri::curveList()
{
	return m_curveList;
}

std::vector<VectorUniformCurve*> VectorDistri::uniformCurveList()
{
	return m_uniformCurveList;
}

void VectorDistri::setAttriName(std::string attriName)
{
	m_attriName = attriName;
}

void VectorDistri::setCons(vec3 cons)
{
	m_cons = cons;
}

void VectorDistri::setMin(vec3 min)
{
	m_min = min;
}
void VectorDistri::setMax(vec3 max)
{
	m_max = max;
}
void VectorDistri::setDataType(int index)
{
	m_type = index;
}

void VectorDistri::setFlags(int flags)
{
	m_flags = flags;
}

void VectorDistri::setIsLoop(bool loop)
{
	m_loop = loop;
}

void VectorDistri::setIsBaked(bool baked)
{
	m_baked = baked;
}

void VectorDistri::setDistriType(int type)
{
	m_distriType = type;
}

void VectorDistri::resetData()
{
	m_cons = vec3(0.0f);
	m_min = vec3(0.0f);
	m_max = vec3(0.0f);
	m_curveList.clear();
	m_uniformCurveList.clear();
	m_loop = false;
	m_bakedData.Clear();
}

void VectorDistri::appendList()
{
	m_curveList.push_back(new VectorConstantCurve(m_curveList.size(), 0, vec3(0.0f), vec3(0.0f), vec3(0.0f), 4));
}

void VectorDistri::appendList(VectorConstantCurve *obj)
{
	m_curveList.push_back(obj);
}

void VectorDistri::appendUniformList()
{
	m_uniformCurveList.push_back(new VectorUniformCurve(m_uniformCurveList.size(), 0, vec3(0.0f), vec3(0.0f), vec3(0.0f), vec3(0.0f), vec3(0.0f), vec3(0.0f), 4));
}

void VectorDistri::appendUniformList(VectorUniformCurve *obj)
{
	m_uniformCurveList.push_back(obj);
}

void VectorDistri::removeList()
{
	if (!m_curveList.empty())
		m_curveList.pop_back();
}

void VectorDistri::removeUniformList()
{
	if (!m_uniformCurveList.empty())
		m_uniformCurveList.pop_back();
}

vec3 VectorDistri::updateCurve(float val)
{
	if (m_curveList.size() == 0)
		return vec3(0.0f);
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
				VectorConstantCurve *curve = m_curveList[i];
				VectorConstantCurve *curve1 = m_curveList[i + 1];
				if (curve->inVal() <= val && val <= curve1->inVal())
				{
					float diff = (float)curve1->inVal() - (float)curve->inVal();
					float alpha = (val - (float)curve->inVal()) / diff;

					if (curve->mode() == VectorConstantCurve::ConstantMode)
						return curve->outVal();
					else if (curve->mode() == VectorConstantCurve::LinearMode)
						return this->lerpVector(curve->outVal(), curve1->outVal(), alpha);
					else if (curve->mode() < VectorConstantCurve::LinearMode && curve->mode() >= VectorConstantCurve::AutoMode)
						return this->cubicInterpVector(curve->outVal(), curve->leaveTan(), curve1->outVal(), curve1->arriveTan(), alpha);
				}
			}
		}
	}
	else if (m_loop)
	{
		float length = abs(m_curveList.back()->inVal() - m_curveList.front()->inVal());

		float offset = m_curveList.front()->inVal();

		int step = floor((val - offset) / length);

		float pos = val - (float)step * length;

		for (int i = 0; i < m_curveList.size() - 1; ++i)
		{
			VectorConstantCurve *curve = m_curveList[i];
			VectorConstantCurve *curve1 = m_curveList[i + 1];
			if (curve->inVal() <= pos && pos <= curve1->inVal())
			{
				float diff = (float)curve1->inVal() - (float)curve->inVal();
				float alpha = (pos - (float)curve->inVal()) / diff;

				if (curve->mode() == VectorConstantCurve::ConstantMode)
					return curve->outVal();
				else if (curve->mode() == VectorConstantCurve::LinearMode)
					return this->lerpVector(curve->outVal(), curve1->outVal(), alpha);
				else if (curve->mode() < VectorConstantCurve::LinearMode && curve->mode() >= VectorConstantCurve::AutoMode)
					return this->cubicInterpVector(curve->outVal(), curve->leaveTan(), curve1->outVal(), curve1->arriveTan(), alpha);
			}
		}
	}
}

vec3 VectorDistri::updateUniformCurve(float val)
{
	vec3 v1 = vec3(0.0f);
	vec3 v2 = vec3(0.0f);

	if (m_uniformCurveList.size() == 0)
		return vec3(0.0f);
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
					VectorUniformCurve *curve = m_uniformCurveList[i];
					VectorUniformCurve *curve1 = m_uniformCurveList[i + 1];
					if (curve->inVal() <= val && val <= curve1->inVal())
					{
						float diff = (float)curve1->inVal() - (float)curve->inVal();
						float alpha = (val - (float)curve->inVal()) / diff;

						if (curve->mode() == VectorUniformCurve::ConstantMode)
						{
							v1 = curve->outVal1();
							v2 = curve->outVal2();
						}
						else if (curve->mode() == VectorUniformCurve::LinearMode)
						{
							v1 = this->lerpVector(curve->outVal1(), curve1->outVal1(), alpha);
							v2 = this->lerpVector(curve->outVal2(), curve1->outVal2(), alpha);
						}
						else if (curve->mode() < VectorUniformCurve::LinearMode && curve->mode() >= VectorUniformCurve::AutoMode)
						{
							v1 = this->cubicInterpVector(curve->outVal1(), curve->leaveTan1(), curve1->outVal1(), curve1->arriveTan1(), alpha);
							v2 = this->cubicInterpVector(curve->outVal2(), curve->leaveTan2(), curve1->outVal2(), curve1->arriveTan2(), alpha);
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
				VectorUniformCurve *curve = m_uniformCurveList[i];
				VectorUniformCurve *curve1 = m_uniformCurveList[i + 1];
				if (curve->inVal() <= pos && pos <= curve1->inVal())
				{
					float diff = (float)curve1->inVal() - (float)curve->inVal();
					float alpha = (pos - (float)curve->inVal()) / diff;

					if (curve->mode() == VectorUniformCurve::ConstantMode)
					{
						v1 = curve->outVal1();
						v2 = curve->outVal2();
					}
					else if (curve->mode() == VectorUniformCurve::LinearMode)
					{
						v1 = this->lerpVector(curve->outVal1(), curve1->outVal1(), alpha);
						v2 = this->lerpVector(curve->outVal2(), curve1->outVal2(), alpha);
					}
					else if (curve->mode() < VectorUniformCurve::LinearMode && curve->mode() >= VectorUniformCurve::AutoMode)
					{
						v1 = this->cubicInterpVector(curve->outVal1(), curve->leaveTan1(), curve1->outVal1(), curve1->arriveTan1(), alpha);
						v2 = this->cubicInterpVector(curve->outVal2(), curve->leaveTan2(), curve1->outVal2(), curve1->arriveTan2(), alpha);
					}
				}

			}
		}
	}

	m_currentUniformCurveMax = v1;
	m_currentUniformCurveMin = v2;
	return v1 + Random::Instance()->OneFloat() * (v2 - v1);
}

vec3 VectorDistri::lerpVector(vec3 out0, vec3 out1, float alpha)
{
	return out0 + alpha * (out1 - out0);
}

vec3 VectorDistri::cubicInterpVector(vec3 out0, vec3 leaveTan, vec3 out1, vec3 arriveTan, float alpha)
{
	const float A2 = alpha * alpha;
	const float A3 = A2 * alpha;
    
	return (((2 * A3) - (3 * A2) + 1) * out0) + ((A3 - (2 * A2) + alpha) * leaveTan * (out1 - out0)) + ((A3 - A2) * arriveTan * (out1 - out0)) + (((-2 * A3) + (3 * A2)) * out1);
}

void VectorDistri::setBakedData(jsonVal &bakedData)
{
	m_bakedData = bakedData;
}

//jsonVal VectorDistri::getBakedData()
//{
//	return m_bakedData;
//}

vec3 VectorDistri::getCurveBaked(float val)
{
	if (m_bakedData.Size() == 0)
		return vec3(0.0f);

	int index = floor(val * 60.0f);

	if (this->dataType() == VectorDistri::CONSCURVE)
	{
		jsonVal& vec = m_bakedData[index];
		
		/*std::cout << "m_bakedData" << m_bakedData.dump() << std::endl;

		//std::cout << "val" << val << std::endl;

		//std::cout << "index" << index << std::endl;
		*/
		//std::cout << "vec" << vec.dump() << std::endl;
		
		/*if (vec == NULL)
			vec =  m_bakedData[m_bakedData.size() - 1];*/

		return vec3(vec[0].GetFloat(), vec[1].GetFloat(), vec[2].GetFloat());
	}
	else if (this->dataType() == VectorDistri::UNIFORMCURVE)
	{
		jsonVal& minVec = m_bakedData[index * 2];
		jsonVal& maxVec = m_bakedData[index * 2 + 1];

		/*if (minVec == NULL)
			minVec = m_bakedData[m_bakedData.size() - 2];

		if (maxVec == NULL)
			maxVec = m_bakedData[m_bakedData.size() - 1];*/

		float val0 = float(minVec[0].GetFloat()) + Random::Instance()->OneFloat() * (float(maxVec[0].GetFloat()) - float(minVec[0].GetFloat()));
		float val1 = float(minVec[0].GetFloat()) + Random::Instance()->OneFloat() * (float(maxVec[1].GetFloat()) - float(minVec[1].GetFloat()));
		float val2 = float(minVec[0].GetFloat()) + Random::Instance()->OneFloat() * (float(maxVec[2].GetFloat()) - float(minVec[2].GetFloat()));
		return vec3(val0, val1, val2);
	}
}






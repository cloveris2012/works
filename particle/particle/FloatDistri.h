#ifndef FLOATDISTRI_H
#define FLOATDISTRI_H
#include "random.h"
#include "FloatConstantCurve.h"
#include "FloatUniformCurve.h"
#include <vector>
#include <map>


class FloatDistri
{
	//using json = nlohmann::json;
	using jsonDoc = rapidjson::Document;
	using jsonVal = rapidjson::Value;
public:
	FloatDistri(std::string attriName = "---",
		int flags = 0, float cons = 0,
		float min = 0, float max = 0,
		int type = 0, bool isLoop = false, bool isBaked = false);

	~FloatDistri();

	enum { CONSTANT, UNIFORM, CONSCURVE, UNIFORMCURVE };

	std::string m_attriName;
	int m_distriType;
	float m_cons;
	float m_min;
	float m_max;
	int m_type;
	int m_flags;
	bool m_loop;
	bool m_baked;
	std::vector<FloatConstantCurve*> m_curveList;
    std::vector<FloatUniformCurve*> m_uniformCurveList;
	jsonVal m_bakedData;
	float m_currentUniformCurveMin;
	float m_currentUniformCurveMax;

	std::string attriName();
	float cons();
	float min();
	float max();
	int dataType();
	int flags();
	bool isLoop();
	bool isBaked();
	int distriType();
	std::vector<FloatConstantCurve*> curveList();
	std::vector<FloatUniformCurve*> uniformCurveList();

	void setAttriName(std::string name);
	void setCons(float cons);
	void setMin(float min);
	void setMax(float max);
	void setDataType(int index);
	void setFlags(int flags);
	void setIsLoop(bool loop);
	void setIsBaked(bool baked);
	void setDistriType(int type);

	float getMaxValue();
	void resetData();
	void appendList();
	void appendList(FloatConstantCurve *obj);
	void appendUniformList();
	void appendUniformList(FloatUniformCurve* obj);
	void removeList();
	void removeUniformList();
	float updateCurve(float val);
	float updateUniformCurve(float val);
	float lerpFloat(float out0, float out1, float alpha);
	float cubicInterpFloat(float out0, float leaveTan, float out1, float arriveTan, float alpha);
	void setBakedData(jsonVal &bakedData);
	//jsonVal getBakedData();
	float getCurveBaked(float val);
};
#endif // FLOATDISTRI_H


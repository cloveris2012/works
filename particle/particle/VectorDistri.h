#ifndef VECTORDISTRI_H
#define VECTORDISTRI_H
#include "random.h"
#include "VectorConstantCurve.h"
#include "VectorUniformCurve.h"
#include <vector>


class VectorDistri 
{
	using vec3 = glm::vec3;
	//using json = nlohmann::json;
	using jsonDoc = rapidjson::Document;
	using jsonVal = rapidjson::Value;
public:
	VectorDistri(std::string attriName = "---",
		int flags = 0, vec3 cons = vec3(),
		vec3 min = vec3(), vec3 max = vec3(),
		int type = 0, bool isLoop = false, bool isBaked = false);
	
	~VectorDistri();

	enum { CONSTANT, UNIFORM, CONSCURVE, UNIFORMCURVE };

	std::string attriName();
	int distriType();
	vec3 cons();
	vec3 min();
	vec3 max();
	int dataType();
	int flags();
	bool isLoop();
	bool isBaked();
	std::vector<VectorConstantCurve*> curveList();
	std::vector<VectorUniformCurve*> uniformCurveList();

	void setAttriName(std::string attriName);
	void setCons(vec3 cons);
	void setMin(vec3 min);
	void setMax(vec3 max);
	void setDataType(int index);
	void setFlags(int flags);
	void setIsLoop(bool loop);
	void setIsBaked(bool baked);
	void setDistriType(int type);

	void resetData();
	void appendList();
	void appendList(VectorConstantCurve *obj);
	void appendUniformList();
	void appendUniformList(VectorUniformCurve* obj);
	void removeList();
	void removeUniformList();
	vec3 updateCurve(float val);
	vec3 updateUniformCurve(float val);
	vec3 lerpVector(vec3 out0, vec3 out1, float alpha);
	vec3 cubicInterpVector(vec3 out0, vec3 leaveTan, vec3 out1, vec3 arriveTan, float alpha);
	void setBakedData(jsonVal &bakedData);
	//jsonVal getBakedData();
	vec3 getCurveBaked(float val);

	std::string m_attriName;
	int m_distriType;
	vec3 m_cons;
	vec3 m_min;
	vec3 m_max;
	int m_type;
	int m_flags;
	bool m_loop;
	bool m_baked;
	std::vector<VectorConstantCurve*> m_curveList;
	std::vector<VectorUniformCurve*> m_uniformCurveList;
	jsonVal m_bakedData;
	vec3 m_currentUniformCurveMin;
	vec3 m_currentUniformCurveMax;
};

#endif // VECTORDISTRI_H

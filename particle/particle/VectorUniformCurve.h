#ifndef VECTORUNIFORMCURVE_H
#define VECTORUNIFORMCURVE_H
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_PRECISION_LOWP_FLOAT
//#include "json.hpp"
#include "rapidjson/document.h"
#include "glm/glm.hpp"



class VectorUniformCurve
{
	//using json = nlohmann::json;
	using vec3 = glm::vec3;

public:
	VectorUniformCurve(int title, float inVal,
		vec3 outVal1, vec3 outVal2,
		vec3 arriveTan1, vec3 arriveTan2,
		vec3 leaveTan1, vec3 leaveTan2,
		int mode);

	enum {
		AutoMode = 0,
		AutoClampedMode = 1,
		UserMode = 2,
		BreakMode = 3,
		LinearMode = 4,
		ConstantMode = 5
	};

	int title();
	float inVal();
	vec3 outVal1();
	vec3 outVal2();
	vec3 arriveTan1();
	vec3 arriveTan2();
	vec3 leaveTan1();
	vec3 leaveTan2();
	int mode();

	void setTitle(int title);
	void setInVal(float inVal);
	void setOutVal1(vec3 outVal);
	void setOutVal2(vec3 outVal);
	void setArriveTan1(vec3 arriveTan);
	void setArriveTan2(vec3 arriveTan);
	void setLeaveTan1(vec3 leaveTan);
	void setLeaveTan2(vec3 leaveTan);
	void setMode(int mode);
	//void setData(json data);

private:
	int m_title;
	float m_inVal;
	vec3 m_outVal1;
	vec3 m_outVal2;
	vec3 m_arriveTan1;
	vec3 m_arriveTan2;
	vec3 m_leaveTan1;
	vec3 m_leaveTan2;
	int m_mode;
};
#endif // VECTORUNIFORMCURVE_H


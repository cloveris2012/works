#ifndef VECTORCONSTANTCURVE_H
#define VECTORCONSTANTCURVE_H
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_PRECISION_LOWP_FLOAT
#include "glm/glm.hpp"
//#include "json.hpp"
#include "rapidjson/document.h"


class VectorConstantCurve 
{
	//using json = nlohmann::json;
	using vec3 = glm::vec3;

public:
	VectorConstantCurve(int title, float inVal, vec3 outVal, vec3 arriveTan, vec3 leaveTan, int mode);

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
	vec3 outVal();
	vec3 arriveTan();
	vec3 leaveTan();
	int mode();

	void setTitle(int title);
	void setInVal(float inVal);
	void setOutVal(vec3 outVal);
	void setArriveTan(vec3 arriveTan);
	void setLeaveTan(vec3 leaveTan);
	void setMode(int mode);
	//void setData(json data);

private:
	int m_title;
	float m_inVal;
	vec3 m_outVal;
	vec3 m_arriveTan;
	vec3 m_leaveTan;
	int m_mode;
};

#endif // VECTORCONSTANTCURVE_H

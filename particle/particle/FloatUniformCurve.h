#ifndef FLOATUNIFORMCURVE_H
#define FLOATUNIFORMCURVE_H
//#include "json.hpp"
#include "rapidjson/document.h"


class FloatUniformCurve
{
	//using json = nlohmann::json;

public:
	FloatUniformCurve(int title, 
		              float inVal,
		              float outVal1, float outVal2,
		              float arriveTan1, float arriveTan2,
		              float leaveTan1, float leaveTan2, 
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
	float outVal1();
	float outVal2();
	float arriveTan1();
	float arriveTan2();
	float leaveTan1();
	float leaveTan2();
	int mode();

	void setTitle(int title);
	void setInVal(float inVal);
	void setOutVal1(float outVal);
	void setOutVal2(float outVal);
	void setArriveTan1(float arriveTan);
	void setArriveTan2(float arriveTan);
	void setLeaveTan1(float leaveTan);
	void setLeaveTan2(float leaveTan);
	void setMode(int mode);
	//void setData(json data);

private:
	int m_title;
	float m_inVal;
	float m_outVal1;
	float m_outVal2;
	float m_arriveTan1;
	float m_arriveTan2;
	float m_leaveTan1;
	float m_leaveTan2;
	int m_mode;
};
#endif // FLOATUNIFORMCURVE_H

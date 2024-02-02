#ifndef FLOATCONSTANTCURVE_H
#define FLOATCONSTANTCURVE_H
//#include "json.hpp"
#include "rapidjson/document.h"


class FloatConstantCurve
{
	//using json = nlohmann::json;
public:
	FloatConstantCurve(int title, float inVal, float outVal, float arriveTan, float leaveTan, int mode);

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
	float outVal();
	float arriveTan();
	float leaveTan();
	int mode();

	void setTitle(int title);
	void setInVal(float inVal);
	void setOutVal(float outVal);
	void setArriveTan(float arriveTan);
	void setLeaveTan(float leaveTan);
	void setMode(int mode);
	//void setData(json data);

private:
	int m_title;
	float m_inVal;
	float m_outVal;
	float m_arriveTan;
	float m_leaveTan;
	int m_mode;
};

#endif // FLOATCONSTANTCURVE_H

#ifndef RANDOM_H
#define RANDOM_H
#define GLM_PRECISION_LOWP_FLOAT
#include "glm/glm.hpp"
#include <iostream>

static unsigned int mirand = 1;

class Random {
	using vec2 = glm::vec2;
	using vec3 = glm::vec3;

public:
	static Random* Instance();

	inline float OneMinusOneFloat()
	{
		unsigned int a; mirand *= 16807; a = (mirand & 0x007fffff) | 0x40000000; return(*((float*)&a) - 3.0f);
	}
	int IntNum(int num);
	float OneFloat();
	vec2 OneVector2D();
	vec2 OneMinusOneVector2D();
	vec3 OneVector3D();
	vec3 OneMinusOneVector3D();

	//void refreshSeed();
private:
	Random() {}
	Random(Random const&) {}
	Random& operator=(Random const&) {}
	static Random* m_pInstance;

	
};

#endif // RANDOM_H

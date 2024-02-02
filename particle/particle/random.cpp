#include "random.h"
#include <math.h>

using vec2 = glm::vec2;
using vec3 = glm::vec3;

Random* Random::m_pInstance = NULL;

Random* Random::Instance()
{
	if (!m_pInstance)
		m_pInstance = new Random;
	return m_pInstance;
}

int Random::IntNum(int num)
{	
	return floor(std::abs(OneMinusOneFloat()) * num);
}

float Random::OneFloat()
{
	return std::abs(OneMinusOneFloat());
}

vec2 Random::OneVector2D()
{
	return vec2(OneFloat(),OneFloat());
}

vec2 Random::OneMinusOneVector2D()
{
	return vec2(OneMinusOneFloat(), OneMinusOneFloat());
}

vec3 Random::OneVector3D()
{
	return vec3(OneFloat(), OneFloat(), OneFloat());
}

vec3 Random::OneMinusOneVector3D()
{
	return vec3(OneMinusOneFloat(), OneMinusOneFloat(), OneMinusOneFloat());
}

//void Random::refreshSeed()
//{
//}

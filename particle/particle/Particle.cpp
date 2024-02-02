#include "Particle.h"
#include <glm/gtc/matrix_transform.hpp>

using vec4 = glm::vec4;
using mat4 = glm::mat4;
using vec3 = glm::vec3;

template <class T>
Particle<T>::Particle(Emittter<T> *emitter) : m_oriPos(vec3(0.0))
{
	m_emitter = emitter;
	m_pos = vec3(0.0f);
	m_oriPos = vec3(emitter->m_emitterPosX, emitter->m_emitterPosY, 0.0f);
	m_model = mat4(1.f);
	m_rotMat = mat4(1.f);
	m_currentSize = 10.0f;
	m_trans = vec3(0.0f);
	m_worldOffset = vec3(0.0f);
	m_orbit = vec3(0.0f);
	m_orbitOffset = vec3(0.0f);
	m_orbitRotation = vec3(0.0f);
	m_orbitRotationRate = vec3(0.0f);
	m_orbitRotationRateAmount = vec3(0.0f);
	m_hitFloor = false;
	m_hitLine = false;
	m_hitRect = false;
	m_hitSphere = false;
	m_rotate = 0.0f;
	m_rotDamp = 1.0f;
	m_collisionCount = 0;
	m_isUpdate = false;
	m_isUpdateTrans = true;
	m_isUpdateRot = true;
	m_dirLocOffset = vec3(0.0f);

	m_isActivated = false;
	m_velocity = vec3(0.0f);
	m_acceleration = vec3(0.0f);
	m_drag = 0.0f;
	m_initColor = vec3(1.0f);
	m_currentColor = vec3(1.0f);
	m_currentAlpha = 1.0f;
	m_currentLife = 0.0f;
	m_lifeTime = 0.0f;
	m_radial = vec3(0.0f);
	m_radialSpeed = 0.0f;
	m_isTexture = true;
	m_flipU = 0;
	m_flipV = 0;
	m_defaultSubCoord = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	m_subCoord = m_defaultSubCoord;
	m_interlopMode = 0;
	m_subCurrentIndex = -1;
	m_subCoordNext = m_defaultSubCoord;
	m_subRatio = 0.0f;
	m_shapeVel = vec3(0.0f);
	m_velRotation = 0.0f;
	m_tangentSpeed = vec3(0.0f);
	m_collisionFrame = false;
	m_spawnMat = mat4(1.0f);
	m_spawnViewScale = vec2(1.0f, 1.0f);
	m_currentScaleFactor = 1.0;
	m_currentParentRotationMat = mat2(1.0f);
}

template<class T>
Particle<T>::~Particle()
{
}


//Particle::~Particle()
//{
//}

template<class T>
void Particle<T>::setOriPos(vec3 pos)
{
	m_oriPos = pos;
}

template <typename T>
vec3 Particle<T>::getShaderAttriPos()
{
	/*vec4 pos = (m_model * vec4(m_pos, 1.0f));
	return vec3(pos.x, pos.y, pos.z);*/

	return m_pos;
}

template <typename T>
float Particle<T>::getShaderAttriSize()
{
	return m_currentSize;
}

template <typename T>
vec3 Particle<T>::getShaderAttriColor()
{
	return m_currentColor;
}

template <typename T>
float Particle<T>::getShaderAttriAlpha()
{
	return m_currentAlpha;
}

template <typename T>
float Particle<T>::getShaderAttriFlipU()
{
	return m_flipU;
}

template <typename T>
float Particle<T>::getShaderAttriFlipV()
{
	return m_flipV;
}

template <typename T>
float Particle<T>::getShaderAttriRot()
{
	return (m_rotate + m_velRotation) * m_rotDamp;
}

template <typename T>
vec4 Particle<T>::getShaderAttriSubCoord()
{
	return m_subCoord;
}

template <typename T>
vec4 Particle<T>::getShaderAttriSubCoordNext()
{
	return m_subCoordNext;
}

template <typename T>
float Particle<T>::getShaderAttriSubRatio()
{
	return m_subRatio;
}

template<class T>
void Particle<T>::setVelocity(vec3 vel)
{
	m_velocity = vel;
}

template <typename T>
vec3 Particle<T>::getVelocity()
{
	return m_velocity;
}

template <typename T>
float Particle<T>::getRotation()
{
	return m_rotate + m_velRotation;
}

template <typename T>
void Particle<T>::setModelMatrix(mat4 mat)
{
	m_model = mat;
}

template <typename T>
mat4 Particle<T>::getModelMatrix()
{
	return m_model;
}

template <typename T>
void Particle<T>::reset(int index)
{   
	//std::cout << "reset ###################################################################" << std::endl;
	
	m_pos = vec3(0.0f);

	m_oriPos = vec3(m_emitter->m_emitterPosX, m_emitter->m_emitterPosY, 0.0f);

	if (m_emitter->m_isLocalSpace == false)
	{
		m_spawnMat = m_emitter->m_currentMat;

		m_spawnViewScale = m_emitter->m_currentViewScale;

		vec2 parentScale = vec2(glm::length(m_spawnMat[0]), glm::length(m_spawnMat[1]));
		vec2 scaleFactor = m_spawnViewScale * parentScale;
		m_currentScaleFactor = scaleFactor.x < scaleFactor.y ? scaleFactor.x : scaleFactor.y;

		m_currentParentRotationMat = mat2(m_spawnMat[0][0] / parentScale.x, m_spawnMat[0][1] / parentScale.x,
			m_spawnMat[1][0] / parentScale.y, m_spawnMat[1][1] / parentScale.y);
	}
	

	m_rotMat = mat4(1.f);

	m_worldOffset = m_emitter->getModuleMap()[Emittter<T>::WorldOffset] ? m_emitter->getWorldOffsetValue() : vec3(0.0f);

	m_trans = vec3(0.0f);

	m_trans += m_emitter->getModuleMap()[Emittter<T>::InitLocation] ? m_emitter->getInitLocationValue() : vec3(0.0f);

	//std::cout << "pos  " << m_trans.y << std::endl;

	int locParIndex = 0;

	int particleCount = m_emitter->getLocPosAttribute().size();

	if (m_emitter->getModuleMap()[Emittter<T>::EmitterInitLoc])
	{
		if (m_emitter->m_locEmitterMode == 0)
		{
			int particleCount = m_emitter->getLocPosAttribute().size();

			if (particleCount != 0)
			{
				//std::cout << "m_parIndex  " << locParIndex << std::endl;
				//std::cout << "m_emitter->getLocPosAttribute().size()  " << m_emitter->getLocPosAttribute().size() << std::endl;
				locParIndex = Random::Instance()->IntNum(particleCount);
				m_trans += m_emitter->getLocPosAttribute()[locParIndex];
			}
		}
		else if (m_emitter->m_locEmitterMode == 1)
		{
			if (particleCount != 0)
			{
				locParIndex = fmod(m_emitter->getLocParticleIndex(), particleCount);

				//std::cout << "index = " << m_emitter->getLocParticleIndex() << "  particleCount = " << particleCount << "  locParIndex " << locParIndex << std::endl;

				m_trans += m_emitter->getLocPosAttribute()[locParIndex];
                
				m_emitter->setLocParticleIndex(m_emitter->getLocParticleIndex() + 1);
			}
		}

		//m_trans += m_emitter->getLocPosAttribute()[locParIndex];
	}

	m_lifeTime = m_emitter->getModuleMap()[Emittter<T>::Lifetime] ? m_emitter->getFloatDistriValueFloor(m_emitter->m_lifeTime) : 1000.0f;

	m_initColor = m_emitter->getModuleMap()[Emittter<T>::InitialColor] ? m_emitter->getVectorDistriValue(m_emitter->m_initColor) / vec3(255.0f) : vec3(1.0f);

	m_initAlpha = m_emitter->getModuleMap()[Emittter<T>::InitialColor] ? m_emitter->getInitAlphaValue() / 255.0f : 1.0f;

	m_initSize = m_emitter->getModuleMap()[Emittter<T>::InitialSize] ? m_emitter->getFloatDistriValueFloor(m_emitter->m_initSize) : 10.0f;

	m_velocity = m_emitter->getModuleMap()[Emittter<T>::InitialVelocity] ? m_emitter->getVectorDistriValue(m_emitter->m_initVelocity) : vec3(0.0f);

    sphereLocCal();
    
    triangleLocCal();
    
    orbitSetCal();

	if (m_emitter->getModuleMap()[Emittter<T>::EmitterInitLoc] && m_emitter->m_inheritSourceVelocity)
	{
		if (particleCount != 0)
		{
			m_velocity += m_emitter->getLocVelAttribute()[locParIndex] * m_emitter->m_inheritVelScale;
		}
	}

	m_radialSpeed = m_emitter->getModuleMap()[Emittter<T>::InitialVelocity] ? m_emitter->getFloatDistriValue(m_emitter->m_initVelocityRadial) : 0.0f;

	m_radial = glm::length(m_trans) > 0.0f ? glm::normalize(m_trans) : vec3(0.0f);
		
	m_radial *= vec3(m_radialSpeed);

	m_velocity += m_radial;

	m_acceleration = m_emitter->getModuleMap()[Emittter<T>::InitialAccel] ? m_emitter->getVectorDistriValue(m_emitter->m_initAcceleration) : vec3(0.0f);

	m_drag = m_emitter->getModuleMap()[Emittter<T>::Drag] ? m_emitter->getFloatDistriValue(m_emitter->m_drag) : 0.0f;

	m_rotate = m_emitter->getModuleMap()[Emittter<T>::InitRotate] ? m_emitter->getFloatDistriValue(m_emitter->m_initRotate) : 0.0f;

	if (m_emitter->getModuleMap()[Emittter<T>::DirectLocation] == true)
		m_dirLocOffset = m_emitter->getVectorDistriValue(m_emitter->m_dirLocationOffset);

	if (m_emitter->getModuleMap()[Emittter<T>::EmitterInitLoc] && m_emitter->m_inheritSourceRotation)
	{
		if (particleCount != 0)
		{
			m_rotate += m_emitter->getLocRotAttribute()[locParIndex] * 180.0f / glm::pi<float>() * m_emitter->m_inheritRotScale;
		}
	}
	m_rotRate = m_emitter->getModuleMap()[Emittter<T>::InitRotRate] ? m_emitter->getFloatDistriValue(m_emitter->m_initRotRate) : 0.0f;

	m_rotate = m_rotate / 180.0f * glm::pi<float>();

	m_coordList = m_emitter->getSubCoordList();

	m_subCurrentIndex = -1;

	m_coordLength = m_coordList.size();

	m_interlopMode = m_emitter->m_subUVMode;

	velocityConeCal();

	m_baseVelocity = m_velocity;
	
	m_currentLife = 0.0f;

	m_isActivated = false;

	m_isUpdate = false;

	m_isUpdateTrans = true;

	m_isUpdateRot = true;

	setFlipUV();

	m_hitFloor = false;

	m_hitLine = false;

	m_hitRect = false;

	m_hitSphere = false;

	m_rotDamp = 1.0f;

	m_collisionCount = 0;
}

template <typename T>
void Particle<T>::update(int64_t dt, int index)
{
    killBoxCal();
    
    killHeightCal();
    
    updateSubCoord();

	m_collisionFrame = false;

	if (m_isUpdateTrans)
	{
		//std::cout << "m_trans" << m_trans.x << m_trans.y << m_trans.z << std::endl;

		vec3 radicalSpeed = vec3(0.0f);

		if (glm::length(m_trans) > 0.0f)
		{
			radicalSpeed = glm::normalize(m_trans);

			//std::cout << radicalSpeed.x << radicalSpeed.y << radicalSpeed.z << std::endl;

			m_tangentSpeed.x = -radicalSpeed.y;

			m_tangentSpeed.y = radicalSpeed.x;

			m_tangentSpeed.z = radicalSpeed.z;

			//std::cout << m_tangentSpeed.x << m_tangentSpeed.y << m_tangentSpeed.z << std::endl;
		}

		m_acceleration = m_emitter->getModuleMap()[Emittter<T>::AccelOverLife] ? m_emitter->getVectorDistriValue(m_emitter->m_accelOverLife, getParticleLifeRate()) : m_acceleration;

		if (m_emitter->getModuleMap()[Emittter<T>::VelOverLife])
		{
			if (m_emitter->m_velocityAbsolute)
			{
				m_velocity = m_emitter->getVectorDistriValue(m_emitter->m_velOverLife, getParticleLifeRate());
			}
			else
			{
				m_velocity = m_baseVelocity * m_emitter->getVectorDistriValue(m_emitter->m_velOverLife, getParticleLifeRate());
			}
		}

		m_velocity += m_acceleration / vec3(16.666667, 16.666667, 16.666667) * vec3(dt,dt,dt);

		m_velocity += m_tangentSpeed * 0.0f;//m_emitter->m_tangentSpeed

		vec3 vec;

		vec = m_velocity + attractorCal(dt, false);

		if (m_emitter->m_affectBaseVelocity)
			m_velocity = vec;

		vec += attractorLineCal(dt);

		vec += m_emitter->m_sphereVelocity ? (m_shapeVel) : vec3(0.0f);

		float dtMile = (float)dt * 0.001;

		float speedScale = 1.0 - dtMile * m_drag;

		vec *= vec3(speedScale, speedScale, speedScale);

		m_trans = m_trans + vec * vec3(dtMile, dtMile, dtMile);

		m_velocity *= vec3(speedScale, speedScale, speedScale);
		
		if (m_emitter->m_velRotation) //emitter->m_velRotation;
		{
			glm::normalize(vec);

			m_velRotation = glm::atan(vec.x / vec.y);

			if (vec.y < 0.0f)
				m_velRotation += 3.14f;
		}
		/*std::cout << "radian--->" << m_velRotation
			<< "    angle---->" << m_velRotation * 180.0f / glm::pi<float>()
			<< "    vX,vY" << m_velocity.x << "  " << m_velocity.y << std::endl;*/
		orbitUpdateCal(dt);
	}

	float eLifeTime = m_emitter->getEmitterLifeTime();

	//make collision when rate is 0--->when duration ends the remain particle also needs collision
	if (m_emitter->getModuleMap()[Emittter<T>::CollisionFloor])
	{
		if ((eLifeTime == 0.0f) || (eLifeTime * 1000.0f > m_emitter->m_floorCollisionDelayAmount))
			floorCollisionCal();
	}

	if (m_emitter->getModuleMap()[Emittter<T>::CollisionLine])
	{
		if ((eLifeTime == 0.0f) || (eLifeTime * 1000.0f > m_emitter->m_lineCollisionDelayAmount))
			lineCollisionCal();
	}

	if (m_emitter->getModuleMap()[Emittter<T>::CollisionRect])
	{
		if ((eLifeTime == 0.0f) || (eLifeTime * 1000.0f > m_emitter->m_rectCollisionDelayAmount))
			rectCollisionCal();
		
	}

	if (m_emitter->getModuleMap()[Emittter<T>::CollisionSphere])
	{
		if ((eLifeTime == 0.0f) || (eLifeTime * 1000.0f > m_emitter->m_sphereCollisionDelayAmount))
			sphereCollisionCal();
		
	}

	if (m_isUpdateRot)
	{
		m_rotate = m_emitter->getModuleMap()[Emittter<T>::RotateOverLife] ? m_emitter->getFloatDistriValue(m_emitter->m_rotateOverLife, getParticleLifeRate()) : m_rotate;
	
		if (m_emitter->getModuleMap()[Emittter<T>::RotRateLife])
		{
			m_rotRate = m_emitter->getFloatDistriValue(m_emitter->m_rotRateLife);
		}

		m_rotate = m_rotate + m_rotRate / 1000.0f * dt * glm::pi<float>() * 2.0f;
	}

	m_currentColor = m_emitter->getModuleMap()[Emittter<T>::ColorOverLife] ? m_emitter->getVectorDistriValue(m_emitter->m_colorOverLife, getParticleLifeRate()) / vec3(255.0f) : m_initColor;

	m_currentAlpha = m_emitter->getModuleMap()[Emittter<T>::ColorOverLife] ? m_emitter->getAlphaOverLifeValue(getParticleLifeRate()) / 255.0f : m_initAlpha;

	if (m_emitter->getModuleMap()[Emittter<T>::ColorScaleLife])
	{
		if (m_emitter->m_colorScaleEmitterLife)
		{
			m_currentColor *= m_emitter->getVectorDistriValue(m_emitter->m_colorScaleOverLife);
			m_currentAlpha *= m_emitter->getFloatDistriValue(m_emitter->m_alphaScaleOverLife);
		}
		else
		{
			m_currentColor *= m_emitter->getVectorDistriValue(m_emitter->m_colorScaleOverLife, getParticleLifeRate());
			m_currentAlpha *= m_emitter->getFloatDistriValue(m_emitter->m_alphaScaleOverLife, getParticleLifeRate());
		}
	}
	
	m_currentSize = m_initSize;

	m_currentSize *= m_emitter->getModuleMap()[Emittter<T>::SizeByLife] ? m_emitter->getFloatDistriValueFloor(m_emitter->m_sizeLife, getParticleLifeRate()) : 1.0f;

	m_currentSize *= m_emitter->getModuleMap()[Emittter<T>::SizeBySpeed] ? sqrt(m_emitter->getSpeedSizeX() * m_emitter->getSpeedSizeX() * m_velocity.x * m_velocity.x + m_emitter->getSpeedSizeY() * m_emitter->getSpeedSizeY() * m_velocity.y * m_velocity.y) : 1.0f;

	if (m_emitter->getModuleMap()[Emittter<T>::SizeByScale])
	{
		m_currentSize *= m_emitter->getFloatDistriValueFloor(m_emitter->m_sizeScale, getParticleLifeRate());
	}


	if (m_hitFloor == true)
		m_hitFloor = false;
	if (m_hitLine == true)
		m_hitLine = false;
	if (m_hitRect == true)
		m_hitRect = false;
	if (m_hitSphere == true)
		m_hitSphere = false;

	if (!m_emitter->getModuleMap()[Emittter<T>::EmitterDirectLoc])
	{
		m_model = mat4(1.f);

		vec3 offset = m_oriPos;

		offset += m_worldOffset;

		m_model = glm::translate(m_model, offset);

		//if (m_emitter->m_isLocalSpace == true)
		//{
		//	m_model = glm::rotate(m_model, (-m_emitter->m_emitterRot) / 180.0f * glm::pi<float>(), vec3(0.0, 0.0, 1.0));//- 180.0f
		//}
		//else
		//{
		//	m_model = glm::rotate(m_model, (m_emitter->m_emitterRot - 180.0f) / 180.0f * glm::pi<float>(), vec3(0.0, 0.0, 1.0));//- 180.0f
		//}

		offset = vec3(0.0f);

		offset += m_trans;

		if (m_emitter->getModuleMap()[Emittter<T>::Orbit])
		{
			offset += m_orbit;
		}

		m_model = glm::translate(m_model, offset);
	}

	//std::cout << "m_emitter->getModuleMap()[Emittter<T>::DirectLocation]" << m_emitter->getModuleMap()[Emittter<T>::DirectLocation] << std::endl;
	
	if (m_emitter->getModuleMap()[Emittter<T>::DirectLocation])
	{
		m_model = mat4(1.f);

		vec3 loc = m_emitter->getVectorDistriValue(m_emitter->m_directLocation, getParticleLifeRate());
		loc += m_dirLocOffset;
		m_trans = loc;
		m_model = glm::translate(m_model, loc);
	}
	m_model = m_model;

	m_pos = vec3(m_model[3]);

	if (m_emitter->m_isLocalSpace == false)
	{
		m_pos.y = -m_pos.y;
		m_pos *= vec3(m_spawnViewScale, 1.0);
		m_pos = m_spawnMat * vec4(m_pos, 1.0);
	}
		

	//算完本地坐标系位置后直接乘这个粒子创建时的变换矩阵
	//m_pos = m_initModelView * m_pos;

	/*std::cout << m_model[0][0] << m_model[0][1] << m_model[0][2] << m_model[0][3]
		<< m_model[1][0] << m_model[1][1] << m_model[1][2] << m_model[1][3]
		<< m_model[2][0] << m_model[2][1] << m_model[2][2] << m_model[2][3]
		<< m_model[3][0] << m_model[3][1] << m_model[3][2] << m_model[3][3] << std::endl;*/

	if (!m_emitter->m_randomTexU)
	{
		m_flipU = m_emitter->m_flipTexcoordU ? 1 : 0;
	}

	if (!m_emitter->m_randomTexV)
	{
		m_flipV = m_emitter->m_flipTexcoordV ? 1 : 0;
	}

	if (m_emitter->getModuleMap()[Emittter<T>::EmitterDirectLoc])
	{
		int particleCount = m_emitter->getDirectPosAttribute().size();

		if (particleCount != 0)
		{
			if (index < particleCount) 
			    m_pos = m_emitter->getDirectPosAttribute()[index];
		}
	}
	
	killCanvas();
}

template <typename T>
void Particle<T>::updateLife(int64_t dt)
{
	m_currentLife += (float)dt;
}

template <typename T>
bool Particle<T>::isDead()
{
	if (m_currentLife > m_lifeTime)
	{
		m_isActivated = false;
		return true;
	}
	else
	    return false;
}

template <typename T>
bool Particle<T>::isActivated()
{
	return m_isActivated;
}

template <typename T>
void Particle<T>::setActivate(bool val)
{
	m_isActivated = val;
}

template <typename T>
bool Particle<T>::isUpdate()
{
	return m_isUpdate;
}

template <typename T>
void Particle<T>::setUpdate(bool val)
{
	m_isUpdate = val;
}

template <typename T>
bool Particle<T>::isUpdateTrans()
{
	return m_isUpdateTrans;
}

template <typename T>
void Particle<T>::setUpdateTrans(bool update)
{
	m_isUpdateTrans = update;
}

template <typename T>
bool Particle<T>::isUpdateRot()
{
	return m_isUpdateRot;
}

template <typename T>
void Particle<T>::setUpdateRot(bool rot)
{
	m_isUpdateRot = rot;
}

template <typename T>
float Particle<T>::getParticleLifeRate()
{
	float life = m_currentLife / m_lifeTime;
	//std::cout << "life" << life << "m_currentLife" << m_currentLife << "m_lifetime" << m_lifeTime;
	return life > 1.0f ? 1.0f : life;
}

template<class T>
void Particle<T>::setFlipUV()
{
	if (m_emitter->m_randomTexU && (!m_emitter->m_randomTexV))
	{
		if (Random::Instance()->OneMinusOneFloat() > 0)
			m_flipU = 1;
		else
			m_flipU = 0;

		m_flipV = 0;
	}
	else if ((!m_emitter->m_randomTexU) && m_emitter->m_randomTexV)
	{
		if (Random::Instance()->OneMinusOneFloat() > 0)
			m_flipV = 1;
		else
			m_flipV = 0;
	 
		m_flipU = 0;
	}
	else if ((!m_emitter->m_randomTexU) && (!m_emitter->m_randomTexV))
	{
		m_flipU = 0;
		m_flipV = 0;
	}
	else
	{
		if (Random::Instance()->OneMinusOneFloat() > 0)
			m_flipU = 1;
		else
			m_flipU = 0;

		if (Random::Instance()->OneMinusOneFloat() > 0)
			m_flipV = 1;
		else
			m_flipV = 0;
	}
}

template<class T>
void Particle<T>::velocityConeCal()
{
	if (m_emitter->getModuleMap()[Emittter<T>::VelocityCone])
	{
		float angle = m_emitter->getFloatDistriValueFloor(m_emitter->m_coneVelocityAngle);
		float dir = m_emitter->m_coneDirection;
		float dirAngle = dir + Random::Instance()->OneMinusOneFloat() * angle / 2.0f;
		dirAngle = dirAngle / 180.0f * glm::pi<float>();
		//std::cout << "velocityCone" << angle << "   " << dir << "   " << dirAngle << "   " << std::endl;
		vec3 vel = vec3(0.0f,0.0f,0.0f);
		vel.x = glm::sin(dirAngle);
		vel.y = glm::cos(dirAngle);
		
		float coneVelocity = m_emitter->getFloatDistriValue(m_emitter->m_coneVelocityVelocity);
		
		//std::cout << "vel" << vel.x << "  " << vel.y << "  " << coneVelocity << std::endl;

		vel *= vec3(coneVelocity);

		//std::cout << "vel * coneVel" << vel.x << "  " << vel.y << std::endl;
		m_velocity += vel;

		//std::cout << "velocity   " << m_velocity.x << " " << m_velocity.y << "  " << m_velocity.z << std::endl;
	}
}

template<class T>
void Particle<T>::sphereLocCal()
{
	if (m_emitter->getModuleMap()[Emittter<T>::Sphere])
	{
		float rad = Random::Instance()->OneFloat() * glm::pi<float>() * 2;

		m_shapeVel.x = glm::sin(rad);
		m_shapeVel.y = glm::cos(rad);

		if (!m_emitter->m_spherePositiveX)
		{
			if (!m_emitter->m_sphereNegativeX)
				m_shapeVel.x = 0;
			else
				m_shapeVel.x = -abs(m_shapeVel.x);
		}
		else
		{
			if (!m_emitter->m_sphereNegativeX)
				m_shapeVel.x = abs(m_shapeVel.x);
		}

		if (!m_emitter->m_spherePositiveY)
		{
			if (!m_emitter->m_sphereNegativeY)
				m_shapeVel.y = 0;
			else
				m_shapeVel.y = -abs(m_shapeVel.y);
		}
		else
		{
			if (!m_emitter->m_sphereNegativeY)
				m_shapeVel.y = abs(m_shapeVel.y);
		}

		float v = m_emitter->getFloatDistriValue(m_emitter->m_sphereRadius);
		vec3 sphereRadius = vec3(v);

		if (m_emitter->m_sphereSurface)
			m_trans += m_shapeVel * sphereRadius;
		else
			m_trans += m_shapeVel * sphereRadius * Random::Instance()->OneVector3D();

		float vel = m_emitter->getFloatDistriValue(m_emitter->m_sphereVelocityScale);

		vec3 sphereVelScale = vec3(vel);

		m_shapeVel *= sphereVelScale;
	}
}

template<class T>
void Particle<T>::triangleLocCal()
{
	if (m_emitter->getModuleMap()[Emittter<T>::Triangle])
	{
		vec3 offset = m_emitter->getVectorDistriValue(m_emitter->m_triangleOffset);
		float height = m_emitter->getFloatDistriValueFloor(m_emitter->m_triangleHeight);
		float angle = m_emitter->getFloatDistriValueFloor(m_emitter->m_triangleAngle);
		float baseLength = height * glm::tan(angle * glm::pi<float>() / 180.0f);

		std::vector<vec3> corners;

		vec3 v1 = offset + vec3(height * 0.5f, 0.0f, 0.0f);
		corners.push_back(v1);
		vec3 v2 = offset + vec3(-height * 0.5f, baseLength, 0.0f);
		corners.push_back(v2);
		vec3 v3 = offset + vec3(-height * 0.5f, -baseLength, 0.0f);
		corners.push_back(v3);

		float barycentricCoords[3] = {Random::Instance()->OneFloat() ,Random::Instance()->OneFloat() ,Random::Instance()->OneFloat()};

		vec3 locationOffset = vec3(0.0f);

		float sum = barycentricCoords[0] + barycentricCoords[1] + barycentricCoords[2];

		for (int i = 0; i < 3; i++)
		{
			locationOffset += (vec3(barycentricCoords[i]) / vec3(sum)) * corners[i];
		}
		m_trans += locationOffset;
	}
}

template<class T>
void Particle<T>::orbitSetCal()
{
	if (m_emitter->getModuleMap()[Emittter<T>::Orbit])
	{
		if (m_emitter->getOrbitConfig(Emittter<T>::OFFSET, Emittter<T>::SPAWN))
		{
			if (m_emitter->getOrbitConfig(Emittter<T>::OFFSET, Emittter<T>::EMITTER_TIME))
				m_orbitOffset = m_emitter->getVectorDistriValue(m_emitter->m_orbitOffset);
			else
				m_orbitOffset = m_emitter->getVectorDistriValue(m_emitter->m_orbitOffset, getParticleLifeRate());

		}

		if (m_emitter->getOrbitConfig(Emittter<T>::ROTATION, Emittter<T>::SPAWN))
		{
			if (m_emitter->getOrbitConfig(Emittter<T>::ROTATION, Emittter<T>::EMITTER_TIME))
				m_orbitRotation = m_emitter->getVectorDistriValue(m_emitter->m_orbitRotation);
			else
				m_orbitRotation = m_emitter->getVectorDistriValue(m_emitter->m_orbitRotation, getParticleLifeRate());
		}

		if (m_emitter->getOrbitConfig(Emittter<T>::ROTATERATE, Emittter<T>::SPAWN))
		{
			if (m_emitter->getOrbitConfig(Emittter<T>::ROTATERATE, Emittter<T>::EMITTER_TIME))
				m_orbitRotationRate = m_emitter->getVectorDistriValue(m_emitter->m_orbitRotationRate) / vec3(1000.0f);
			else
				m_orbitRotationRate = m_emitter->getVectorDistriValue(m_emitter->m_orbitRotationRate, getParticleLifeRate()) / vec3(1000.0f);
		}

		float radFactor = glm::pi<float>() / 180.0f;
		m_orbitRotation *= vec3(radFactor);
		m_orbitRotationRateAmount = vec3(0.0f);
	}
}

template<class T>
void Particle<T>::updateSubCoord()
{
	if (m_interlopMode == 0)
		m_subCoord = m_defaultSubCoord;
	else if (m_interlopMode == 1 || m_interlopMode == 2)
	{
		//std::cout << "11111" << std::endl;
		if (m_emitter->getModuleMap()[Emittter<T>::SubUV])
		{
			if (m_coordLength == 0)
				m_subCoord = m_defaultSubCoord;
			else if (m_coordLength > 0)
			{
				float rate = (getParticleLifeRate() >= 1) ? 0.99 : getParticleLifeRate();

				float emitterIndex = m_emitter->getFloatDistriValueFloor(m_emitter->m_subUVIndex, rate);
				emitterIndex = (emitterIndex == 0) ? 0.01 : emitterIndex;

				//std::cout << "emitterIndex " << emitterIndex << " rate" << rate << std::endl;

				float index = floor(emitterIndex);
				float scale = floor(index / m_coordLength);

				//std::cout << "index " << index << " scale" << scale << std::endl;

				m_subCurrentIndex = index - scale * m_coordLength;

				m_subCoord = m_coordList[m_subCurrentIndex];

				if (m_interlopMode == 2)
				{
					if (m_subCurrentIndex + 1 == m_coordLength)
						m_subCoordNext = m_coordList[m_subCurrentIndex];
					else
						m_subCoordNext = m_coordList[m_subCurrentIndex + 1];

					m_subRatio = emitterIndex - index;
				}
			}
		}
		else
		{

			if (m_coordLength == 0)
				m_subCoord = m_defaultSubCoord;
			else if (m_coordLength > 0)
			{
				//std::cout << "22222" << std::endl;
				float rate = (getParticleLifeRate() >= 1) ? 0.99 : getParticleLifeRate();
				m_subCurrentIndex = floor(m_coordLength * rate);
				m_subCoord = m_coordList[m_subCurrentIndex];

				//std::cout << "33333" << std::endl;
				if (m_interlopMode == 2)
				{
					if (m_subCurrentIndex + 1 == m_coordLength)
						m_subCoordNext = m_coordList[m_subCurrentIndex];
					else
						m_subCoordNext = m_coordList[m_subCurrentIndex + 1];

					//std::cout << "44444" << std::endl;
					m_subRatio = m_coordLength * rate - m_subCurrentIndex;
				}
			}
		}

		//std::cout << "m_subCurrentIndex " << m_subCurrentIndex  << " m_coordLength" << m_coordLength <<  std::endl;
	}
	else if (m_interlopMode == 3 || m_interlopMode == 4)
	{
		if (m_coordLength == 0)
			m_subCoord = m_defaultSubCoord;
		else if (m_coordLength > 0)
		{
			float randomInex = floor(m_emitter->m_subUVRandomNum * getParticleLifeRate());

			if (m_subCurrentIndex != randomInex)
			{
				m_subCurrentIndex = randomInex;

				float index = Random::Instance()->IntNum(m_coordLength);

				if (m_interlopMode == 3)
					m_subCoord = m_coordList[index];
				else if (m_interlopMode == 4)
				{
					if (m_subCoord == m_defaultSubCoord && m_subCoordNext == m_defaultSubCoord)
					{
						m_subCoord = m_coordList[Random::Instance()->IntNum(m_coordLength)];
						m_subCoordNext = m_coordList[index];
					}
					else
					{
						m_subCoord = m_subCoordNext;
						m_subCoordNext = m_coordList[index];
					}
				}
			}

			if (m_interlopMode == 4)
				m_subRatio = m_emitter->m_subUVRandomNum * getParticleLifeRate() - m_subCurrentIndex;
		}
	}
}

template<class T>
void Particle<T>::orbitUpdateCal(int64_t dt)
{
	if (m_emitter->getModuleMap()[Emittter<T>::Orbit])
	{
		mat4 rotMat = mat4(1.f);
		
		if (m_emitter->getOrbitConfig(Emittter<T>::OFFSET, Emittter<T>::UPDATE))
		{
			if (m_emitter->getOrbitConfig(Emittter<T>::OFFSET, Emittter<T>::EMITTER_TIME))
				m_orbitOffset = m_emitter->getVectorDistriValue(m_emitter->m_orbitOffset);
			else
				m_orbitOffset = m_emitter->getVectorDistriValue(m_emitter->m_orbitOffset, getParticleLifeRate());

		}

		if (m_emitter->getOrbitConfig(Emittter<T>::ROTATION, Emittter<T>::UPDATE))
		{
			if (m_emitter->getOrbitConfig(Emittter<T>::ROTATION, Emittter<T>::EMITTER_TIME))
				m_orbitRotation = m_emitter->getVectorDistriValue(m_emitter->m_orbitRotation);
			else
				m_orbitRotation = m_emitter->getVectorDistriValue(m_emitter->m_orbitRotation, getParticleLifeRate());
		}

		if (m_emitter->getOrbitConfig(Emittter<T>::ROTATERATE, Emittter<T>::UPDATE))
		{
			if (m_emitter->getOrbitConfig(Emittter<T>::ROTATERATE, Emittter<T>::EMITTER_TIME))
				m_orbitRotationRate = m_emitter->getVectorDistriValue(m_emitter->m_orbitRotationRate) / vec3(1000.0f);
			else
				m_orbitRotationRate = m_emitter->getVectorDistriValue(m_emitter->m_orbitRotationRate, getParticleLifeRate()) / vec3(1000.0f);
		}

		float t = 360.0f * (float)dt;
		m_orbitRotationRateAmount += m_orbitRotationRate * vec3(t);

		vec3 angleVec = m_orbitRotation + m_orbitRotationRateAmount;
		float radFactor = glm::pi<float>() / 180.0f;
		angleVec *= vec3(radFactor);
		rotMat = glm::rotate(rotMat, angleVec.x, vec3(1.0f, 0.0f, 0.0f));
		rotMat = glm::rotate(rotMat, angleVec.y, vec3(0.0f, 1.0f, 0.0f));
		rotMat = glm::rotate(rotMat, angleVec.z, vec3(0.0f, 0.0f, 1.0f));

		vec4 orbitPos = rotMat * vec4(m_orbitOffset, 1.0f);
		m_orbit = vec3(orbitPos.x,orbitPos.y,orbitPos.z);
	}
}

template<class T>
vec3 Particle<T>::attractorCal(int64_t dt, bool baseVel)
{
	if (m_emitter->getModuleMap()[Emittter<T>::PointAttractor])
	{
		vec3 dir = m_emitter->getVectorDistriValue(m_emitter->m_pointAttractorPosition) - (m_trans + m_orbit);
		float distance = glm::length(dir);
		float range = m_emitter->getFloatDistriValue(m_emitter->m_pointAttractorRange);

		if (distance <= range && distance != 0)
		{
			float attractorStrength = 0;

			if (m_emitter->m_strengthByDistance)
			{
				if (range == 0)
					attractorStrength = 0;
				else
				{
					attractorStrength = m_emitter->getFloatDistriValue(m_emitter->m_pointAttractorStrength) * (range - distance) / range;
				}
			}
			else
			{
				attractorStrength = m_emitter->getFloatDistriValue(m_emitter->m_pointAttractorStrength);
			}

			dir = dir / vec3(distance);

			if (attractorStrength < 0)
			{
				dir = -dir;
				attractorStrength = -attractorStrength;
			}


			glm::clamp(dir, vec3(-1), vec3(1));

			if (baseVel == true)
				attractorStrength = attractorStrength * 0.0001;

			vec3 velVec = vec3(attractorStrength * dt);

			return dir * velVec;
		}
		else
		{
			return vec3(0.0f);
		}
	}
	else
		return vec3(0.0f);
}

template<class T>
vec3 Particle<T>::attractorLineCal(int64_t dt)
{
	if (m_emitter->getModuleMap()[Emittter<T>::LineAttractor])
	{
		vec3 endPoint1 = vec3(m_emitter->m_lineAttractorPoint1X, m_emitter->m_lineAttractorPoint1Y, 0.0f);
		vec3 endPoint2 = vec3(m_emitter->m_lineAttractorPoint2X, m_emitter->m_lineAttractorPoint2Y, 0.0f);
		vec3 line = endPoint2 - endPoint1;
		vec3 EP1TOParticle = (m_trans + m_orbit) - endPoint1;
		vec3 projectParticle = line * glm::dot(line, EP1TOParticle) / glm::dot(line, line);

		vec3 ratio = vec3(0.0f);

		if (line.x)
			ratio.x = (projectParticle.x - endPoint1.x) / line.x;
		if (line.y)
			ratio.y = (projectParticle.y - endPoint1.y) / line.y;
		if (line.z)
			ratio.z = (projectParticle.z - endPoint1.z) / line.z;

		float ratiof = -1.0f;

		if (ratio.x || ratio.y || ratio.z)
		{
			if (ratio.x)
				ratiof = ratio.x;
			else if (ratio.y)
				ratiof = ratio.y;
			else if (ratio.z)
				ratiof = ratio.z;
		}

		if (ratiof >= 0 || ratiof <= 1)
		{
			float range = m_emitter->getFloatDistriValue(m_emitter->m_lineAttractorRange);
			vec3 lineToPoint = (m_trans + m_orbit) - projectParticle;
			float distance = glm::length(lineToPoint);

			if (range > 0 && distance < range)
			{
				float strength = m_emitter->getFloatDistriValue(m_emitter->m_lineAttractorStrength) * (range - distance) / range;
				vec3 direction = glm::cross(lineToPoint, line);
				float s = strength * dt / 1000.0f;
				return direction * vec3(s);
			}
			return vec3(0.0f);
		}
		return vec3(0.0f);
	}
	else
	{
		return vec3(0.0f);
	}
}

template<class T>
void Particle<T>::killCanvas()
{
	if (m_emitter->m_clip)
	{
		vec2 canvasSize = m_emitter->m_canvasSize;
		float stepX = canvasSize.x / 2.0f;
		float stepY = canvasSize.y / 2.0f;

		//canvas should do in world space
		//canvas removing will render the last fram that outside the border, better outcome is to do render clip
		vec3 pos = m_pos + m_velocity / vec3(60.0f);
		
		bool outSide = (pos.x < -stepX) || (pos.x > stepX) || (pos.y < -stepY) || (pos.y > stepY);

		if (outSide)
		{
			setActivate(false);
			m_currentLife = m_lifeTime + 1.0f;
		}
	}
}

template<class T>
void Particle<T>::killBoxCal()
{
	if (m_emitter->getModuleMap()[Emittter<T>::KillBox])
	{
		float parSize = m_currentSize * 0.5f;
		vec3 topLeft = m_emitter->getVectorDistriValue(m_emitter->m_killBoxTopLeft);
		vec3 lowRigth = m_emitter->getVectorDistriValue(m_emitter->m_killBoxLowRight);

		//box should do in local space
		//will remove before the last frame 
		vec3 pos = m_trans + m_orbit + m_velocity / vec3(60.0f) + parSize;

		bool inSide = (pos.x < lowRigth.x) && (pos.x > topLeft.x) && (pos.y < topLeft.y) && (pos.y > lowRigth.y);
	    
		if (m_emitter->m_killInside == inSide)
		{
			setActivate(false);
			m_currentLife = m_lifeTime + 1.0f;
		}
	}
}

template<class T>
void Particle<T>::killHeightCal()
{
	if (m_emitter->getModuleMap()[Emittter<T>::KillHeight])
	{
		float parSize = m_currentSize * 0.5f;
		float height = m_emitter->getFloatDistriValue(m_emitter->m_killHeight);
		//height should do in local space
		//will remove before the last frame 
		vec3 pos = m_trans + m_orbit + m_velocity / vec3(60.0f) + parSize;
		bool aboveFloor = pos.y > height;
		bool onFloor = m_emitter->m_killFloor;
		if (onFloor == aboveFloor)
		{
			setActivate(false);
			m_currentLife = m_lifeTime + 1.0f;
		}
	}
}

template<class T>
void Particle<T>::processMaxCollisionOpt(int type)
{
	if (type == 0)
	{
		setActivate(false);
		m_currentLife = m_lifeTime + 1.0f;
	}
	else if (type == 1)
	{
		//freeze
		setUpdate(false);
	}
	else if (type == 2)
	{
		//do nothing
	}
	else if (type == 3)
	{
		setUpdateTrans(false);
	}
	else if (type == 4)
	{
		setUpdateRot(false);
	}
	else if (type == 5)
	{
		setUpdateTrans(false);
		setUpdateRot(false);
	}
}

template<class T>
void Particle<T>::floorCollisionCal()
{
	int maxCollision = m_emitter->getFloatDistriValue(m_emitter->m_floorMaxCollision);

	bool doCollision = (m_collisionCount < maxCollision) || (maxCollision == -1);

	//float parSize = m_currentSize * 0.5f;

	if (doCollision)
	{
		float pos = m_emitter->m_floorCollisionAxisPos;
		int dir = m_emitter->m_floorCollisionAxis;
		vec3 frameVel = m_velocity / vec3(60.0f);
		vec3 parPos = m_trans + m_orbit + frameVel;

		if (dir == 0)
		{
			vec3 n = vec3(1.0f, 0.0f, 0.0f);
			bool hit = abs(parPos.x - pos) < abs(frameVel.x);

			if (hit && (!m_hitFloor))
			{
				float dot = glm::dot(m_velocity, n);
				m_velocity -= vec3(2.0f) * vec3(dot) * n;
				m_velocity *= m_emitter->getVectorDistriValue(m_emitter->m_floorDampVel);
				m_rotDamp *= m_emitter->getFloatDistriValue(m_emitter->m_floorDampRot);
				m_hitFloor = true;
				m_collisionCount = m_collisionCount + 1;
				m_collisionFrame = true;
			}
		}
		else if (dir == 1)
		{
			vec3 n = vec3(0.0f, 1.0f, 0.0f);
			bool hit = abs(parPos.y - pos) < abs(frameVel.y);

			if (hit && (!m_hitFloor))
			{
				float dot = glm::dot(m_velocity, n);
				m_velocity -= vec3(2.0f) * vec3(dot) * n;
				m_velocity *= m_emitter->getVectorDistriValue(m_emitter->m_floorDampVel);
				m_rotDamp *= m_emitter->getFloatDistriValue(m_emitter->m_floorDampRot);
				m_hitFloor = true;
				m_collisionCount = m_collisionCount + 1;
				m_collisionFrame = true;
			}
		}
	}
	else
		processMaxCollisionOpt(m_emitter->m_floorCollisionCompleteOpt);
}

template<class T>
void Particle<T>::lineCollisionCal()
{
	int maxCollision = m_emitter->getFloatDistriValue(m_emitter->m_lineMaxCollision);

	bool doCollision = (m_collisionCount < maxCollision) || (maxCollision == -1);

	//float parSize = m_currentSize * 0.5f;

	if (doCollision)
	{
		vec2 point0 = vec2(m_emitter->m_lineCollisionPoint0X, m_emitter->m_lineCollisionPoint0Y);
		vec2 point1 = vec2(m_emitter->m_lineCollisionPoint1X, m_emitter->m_lineCollisionPoint1Y);
		vec3 frameVel = m_velocity / vec3(60.0f);
		vec3 p = m_trans + m_orbit + frameVel;
		vec2 pos = vec2(p.x, p.y);
		float dist1 = glm::length(pos - point0);
		float dist2 = glm::length(pos - point1);
		bool hit = abs(dist1 + dist2 - glm::length(point0 - point1)) < glm::length(frameVel);

		if (hit && (!m_hitLine))
		{
			vec3 n = vec3(-(point1.y - point0.y), point1.x - point0.x, 0.0f);
			n = glm::normalize(n);

			float dot = glm::dot(m_velocity, n);
			m_velocity -= vec3(2.0f) * vec3(dot) * n;
			m_velocity *= m_emitter->getVectorDistriValue(m_emitter->m_lineDampVel);
			m_rotDamp *= m_emitter->getFloatDistriValue(m_emitter->m_lineDampRot);
			m_hitLine = true;
			m_collisionCount = m_collisionCount + 1;
			m_collisionFrame = true;
		}
	}
	else
		processMaxCollisionOpt(m_emitter->m_lineCollisionCompleteOpt);
}

template<class T>
void Particle<T>::rectCollisionCal()
{
	int maxCollision = m_emitter->getFloatDistriValue(m_emitter->m_rectMaxCollision);

	bool doCollision = (m_collisionCount < maxCollision) || (maxCollision == -1);

	float parSize = m_currentSize * 0.5f;

	if (doCollision)
	{
		float posX = m_emitter->m_rectCollisionPosX;
		float posY = m_emitter->m_rectCollisionPosY;
		float width = m_emitter->m_rectCollisionWidth;
		float height = m_emitter->m_rectCollisionHeight;
		vec3 parPos = m_trans + m_orbit + m_velocity / vec3(60.0f);
		bool hit = (parPos.x < posX + parSize) || (parPos.x > (posX + width - parSize)) || (parPos.y > posY - parSize) || (parPos.y < (posY - height + parSize));

		if (hit && (!m_hitRect))
		{
			vec3 n = vec3(0.0f);
			if (parPos.y > posY - parSize)
				n = vec3(0.0f, -1.0f, 0.0f);
			else if (parPos.y < (posY - height + parSize))
				n = vec3(0.0f, 1.0f, 0.0f);
			else if (parPos.x < posX + parSize)
				n = vec3(1.0f, 0.0f, 0.0f);
			else if (parPos.x > (posX + width - parSize))
				n = vec3(-1.0f, 0.0f, 0.0f);

			n = glm::normalize(n);

			float dot = glm::dot(m_velocity, n);
			m_velocity -= vec3(2.0f) * vec3(dot) * n;
			m_velocity *= m_emitter->getVectorDistriValue(m_emitter->m_rectDampVel);
			m_rotDamp *= m_emitter->getFloatDistriValue(m_emitter->m_rectDampRot);
			m_hitRect = true;
			m_collisionCount = m_collisionCount + 1;
			m_collisionFrame = true;
		}
	}
	else
	{
		processMaxCollisionOpt(m_emitter->m_rectCollisionCompleteOpt);
	}
}

template<class T>
void Particle<T>::sphereCollisionCal()
{
	int maxCollision = m_emitter->getFloatDistriValue(m_emitter->m_sphereMaxCollision);

	bool doCollision = (m_collisionCount < maxCollision) || (maxCollision == -1);

	float parSize = m_currentSize * 0.5f;

	if (doCollision)
	{
		float posX = m_emitter->m_sphereCollisionCenterX;
		float posY = m_emitter->m_sphereCollisionCenterY;
		float radius = m_emitter->m_sphereCollisionRadius;

		vec3 parPos = m_trans + m_orbit + m_velocity / vec3(60.0f);

		float parLength = glm::length(vec2(parPos.x - posX, parPos.y - posY));
		float velLength = glm::length(m_velocity);

		bool hit = abs(parLength - radius) - parSize < velLength / 60.0f;

		if (hit && (!m_hitSphere))
		{
			vec3 n = vec3(parPos.x - posX, parPos.y - posY, 0.0f);
			n = glm::normalize(n);

			float dot = glm::dot(m_velocity, n);
			m_velocity -= vec3(2.0f) * vec3(dot) * n;
			m_velocity *= m_emitter->getVectorDistriValue(m_emitter->m_sphereDampVel);
			m_rotDamp *= m_emitter->getFloatDistriValue(m_emitter->m_sphereDampRot);
			m_hitSphere = true;
			m_collisionCount = m_collisionCount + 1;
			m_collisionFrame = true;
		}
	}
	else
	{
		processMaxCollisionOpt(m_emitter->m_sphereCollisionCompleteOpt);
	}
}

template <class T>
bool Particle<T>::getCollisionFrameState()
{
	return m_collisionFrame;
}









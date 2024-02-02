#ifndef  PARTICLE_H
#define  PARTICLE_H
#include "random.h"
#include "Emitter.h"
#define MATH_PI 3.1415926

template<class T>
class Particle
{
	using vec4 = glm::vec4;
	using mat4 = glm::mat4;
	using mat3 = glm::mat3;
	using mat2 = glm::mat2;
	using vec3 = glm::vec3;
	using vec2 = glm::vec2;
public:
	Particle(Emittter<T> *emitter);
	~Particle();

	Emittter<T> *m_emitter;
	vec3 m_pos;
	vec3 m_oriPos;
	mat4 m_model;
	mat4 m_rotMat;
	float m_currentSize;
	vec3 m_trans;
	vec3 m_worldOffset;
	vec3 m_orbit;
	vec3 m_orbitOffset;
	vec3 m_orbitRotation;
	vec3 m_orbitRotationRate;
	vec3 m_orbitRotationRateAmount;
	bool m_hitFloor;
	bool m_hitLine;
	bool m_hitRect;
	bool m_hitSphere;
	float m_rotate;
	float m_rotRate;
	float m_rotDamp;
	int m_collisionCount;
	bool m_isUpdate;
	bool m_isUpdateTrans;
	bool m_isUpdateRot;
	vec3 m_dirLocOffset;

	bool m_isActivated;
	vec3 m_velocity;
	vec3 m_baseVelocity;
	vec3 m_acceleration;
	float m_drag;
	float m_lifeTime;
	float m_initSize;
	vec3 m_initColor;
	vec3 m_currentColor;
	float m_initAlpha;
	float m_currentAlpha;
	float m_currentLife;
	vec3 m_radial;
	float m_radialSpeed;
	bool m_isTexture;
	int m_flipU;
	int m_flipV;
	vec4 m_defaultSubCoord;
	vec4 m_subCoord;
	int m_interlopMode;
	int m_subCurrentIndex;
	vec4 m_subCoordNext;
	std::vector<vec4> m_coordList;
	int m_coordLength;
	float m_subRatio;
	vec3 m_shapeVel;
	float m_velRotation;
	vec3 m_tangentSpeed;
	float m_worldSpaceRotAdjust;
	bool m_collisionFrame;
	mat4 m_spawnMat;
	vec2 m_spawnViewScale;
	float m_currentScaleFactor;
	mat2 m_currentParentRotationMat;
	
	void setOriPos(vec3 pos);
	vec3 getShaderAttriPos();
	float getShaderAttriSize();
	vec3 getShaderAttriColor();
	float getShaderAttriAlpha();
	float getShaderAttriFlipU();
	float getShaderAttriFlipV();
	float getShaderAttriRot();
	vec4 getShaderAttriSubCoord();
	vec4 getShaderAttriSubCoordNext();
	float getShaderAttriSubRatio();
	void setVelocity(vec3 vel);
	vec3 getVelocity();
	float getRotation();
	void setModelMatrix(mat4 mat);
	mat4 getModelMatrix();


	void reset(int index);
	void update(int64_t dt, int index);
	void updateLife(int64_t dt);
	
	bool isDead();
	bool isActivated();
	void setActivate(bool val);
	bool isUpdate();
	void setUpdate(bool val);
	bool isUpdateTrans();
	void setUpdateTrans(bool update);
	bool isUpdateRot();
	void setUpdateRot(bool rot);
	float getParticleLifeRate();

	//calculation in reset
	void setFlipUV();
	void velocityConeCal();
	void sphereLocCal();
	void triangleLocCal();
	void orbitSetCal();


	//calculation in update
	void updateSubCoord();
	void orbitUpdateCal(int64_t dt);
	vec3 attractorCal(int64_t dt, bool baseVel);
	vec3 attractorLineCal(int64_t dt);
	void killCanvas();
	void killBoxCal();
	void killHeightCal();
	void processMaxCollisionOpt(int type);
	void floorCollisionCal();
	void lineCollisionCal();
	void rectCollisionCal();
	void sphereCollisionCal();
	bool getCollisionFrameState();

};
#endif // ! PARTICLE_H




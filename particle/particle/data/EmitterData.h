#pragma once
#include <math.h>

#include "FloatDistriData.h"
#include "VectorDistriData.h"
#include "ParticleEventData.h"
#include "LuaIntf/LuaIntf.h"

#define Get_Float(keyName, keyValue)\
emitterDataRef.has(keyName) && (emitterDataRef.get(keyName).type() == LuaIntf::LuaTypeID::NUMBER) ? emitterDataRef.get(keyName).toValue<float>() : keyValue;\

#define Get_Int(keyName, keyValue)\
emitterDataRef.has(keyName) && (emitterDataRef.get(keyName).type() == LuaIntf::LuaTypeID::NUMBER) ? emitterDataRef.get(keyName).toValue<int>() : keyValue;\

#define Get_Boolean(keyName, keyValue)\
emitterDataRef.has(keyName) && emitterDataRef.get(keyName).type() == LuaIntf::LuaTypeID::BOOLEAN ? emitterDataRef.get(keyName).toValue<bool>() : keyValue;\

#define Get_String(keyName, keyValue)\
emitterDataRef.has(keyName) && emitterDataRef.get(keyName).type() == LuaIntf::LuaTypeID::STRING ? emitterDataRef.get(keyName).toValue<std::string>() : keyValue;\

typedef struct TextureInfo
{
	float x = 0;
    float y = 0;
	float width = 0;
	float height = 0;
	bool rotated = false;
	bool isPinMap = false;
} TextureInfo;

class EmitterData
{
	using vec3 = glm::vec3;

public:	
	EmitterData();
	EmitterData(LuaIntf::LuaRef &emitterDataRef);
	~EmitterData();

private:
	FloatDistriData* importFloatDistri(LuaIntf::LuaRef floatDistriData);
	VectorDistriData* importVectorDistri(LuaIntf::LuaRef vectorDistriData);

public:
	enum ModuleType {
		Required,
		Spawn,
		InitialSize,
		SizeByScale,
		SizeByLife,
		SizeBySpeed,
		Lifetime,
		InitialColor,
		ColorOverLife,
		ColorScaleLife,
		InitialVelocity,
		VelocityCone,
		VelOverLife,
		InitialAccel,
		Drag,
		AccelOverLife,
		InitRotate,
		RotateOverLife,
		InitRotRate,
		RotRateLife,
		InitLocation,
		WorldOffset,
		DirectLocation,
		EmitterInitLoc,
		EmitterDirectLoc,
		Sphere,
		Triangle,
		SubUV,
		Orbit,
		PointAttractor,
		LineAttractor,
		KillBox,
		KillHeight,
		CollisionFloor,
		CollisionLine,
		CollisionRect,
		CollisionSphere,
		EventGenerator,
		EventReceiver,
	};

	bool m_moduleMap[39] = { true, true,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false };

	int m_particleNum;
	TextureInfo m_texturePathInfo;

	//emitter and defalut modules' attri
	std::string m_emitterName;
	float m_emitterPosX;
	float m_emitterPosY;
	float m_emitterWorldPosX;
	float m_emitterWorldPosY;
	float m_emitterRot;

	bool m_killOnComplete;
	bool m_killOnDeactivate;

	int64_t	m_duration;
	int64_t	m_durationLow;
	bool m_useRange;
	bool m_durationRecal;

	int m_loop;

	int64_t m_delay;
	int64_t m_delayLow;
	bool m_delayUseRange;
	bool m_delayFirstLoop;

	int m_maxCount;
	bool m_countUseMax;

	int m_subUVMode;
	int m_subUVHori;
	int m_subUVVerti;
	int m_subUVRandomNum;

	bool m_clip;
	bool m_isLocalSpace;

	int m_flipUV;
	bool m_flipTexcoordU;
	bool m_flipTexcoordV;
	bool m_randomTexU;
	bool m_randomTexV;

	int m_brustNum;
	int m_brustNumLow;
	float m_brustTiming;
	bool m_useBrust;


	//modules's attri
	float m_speedSizeX;
	float m_speedSizeY;
	float m_speedSizeXMax;
	float m_speedSizeYMax;

	bool m_clampAlpha;
	bool m_clampAlphaLife;
	bool m_colorScaleEmitterLife;

	float m_coneDirection;
	bool m_velocityAbsolute;

	int m_locDistriPoint;
	float m_locDistriThreshold;
	int m_worldOffsetPoint;
	float m_worldOffsetThreshold;

	std::string	m_locEmitterName;
	int m_locEmitterMode;
	int m_locEmitterCount;
	bool m_inheritSourceVelocity;
	bool m_inheritSourceRotation;
	float m_inheritVelScale;
	float m_inheritRotScale;
	std::string m_locDirectEmitterName;

	bool m_spherePositiveX;
	bool m_sphereNegativeX;
	bool m_spherePositiveY;
	bool m_sphereNegativeY;
	bool m_sphereSurface;
	bool m_sphereVelocity;

	bool m_orbitOffsetSpawn;
	bool m_orbitOffsetUpdate;
	bool m_orbitOffsetEmitterTime;
	bool m_orbitRotationSpawn;
	bool m_orbitRotationUpdate;
	bool m_orbitRotationEmitterTime;
	bool m_orbitRotationRateSpawn;
	bool m_orbitRotationRateUpdate;
	bool m_orbitRotationRateEmitterTime;
	bool m_strengthByDistance;
	bool m_affectBaseVelocity;

	float m_lineAttractorPoint1X;
	float m_lineAttractorPoint1Y;
	float m_lineAttractorPoint2X;
	float m_lineAttractorPoint2Y;

	bool m_killInside;
	bool m_killFloor;

	int m_floorCollisionAxis;
	int m_floorCollisionDelayAmount;
	float m_floorCollisionAxisPos;
	int m_floorCollisionCompleteOpt;

	float m_lineCollisionPoint0X;
	float m_lineCollisionPoint0Y;
	float m_lineCollisionPoint1X;
	float m_lineCollisionPoint1Y;
	int m_lineCollisionDelayAmount;
	int m_lineCollisionCompleteOpt;

	float m_rectCollisionPosX;
	float m_rectCollisionPosY;
	float m_rectCollisionWidth;
	float m_rectCollisionHeight;
	int m_rectCollisionDelayAmount;
	int m_rectCollisionCompleteOpt;

	float m_sphereCollisionCenterX;
	float m_sphereCollisionCenterY;
	float m_sphereCollisionRadius;
	int m_sphereCollisionDelayAmount;
	int m_sphereCollisionCompleteOpt;

	bool m_velRotation;
	//float m_tangentSpeed;

	FloatDistriData*  m_emission;
	FloatDistriData*  m_emissionScale;
	FloatDistriData*  m_brustScale;
	FloatDistriData*  m_initSize;
	FloatDistriData*  m_sizeLife;
	FloatDistriData*  m_sizeScale;
	FloatDistriData*  m_lifeTime;
	VectorDistriData* m_initColor;
	FloatDistriData*  m_initAlpha;
	VectorDistriData* m_colorOverLife;
	FloatDistriData*  m_alphaOverLife;
	VectorDistriData* m_colorScaleOverLife;
	FloatDistriData*  m_alphaScaleOverLife;
	VectorDistriData* m_initVelocity;
	FloatDistriData*  m_initVelocityRadial;
	VectorDistriData* m_velOverLife;
	FloatDistriData*  m_coneVelocityAngle;
	FloatDistriData*  m_coneVelocityVelocity;
	VectorDistriData* m_initAcceleration;
	FloatDistriData*  m_drag;
	VectorDistriData* m_accelOverLife;
	FloatDistriData*  m_initRotate;
	FloatDistriData*  m_rotateOverLife;
	FloatDistriData*  m_initRotRate;
	FloatDistriData*  m_rotRateLife;
	VectorDistriData* m_initLocation;
	VectorDistriData* m_worldOffset;
	VectorDistriData* m_directLocation;
	VectorDistriData* m_dirLocationOffset;
	VectorDistriData* m_dirLocationScale;
	FloatDistriData*  m_sphereRadius;
	FloatDistriData*  m_sphereVelocityScale;
	VectorDistriData* m_sphereOffset;
	FloatDistriData*  m_triangleHeight;
	FloatDistriData*  m_triangleAngle;
	VectorDistriData* m_triangleOffset;
	FloatDistriData*  m_subUVIndex;
	VectorDistriData* m_orbitOffset;
	VectorDistriData* m_orbitRotation;
	VectorDistriData* m_orbitRotationRate;
	VectorDistriData* m_pointAttractorPosition;
	FloatDistriData*  m_pointAttractorRange;
	FloatDistriData*  m_pointAttractorStrength;
	FloatDistriData*  m_lineAttractorRange;
	FloatDistriData*  m_lineAttractorStrength;
	VectorDistriData* m_killBoxTopLeft;
	VectorDistriData* m_killBoxLowRight;
	FloatDistriData*  m_killHeight;
	VectorDistriData* m_floorDampVel;
	FloatDistriData*  m_floorDampRot;
	FloatDistriData*  m_floorMaxCollision;
	VectorDistriData* m_lineDampVel;
	FloatDistriData*  m_lineDampRot;
	FloatDistriData*  m_lineMaxCollision;
	VectorDistriData* m_rectDampVel;
	FloatDistriData*  m_rectDampRot;
	FloatDistriData*  m_rectMaxCollision;
	VectorDistriData* m_sphereDampVel;
	FloatDistriData*  m_sphereDampRot;
	FloatDistriData*  m_sphereMaxCollision;
	ParticleEventData* m_particleEvent;
};


#ifndef EMITTER_H
#define EMITTER_H
#include <vector>
#include <iostream>

#include "FloatDistri.h"
#include "VectorDistri.h"
#include "ParticleEvent.h"
#include "ParticleLoader.h"

#define EMITTER_FRAME_TIME_STEP = 100.0/6.0   //1000ms / 60frame
#define PARTICLE_FRAME_TIME_STEP = 10.0/6.0   //1000ms / 600frame
#define PARTICLE_LIFE_CONSTANT = 1000         //its a fake lifetime in order to have reasonable precsion for baking data,
                                              //due to particles' life time could be variant
                                              //when particles' life is greater than 10, it may lost accurancy
#define genStruct(formatType,length) typedef struct formatType { float data[length];}formatType;

genStruct(format3, 3)
genStruct(format4, 4)
genStruct(format5, 5)
genStruct(format6, 6)
genStruct(format7, 7)
genStruct(format8, 8)
genStruct(format9, 9)
genStruct(format10, 10)
genStruct(format11, 11)
genStruct(format12, 12)
genStruct(format13, 13)
genStruct(format14, 14)
genStruct(format15, 15)
genStruct(format16, 16)
genStruct(format17, 17)
genStruct(format18, 18)
genStruct(format19, 19)
genStruct(format20, 20)
genStruct(format21, 21)
genStruct(format22, 22)
genStruct(format23, 23)
genStruct(format24, 24)
genStruct(format25, 25)
genStruct(format26, 26)
genStruct(format27, 27)
genStruct(format28, 28)
genStruct(format29, 29)

template<class T>
class Particle;
//24

template<class T>
class Emittter
{
	using vec4 = glm::vec4;
	using vec3 = glm::vec3;
	using vec2 = glm::vec2;
	using mat4 = glm::mat4;
	using mat3 = glm::mat3;
	using mat2 = glm::mat2;
	//using json = nlohmann::json;
	using jsonDoc = rapidjson::Document;
	using jsonVal = rapidjson::Value;

	struct ParticleEventInfo
	{
		vec3 pos;
		vec3 vel;
		//float time;
	};

	typedef std::map<std::string, std::vector<ParticleEventInfo>> EventParticleMap;

public:
	Emittter();
	~Emittter();
	enum ModuleType {   Required, 
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
	enum ORBIT_DATA_TYPE {OFFSET,ROTATION,ROTATERATE};
	enum ORBIT_CONTROL_TYPE {SPAWN,UPDATE,EMITTER_TIME};
	enum DISTRI_TYPE {FLOAT_DISTRI,VECTOR_DISTRI};
	enum RUNNING_FRAME_STATE {IDEL,RUNNING,LOOP_END,FINISHED};

	bool m_moduleMap[39] = { true, true,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false };
	jsonDoc m_attributeFormat;
	jsonDoc m_document;

	int m_particleNum;
	bool m_isVisible;
    jsonVal m_texturePath;
	TextureInfo m_texturePathInfo;
	int m_editingMode;
	//float m_worldSpaceRotAdjust;
	int m_locParticleIndex;
	vec2 m_textureSize;
	vec2 m_canvasSize;

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

	int m_subUVMode;
	int m_subUVHori;
	int m_subUVVerti;
	int m_subUVRandomNum;

	bool m_clip;
	bool m_isLocalSpace;
	bool m_countUseMax;

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
	
	FloatDistri*  m_emission;
	FloatDistri*  m_emissionScale;
	FloatDistri*  m_brustScale;
	FloatDistri*  m_initSize;
	FloatDistri*  m_sizeLife;
	FloatDistri*  m_sizeScale;
	FloatDistri*  m_lifeTime;
	VectorDistri* m_initColor;
	FloatDistri*  m_initAlpha;
	VectorDistri* m_colorOverLife;
	FloatDistri*  m_alphaOverLife;
	VectorDistri* m_colorScaleOverLife;
	FloatDistri*  m_alphaScaleOverLife;
	VectorDistri* m_initVelocity;
	FloatDistri*  m_initVelocityRadial;
	VectorDistri* m_velOverLife;
	FloatDistri*  m_coneVelocityAngle;
	FloatDistri*  m_coneVelocityVelocity;
	VectorDistri* m_initAcceleration;
	FloatDistri*  m_drag;
	VectorDistri* m_accelOverLife;
	FloatDistri*  m_initRotate;
	FloatDistri*  m_rotateOverLife;
	FloatDistri*  m_initRotRate;
	FloatDistri*  m_rotRateLife;
	VectorDistri* m_initLocation;
	VectorDistri* m_worldOffset;
	VectorDistri* m_directLocation;
	VectorDistri* m_dirLocationOffset;
	VectorDistri* m_dirLocationScale;
	FloatDistri*  m_sphereRadius;
	FloatDistri*  m_sphereVelocityScale;
	VectorDistri* m_sphereOffset;
	FloatDistri*  m_triangleHeight;
	FloatDistri*  m_triangleAngle;
	VectorDistri* m_triangleOffset;
	FloatDistri*  m_subUVIndex;
	VectorDistri* m_orbitOffset;
	VectorDistri* m_orbitRotation;
	VectorDistri* m_orbitRotationRate;
	VectorDistri* m_pointAttractorPosition;
	FloatDistri*  m_pointAttractorRange;
	FloatDistri*  m_pointAttractorStrength;
	FloatDistri*  m_lineAttractorRange;
	FloatDistri*  m_lineAttractorStrength;
	VectorDistri* m_killBoxTopLeft;
	VectorDistri* m_killBoxLowRight;
	FloatDistri*  m_killHeight;
	VectorDistri* m_floorDampVel;
	FloatDistri*  m_floorDampRot;
	FloatDistri*  m_floorMaxCollision;
	VectorDistri* m_lineDampVel;
	FloatDistri*  m_lineDampRot;
	FloatDistri*  m_lineMaxCollision;
	VectorDistri* m_rectDampVel;
	FloatDistri*  m_rectDampRot;
	FloatDistri*  m_rectMaxCollision;
	VectorDistri* m_sphereDampVel;
	FloatDistri*  m_sphereDampRot;
	FloatDistri*  m_sphereMaxCollision;
	ParticleEvent* m_particleEvent;

	//inner state member
	int64_t m_currentDuration;
	int64_t m_currentDelay;
	int m_currentIndex;
	int m_currentBrust;
	int m_particleCount;
	int64_t m_elapsed;
	int64_t m_elapsedDraw;
	float m_emitCount;
	int m_loopCount;
	float m_emitterLifeTime;
	float m_pinAngle;
	vec4 m_pinCoord;
	std::vector<vec4> m_coordList;
	std::vector<Particle<T>*> m_particleList;
	std::vector<T> m_shaderAttribute;
	int m_attributeFormatLength;
	int m_stripeSize;
	
	jsonDoc emitterData;
	std::vector<vec3> locEmitterPosData;
	std::vector<vec3> locEmitterVelData;
	std::vector<float> locEmitterRotData;
	std::vector<vec3> directEmitterPosData;
	RUNNING_FRAME_STATE m_emitterRunningState;
	EventParticleMap m_deathParticleGenDataMap;
	EventParticleMap m_spawnParticleGenDataMap;
	EventParticleMap m_collisionParticleGenDataMap;
	EventParticleMap m_receiverParticleGenDataMap;
	int m_deathParticleFrameCounter;
	int m_spawnParticleFrameCounter;
	int m_collisionParticleFrameCounter;
	jsonDoc m_receivedDataJson;
	std::string m_frameData;
	mat4 m_currentMat;
	vec2 m_currentViewScale;
	//std::string m_particleEventDataString;

	void loadEmitterData(std::string data);
	void loadEmitterDataFromId(std::string id);
	FloatDistri* importFloatDistri(jsonVal& distri);
	FloatDistri* importFloatDistriByStr(std::string distriStr);//
	FloatDistri* importFloatDistri(FloatDistriData* floatDistriData);
	VectorDistri* importVectorDistri(jsonVal& distri);
	VectorDistri* importVectorDistriByStr(std::string distriStr);//
	VectorDistri* importVectorDistri(VectorDistriData* vectorDistriData);
	void setAttributeFormat();
	bool isFull();
	bool isMax();

	Particle<T> *addParticleInner();
	void addParticle();
	void addParticlePos(vec3 pos);
	void addParticleVel(vec3 vel);
	void addParticlePosVel(vec3 pos, vec3 vel);
	void applyParticleEvent(std::string particleEventDataStr);
	void addParticleByEvent();

	void clearAllEventParticleMap();
	void clearEventParticleMap(EventParticleMap& eventParMap);

	bool allDead();
	void updateParticle(int64_t dt, Particle<T> *par, int i);
	void update(int64_t dt);
	
	void EventParticleDataToJson(EventParticleMap &eventDataMap, jsonVal& eventDataCollector, jsonDoc::AllocatorType& allocator);
	std::string getParticleEventData();
	//LuaIntf::LuaRef getParticleEventData();

	void reactivated();
	void resetParticlePool();
	void reset();
	void clear();
	float getFloatDistriValue(FloatDistri *dis);
	float getFloatDistriValue(FloatDistri *dis, float parLifeRate);
	float getFloatDistriValueFloor(FloatDistri *dis);
	float getFloatDistriValueFloor(FloatDistri *dis, float parLifeRate);
	vec3 getVectorDistriValue(VectorDistri * dis);
	vec3 getVectorDistriValue(VectorDistri * dis, float parLifeRate);
	vec3 getVectorDistriValueFloor(VectorDistri * dis);
	vec3 getVectorDistriValueFloor(VectorDistri * dis, float parLifeRate);
	float clampVal(float val);
	void setSubCoordList();
	std::vector<vec4> getSubCoordList();
	int getParticleCount();
	//float getParticleLifeRate();
	int getMaxParticleCount();
	std::string getAttributeFormat();
	int getParticleNum();
	int getAttriStripeSize();
	void setCurrentBrust();
	int getCurrentBrust();
	void setCurrentDuration();
	int64_t getCurrentDuration();
	void setCurrentDelay();
	int64_t getCurrentDelay();
	void setFlipUV();
	void setFlipTexU(bool val);
	void setFlipTexV(bool val);
	void setRandomFlipU(bool val);
	void setRandomFlipV(bool val);
	float getSpeedSizeX();
	float getSpeedSizeY();
	int getOrbitConfig(int dataType, int controlType);
	float getInitAlphaValue();
	float getAlphaOverLifeValue(float parLifeRate);
	bool* getModuleMap();
	float getEmitterLifeTime();
	void* getShaderAttribute();
	std::string getShaderLocAttribute();
	void setLocEmitterAttribute(std::string posAttribute);
	void setDirectEmitterAttribute(std::string posAttribute);
	std::vector<vec3> getLocPosAttribute();
	std::vector<vec3> getLocVelAttribute();
	std::vector<float> getLocRotAttribute();
	std::vector<vec3> getDirectPosAttribute();
	vec3 getInitLocationValue();
	vec3 getWorldOffsetValue();
	vec3 locCal(VectorDistri* distri, int locPoint);
	void setTextureSize(float w, float h);
	void setCanvasSize(float w, float h);
	int getLoop();
	int getLoopCount();
	void setLocParticleIndex(int index);
	int getLocParticleIndex();
	void updateEmitterWorldPos(float worldPosX, float worldPosY);
	void updateEmitterCurrentMatrix(float num1, float num2, float num3, float num4, float num5, float num6, float num7, float num8,
									float num9, float num10, float num11, float num12, float num13, float num14, float num15, float num16);
	void updateEmitterCurrentViewScale(float scaleX, float scaleY);
	std::string getFrameData();
};
#endif // ! EMITTER_H

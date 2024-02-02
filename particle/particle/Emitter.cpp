#include "Emitter.h"
#include "Particle.h"
#include <math.h>
#include <limits>
//#include "json.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

//extern lua_State* global_lua_state;

using vec4 = glm::vec4;
using vec3 = glm::vec3;
using vec2 = glm::vec2;
using mat4 = glm::mat4;
//using json = nlohmann::json;
using jsonDoc = rapidjson::Document;
using jsonVal = rapidjson::Value;

template <typename T>
Emittter<T>::Emittter()
	: m_currentIndex(0)
	,m_particleCount(0)
	,m_particleNum(0)
	,m_elapsed(0)
	,m_elapsedDraw(0)
	,m_emitCount(0)
	,m_loopCount(0)
	,m_isVisible(true)
	,m_emitterLifeTime(0)
	,m_stripeSize(3)
	,m_emitterRunningState(RUNNING_FRAME_STATE::IDEL)
	,m_texturePath("")
	//,m_worldSpaceRotAdjust(0)
	,m_locParticleIndex(0)
	,m_textureSize(vec2(0.0f))
	,m_canvasSize(vec2(0.0f))

	,m_emitterName("Emitter")
	,m_emitterPosX(0)
	,m_emitterPosY(0)
	,m_emitterWorldPosX(0)
	,m_emitterWorldPosY(0)
	,m_emitterRot(0)

	,m_killOnComplete(false)
	,m_killOnDeactivate(true)

	,m_duration(3000)
	,m_durationLow(0)
	,m_useRange(false)
	,m_durationRecal(false)

	,m_loop(0)

	,m_delay(500)
	,m_delayLow(0)
	,m_delayUseRange(false)
	,m_delayFirstLoop(false)

	,m_maxCount(0)

	,m_subUVHori(1)
	,m_subUVVerti(1)
	,m_subUVMode(0)
	,m_subUVRandomNum(1)

	,m_clip(true)
	,m_isLocalSpace(true)
	,m_countUseMax(false)

	,m_flipUV(0)
	,m_flipTexcoordU(false)
	,m_flipTexcoordV(false)
	,m_randomTexU(false)
	,m_randomTexV(false)
	
	,m_brustNum(0)
	,m_brustNumLow(-1)
	,m_brustTiming(0)
	,m_useBrust(true)

	,m_speedSizeX(1)
	,m_speedSizeY(1)
	,m_speedSizeXMax(0)
	,m_speedSizeYMax(0)

	,m_clampAlpha(false)
	,m_clampAlphaLife(false)
	,m_colorScaleEmitterLife(false)

	,m_coneDirection(0)
	,m_velocityAbsolute(false)

	,m_locDistriPoint(0)
	,m_locDistriThreshold(0)
	,m_worldOffsetPoint(0)
	,m_worldOffsetThreshold(0)

	,m_locEmitterName("")
	,m_locEmitterMode(0)
	,m_locEmitterCount(0)
	,m_inheritSourceVelocity(false)
	,m_inheritSourceRotation(false)
	,m_inheritVelScale(1)
	,m_inheritRotScale(1)
	,m_locDirectEmitterName("")

	,m_spherePositiveX(true)
	,m_sphereNegativeX(true)
	,m_spherePositiveY(true)
	,m_sphereNegativeY(true)
	,m_sphereSurface(false)
	,m_sphereVelocity(false)

	,m_orbitOffsetSpawn(false)
	,m_orbitOffsetUpdate(false)
	,m_orbitOffsetEmitterTime(false)
	,m_orbitRotationSpawn(false)
	,m_orbitRotationUpdate(false)
	,m_orbitRotationEmitterTime(false)
	,m_orbitRotationRateSpawn(false)
	,m_orbitRotationRateUpdate(false)
	,m_orbitRotationRateEmitterTime(false)
	,m_strengthByDistance(false)
	,m_affectBaseVelocity(false)

	,m_lineAttractorPoint1X(0)
	,m_lineAttractorPoint1Y(0)
	,m_lineAttractorPoint2X(0)
	,m_lineAttractorPoint2Y(0)

	,m_killInside(false)
	,m_killFloor(true)

	,m_floorCollisionAxis(0)
	,m_floorCollisionAxisPos(0)
	,m_floorCollisionDelayAmount(0)
	,m_floorCollisionCompleteOpt(0)

	,m_lineCollisionPoint0X(0)
	,m_lineCollisionPoint0Y(0)
	,m_lineCollisionPoint1X(0)
	,m_lineCollisionPoint1Y(0)
	,m_lineCollisionDelayAmount(0)
	,m_lineCollisionCompleteOpt(0)

	,m_rectCollisionPosX(0)
	,m_rectCollisionPosY(0)
	,m_rectCollisionWidth(0)
	,m_rectCollisionHeight(0)
	,m_rectCollisionDelayAmount(0)
	,m_rectCollisionCompleteOpt(0)

	,m_sphereCollisionCenterX(0)
	,m_sphereCollisionCenterY(0)
	,m_sphereCollisionRadius(0)
	,m_sphereCollisionDelayAmount(0)
	,m_sphereCollisionCompleteOpt(0)

	,m_velRotation(false)

	,m_frameData("")

	,m_currentMat(mat4(1.0f))
	,m_currentViewScale(vec2(1.0,1.0))
	
	//,m_tangentSpeed(0)

	,m_emission( new FloatDistri("Emission Rate", 0, 100))
	,m_emissionScale( new FloatDistri("Emission Scale", 1, 1))
	,m_brustScale( new FloatDistri("Brust Scale", 2, 1))
	,m_initSize( new FloatDistri("Init Size", 3, 30))
	,m_sizeLife( new FloatDistri("Size By Life", 4, 1))
	,m_sizeScale( new FloatDistri("Size By Scale", 5, 1))
	,m_lifeTime( new FloatDistri("Lifetime", 6, 1000))
	,m_initColor( new VectorDistri("Init Color", 7, vec3(255, 255, 255), vec3(0, 0, 0), vec3(255, 255, 255)))
	,m_initAlpha( new FloatDistri("Init Alpha", 8, 255, 0, 255))
	,m_colorOverLife( new VectorDistri("Color Over Life", 9, vec3(255, 255, 255), vec3(0, 0, 0), vec3(255, 255, 255)))
	,m_alphaOverLife( new FloatDistri("Alpha Over Life", 10, 255, 0, 255))
	,m_colorScaleOverLife( new VectorDistri("Color Scale Over Life", 11, vec3(1, 1, 1), vec3(0, 0, 0), vec3(1, 1, 1)))
	,m_alphaScaleOverLife( new FloatDistri("Alpha Scale Over Life", 12, 1, 0, 1))
	,m_initVelocity( new VectorDistri("Init Velocity", 13, vec3(0, 100, 0)))
	,m_initVelocityRadial( new FloatDistri("Init Velocity Radial", 14))
	,m_velOverLife( new VectorDistri("Vel Over Life", 35))
	,m_coneVelocityAngle( new FloatDistri("Velocity Angle", 15, 50))
	,m_coneVelocityVelocity( new FloatDistri("Velocity Speed", 16, 100, 100, 100))
	,m_initAcceleration( new VectorDistri("Init Acceleration", 17, vec3(100, 100, 0)))
	,m_drag( new FloatDistri("Drag", 18, 0.5))
	,m_accelOverLife( new VectorDistri("Accel Over Life", 19, vec3(50, 50, 0)))
	,m_initRotate( new FloatDistri("Init Rotate", 20, 90))
	,m_rotateOverLife( new FloatDistri("Rot Over Life", 21, 90))
	,m_initRotRate( new FloatDistri("Init Rot Rate", 22, 5))
	,m_rotRateLife( new FloatDistri("Rot Rate Life", 23, 5))
	,m_initLocation( new VectorDistri("Init Location", 24))
	,m_worldOffset( new VectorDistri("World Offset", 25))
	,m_directLocation( new VectorDistri("Direct Location", 26))
	,m_dirLocationOffset( new VectorDistri("Dir Location Offset", 27))
	,m_dirLocationScale( new VectorDistri("Vel Scale", 28))
	,m_sphereRadius( new FloatDistri("Sphere Radius", 29))
	,m_sphereVelocityScale( new FloatDistri("Sphere Vel Scale", 30, 1, 1, 1))
	,m_sphereOffset( new VectorDistri("Sphere Offset", 31))
	,m_triangleHeight( new FloatDistri("Triangle Height", 32))
	,m_triangleAngle( new FloatDistri("Triangle Angle", 33))
	,m_triangleOffset( new VectorDistri("Triangle Offset", 34))
	,m_subUVIndex( new FloatDistri("SubUV Index", 36))
	,m_orbitOffset( new VectorDistri("Orbit offset", 37))
	,m_orbitRotation( new VectorDistri("Orbit Rotation", 38))
	,m_orbitRotationRate( new VectorDistri("Orbit Rot Rate", 39))
	,m_pointAttractorPosition( new VectorDistri("Point Attractor Pos", 40))
	,m_pointAttractorRange( new FloatDistri("Point Attractor Range", 41))
	,m_pointAttractorStrength( new FloatDistri("Point Attractor Str", 42))
	,m_lineAttractorRange( new FloatDistri("Line Attractor Range", 43))
	,m_lineAttractorStrength( new FloatDistri("Line Attractor Str", 44))
	,m_killBoxTopLeft( new VectorDistri("Box Top Left", 45))
	,m_killBoxLowRight( new VectorDistri("Box Low Right", 46))
	,m_killHeight( new FloatDistri("Kill Height", 47))
	,m_floorDampVel( new VectorDistri("Floor Damp Vel", 48, vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1)))
	,m_floorDampRot( new FloatDistri("Floor Damp Rot", 49, 1, 1, 1))
	,m_floorMaxCollision( new FloatDistri("Floor Max Collision", 50, -1, -1, -1))
	,m_lineDampVel( new VectorDistri("Line Damp Vel", 51, vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1)))
	,m_lineDampRot( new FloatDistri("Line Damp Rot", 52, 1, 1, 1))
	,m_lineMaxCollision( new FloatDistri("Line Max Collision", 53, -1, -1, -1))
	,m_rectDampVel( new VectorDistri("Rect Damp Vel", 54, vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1)))
	,m_rectDampRot( new FloatDistri("Rect Damp Rot", 55, 1, 1, 1))
	,m_rectMaxCollision( new FloatDistri("Rect Max Collision", 56, -1, -1, -1))
	,m_sphereDampVel( new VectorDistri("Sphere Damp Vel", 57, vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1)))
	,m_sphereDampRot( new FloatDistri("Sphere Damp Rot", 58, 1, 1, 1))
	,m_sphereMaxCollision( new FloatDistri("Sphere Max Collision", 59, -1, -1, -1))

{
	//std::cout << "Emittter ctor" << std::endl;

	m_attributeFormat.SetObject();
	m_attributeFormat.AddMember("pinAttribute", false, m_attributeFormat.GetAllocator());
	m_attributeFormat.AddMember("sizeAttribute", false, m_attributeFormat.GetAllocator());
	m_attributeFormat.AddMember("colorAttribute", false, m_attributeFormat.GetAllocator());
	m_attributeFormat.AddMember("flipAttribute", false, m_attributeFormat.GetAllocator());
	m_attributeFormat.AddMember("rotationAttribute", false, m_attributeFormat.GetAllocator());
	m_attributeFormat.AddMember("subUVAttribute", false, m_attributeFormat.GetAllocator());
	m_attributeFormat.AddMember("subUVBlendAttribute", false, m_attributeFormat.GetAllocator());

	m_currentDuration = m_duration;
	m_currentDelay = m_delay;
	m_currentIndex = 0;
	m_currentBrust = 0;
	m_elapsed = 0;
	m_elapsedDraw = 0;
	m_emitCount = 0.0f;
	m_loopCount = 0;
	m_emitterLifeTime = 0.0f;
	m_pinAngle = 0.0f;
	m_pinCoord = vec4(0.0f);
	
	setCurrentBrust();
	setAttributeFormat();

	m_receivedDataJson.SetObject();
}

template<class T>
Emittter<T>::~Emittter()
{
	delete m_particleEvent;

	for (int i = 0; i < m_particleList.size(); i++)
	{
		auto par = m_particleList[i];

		delete par;
	}

	m_particleList.clear();

	delete m_emission;
	delete m_emissionScale;
	delete m_brustScale;
	delete m_initSize;
	delete m_sizeLife;
	delete m_sizeScale;
	delete m_lifeTime;
	delete m_initColor;
	delete m_initAlpha;
	delete m_colorOverLife;
	delete m_alphaOverLife;
	delete m_colorScaleOverLife;
	delete m_alphaScaleOverLife;
	delete m_initVelocity;
	delete m_initVelocityRadial;
	delete m_velOverLife;
	delete m_coneVelocityAngle;
	delete m_coneVelocityVelocity;
	delete m_initAcceleration;
	delete m_drag;
	delete m_accelOverLife;
	delete m_initRotate;
	delete m_rotateOverLife;
	delete m_initRotRate;
	delete m_rotRateLife;
	delete m_initLocation;
	delete m_worldOffset;
	delete m_directLocation;
	delete m_dirLocationOffset;
	delete 	m_dirLocationScale;
	delete 	m_sphereRadius;
	delete m_sphereVelocityScale;
	delete m_sphereOffset;
	delete m_triangleHeight;
	delete m_triangleAngle;
	delete m_triangleOffset;
	delete m_subUVIndex;
	delete m_orbitOffset;
	delete m_orbitRotation;
	delete m_orbitRotationRate;
	delete m_pointAttractorPosition;
	delete m_pointAttractorRange;
	delete m_pointAttractorStrength;
	delete m_lineAttractorRange;
	delete m_lineAttractorStrength;
	delete m_killBoxTopLeft;
	delete m_killBoxLowRight;
	delete m_killHeight;
	delete m_floorDampVel;
	delete m_floorDampRot;
	delete m_floorMaxCollision;
	delete m_lineDampVel;
	delete m_lineDampRot;
	delete m_lineMaxCollision;
	delete m_rectDampVel;
	delete m_rectDampRot;
	delete m_rectMaxCollision;
	delete m_sphereDampVel;
	delete m_sphereDampRot;
	delete m_sphereMaxCollision;
}

template <typename T>
void Emittter<T>::loadEmitterData(std::string data)
{
	//std::cout << "loadEmitterData" << std::endl;
	//std::cout << data.c_str() << std::endl;

	emitterData.Parse(data.c_str());
	

	jsonVal& moduleMap = emitterData["m_moduleMap"];

	m_moduleMap[Required] = moduleMap["Required"].GetBool();
	m_moduleMap[Spawn] = moduleMap["Spawn"].GetBool();
	m_moduleMap[InitialSize] = moduleMap["Initial Size"].GetBool();
	m_moduleMap[SizeByScale] = moduleMap["Size By Scale"].GetBool();
	m_moduleMap[SizeByLife] = moduleMap["Size By Life"].GetBool();
	m_moduleMap[SizeBySpeed] = moduleMap["Size By Speed"].GetBool();
	m_moduleMap[Lifetime] = moduleMap["Lifetime"].GetBool();
	m_moduleMap[InitialColor] = moduleMap["Initial Color"].GetBool();
	m_moduleMap[ColorOverLife] = moduleMap["Color Over Life"].GetBool();
	m_moduleMap[ColorScaleLife] = moduleMap["Color Scale Life"].GetBool();
	m_moduleMap[InitialVelocity] = moduleMap["Initial Velocity"].GetBool();
	m_moduleMap[VelocityCone] = moduleMap["Velocity Cone"].GetBool();
	m_moduleMap[VelOverLife] = moduleMap["Vel Over Life"].GetBool();
	m_moduleMap[InitialAccel] = moduleMap["Initial Accel"].GetBool();
	m_moduleMap[Drag] = moduleMap["Drag"].GetBool();
	m_moduleMap[AccelOverLife] = moduleMap["Accel Over Life"].GetBool();
	m_moduleMap[InitRotate] = moduleMap["Init Rotate"].GetBool();
	m_moduleMap[RotateOverLife] = moduleMap["Rotate Over Life"].GetBool();
	m_moduleMap[InitRotRate] = moduleMap["Init Rot Rate"].GetBool();
	m_moduleMap[RotRateLife] = moduleMap["Rot Rate Life"].GetBool();
	m_moduleMap[InitLocation] = moduleMap["Init Location"].GetBool();
	m_moduleMap[WorldOffset] = moduleMap["World Offset"].GetBool();
	m_moduleMap[DirectLocation] = moduleMap["Direct Location"].GetBool();
	m_moduleMap[EmitterInitLoc] = moduleMap["Emitter Init Loc"].GetBool();
	m_moduleMap[EmitterDirectLoc] = moduleMap["Emitter Direct Loc"].GetBool();
	m_moduleMap[Sphere] = moduleMap["Sphere"].GetBool();
	m_moduleMap[Triangle] = moduleMap["Triangle"].GetBool();
	m_moduleMap[SubUV] = moduleMap["Sub UV"].GetBool();
	m_moduleMap[Orbit] = moduleMap["Orbit"].GetBool();
	m_moduleMap[PointAttractor] = moduleMap["Point Attractor"].GetBool();
	m_moduleMap[LineAttractor] = moduleMap["Line Attractor"].GetBool();
	m_moduleMap[KillBox] = moduleMap["Kill Box"].GetBool();
	m_moduleMap[KillHeight] = moduleMap["Kill Height"].GetBool();
	m_moduleMap[CollisionFloor] = moduleMap["Collision Floor"].GetBool();
	m_moduleMap[CollisionLine] = moduleMap["Collision Line"].GetBool();
	m_moduleMap[CollisionRect] = moduleMap["Collision Rect"].GetBool();
	m_moduleMap[CollisionSphere] = moduleMap["Collision Sphere"].GetBool();

	if (moduleMap.HasMember("Event Generator"))
	{
		m_moduleMap[EventGenerator] = moduleMap["Event Generator"].GetBool();
	}
	if (moduleMap.HasMember("Event Receiver"))
	{
		m_moduleMap[EventReceiver] = moduleMap["Event Receiver"].GetBool();
	}

	//std::cout << "11111111111111111";

	m_particleNum = emitterData["m_particleNum"].IsNumber() ? emitterData["m_particleNum"].GetInt() : 0;
	//std::cout << "a00000";
	//std::cout << emitterData.HasMember("m_texturePath");
	
	if (emitterData.HasMember("m_texturePath")) 
	    m_texturePath = emitterData["m_texturePath"];
	
	//std::cout << "a11111";
	m_emitterName = emitterData["m_emitterName"].GetString();
	//std::cout << "a222222";
	m_emitterPosX = emitterData["m_emitterPosX"].IsNumber() ? emitterData["m_emitterPosX"].GetFloat() : 0.0f;
	//std::cout << "a333333" << "m_emitterPosX" << m_emitterPosX;
	m_emitterPosY = emitterData["m_emitterPosY"].IsNumber() ? emitterData["m_emitterPosY"].GetFloat() : 0.0f;
	//std::cout << "a444444" << "m_emitterPosY" << m_emitterPosY;
	m_emitterRot = emitterData["m_emitterRot"].IsNumber() ? emitterData["m_emitterRot"].GetFloat() : 0.0f;
	//std::cout << "aaaaaa";
	m_killOnComplete = emitterData["m_killOnComplete"].GetBool();
	m_killOnDeactivate = emitterData["m_killOnDeactivate"].GetBool();
	m_useRange = emitterData["m_useRange"].GetBool();
	m_loop = emitterData["m_loop"].IsNumber() ? emitterData["m_loop"].GetInt() : -1;
	m_durationRecal = emitterData["m_durationRecal"].GetBool();
	m_delay = emitterData["m_delay"].IsNumber() ? emitterData["m_delay"].GetInt() : 0;
	m_delayLow = emitterData["m_delayLow"].IsNumber() ? emitterData["m_delayLow"].GetInt() : 0;
	m_delayUseRange = emitterData["m_delayUseRange"].GetBool();
	m_delayFirstLoop = emitterData["m_delayFirstLoop"].GetBool();
	//std::cout << "bbbbb";
	m_maxCount = emitterData["m_maxCount"].IsNumber() ? emitterData["m_maxCount"].GetInt() : 0;
	m_countUseMax = emitterData["m_countUseMax"].GetBool();
	m_flipUV = emitterData["m_flipUV"].IsNumber() ? emitterData["m_flipUV"].GetInt() : 0;
	m_flipTexcoordU = emitterData["m_flipTexcoordU"].GetBool();
	m_flipTexcoordV = emitterData["m_flipTexcoordV"].GetBool();
	m_randomTexU = emitterData["m_randomTexU"].GetBool();
	m_randomTexV = emitterData["m_randomTexV"].GetBool();
	m_subUVHori = emitterData["m_subUVHori"].IsNumber() ? emitterData["m_subUVHori"].GetInt() : 1;
	m_subUVVerti = emitterData["m_subUVVerti"].IsNumber() ? emitterData["m_subUVVerti"].GetInt() : 1;
	m_subUVMode = emitterData["m_subUVMode"].IsNumber() ? emitterData["m_subUVMode"].GetInt() : 0;
	m_subUVRandomNum = emitterData["m_subUVRandomNum"].IsNumber() ? emitterData["m_subUVRandomNum"].GetInt() : 0;
	//std::cout << "cccccc";
	m_brustNum = emitterData["m_brustNum"].IsNumber() ? emitterData["m_brustNum"].GetInt() : 0;
	m_brustNumLow = emitterData["m_brustNumLow"].IsNumber() ? emitterData["m_brustNumLow"].GetInt() : 0;
	m_brustTiming = emitterData["m_brustTiming"].IsNumber() ? emitterData["m_brustTiming"].GetFloat() : 0.0f;
	m_useBrust = emitterData["m_useBrust"].GetBool();
	m_duration = emitterData["m_duration"].IsNumber() ? emitterData["m_duration"].GetInt() : 0;
	m_durationLow = emitterData["m_durationLow"].IsNumber() ? emitterData["m_durationLow"].GetInt() : 0;
	m_clip = emitterData["m_clip"].IsBool() ? emitterData["m_clip"].GetBool() : true;
	m_isLocalSpace = emitterData["m_isLocalSpace"].IsBool() ? emitterData["m_isLocalSpace"].GetBool() : true;
	//std::cout << "222222";

	m_speedSizeX = emitterData["m_speedSizeX"].IsNumber() ? emitterData["m_speedSizeX"].GetFloat() : 1.0f;
	m_speedSizeY = emitterData["m_speedSizeY"].IsNumber() ? emitterData["m_speedSizeY"].GetFloat() : 1.0f;
	m_speedSizeXMax = emitterData["m_speedSizeXMax"].IsNumber() ? emitterData["m_speedSizeXMax"].GetFloat() : 0.0f;
	m_speedSizeYMax = emitterData["m_speedSizeYMax"].IsNumber() ? emitterData["m_speedSizeYMax"].GetFloat() : 0.0f;
	m_clampAlpha = emitterData["m_clampAlpha"].GetBool();
	m_clampAlphaLife = emitterData["m_clampAlphaLife"].GetBool();
	m_colorScaleEmitterLife = emitterData["m_colorScaleEmitterLife"].GetBool();
	m_coneDirection = emitterData["m_coneDirection"].IsNumber() ? emitterData["m_coneDirection"].GetFloat() : 0.0f;
	m_velocityAbsolute = emitterData["m_velocityAbsolute"].GetBool();
	m_locDistriPoint = emitterData["m_locDistriPoint"].IsNumber() ? emitterData["m_locDistriPoint"].GetInt() : 0;
	m_locDistriThreshold = emitterData["m_locDistriThreshold"].IsNumber() ? emitterData["m_locDistriThreshold"].GetFloat() : 0.0f;
	m_worldOffsetPoint = emitterData["m_worldOffsetPoint"].IsNumber() ? emitterData["m_worldOffsetPoint"].GetInt() : 0;
	m_worldOffsetThreshold = emitterData["m_worldOffsetThreshold"].IsNumber() ? emitterData["m_worldOffsetThreshold"].GetFloat() : 0.0f;
	m_locEmitterName = emitterData["m_locEmitterName"].GetString() ;
	m_locEmitterMode = emitterData["m_locEmitterMode"].IsNumber() ? emitterData["m_locEmitterMode"].GetInt() : 0;
	m_locEmitterCount = emitterData["m_locEmitterCount"].IsNumber() ? emitterData["m_locEmitterCount"].GetInt() : 0;
	m_inheritSourceVelocity = emitterData["m_inheritSourceVelocity"].GetBool();
	m_inheritSourceRotation = emitterData["m_inheritSourceRotation"].GetBool();
	m_inheritVelScale = emitterData["m_inheritVelScale"].IsNumber() ? emitterData["m_inheritVelScale"].GetFloat() : 1.0f;
	m_inheritRotScale = emitterData["m_inheritRotScale"].IsNumber() ? emitterData["m_inheritRotScale"].GetFloat() : 1.0f;
	m_locDirectEmitterName = emitterData["m_locDirectEmitterName"].GetString();
	m_spherePositiveX = emitterData["m_spherePositiveX"].GetBool();
	m_sphereNegativeX = emitterData["m_sphereNegativeX"].GetBool();
	m_spherePositiveY = emitterData["m_spherePositiveY"].GetBool();
	m_sphereNegativeY = emitterData["m_sphereNegativeY"].GetBool();
	m_sphereSurface = emitterData["m_sphereSurface"].GetBool();
	m_sphereVelocity = emitterData["m_sphereVelocity"].GetBool();
	m_orbitOffsetSpawn = emitterData["m_orbitOffsetSpawn"].GetBool();
	m_orbitOffsetUpdate = emitterData["m_orbitOffsetUpdate"].GetBool();
	m_orbitOffsetEmitterTime = emitterData["m_orbitOffsetEmitterTime"].GetBool();
	m_orbitRotationSpawn = emitterData["m_orbitRotationSpawn"].GetBool();
	m_orbitRotationUpdate = emitterData["m_orbitRotationUpdate"].GetBool();
	m_orbitRotationEmitterTime = emitterData["m_orbitRotationEmitterTime"].GetBool();
	m_orbitRotationRateSpawn = emitterData["m_orbitRotationRateSpawn"].GetBool();
	m_orbitRotationRateUpdate = emitterData["m_orbitRotationRateUpdate"].GetBool();
	m_orbitRotationRateEmitterTime = emitterData["m_orbitRotationRateEmitterTime"].GetBool();

	//std::cout << "333333";

	m_strengthByDistance = emitterData["m_strengthByDistance"].GetBool();
	m_affectBaseVelocity = emitterData["m_affectBaseVelocity"].GetBool();
	m_lineAttractorPoint1X = emitterData["m_lineAttractorPoint1X"].IsNumber() ? emitterData["m_lineAttractorPoint1X"].GetFloat() : 0.0f;
	m_lineAttractorPoint1Y = emitterData["m_lineAttractorPoint1Y"].IsNumber() ? emitterData["m_lineAttractorPoint1Y"].GetFloat() : 0.0f;
	m_lineAttractorPoint2X = emitterData["m_lineAttractorPoint2X"].IsNumber() ? emitterData["m_lineAttractorPoint2X"].GetFloat() : 0.0f;
	m_lineAttractorPoint2Y = emitterData["m_lineAttractorPoint2Y"].IsNumber() ? emitterData["m_lineAttractorPoint2Y"].GetFloat() : 0.0f;
	m_killInside = emitterData["m_killInside"].GetBool();
	m_killFloor = emitterData["m_killFloor"].GetBool();
	m_floorCollisionAxis = emitterData["m_floorCollisionAxis"].IsNumber() ? emitterData["m_floorCollisionAxis"].GetInt() : 0;
	m_floorCollisionAxisPos = emitterData["m_floorCollisionAxisPos"].IsNumber() ? emitterData["m_floorCollisionAxisPos"].GetFloat() : 0.0f;
	m_floorCollisionDelayAmount = emitterData["m_floorCollisionDelayAmount"].IsNumber() ? emitterData["m_floorCollisionDelayAmount"].GetInt() : 0;
	m_floorCollisionCompleteOpt = emitterData["m_floorCollisionCompleteOpt"].IsNumber() ? emitterData["m_floorCollisionCompleteOpt"].GetInt() : 0;
	m_lineCollisionPoint0X = emitterData["m_lineCollisionPoint0X"].IsNumber() ? emitterData["m_lineCollisionPoint0X"].GetFloat() : 0.0f;
	m_lineCollisionPoint0Y = emitterData["m_lineCollisionPoint0Y"].IsNumber() ? emitterData["m_lineCollisionPoint0Y"].GetFloat() : 0.0f;
	m_lineCollisionPoint1X = emitterData["m_lineCollisionPoint1X"].IsNumber() ? emitterData["m_lineCollisionPoint1X"].GetFloat() : 0.0f;
	m_lineCollisionPoint1Y = emitterData["m_lineCollisionPoint1Y"].IsNumber() ? emitterData["m_lineCollisionPoint1Y"].GetFloat() : 0.0f;
	m_lineCollisionDelayAmount = emitterData["m_lineCollisionDelayAmount"].IsNumber() ? emitterData["m_lineCollisionDelayAmount"].GetInt() : 0;
	m_lineCollisionCompleteOpt = emitterData["m_lineCollisionCompleteOpt"].IsNumber() ? emitterData["m_lineCollisionCompleteOpt"].GetInt() : 0;
	m_rectCollisionPosX = emitterData["m_rectCollisionPosX"].IsNumber() ? emitterData["m_rectCollisionPosX"].GetFloat() : 0.0f;
	m_rectCollisionPosY = emitterData["m_rectCollisionPosY"].IsNumber() ? emitterData["m_rectCollisionPosY"].GetFloat() : 0.0f;
	m_rectCollisionWidth = emitterData["m_rectCollisionWidth"].IsNumber() ? emitterData["m_rectCollisionWidth"].GetFloat() : 0.0f;
	m_rectCollisionHeight = emitterData["m_rectCollisionHeight"].IsNumber() ? emitterData["m_rectCollisionHeight"].GetFloat() : 0.0f;
	m_rectCollisionDelayAmount = emitterData["m_rectCollisionDelayAmount"].IsNumber() ? emitterData["m_rectCollisionDelayAmount"].GetInt() : 0;
	m_rectCollisionCompleteOpt = emitterData["m_rectCollisionCompleteOpt"].IsNumber() ? emitterData["m_rectCollisionCompleteOpt"].GetInt() : 0;
	m_sphereCollisionCenterX = emitterData["m_sphereCollisionCenterX"].IsNumber() ? emitterData["m_sphereCollisionCenterX"].GetFloat() : 0.0f;
	m_sphereCollisionCenterY = emitterData["m_sphereCollisionCenterY"].IsNumber() ? emitterData["m_sphereCollisionCenterY"].GetFloat() : 0.0f;
	m_sphereCollisionRadius = emitterData["m_sphereCollisionRadius"].IsNumber() ? emitterData["m_sphereCollisionRadius"].GetFloat() : 0.0f;
	m_sphereCollisionDelayAmount = emitterData["m_sphereCollisionDelayAmount"].IsNumber() ? emitterData["m_sphereCollisionDelayAmount"].GetInt() : 0;
	m_sphereCollisionCompleteOpt = emitterData["m_sphereCollisionCompleteOpt"].IsNumber() ? emitterData["m_sphereCollisionCompleteOpt"].GetInt() : 0;

	m_velRotation = emitterData["m_velRotation"].IsBool() ? emitterData["m_velRotation"].GetBool() : false;
	//m_tangentSpeed = emitterData["m_tangentSpeed"].IsNumber() ? emitterData["m_tangentSpeed"].GetFloat() : 0.0f;*/

	//std::cout << "444444";

	m_emission = importFloatDistri(emitterData["m_emission"]);
	m_emissionScale = importFloatDistri(emitterData["m_emissionScale"]);
	m_brustScale = importFloatDistri(emitterData["m_brustScale"]);
	m_initSize = importFloatDistri(emitterData["m_initSize"]);
	m_sizeLife = importFloatDistri(emitterData["m_sizeLife"]);
	m_sizeScale = importFloatDistri(emitterData["m_sizeScale"]);
	m_lifeTime = importFloatDistri(emitterData["m_lifeTime"]);
	m_initColor = importVectorDistri(emitterData["m_initColor"]);
	m_initAlpha = importFloatDistri(emitterData["m_initAlpha"]);
	m_colorOverLife = importVectorDistri(emitterData["m_colorOverLife"]);
	m_alphaOverLife = importFloatDistri(emitterData["m_alphaOverLife"]);
	m_colorScaleOverLife = importVectorDistri(emitterData["m_colorScaleOverLife"]);
	m_alphaScaleOverLife = importFloatDistri(emitterData["m_alphaScaleOverLife"]);
	m_initVelocity = importVectorDistri(emitterData["m_initVelocity"]);
	m_initVelocityRadial = importFloatDistri(emitterData["m_initVelocityRadial"]);
	m_velOverLife = importVectorDistri(emitterData["m_velOverLife"]);
	m_coneVelocityAngle = importFloatDistri(emitterData["m_coneVelocityAngle"]);
	m_coneVelocityVelocity = importFloatDistri(emitterData["m_coneVelocityVelocity"]);
	m_initAcceleration = importVectorDistri(emitterData["m_initAcceleration"]);
	m_drag = importFloatDistri(emitterData["m_drag"]);
	m_accelOverLife = importVectorDistri(emitterData["m_accelOverLife"]);
	m_initRotate = importFloatDistri(emitterData["m_initRotate"]);
	m_rotateOverLife = importFloatDistri(emitterData["m_rotateOverLife"]);
	m_initRotRate = importFloatDistri(emitterData["m_initRotRate"]);
	m_rotRateLife = importFloatDistri(emitterData["m_rotRateLife"]);
	m_initLocation = importVectorDistri(emitterData["m_initLocation"]);
	m_worldOffset = importVectorDistri(emitterData["m_worldOffset"]);
	m_directLocation = importVectorDistri(emitterData["m_directLocation"]);
	m_dirLocationOffset = importVectorDistri(emitterData["m_dirLocationOffset"]);
	m_dirLocationScale = importVectorDistri(emitterData["m_dirLocationScale"]);
	m_sphereRadius = importFloatDistri(emitterData["m_sphereRadius"]);
	m_sphereVelocityScale = importFloatDistri(emitterData["m_sphereVelocityScale"]);
	m_sphereOffset = importVectorDistri(emitterData["m_sphereOffset"]);
	m_triangleHeight = importFloatDistri(emitterData["m_triangleHeight"]);
	m_triangleAngle = importFloatDistri(emitterData["m_triangleAngle"]);
	m_triangleOffset = importVectorDistri(emitterData["m_triangleOffset"]);
	m_subUVIndex = importFloatDistri(emitterData["m_subUVIndex"]);
	m_orbitOffset = importVectorDistri(emitterData["m_orbitOffset"]);
	m_orbitRotation = importVectorDistri(emitterData["m_orbitRotation"]);
	m_orbitRotationRate = importVectorDistri(emitterData["m_orbitRotationRate"]);
	m_pointAttractorPosition = importVectorDistri(emitterData["m_pointAttractorPosition"]);
	m_pointAttractorRange = importFloatDistri(emitterData["m_pointAttractorRange"]);
	m_pointAttractorStrength = importFloatDistri(emitterData["m_pointAttractorStrength"]);
	m_lineAttractorRange = importFloatDistri(emitterData["m_lineAttractorRange"]);
	m_lineAttractorStrength = importFloatDistri(emitterData["m_lineAttractorStrength"]);
	m_killBoxTopLeft = importVectorDistri(emitterData["m_killBoxTopLeft"]);
	m_killBoxLowRight = importVectorDistri(emitterData["m_killBoxLowRight"]);
	m_killHeight = importFloatDistri(emitterData["m_killHeight"]);
	m_floorDampVel = importVectorDistri(emitterData["m_floorDampVel"]);
	m_floorDampRot = importFloatDistri(emitterData["m_floorDampRot"]);
	m_floorMaxCollision = importFloatDistri(emitterData["m_floorMaxCollision"]);
	m_lineDampVel = importVectorDistri(emitterData["m_lineDampVel"]);
	m_lineDampRot = importFloatDistri(emitterData["m_lineDampRot"]);
	m_lineMaxCollision = importFloatDistri(emitterData["m_lineMaxCollision"]);
	m_rectDampVel = importVectorDistri(emitterData["m_rectDampVel"]);
	m_rectDampRot = importFloatDistri(emitterData["m_rectDampRot"]);
	m_rectMaxCollision = importFloatDistri(emitterData["m_rectMaxCollision"]);
	m_sphereDampVel = importVectorDistri(emitterData["m_sphereDampVel"]);
	m_sphereDampRot = importFloatDistri(emitterData["m_sphereDampRot"]);
	m_sphereMaxCollision = importFloatDistri(emitterData["m_sphereMaxCollision"]);

	   
	m_particleEvent = new ParticleEvent(emitterData);

 	for (int i = 0; i < m_particleEvent->getGeneratorsCount(); i++)
	{
		auto particleGenList = m_particleEvent->getGenerators();
		auto gen = particleGenList[i];
		if (gen->getEventType() == eSpawn)
		{
			std::vector<ParticleEventInfo> spawnParData;
			m_spawnParticleGenDataMap[gen->getName()] = spawnParData;
		}
		else if (gen->getEventType() == eDeath)
		{
			std::vector<ParticleEventInfo> deathParData;
			m_deathParticleGenDataMap[gen->getName()] = deathParData;

		}
		else if (gen->getEventType() == eCollision)
		{
			std::vector<ParticleEventInfo> collisionParData;
			m_collisionParticleGenDataMap[gen->getName()] = collisionParData;
		}
	}

	for (int i = 0; i < m_particleEvent->getReceiversCount(); i++)
	{
		auto particleRecvList = m_particleEvent->getReceivers();
		auto recv = particleRecvList[i];
		jsonVal& spawnCountJsonObj = recv->getSpawnCountJsonObj();
		recv->setSpawnCount(importFloatDistri(spawnCountJsonObj));
		jsonVal& inheritJsonObj = recv->getInheritScaleJsonObj();
		recv->setInheritScale(importVectorDistri(inheritJsonObj));
	}
	
	reset();
}
template<class T>
void Emittter<T>::loadEmitterDataFromId(std::string id)
{
	auto emitterDataSp = ParticleLoader::getEmitterData(id);

	if (EmitterData* emitterData = emitterDataSp.get())
	{
		for (int i = 0; i < 39; ++i)
		{
			m_moduleMap[i] = emitterData->m_moduleMap[i];
		}

		m_particleNum = emitterData->m_particleNum;

		if (emitterData->m_texturePathInfo.isPinMap == true)
		{
			m_texturePathInfo = emitterData->m_texturePathInfo;
		}

		m_emitterName = emitterData->m_emitterName;
		m_emitterPosX = emitterData->m_emitterPosX;
		m_emitterPosY = emitterData->m_emitterPosY;
		m_emitterRot = emitterData->m_emitterRot;
		m_killOnComplete = emitterData->m_killOnComplete;
		m_killOnDeactivate = emitterData->m_killOnDeactivate;
		m_useRange = emitterData->m_useRange;
		m_loop = emitterData->m_loop;
		m_durationRecal = emitterData->m_durationRecal;
		m_delay = emitterData->m_delay;
		m_delayLow = emitterData->m_delayLow;
		m_delayUseRange = emitterData->m_delayUseRange;
		m_delayFirstLoop = emitterData->m_delayFirstLoop;
		m_maxCount = emitterData->m_maxCount;
		m_countUseMax = emitterData->m_countUseMax;
		m_flipUV = emitterData->m_flipUV;
		m_flipTexcoordU = emitterData->m_flipTexcoordU;
		m_flipTexcoordV = emitterData->m_flipTexcoordV;
		m_randomTexU = emitterData->m_randomTexU;
		m_randomTexV = emitterData->m_randomTexV;
		m_subUVHori = emitterData->m_subUVHori;
		m_subUVVerti = emitterData->m_subUVVerti;
		m_subUVMode = emitterData->m_subUVMode;
		m_subUVRandomNum = emitterData->m_subUVRandomNum;
		m_brustNum = emitterData->m_brustNum;
		m_brustNumLow = emitterData->m_brustNumLow;
		m_brustTiming = emitterData->m_brustTiming;
		m_useBrust = emitterData->m_useBrust;
		m_duration = emitterData->m_duration;
		m_durationLow = emitterData->m_durationLow;
		m_clip = emitterData->m_clip;
		m_isLocalSpace = emitterData->m_isLocalSpace;
		m_speedSizeX = emitterData->m_speedSizeX;
		m_speedSizeY = emitterData->m_speedSizeY;
		m_speedSizeXMax = emitterData->m_speedSizeXMax;
		m_speedSizeYMax = emitterData->m_speedSizeYMax;
		m_clampAlpha = emitterData->m_clampAlpha;
		m_clampAlphaLife = emitterData->m_clampAlphaLife;
		m_colorScaleEmitterLife = emitterData->m_colorScaleEmitterLife;
		m_coneDirection = emitterData->m_coneDirection;
		m_velocityAbsolute = emitterData->m_velocityAbsolute;
		m_locDistriPoint = emitterData->m_locDistriPoint;
		m_locDistriThreshold = emitterData->m_locDistriThreshold;
		m_worldOffsetPoint = emitterData->m_worldOffsetPoint;
		m_worldOffsetThreshold = emitterData->m_worldOffsetThreshold;
		m_locEmitterName = emitterData->m_locEmitterName;
		m_locEmitterMode = emitterData->m_locEmitterMode;
		m_locEmitterCount = emitterData->m_locEmitterCount;
		m_inheritSourceVelocity = emitterData->m_inheritSourceVelocity;
		m_inheritSourceRotation = emitterData->m_inheritSourceRotation;
		m_inheritVelScale = emitterData->m_inheritVelScale;
		m_inheritRotScale = emitterData->m_inheritRotScale;
		m_locDirectEmitterName = emitterData->m_locDirectEmitterName;
		m_spherePositiveX = emitterData->m_spherePositiveX;
		m_sphereNegativeX = emitterData->m_sphereNegativeX;
		m_spherePositiveY = emitterData->m_spherePositiveY;
		m_sphereNegativeY = emitterData->m_sphereNegativeY;
		m_sphereSurface = emitterData->m_sphereSurface;
		m_sphereVelocity = emitterData->m_sphereVelocity;
		m_orbitOffsetSpawn = emitterData->m_orbitOffsetSpawn;
		m_orbitOffsetUpdate = emitterData->m_orbitOffsetUpdate;
		m_orbitOffsetEmitterTime = emitterData->m_orbitOffsetEmitterTime;
		m_orbitRotationSpawn = emitterData->m_orbitRotationSpawn;
		m_orbitRotationUpdate = emitterData->m_orbitRotationUpdate;
		m_orbitRotationEmitterTime = emitterData->m_orbitRotationEmitterTime;
		m_orbitRotationRateSpawn = emitterData->m_orbitRotationRateSpawn;
		m_orbitRotationRateUpdate = emitterData->m_orbitRotationRateUpdate;
		m_orbitRotationRateEmitterTime = emitterData->m_orbitRotationRateEmitterTime;

		m_strengthByDistance = emitterData->m_strengthByDistance;
		m_affectBaseVelocity = emitterData->m_affectBaseVelocity;
		m_lineAttractorPoint1X = emitterData->m_lineAttractorPoint1X;
		m_lineAttractorPoint1Y = emitterData->m_lineAttractorPoint1Y;
		m_lineAttractorPoint2X = emitterData->m_lineAttractorPoint2X;
		m_lineAttractorPoint2Y = emitterData->m_lineAttractorPoint2Y;
		m_killInside = emitterData->m_killInside;
		m_killFloor = emitterData->m_killFloor;
		m_floorCollisionAxis = emitterData->m_floorCollisionAxis;
		m_floorCollisionAxisPos = emitterData->m_floorCollisionAxisPos;
		m_floorCollisionDelayAmount = emitterData->m_floorCollisionDelayAmount;
		m_floorCollisionCompleteOpt = emitterData->m_floorCollisionCompleteOpt;
		m_lineCollisionPoint0X = emitterData->m_lineCollisionPoint0X;
		m_lineCollisionPoint0Y = emitterData->m_lineCollisionPoint0Y;
		m_lineCollisionPoint1X = emitterData->m_lineCollisionPoint1X;
		m_lineCollisionPoint1Y = emitterData->m_lineCollisionPoint1Y;
		m_lineCollisionDelayAmount = emitterData->m_lineCollisionDelayAmount;
		m_lineCollisionCompleteOpt = emitterData->m_lineCollisionCompleteOpt;
		m_rectCollisionPosX = emitterData->m_rectCollisionPosX;
		m_rectCollisionPosY = emitterData->m_rectCollisionPosY;
		m_rectCollisionWidth = emitterData->m_rectCollisionWidth;
		m_rectCollisionHeight = emitterData->m_rectCollisionHeight;
		m_rectCollisionDelayAmount = emitterData->m_rectCollisionDelayAmount;
		m_rectCollisionCompleteOpt = emitterData->m_rectCollisionCompleteOpt;
		m_sphereCollisionCenterX = emitterData->m_sphereCollisionCenterX;
		m_sphereCollisionCenterY = emitterData->m_sphereCollisionCenterY;
		m_sphereCollisionRadius = emitterData->m_sphereCollisionRadius;
		m_sphereCollisionDelayAmount = emitterData->m_sphereCollisionDelayAmount;
		m_sphereCollisionCompleteOpt = emitterData->m_sphereCollisionCompleteOpt;

		m_velRotation = emitterData->m_velRotation;

		m_emission = importFloatDistri(emitterData->m_emission);
		m_emissionScale = importFloatDistri(emitterData->m_emissionScale);
		m_brustScale = importFloatDistri(emitterData->m_brustScale);
		m_initSize = importFloatDistri(emitterData->m_initSize);
		m_sizeLife = importFloatDistri(emitterData->m_sizeLife);
		m_sizeScale = importFloatDistri(emitterData->m_sizeScale);
		m_lifeTime = importFloatDistri(emitterData->m_lifeTime);
		m_initColor = importVectorDistri(emitterData->m_initColor);
		m_initAlpha = importFloatDistri(emitterData->m_initAlpha);
		m_colorOverLife = importVectorDistri(emitterData->m_colorOverLife);
		m_alphaOverLife = importFloatDistri(emitterData->m_alphaOverLife);
		m_colorScaleOverLife = importVectorDistri(emitterData->m_colorScaleOverLife);
		m_alphaScaleOverLife = importFloatDistri(emitterData->m_alphaScaleOverLife);
		m_initVelocity = importVectorDistri(emitterData->m_initVelocity);
		m_initVelocityRadial = importFloatDistri(emitterData->m_initVelocityRadial);
		m_velOverLife = importVectorDistri(emitterData->m_velOverLife);
		m_coneVelocityAngle = importFloatDistri(emitterData->m_coneVelocityAngle);
		m_coneVelocityVelocity = importFloatDistri(emitterData->m_coneVelocityVelocity);
		m_initAcceleration = importVectorDistri(emitterData->m_initAcceleration);
		m_drag = importFloatDistri(emitterData->m_drag);
		m_accelOverLife = importVectorDistri(emitterData->m_accelOverLife);
		m_initRotate = importFloatDistri(emitterData->m_initRotate);
		m_rotateOverLife = importFloatDistri(emitterData->m_rotateOverLife);
		m_initRotRate = importFloatDistri(emitterData->m_initRotRate);
		m_rotRateLife = importFloatDistri(emitterData->m_rotRateLife);
		m_initLocation = importVectorDistri(emitterData->m_initLocation);
		m_worldOffset = importVectorDistri(emitterData->m_worldOffset);
		m_directLocation = importVectorDistri(emitterData->m_directLocation);
		m_dirLocationOffset = importVectorDistri(emitterData->m_dirLocationOffset);
		m_dirLocationScale = importVectorDistri(emitterData->m_dirLocationScale);
		m_sphereRadius = importFloatDistri(emitterData->m_sphereRadius);
		m_sphereVelocityScale = importFloatDistri(emitterData->m_sphereVelocityScale);
		m_sphereOffset = importVectorDistri(emitterData->m_sphereOffset);
		m_triangleHeight = importFloatDistri(emitterData->m_triangleHeight);
		m_triangleAngle = importFloatDistri(emitterData->m_triangleAngle);
		m_triangleOffset = importVectorDistri(emitterData->m_triangleOffset);
		m_subUVIndex = importFloatDistri(emitterData->m_subUVIndex);
		m_orbitOffset = importVectorDistri(emitterData->m_orbitOffset);
		m_orbitRotation = importVectorDistri(emitterData->m_orbitRotation);
		m_orbitRotationRate = importVectorDistri(emitterData->m_orbitRotationRate);
		m_pointAttractorPosition = importVectorDistri(emitterData->m_pointAttractorPosition);
		m_pointAttractorRange = importFloatDistri(emitterData->m_pointAttractorRange);
		m_pointAttractorStrength = importFloatDistri(emitterData->m_pointAttractorStrength);
		m_lineAttractorRange = importFloatDistri(emitterData->m_lineAttractorRange);
		m_lineAttractorStrength = importFloatDistri(emitterData->m_lineAttractorStrength);
		m_killBoxTopLeft = importVectorDistri(emitterData->m_killBoxTopLeft);
		m_killBoxLowRight = importVectorDistri(emitterData->m_killBoxLowRight);
		m_killHeight = importFloatDistri(emitterData->m_killHeight);
		m_floorDampVel = importVectorDistri(emitterData->m_floorDampVel);
		m_floorDampRot = importFloatDistri(emitterData->m_floorDampRot);
		m_floorMaxCollision = importFloatDistri(emitterData->m_floorMaxCollision);
		m_lineDampVel = importVectorDistri(emitterData->m_lineDampVel);
		m_lineDampRot = importFloatDistri(emitterData->m_lineDampRot);
		m_lineMaxCollision = importFloatDistri(emitterData->m_lineMaxCollision);
		m_rectDampVel = importVectorDistri(emitterData->m_rectDampVel);
		m_rectDampRot = importFloatDistri(emitterData->m_rectDampRot);
		m_rectMaxCollision = importFloatDistri(emitterData->m_rectMaxCollision);
		m_sphereDampVel = importVectorDistri(emitterData->m_sphereDampVel);
		m_sphereDampRot = importFloatDistri(emitterData->m_sphereDampRot);
		m_sphereMaxCollision = importFloatDistri(emitterData->m_sphereMaxCollision);

		m_particleEvent = new ParticleEvent(emitterData->m_particleEvent);

		for (int i = 0; i < m_particleEvent->getGeneratorsCount(); i++)
		{
			auto particleGenList = m_particleEvent->getGenerators();
			auto gen = particleGenList[i];
			if (gen->getEventType() == eSpawn)
			{
				std::vector<ParticleEventInfo> spawnParData;
				m_spawnParticleGenDataMap[gen->getName()] = spawnParData;
			}
			else if (gen->getEventType() == eDeath)
			{
				std::vector<ParticleEventInfo> deathParData;
				m_deathParticleGenDataMap[gen->getName()] = deathParData;

			}
			else if (gen->getEventType() == eCollision)
			{
				std::vector<ParticleEventInfo> collisionParData;
				m_collisionParticleGenDataMap[gen->getName()] = collisionParData;
			}
		}

		for (int i = 0; i < m_particleEvent->getReceiversCount(); i++)
		{
			auto particleRecvList = m_particleEvent->getReceivers();
			auto recv = particleRecvList[i];
			FloatDistriData* spawnCountDistriData = recv->getSpawnCountDistriData();
			recv->setSpawnCount(importFloatDistri(spawnCountDistriData));
			VectorDistriData* inheritJsonDistriData = recv->getInheritScaleDistriData();
			recv->setInheritScale(importVectorDistri(inheritJsonDistriData));
		}
	} 

	reset();
}
template <typename T>
FloatDistri* Emittter<T>::importFloatDistri(jsonVal& distri)
{
	//std::cout << distri[0].GetString() << "distri name" << std::endl;
	//if (distri[0].GetString() == "Size By Scale")
	FloatDistri *fDis = new FloatDistri();
	std::string str(distri[0].GetString());
	fDis->setAttriName(str);
	fDis->setFlags(distri[1].GetInt());
	fDis->setDataType(distri[2].GetInt());
	fDis->setIsLoop(distri[3].GetBool());
	fDis->setIsBaked(distri[4].GetBool());
	fDis->setDistriType(distri[5].GetInt());

	if (fDis->dataType() == FloatDistri::CONSTANT)
		fDis->setCons(distri[6].GetFloat());
	else if (fDis->dataType() == FloatDistri::UNIFORM)
	{
		fDis->setMin(distri[6].GetFloat());
		fDis->setMax(distri[7].GetFloat());
	}
	else if (fDis->dataType() == FloatDistri::CONSCURVE)
	{
		jsonVal& curveList = distri[6];

		if (!curveList.IsArray())
			return fDis;

		for (int i = 0; i < curveList.Size(); i++)
		{
			jsonVal& curveData = curveList[i];
			

			FloatConstantCurve* curve = new FloatConstantCurve(curveData[0].GetInt(), curveData[1].GetFloat(), curveData[2].GetFloat(),
				curveData[3].GetFloat(), curveData[4].GetFloat(), curveData[5].GetInt());
			fDis->appendList(curve);
		}
	}
	else if (fDis->dataType() == FloatDistri::UNIFORMCURVE)
	{
		jsonVal& curveList = distri[6];

		if (!curveList.IsArray())
			return fDis;

		for (int i = 0; i < curveList.Size() ; i++)
		{
			jsonVal& curveData = curveList[i];
			

			FloatUniformCurve* curve = new FloatUniformCurve(curveData[0].GetInt(), curveData[1].GetFloat(),
				curveData[2].GetFloat(), curveData[3].GetFloat(),
				curveData[4].GetFloat(), curveData[5].GetFloat(),
				curveData[6].GetFloat(), curveData[7].GetFloat(),
				curveData[8].GetInt());
			fDis->appendUniformList(curve);
		}
	}

	if (fDis->isBaked())
	{
		fDis->setBakedData(distri[7]);
	}
	return fDis;
}

template<class T>
FloatDistri* Emittter<T>::importFloatDistriByStr(std::string distriStr)//
{
	jsonDoc distri;
	distri.Parse(distriStr.c_str());

	return importFloatDistri(distri);
}

template<class T>
FloatDistri* Emittter<T>::importFloatDistri(FloatDistriData* floatDistriData)
{
	FloatDistri* fDis = new FloatDistri();
	fDis->setAttriName(floatDistriData->m_attriName);
	fDis->setFlags(floatDistriData->m_flags);
	fDis->setDataType(floatDistriData->m_type);
	fDis->setIsLoop(floatDistriData->m_loop);
	fDis->setIsBaked(floatDistriData->m_baked);
	fDis->setDistriType(floatDistriData->m_distriType);

	if (fDis->dataType() == FloatDistri::CONSTANT)
		fDis->setCons(floatDistriData->m_cons);
	else if (fDis->dataType() == FloatDistri::UNIFORM)
	{
		fDis->setMin(floatDistriData->m_min);
		fDis->setMax(floatDistriData->m_max);
	}
	else if (fDis->dataType() == FloatDistri::CONSCURVE)
	{
		for (int i = 0; i < floatDistriData->m_curveList.size(); i++)
		{
			FloatConstantCurveData* data = floatDistriData->m_curveList[i];
			FloatConstantCurve* curve = new FloatConstantCurve(data->m_title, data->m_inVal, data->m_outVal,
				data->m_arriveTan, data->m_leaveTan, data->m_mode);
			fDis->appendList(curve);
		}
	}
	else if (fDis->dataType() == FloatDistri::UNIFORMCURVE)
	{
		for (int i = 0; i < floatDistriData->m_uniformCurveList.size(); i++)
		{
			FloatUniformCurveData* data = floatDistriData->m_uniformCurveList[i];
			FloatUniformCurve* curve = new FloatUniformCurve(data->m_title, data->m_inVal,
				data->m_outVal1, data->m_outVal2,
				data->m_arriveTan1, data->m_arriveTan2,
				data->m_leaveTan1, data->m_leaveTan2,
				data->m_mode);
			fDis->appendUniformList(curve);
		}
	}

	if (fDis->isBaked())
	{
		//Dis->setBakedData(distri[7]);
	}
	return fDis;
}

template <typename T>
VectorDistri* Emittter<T>::importVectorDistri(jsonVal& distri)
{
	//std::cout << distri[0].GetString();
	VectorDistri *vDis = new VectorDistri();
	vDis->setAttriName(std::string(distri[0].GetString()));
	vDis->setFlags(distri[1].GetInt());
	vDis->setDataType(distri[2].GetInt());
	vDis->setIsLoop(distri[3].GetBool());
	vDis->setIsBaked(distri[4].GetBool());
	vDis->setDistriType(distri[5].GetInt());

	if (vDis->dataType() == VectorDistri::CONSTANT)
		vDis->setCons(vec3(distri[6][0].GetFloat(), distri[6][1].GetFloat(), distri[6][2].GetFloat()));
	else if (vDis->dataType() == VectorDistri::UNIFORM)
	{
		vDis->setMin(vec3(distri[6][0].GetFloat(), distri[6][1].GetFloat(), distri[6][2].GetFloat()));
		vDis->setMax(vec3(distri[7][0].GetFloat(), distri[7][1].GetFloat(), distri[7][2].GetFloat()));
	}
	else if (vDis->dataType() == VectorDistri::CONSCURVE)
	{
		jsonVal& curveList = distri[6];

		if (!curveList.IsArray())
			return vDis;

		for (int i = 0; i < curveList.Size(); i++)
		{
			
			jsonVal& curveData = curveList[i];
			
			VectorConstantCurve *curve = new VectorConstantCurve(curveData[0].GetInt(), curveData[1].GetFloat(),
				vec3(curveData[2][0].GetFloat(), curveData[2][1].GetFloat(), curveData[2][2].GetFloat()),
				vec3(curveData[3][0].GetFloat(), curveData[3][1].GetFloat(), curveData[3][2].GetFloat()),
				vec3(curveData[4][0].GetFloat(), curveData[4][1].GetFloat(), curveData[4][2].GetFloat()),
				curveData[5].GetInt());
			vDis->appendList(curve);
		}
	}
	else if (vDis->dataType() == VectorDistri::UNIFORMCURVE)
	{
		jsonVal& curveList = distri[6];
		
		if (!curveList.IsArray())
			return vDis;
		
		for (int i = 0; i < curveList.Size(); i++)
		{
			jsonVal& curveData = curveList[i];
			

			VectorUniformCurve *curve = new VectorUniformCurve(curveData[0].GetInt(), curveData[1].GetFloat(),
				vec3(curveData[2][0].GetFloat(), curveData[2][1].GetFloat(), curveData[2][2].GetFloat()),
				vec3(curveData[3][0].GetFloat(), curveData[3][1].GetFloat(), curveData[3][2].GetFloat()),
				vec3(curveData[4][0].GetFloat(), curveData[4][1].GetFloat(), curveData[4][2].GetFloat()),
				vec3(curveData[5][0].GetFloat(), curveData[5][1].GetFloat(), curveData[5][2].GetFloat()),
				vec3(curveData[6][0].GetFloat(), curveData[6][1].GetFloat(), curveData[6][2].GetFloat()),
				vec3(curveData[7][0].GetFloat(), curveData[7][1].GetFloat(), curveData[7][2].GetFloat()),
				curveData[8].GetInt());
			vDis->appendUniformList(curve);
		}
	}

	if (vDis->isBaked())
	{
		vDis->setBakedData(distri[7]);
	}
	return vDis;
}

template<class T>
VectorDistri* Emittter<T>::importVectorDistriByStr(std::string distriStr) //
{
	jsonDoc distri;
	distri.Parse(distriStr.c_str());

	return importVectorDistri(distri);
}

template<class T>
VectorDistri* Emittter<T>::importVectorDistri(VectorDistriData* vectorDistriData)
{
	VectorDistri* vDis = new VectorDistri();
	vDis->setAttriName(vectorDistriData->m_attriName);
	vDis->setFlags(vectorDistriData->m_flags);
	vDis->setDataType(vectorDistriData->m_type);
	vDis->setIsLoop(vectorDistriData->m_loop);
	vDis->setIsBaked(vectorDistriData->m_baked);
	vDis->setDistriType(vectorDistriData->m_distriType);

	if (vDis->dataType() == VectorDistri::CONSTANT)
		vDis->setCons(vectorDistriData->m_cons);
	else if (vDis->dataType() == VectorDistri::UNIFORM)
	{
		vDis->setMin(vectorDistriData->m_min);
		vDis->setMax(vectorDistriData->m_max);
	}
	else if (vDis->dataType() == VectorDistri::CONSCURVE)
	{
		for (int i = 0; i < vectorDistriData->m_curveList.size(); i++)
		{

			VectorConstantCurveData* data = vectorDistriData->m_curveList[i];

			VectorConstantCurve* curve = new VectorConstantCurve(data->m_title, data->m_inVal,
				data->m_outVal,
				data->m_arriveTan,
				data->m_leaveTan,
				data->m_mode);
			vDis->appendList(curve);
		}
	}
	else if (vDis->dataType() == VectorDistri::UNIFORMCURVE)
	{
		for (int i = 0; i < vectorDistriData->m_uniformCurveList.size(); i++)
		{
			VectorUniformCurveData *data = vectorDistriData->m_uniformCurveList[i];

			VectorUniformCurve* curve = new VectorUniformCurve(data->m_title, data->m_inVal,
				data->m_outVal1, data->m_outVal2,
				data->m_arriveTan1, data->m_arriveTan2,
				data->m_leaveTan1, data->m_leaveTan2,
				data->m_mode);
			vDis->appendUniformList(curve);
		}
	}

	if (vDis->isBaked())
	{
		//vDis->setBakedData(distri[7]);
	}

	return vDis;
}

template <typename T>
void Emittter<T>::setAttributeFormat()
{
	//std::cout << "8888888888" << std::endl;
	if (m_texturePath.IsObject() || m_texturePathInfo.isPinMap == true)
	{	
		m_attributeFormat["pinAttribute"] = true;
		m_stripeSize += 5;
	}
	else
	{
		m_attributeFormat["pinAttribute"] = false;
	}
		//std::cout << "8888888888" << std::endl;
	if (m_moduleMap[InitialSize] == true || m_moduleMap[SizeByScale] == true || m_moduleMap[SizeByLife] == true || m_moduleMap[SizeBySpeed] == true)
	{
		m_attributeFormat["sizeAttribute"] = true;
		m_stripeSize += 1;
	}
	else
		m_attributeFormat["sizeAttribute"] = false;
	//std::cout << "8888888888" << std::endl;
	if (m_moduleMap[InitialColor] == true || m_moduleMap[ColorOverLife] == true || m_moduleMap[ColorScaleLife] == true)
	{
		m_attributeFormat["colorAttribute"] = true;
		m_stripeSize += 4;
	}
	else
		m_attributeFormat["colorAttribute"] = false;

	//std::cout << "8888888888" << std::endl;
	if (m_flipUV != 0)
	{
		m_attributeFormat["flipAttribute"] = true;
		m_stripeSize += 2;
	}
	else
		m_attributeFormat["flipAttribute"] = false;


	if (m_moduleMap[InitRotate] == true || 
		m_moduleMap[RotateOverLife] == true || 
		m_moduleMap[InitRotRate] == true || 
		m_moduleMap[RotRateLife] == true || 
		m_inheritSourceRotation == true)
	{
		m_attributeFormat["rotationAttribute"] = true;
		m_stripeSize += 1;
	}
	else
		m_attributeFormat["rotationAttribute"] = false;


	if (m_subUVMode == 0)
	{
		m_attributeFormat["subUVAttribute"] = false;
	}
	else if (m_subUVMode == 1 || m_subUVMode == 3)
	{
		m_attributeFormat["subUVAttribute"] = true;
		m_stripeSize += 4;
	}
	else if (m_subUVMode == 2 || m_subUVMode == 4)
	{
		m_attributeFormat["subUVAttribute"] = true;
		m_attributeFormat["subUVBlendAttribute"] = true;
		m_stripeSize += 9;
	}

	if (m_isLocalSpace == false)
	{
		m_stripeSize += 5;
	}

	//std::cout << "init vector length" << m_shaderAttribute.size() << m_shaderAttribute.capacity() << std::endl;

	m_particleList.clear();
	m_particleList.reserve(m_particleNum);

	m_shaderAttribute.clear();
	m_shaderAttribute.reserve(m_particleNum);

	int index = 0;

	for (int i = 0; i < m_particleNum; i++)
	{
		Particle<T> *par = new Particle<T>(this);
		m_particleList.push_back(par);
		T attri;

		m_shaderAttribute.push_back(attri);
		vec3 pos = par->getShaderAttriPos();
		m_shaderAttribute[i].data[index] = pos.x;
		m_shaderAttribute[i].data[index+1] = pos.y;
		m_shaderAttribute[i].data[index+2] = pos.z;
	}

	//std::cout << " pos  " << std::endl;

	index += 3;

	if (m_attributeFormat["pinAttribute"] == true)
	{
		vec2 oriSize = m_textureSize;
		vec2 pos = vec2();
		vec2 size = vec2();
		bool rotated = false;
		if (m_texturePath != "" && m_texturePathInfo.isPinMap == false)
		{
			jsonVal& texData = m_texturePath;
			vec2 realPos = vec2(texData["x"].GetFloat(), texData["y"].GetFloat());
			vec2 realSize = vec2(texData["width"].GetFloat(), texData["height"].GetFloat());
			pos = realPos / oriSize;
			size = realSize / oriSize;
			if (texData.HasMember("rotated") && texData["rotated"].IsBool())
				rotated = texData["rotated"].GetBool();
		}
		else if (m_texturePath == "" && m_texturePathInfo.isPinMap == true)
		{
			vec2 realPos = vec2(m_texturePathInfo.x, m_texturePathInfo.y);
			vec2 realSize = vec2(m_texturePathInfo.width, m_texturePathInfo.height);
			pos = realPos / oriSize;
			size = realSize / oriSize;
			rotated = m_texturePathInfo.rotated;
		}
		
		//std::cout << "textureSize" << oriSize.x << "  " << oriSize.y << std::endl;
		
		//maybe could make it uniform;

		if (rotated == true)
			m_pinAngle = 3.1415926 / 2.0f;
		else
			m_pinAngle = 0.0f;

		m_pinCoord = vec4(pos.x,pos.y,size.x,size.y);
      
	    for (int i = 0; i < m_particleNum; i++)
	    {
			m_shaderAttribute[i].data[index] = m_pinCoord.x;
			m_shaderAttribute[i].data[index + 1] = m_pinCoord.y;
			m_shaderAttribute[i].data[index + 2] = m_pinCoord.z;
			m_shaderAttribute[i].data[index + 3] = m_pinCoord.w;
			m_shaderAttribute[i].data[index + 4] = m_pinAngle;
		}

		index += 5;//8

		//std::cout << " pinAttribute  " << std::endl;
	}
	if (m_attributeFormat["sizeAttribute"] == true)
	{
        for (int i = 0; i < m_particleNum; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriSize();
		}

		index++;

		//std::cout << " sizeAttribute  " << std::endl;
	}

	if (m_attributeFormat["colorAttribute"] == true)
	{
		for (int i =0; i < m_particleNum; i++)
		{
			vec3 color = m_particleList[i]->getShaderAttriColor();
			m_shaderAttribute[i].data[index] = color.x;
			m_shaderAttribute[i].data[index + 1] = color.y;
			m_shaderAttribute[i].data[index + 2] = color.z;
			m_shaderAttribute[i].data[index + 3] = m_particleList[i]->getShaderAttriAlpha();
		}
		index += 4;

		//std::cout << " colorAttribute  " << std::endl;
	}

	if (m_attributeFormat["flipAttribute"] == true)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriFlipU();
			m_shaderAttribute[i].data[index + 1] = m_particleList[i]->getShaderAttriFlipV();
		}

		index += 2;

		//std::cout << " flipAttribute  " << std::endl;
	}

	if (m_attributeFormat["rotationAttribute"] == true)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriRot();
		}

		index++;

		//std::cout << " rotationAttribute  " << std::endl;
	}

	if (m_attributeFormat["subUVAttribute"] == true)
	{
		for (int i =0; i < m_particleNum; i++)
		{
		    vec4 coord = m_particleList[i]->getShaderAttriSubCoord();
			m_shaderAttribute[i].data[index] = coord.x;
			m_shaderAttribute[i].data[index + 1] = coord.y;
			m_shaderAttribute[i].data[index + 2] = coord.z;
			m_shaderAttribute[i].data[index + 3] = coord.w;
		}

		index += 4;
		
		//std::cout << " subUVAttribute  " << std::endl;
	}

	if (m_attributeFormat["subUVBlendAttribute"] == true)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			vec4 coordNext = m_particleList[i]->getShaderAttriSubCoordNext();
			m_shaderAttribute[i].data[index] = coordNext.x;
			m_shaderAttribute[i].data[index + 1] = coordNext.y;
			m_shaderAttribute[i].data[index + 2] = coordNext.z;
			m_shaderAttribute[i].data[index + 3] = coordNext.w;
			m_shaderAttribute[i].data[index + 4] = m_particleList[i]->getShaderAttriSubRatio();
		}
		index += 5;

		//std::cout << " subUVBlendAttribute  " << std::endl;
	}

	if (m_isLocalSpace == false)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			float scaleFactor = m_particleList[i]->m_currentScaleFactor;
			mat2 parentRotMat = m_particleList[i]->m_currentParentRotationMat;
			
			m_shaderAttribute[i].data[index] = scaleFactor;
			m_shaderAttribute[i].data[index + 1] = parentRotMat[0][0];
			m_shaderAttribute[i].data[index + 2] = parentRotMat[0][1];
			m_shaderAttribute[i].data[index + 3] = parentRotMat[1][0];
			m_shaderAttribute[i].data[index + 4] = parentRotMat[1][1];

		    //std::cout << glm::to_string(mat) << std::endl;
		}

		index += 5;
	}

	//std::cout << index << std::endl;
 
	//std::cout << " setAttributeFormat =============  " << m_stripeSize << std::endl;

	//for (int i = 0; i < m_particleNum; i++)
	//{
	//	for (int i1 = 0; i1 < m_stripeSize; i1++)
	//	{
	//		std::cout << m_shaderAttribute[i].data[i1] << ",";
	//	}
 //       
	//	//std::cout << std::endl;
	//}

	setSubCoordList();
}

template <typename T>
bool Emittter<T>::isFull()
{
	if (m_particleCount >= m_particleNum)
		return true;
	else
	    return false;
}

template <typename T>
bool Emittter<T>::isMax()
{
	if (m_maxCount > 0 && m_particleCount >= m_maxCount)
		return true;
	else
	    return false;
}

template <typename T>
void Emittter<T>::addParticle()
{
	if (isFull())
		return;
	else
	{
		Particle<T> *parSpawn = m_particleList[m_particleCount];
		parSpawn->reset(m_particleCount);
		parSpawn->setActivate(true);
		parSpawn->setUpdate(true);
		++m_particleCount;

		if (m_moduleMap[EventGenerator] == true)
		{
			for (auto iter = m_spawnParticleGenDataMap.begin(); iter != m_spawnParticleGenDataMap.end(); iter++)
			{
				auto generator = m_particleEvent->findGeneratorByName(iter->first);
				int frequency = generator->getFrequency();
				if (frequency <= 1 || m_spawnParticleFrameCounter % frequency == 0)
				{
					ParticleEventInfo parData;
					parData.pos = parSpawn->getShaderAttriPos();
					parData.vel = parSpawn->getVelocity();
					//parData.time = m_emitterLifeTime;
					iter->second.push_back(parData);
				}
			}
		}

		m_spawnParticleFrameCounter++;
	}
}

template <typename T>
Particle<T> *Emittter<T>::addParticleInner()
{
	if (isFull())
		return NULL;
	else
	{
		Particle<T> *parSpawn = m_particleList[m_particleCount];
		parSpawn->reset(m_particleCount);
		parSpawn->setActivate(true);
		parSpawn->setUpdate(true);
		++m_particleCount;

		if (m_moduleMap[EventGenerator] == true)
		{
 			for (auto iter = m_spawnParticleGenDataMap.begin(); iter != m_spawnParticleGenDataMap.end(); iter++)
			{
				auto generator = m_particleEvent->findGeneratorByName(iter->first);
				int frequency = generator->getFrequency();
				if (frequency <= 1 || m_spawnParticleFrameCounter % frequency == 0)
				{
					ParticleEventInfo parData;
					parData.pos = parSpawn->getShaderAttriPos();
					parData.vel = parSpawn->getVelocity();
					//parData.time = m_emitterLifeTime;
					iter->second.push_back(parData);
				}
			}
		}

		m_spawnParticleFrameCounter++;

		return parSpawn;
	}
}

template<class T>
void Emittter<T>::addParticlePos(vec3 pos)
{
	Particle<T> *par = addParticleInner();

	if (par != NULL)
	{
		par->setOriPos(pos);
	}
}

template<class T>
void Emittter<T>::addParticleVel(vec3 vel)
{
	Particle<T> *par = addParticleInner();
	if (par != NULL)
	{
		vec3 curVel = par->getVelocity();
		par->setVelocity(curVel + vel);
	}
}

template<class T>
void Emittter<T>::addParticlePosVel(vec3 pos, vec3 vel)
{
	Particle<T> *par = addParticleInner();
	if (par != NULL)
	{
		par->setOriPos(pos);
		vec3 curVel = par->getVelocity();
		par->setVelocity(curVel + vel);
	}
}

// receive from former emitter then update by this data
template<class T>
void Emittter<T>::applyParticleEvent(std::string particleEventDataStr)
{
	//printf("0000000000000\n");
	m_receivedDataJson.Parse(particleEventDataStr.c_str());
	for (jsonVal::ConstMemberIterator iter = m_receivedDataJson.MemberBegin(); iter != m_receivedDataJson.MemberEnd(); iter++)
	{
		std::string eventNameJson = iter->name.GetString();
		std::vector<ParticleEventInfo> eventData;
		for (rapidjson::SizeType i = 0; i < iter->value.Size(); i++)
		{
			auto posData = iter->value[i]["pos"].GetArray();
			auto velData = iter->value[i]["vel"].GetArray();
			//auto timeData = iter->value[i]["time"].GetFloat();

			vec3 pos(posData[0].GetFloat(), posData[1].GetFloat(), posData[2].GetFloat());
			vec3 vel(velData[0].GetFloat(), velData[1].GetFloat(), velData[2].GetFloat());

			ParticleEventInfo particleEventInfo;
			particleEventInfo.pos = pos;
			particleEventInfo.vel = vel;
			//particleEventInfo.time = timeData;
			eventData.push_back(particleEventInfo);
		}

		m_receiverParticleGenDataMap[eventNameJson] = eventData;
	}
}


template <typename T>
void Emittter<T>::addParticleByEvent()
{
	typename EventParticleMap::iterator iter;
	for (iter = m_receiverParticleGenDataMap.begin(); iter != m_receiverParticleGenDataMap.end(); iter++)
	{
		// if listenning same name event then get par event datas
		ParticleEventReceiver* receiver = m_particleEvent->findReceiverByName(iter->first);
		if (receiver != NULL)
		{
			std::vector<ParticleEventInfo> particleDataList = iter->second;

			for (int parEventIndex = 0; parEventIndex < particleDataList.size(); parEventIndex++)
			{
				ParticleEventInfo parEventData = particleDataList[parEventIndex];

				
				int spawnCount = getFloatDistriValue(receiver->getSpawnCount());

				for (int i = 0; i < spawnCount; i++)
				{
					if (receiver->getUsePsysLocation() && !receiver->getInheritVal())
					{
						addParticlePos(parEventData.pos);
					}
					else if (!receiver->getUsePsysLocation() && receiver->getInheritVal())
					{
						vec3 velScale = getVectorDistriValue(receiver->getInheritScale());
						addParticleVel(parEventData.vel * velScale);
					}
					else if (receiver->getUsePsysLocation() && receiver->getInheritVal())
					{
						vec3 velScale = getVectorDistriValue(receiver->getInheritScale());
						addParticlePosVel(parEventData.pos, parEventData.vel * velScale);
					}
					else
					{
						addParticle();
					}
				}
			}

		}
	}
}

template <typename T>
void Emittter<T>::clearAllEventParticleMap()
{
	clearEventParticleMap(m_deathParticleGenDataMap);
	clearEventParticleMap(m_spawnParticleGenDataMap);
	clearEventParticleMap(m_collisionParticleGenDataMap);
	clearEventParticleMap(m_receiverParticleGenDataMap);
}

template<class T>
void Emittter<T>::clearEventParticleMap(EventParticleMap& eventParMap)
{
	typename EventParticleMap::iterator iter;

	for (iter = eventParMap.begin(); iter != eventParMap.end(); iter++)
	{
		iter->second.clear();
	}
}

template <typename T>
bool Emittter<T>::allDead()
{
	for (int i = 0; i < m_particleList.size(); ++i)
	{
		if (m_particleList[i]->isActivated())
			return false;
	}
	return true;
}

template <typename T>
void Emittter<T>::updateParticle(int64_t dt, Particle<T> *par, int i)
{
	if (!par->isDead() && par->isActivated())
	{
		par->updateLife(dt);

		if (par->isUpdate())
			par->update(dt, i);

		if (m_moduleMap[EventGenerator] == true)
		{
			bool isCollision = par->getCollisionFrameState();

			if (isCollision)
			{
				typename EventParticleMap::iterator iter;
				for (iter = m_collisionParticleGenDataMap.begin(); iter != m_collisionParticleGenDataMap.end(); iter++)
				{
					auto generator = m_particleEvent->findGeneratorByName(iter->first);
					int frequency = generator->getFrequency();
					if (frequency <= 1 || m_collisionParticleFrameCounter % frequency == 0)
					{
						ParticleEventInfo parData;
						parData.pos = par->getShaderAttriPos();
						parData.vel = par->getVelocity();
						//parData.time = m_emitterLifeTime;
						iter->second.push_back(parData);
					}
				}
			}

			m_collisionParticleFrameCounter++;
		}

		m_currentIndex++;
	}
	else if (par->isDead())
	{
		Particle<T> *parDied = m_particleList[i];

		if (m_particleCount > 1)
		{
			m_particleList[i] = m_particleList[m_particleCount - 1];
			m_particleList[m_particleCount - 1] = parDied;
		}

		--m_particleCount;

		if (m_moduleMap[EventGenerator] == true)
		{
			// collects particle triggered event data , by generator config
			// <GenEventName, ParticleData>
			typename EventParticleMap::iterator iter;
			for (iter = m_deathParticleGenDataMap.begin(); iter != m_deathParticleGenDataMap.end(); iter++)
			{
				auto generator = m_particleEvent->findGeneratorByName(iter->first);
				int frequency = generator->getFrequency();
				if (frequency <= 1 || m_deathParticleFrameCounter % frequency == 0)
				{
					ParticleEventInfo parData;
					parData.pos = parDied->getShaderAttriPos();
					parData.vel = parDied->getVelocity();
					//parData.time = m_emitterLifeTime;
					iter->second.push_back(parData);
				}
			}

			m_deathParticleFrameCounter++;
		}

		
	}
}

template <typename T>
void Emittter<T>::update(int64_t dt)
{
	float delay = m_currentDelay;
    // deal with delay, delay only first loop and loops
    if (m_currentDuration != 0)
    {
        m_elapsed = m_elapsed + dt;

        m_elapsedDraw = m_elapsedDraw + dt;

        // for clear logic
        // if delay every loop, then do nothing
        if (!m_delayFirstLoop)
		{
		}
        // if delay first loop and current loop is in the first loop, do nothing
        else if (m_delayFirstLoop && m_loopCount == 0)
        {
		}
		//if delay first loop and current loop is not first loop, make delay time 0
        else
            delay = 0.0f;
	}

	//during delay time
	if (m_elapsed < delay)
	{
		m_emitterRunningState = RUNNING_FRAME_STATE::IDEL;
		m_emitterLifeTime = 0.0f;
	}
	//end delay,doing loop update
    else if ((m_elapsed >= delay) && ((m_elapsed - delay) < m_currentDuration))
    {
		//return life rate or seconds
		//self.m_emitterLifeTime = (self.m_elapsed - self.delay) / self.m_currentDuration;
		
		m_emitterRunningState = RUNNING_FRAME_STATE::RUNNING;
		m_emitterLifeTime = ((float)m_elapsed - delay) / 1000.0f;


		if (getFloatDistriValue(m_emission) > 0.0f || m_useBrust)
		{
			// doing loops in loopCount
			if ((m_loop == 0) || (m_loopCount < m_loop))
			{
				if (m_emitCount == 0.0f && getFloatDistriValue(m_emission) > 0.0f)
					addParticle();

				float emission = getFloatDistriValue(m_emission) * getFloatDistriValue(m_emissionScale) / 1000.0f;

				//std::cout << "emission " << getFloatDistriValue(m_emission) << std::endl;

				if (emission != 0.0)
				{
					float perParticleTime = 1.0f / emission;
					m_emitCount = m_emitCount + (float)dt;

					//emit one frame particles
					while ((!isFull()) && m_emitCount > perParticleTime)
					{
						m_emitCount = m_emitCount - perParticleTime;

						addParticle();
					}
				}
				else
					m_emitCount = -0.000001;
				
			}
			else
				m_currentBrust = 0;
		}
	}
	// if end a loop 
    else if ((m_elapsed - delay) >= m_currentDuration)
    {
		m_emitterRunningState = RUNNING_FRAME_STATE::LOOP_END;
		//std::cout << "Emitter One Loop End" << std::endl;

		//emitter loop end state = true --> render thread put end state --> lua do callback



		//when emitter deactivated kill all particles
		if (m_killOnDeactivate == true)
		{
			/*for (int i = 0; i < m_particleCount; i++)
			{
				m_particleList[i]->reset();
			}*/

			m_particleCount = 0;//need reset attribute as well
		}

		m_emitterLifeTime = 0.0f; 
		m_elapsed = 0;
        m_loopCount = m_loopCount + 1;
		setCurrentBrust();
		if (m_durationRecal == true)
		{
			setCurrentDuration();
			resetParticlePool();
			m_particleList.resize(m_particleNum);
			m_shaderAttribute.resize(m_particleNum);
			return;
		}
	}

    //brust..... needs redo: to do add mutiple support(loop through points)
    if (m_useBrust && (m_elapsed > m_currentDuration * m_brustTiming + delay))
    {
		if (m_currentBrust != 0)
        {
		    for (int i = 0; i < m_currentBrust; i++)
            { 
				if (!isFull())
                {
                    addParticle();
				}
			}
            m_currentBrust = 0;
        }
    }

    //update particles
    m_currentIndex = 0;

	if (m_moduleMap[EventReceiver] == true)
	{
		addParticleByEvent();
	}

    while (m_currentIndex < m_particleCount) 
	{
        this->updateParticle(dt,m_particleList[m_currentIndex],m_currentIndex);
    }

	int index = 0;

	//m_frameData = "";

    for (int i = 0; i < m_particleCount; i++)
	{
		vec3 pos = m_particleList[i]->getShaderAttriPos();

		m_shaderAttribute[i].data[index] = pos.x;
		m_shaderAttribute[i].data[index+1] = pos.y;
		m_shaderAttribute[i].data[index+2]= pos.z;

		//m_frameData += " x = " + tostring(pos.x) + " y = " + pos.y + " z = " + pos.z + "\n";
	}

	index += 3;//3

	if (m_attributeFormat["pinAttribute"] == true)
	{ 
	    for (int i = 0; i < m_particleCount; i++)
	    {
			m_shaderAttribute[i].data[index] = m_pinCoord.x;
			m_shaderAttribute[i].data[index+1] = m_pinCoord.y;
			m_shaderAttribute[i].data[index+2] = m_pinCoord.z;
			m_shaderAttribute[i].data[index+3] = m_pinCoord.w;
			m_shaderAttribute[i].data[index+4] = m_pinAngle;
		}

		//m_frameData += " pinCoordx = " + m_pinCoord.x + " pinCoordy = " + m_pinCoord.y + " pinCoordz = " + m_pinCoord.z + " pinCoordw = " + m_pinCoord.w + "\n";

		index += 5;//8
	}

	if (m_attributeFormat["sizeAttribute"] == true)
	{
        for (int i = 0; i < m_particleCount; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriSize();
		}

		//m_frameData += " size = " + m_particleList[i]->getShaderAttriSize();

		index++;//9
	}

	if (m_attributeFormat["colorAttribute"] == true)
	{
		for (int i =0; i < m_particleCount; i++)
		{
			vec3 color = m_particleList[i]->getShaderAttriColor();
			m_shaderAttribute[i].data[index] = color.x;
			m_shaderAttribute[i].data[index+1] = color.y;
			m_shaderAttribute[i].data[index+2] = color.z;
			m_shaderAttribute[i].data[index+3] = m_particleList[i]->getShaderAttriAlpha();
		}

		//m_frameData += " colorx = " + color.x + " colory = " + color.y + " colorz = " + color.z + " colora = " + m_particleList[i]->getShaderAttriAlpha() + "\n";

		index += 4;
	}

	if (m_attributeFormat["flipAttribute"] == true)
	{
		for (int i = 0; i < m_particleCount; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriFlipU();
			m_shaderAttribute[i].data[index+1] = m_particleList[i]->getShaderAttriFlipV();
		}

		index += 2;
	}
	
	if (m_attributeFormat["rotationAttribute"] == true)
	{
		for (int i = 0; i < m_particleCount; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriRot();
		}

		index++;
	}

	if (m_attributeFormat["subUVAttribute"] == true)
	{
		for (int i =0; i < m_particleCount; i++)
		{
		    vec4 coord = m_particleList[i]->getShaderAttriSubCoord();
			m_shaderAttribute[i].data[index] = coord.x;
			m_shaderAttribute[i].data[index+1] = coord.y;
			m_shaderAttribute[i].data[index+2] = coord.z;
			m_shaderAttribute[i].data[index+3] = coord.w;

			/*std::cout << "subUVAttribute" 
				<< m_shaderAttribute[i].data[index] <<   "[" << index << "]" << ","
				<< m_shaderAttribute[i].data[index + 1] << "[" << index+1 << "]" << ","
				<< m_shaderAttribute[i].data[index + 2] << "[" << index+2 << "]" << ","
				<< m_shaderAttribute[i].data[index + 3] << "[" << index+3 << "]" << ","
				<< std::endl;*/
		}

		index += 4;
	}

	if (m_attributeFormat["subUVBlendAttribute"] == true)
	{
		for (int i = 0; i < m_particleCount; i++)
		{
			vec4 coordNext = m_particleList[i]->getShaderAttriSubCoordNext();
			m_shaderAttribute[i].data[index] = coordNext.x;
			m_shaderAttribute[i].data[index+1] = coordNext.y;
			m_shaderAttribute[i].data[index+2] = coordNext.z;
			m_shaderAttribute[i].data[index+3] = coordNext.w;
			m_shaderAttribute[i].data[index+4] = m_particleList[i]->getShaderAttriSubRatio();
			/*std::cout << "insert blend attribute :" 
				<< m_shaderAttribute[i].data[index] << "[" << index << "]" << ","
				<< m_shaderAttribute[i].data[index + 1] << "[" << index+1 << "]" << ","
				<< m_shaderAttribute[i].data[index + 2] << "[" << index+2 << "]" << ","
				<< m_shaderAttribute[i].data[index + 3] << "[" << index+3 << "]" << ","
				<< m_shaderAttribute[i].data[index + 4] << "[" << index+4 << "]" << ","
				<< std::endl; */
		}

		index += 5;
	}

	if (m_isLocalSpace == false)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			float scaleFactor = m_particleList[i]->m_currentScaleFactor;
			mat2 parentRotMat = m_particleList[i]->m_currentParentRotationMat;

			m_shaderAttribute[i].data[index] = scaleFactor;
			m_shaderAttribute[i].data[index + 1] = parentRotMat[0][0];
			m_shaderAttribute[i].data[index + 2] = parentRotMat[0][1];
			m_shaderAttribute[i].data[index + 3] = parentRotMat[1][0];
			m_shaderAttribute[i].data[index + 4] = parentRotMat[1][1];

			
			//std::cout << glm::to_string(mat) << std::endl;
		}
	}

	//std::cout << " update =============  " << m_stripeSize << std::endl;

	/*for (int i = 0; i < m_particleCount; i++)
	{
		for (int i1 = 0; i1 < m_stripeSize; i1++)
		{
			std::cout << m_shaderAttribute[i].data[i1] << ",";
		}

		std::cout << std::endl;
	}*/

	//decide action when emitter finished
    if((m_loop != 0) && ((m_elapsedDraw - delay * m_loop) > (m_currentDuration * m_loop)))
	{
		m_emitterRunningState = RUNNING_FRAME_STATE::FINISHED;
		//std::cout << "Emitter finish" << std::endl;

		//emitter finish state = true --> render thread put finish state --> lua do callback

		// on finish remove self from parent  should do in lua thread
		//if (m_killOnComplete)
		//{
		//     // should remove self from parent 	
		//}
	}
}

template<class T>
void Emittter<T>::EventParticleDataToJson(EventParticleMap &eventDataMap, jsonVal &eventDataCollector, jsonDoc::AllocatorType& allocator)
{
	//get eventDataMap, collects from update event
	for (auto iter = eventDataMap.begin(); iter != eventDataMap.end(); iter++)
	{
		std::vector<ParticleEventInfo> data = iter->second;

		jsonVal parDataList;
		parDataList.SetArray();

		for (int i = 0; i < data.size(); i++)
		{
			jsonVal posVec;
			posVec.SetArray();
			posVec.PushBack(data[i].pos.x, allocator);
			posVec.PushBack(data[i].pos.y, allocator);
			posVec.PushBack(data[i].pos.z, allocator);

			jsonVal velVec;
			velVec.SetArray();
			velVec.PushBack(data[i].vel.x, allocator);
			velVec.PushBack(data[i].vel.y, allocator);
			velVec.PushBack(data[i].vel.z, allocator);


			jsonVal parData;
			parData.SetObject();

			parData.AddMember("pos", posVec, allocator);
			parData.AddMember("vel", velVec, allocator);
			//parData.AddMember("time", data[i].time, allocator);

			parDataList.PushBack(parData, allocator);
		}

		jsonVal val(iter->first.c_str(), iter->first.size(), allocator);
		eventDataCollector.AddMember(val, parDataList, allocator);
	}
}

template<class T>
std::string Emittter<T>::getParticleEventData()
{
	jsonDoc document;

	jsonDoc::AllocatorType& allocator = document.GetAllocator();

	jsonVal eventDataCollector;
	eventDataCollector.SetObject();

	typename EventParticleMap::iterator iter;

	EventParticleDataToJson(m_deathParticleGenDataMap, eventDataCollector, allocator);

	EventParticleDataToJson(m_spawnParticleGenDataMap, eventDataCollector, allocator);

	EventParticleDataToJson(m_collisionParticleGenDataMap, eventDataCollector, allocator);

	EventParticleDataToJson(m_receiverParticleGenDataMap, eventDataCollector, allocator);

	clearAllEventParticleMap();

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	
	eventDataCollector.Accept(writer);

	std::string str(buffer.GetString());

	return str;
}

//template<class T>
//LuaIntf::LuaRef Emittter<T>::getParticleEventData()
//{
//	LuaIntf::LuaState LS(global_lua_state);
//	LS.newTable();
//	LuaIntf::LuaRef ref(global_lua_state, -1);
//	LS.pop();
//
//	EventParticleMap::iterator iter;
//
//	for (iter = m_deathParticleGenDataMap.begin(); iter != m_deathParticleGenDataMap.end(); iter++)
//	{
//		LS.newTable();
//		LuaIntf::LuaRef deathEventData(global_lua_state, -1);
//		LS.pop();
//
//		ref.set<std::string, LuaIntf::LuaRef>(iter->first, deathEventData);
//
//		std::vector<ParticleEventInfo> data = iter->second;
//
//		for (int i = 0; i < data.size(); i++)
//		{
//			LS.newTable();
//			LuaIntf::LuaRef parData(global_lua_state, -1);
//			LS.pop();
//			deathEventData.set<int, LuaIntf::LuaRef>(i + 1, parData);
//
//			LS.newTable();
//			LuaIntf::LuaRef posData(global_lua_state, -1);
//			LS.pop();
//
//			parData.set<std::string, LuaIntf::LuaRef>("pos", posData);
//
//			posData.set<int, float>(i + 1, data[i].pos.x);
//			posData.set<int, float>(i + 2, data[i].pos.y);
//			posData.set<int, float>(i + 3, data[i].pos.z);
//
//			LS.newTable();
//			LuaIntf::LuaRef velData(global_lua_state, -1);
//			LS.pop();
//
//			parData.set<std::string, LuaIntf::LuaRef>("vel", velData);
//
//			posData.set<int, float>(i + 1, data[i].vel.x);
//			posData.set<int, float>(i + 2, data[i].vel.y);
//			posData.set<int, float>(i + 3, data[i].vel.z);
//		}
//	}
//
//	return ref;
//}

template<class T>
void Emittter<T>::reactivated()
{
}

template <typename T>
void Emittter<T>::resetParticlePool()
{
	//std::cout << "Emitter Reset ParitclePool" << std::endl;

	float emissionRate = m_emission->getMaxValue() * getFloatDistriValue(m_emissionScale);

	float lifeTime = 1.0f;
	if (m_moduleMap[Emittter<T>::Lifetime])
	    lifeTime = m_lifeTime->getMaxValue() / 1000.0f;

	if (lifeTime < 1)
		lifeTime = 1;

	int particleLastNum = m_particleNum;

	if (m_maxCount > 0 && m_countUseMax)
	{
		m_particleNum = m_maxCount + 1;
	}
	else
	{
		m_particleNum = emissionRate * (lifeTime + 1) + m_brustNum * 2;
	}
	//std::vector<T> s;

	//std::cout << m_particleNum << "  " << s.max_size()<< std::endl;

	if (m_particleNum < 0)
		m_particleNum = 0;
	/*else if (m_particleNum > std::numeric_limits<unsigned short>::max())
		m_particleNum = std::numeric_limits<unsigned short>::max() - 1;*/
	else if (m_particleNum > 50000)
		m_particleNum = 50000;
	

	//std::cout << "particleNum----->" << emissionRate << "  " << lifeTime << "  " << m_brustNum << "  "  << m_particleNum << std::endl;
	
}

// reset emitter states
template <typename T>
void Emittter<T>::reset()
{
	//resetSeed()
	//std::cout << "Emitter Reset" << std::endl;

	m_currentIndex = 0;//index count for activated particles 
	m_particleCount = 0;//current activated particles
	m_elapsed = 0;//elapsed in single loop
	m_elapsedDraw = 0;//whole emitter elapsedtime
	m_emitCount = 0;//particle count for every single frame
	m_loopCount = 0;//current loops count
	m_locParticleIndex = 0;//the emitter location sequence index record
	m_deathParticleFrameCounter = 0;
	m_spawnParticleFrameCounter = 0;
	m_collisionParticleFrameCounter = 0;

	resetParticlePool();//define paricleNum, how many particle in pool
	setCurrentBrust();
	setCurrentDuration();
	setCurrentDelay();
	setAttributeFormat();
	setFlipUV();
}
template <typename T>
void Emittter<T>::clear()
{
	//std::cout << "clear*************************" << std::endl;
	m_particleList.clear();

	reset();
}
template <typename T>
float Emittter<T>::getFloatDistriValue(FloatDistri *dis)
{

	if (dis->dataType() == FloatDistri::CONSTANT)
		return dis->cons();
	else if (dis->dataType() == FloatDistri::UNIFORM)
	{
		return dis->min() + Random::Instance()->OneFloat() * (dis->max() - dis->min());
	}
	else if (dis->dataType() == FloatDistri::CONSCURVE && dis->curveList().size() > 0)
	{
		if (dis->isBaked())
			return dis->getCurveBaked(m_emitterLifeTime);
		else
			return dis->updateCurve(m_emitterLifeTime);
	}
	else if (dis->dataType() == FloatDistri::UNIFORMCURVE && dis->uniformCurveList().size() > 0)
	{
		if (dis->isBaked())
			return dis->getCurveBaked(m_emitterLifeTime);
		else
			return dis->updateUniformCurve(m_emitterLifeTime);
	}
	else
	{
		return 0.0f;//assert?
	}

}
template <typename T>
float Emittter<T>::getFloatDistriValue(FloatDistri *dis, float parLifeRate)
{

	//qDebug() << "getFloatDistriValue" << parLifeRate;
	if (dis->dataType() == FloatDistri::CONSTANT)
		return dis->cons();
	else if (dis->dataType() == FloatDistri::UNIFORM)
		return dis->min() + Random::Instance()->OneFloat() * (dis->max() - dis->min());
	else if (dis->dataType() == FloatDistri::CONSCURVE && dis->curveList().size() > 0)
	{
		if (dis->isBaked())
			return dis->getCurveBaked(parLifeRate * 10.0f);
		else
			return dis->updateCurve(parLifeRate);
	}
	else if (dis->dataType() == FloatDistri::UNIFORMCURVE && dis->uniformCurveList().size() > 0)
	{
		if (dis->isBaked())
			return dis->getCurveBaked(parLifeRate * 10.0f);
		else
			return dis->updateUniformCurve(parLifeRate);
	}
	else
	{
		return 0.0f;//assert?
	}
}
template <typename T>
float Emittter<T>::getFloatDistriValueFloor(FloatDistri * dis)
{
	float val = getFloatDistriValue(dis);
    return val > 0.0f ? val : 0.0f;
}
template <typename T>
float Emittter<T>::getFloatDistriValueFloor(FloatDistri * dis, float parLifeRate)
{
	float val = getFloatDistriValue(dis, parLifeRate);
	return val > 0.0f ? val : 0.0f;
}
template <typename T>
vec3 Emittter<T>::getVectorDistriValue(VectorDistri *dis)
{
	if (dis->dataType() == VectorDistri::CONSTANT)
		return dis->cons();
	else if (dis->dataType() == VectorDistri::UNIFORM)
		return dis->min() + Random::Instance()->OneVector3D() * (dis->max() - dis->min());
	else if (dis->dataType() == VectorDistri::CONSCURVE && dis->curveList().size() > 0)
	{
		if (dis->isBaked())
			return dis->getCurveBaked(m_emitterLifeTime);
		else
			return dis->updateCurve(m_emitterLifeTime);
	}
	else if (dis->dataType() == VectorDistri::UNIFORMCURVE && dis->uniformCurveList().size() > 0)
	{
		if (dis->isBaked())
			return dis->getCurveBaked(m_emitterLifeTime);
		else
			return dis->updateUniformCurve(m_emitterLifeTime);
	}
	else
	{
		return vec3(0.0f);//assert?
	}
}
template <typename T>
vec3 Emittter<T>::getVectorDistriValue(VectorDistri *dis, float parLifeRate)
{
	if (dis->dataType() == VectorDistri::CONSTANT)
		return dis->cons();
	else if (dis->dataType() == VectorDistri::UNIFORM)
		return dis->min() + Random::Instance()->OneVector3D() * (dis->max() - dis->min());
	else if (dis->dataType() == VectorDistri::CONSCURVE && dis->curveList().size() > 0)
	{
		if (dis->isBaked())
		{
			//std::cout << "isBaked" << std::endl;
			return dis->getCurveBaked(parLifeRate * 10.0f);
		}
		else
			return dis->updateCurve(parLifeRate);
	}
	else if (dis->dataType() == VectorDistri::UNIFORMCURVE && dis->uniformCurveList().size() > 0)
	{
		if (dis->isBaked())
			return dis->getCurveBaked(parLifeRate * 10.0f);
		else
			return dis->updateUniformCurve(parLifeRate);
	}
	else
	{
		return vec3(0.0f);//assert?
	}
}
template <typename T>
vec3 Emittter<T>::getVectorDistriValueFloor(VectorDistri * dis)
{
	vec3 val = getVectorDistriValue(dis);
	val.x = val.x > 0 ? val.x : 0.0f;
	val.y = val.y > 0 ? val.y : 0.0f;
	val.z = val.z > 0 ? val.z : 0.0f;
	return val;
}
template <typename T>
vec3 Emittter<T>::getVectorDistriValueFloor(VectorDistri * dis, float parLifeRate)
{
	vec3 val = getVectorDistriValue(dis, parLifeRate);
	val.x = val.x > 0 ? val.x : 0.0;
	val.y = val.y > 0 ? val.y : 0.0;
	val.z = val.z > 0 ? val.z : 0.0;
	return val;
}
template <typename T>
float Emittter<T>::clampVal(float val)
{
	val = val > 255 ? 255 : val;
	val = val < 0 ? 0 : val;

	return val;
}
template <typename T>
void Emittter<T>::setSubCoordList()
{
	m_coordList.clear();

	float width = 1.0 / m_subUVHori;
	float height = 1.0 / m_subUVVerti;

	if (m_attributeFormat["pinAttribute"] == true)
	{
		for (int row = 0; row < m_subUVHori; row++)
		{
			for (int col = m_subUVVerti - 1; col >= 0; col--)
			{
				m_coordList.push_back(vec4(row * width, col * height, width, height));
			}
		}
	}
	else
	{
		for (int col = 0; col < m_subUVVerti; col++)
		{
			for (int row = 0; row < m_subUVHori; row++)
			{
				m_coordList.push_back(vec4(row * width, col * height, width, height));
		    }
	    }
    }
}
template <typename T>
std::vector<vec4> Emittter<T>::getSubCoordList()
{
	return m_coordList;
}
template <typename T>
int Emittter<T>::getParticleCount()
{
	if (m_countUseMax && isMax())
	{
		return m_maxCount;
	}
	else if (m_particleCount >= (m_particleNum - 1))
	{
		return m_particleNum - 1;
	}
	else
	{
		return m_particleCount;
	}
}
//template <typename T>
//float Emittter<T>::getParticleLifeRate()
//{
//	return m_emitterLifeTime;
//}
template <typename T>
int Emittter<T>::getMaxParticleCount()
{
	if (m_countUseMax && isMax())
		return m_maxCount;
	else
		return m_particleCount;
}

template <typename T>
std::string Emittter<T>::getAttributeFormat()
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	m_attributeFormat.Accept(writer);

	std::string str(buffer.GetString());

	return str;
}
template <typename T>
int Emittter<T>::getParticleNum()
{
	return m_particleNum;
}

template <typename T>
int Emittter<T>::getAttriStripeSize()
{
	return m_shaderAttribute.size() > 0 ? m_stripeSize : 0;
}
template <typename T>
void Emittter<T>::setCurrentBrust()
{
	if (m_brustNumLow != -1)
		m_currentBrust = (m_brustNumLow + Random::Instance()->IntNum(m_brustNum - m_brustNumLow)) * getFloatDistriValue(m_brustScale);
	else
		m_currentBrust = m_brustNum;
}
template <typename T>
int Emittter<T>::getCurrentBrust()
{
	return m_currentBrust;
}
template <typename T>
void Emittter<T>::setCurrentDuration()
{
	int64_t duration = m_duration;
	int64_t durationLow = m_durationLow;

	if (m_useRange == true)
		m_currentDuration = durationLow + Random::Instance()->IntNum(duration - durationLow);
	else
		m_currentDuration = duration;
}
template <typename T>
int64_t Emittter<T>::getCurrentDuration()
{
	return m_currentDuration;
}
template <typename T>
void Emittter<T>::setCurrentDelay()
{
	int64_t delay = m_delay;
	int64_t delayLow = m_delayLow;
	
	if (m_delayUseRange == true)
		m_currentDelay = delayLow + Random::Instance()->IntNum(delay - delayLow);
	else
		m_currentDelay = delay;
}
template <typename T>
int64_t Emittter<T>::getCurrentDelay()
{
	return m_currentDelay;
}

template <typename T>
void Emittter<T>::setFlipUV()
{
	if (m_flipUV == 0)
	{
		setFlipTexU(false);
		setFlipTexV(false);
		setRandomFlipU(false);
		setRandomFlipV(false);
	}
	else if (m_flipUV == 1)
	{
		setFlipTexU(true);
		setFlipTexV(true);
		setRandomFlipU(false);
		setRandomFlipV(false);
	}
	else if (m_flipUV == 2)
	{
		setFlipTexU(true);
		setFlipTexV(false);
		setRandomFlipU(false);
		setRandomFlipV(false);
	}
	else if (m_flipUV == 3)
	{
		setFlipTexU(false);
		setFlipTexV(true);
		setRandomFlipU(false);
		setRandomFlipV(false);
	}
	else if (m_flipUV == 4)
	{
		setFlipTexU(false);
		setFlipTexV(false);
		setRandomFlipU(true);
		setRandomFlipV(false);
	}
	else if (m_flipUV == 5)
	{
		setFlipTexU(false);
		setFlipTexV(false);
		setRandomFlipU(false);
		setRandomFlipV(true);
	}
	else if (m_flipUV == 6)
	{
		setFlipTexU(false);
		setFlipTexV(false);
		setRandomFlipU(true);
		setRandomFlipV(true);
	}
}
template <typename T>
void Emittter<T>::setFlipTexU(bool val)
{
	m_flipTexcoordU = val;
}
template <typename T>
void Emittter<T>::setFlipTexV(bool val)
{
	m_flipTexcoordV = val;
}
template <typename T>
void Emittter<T>::setRandomFlipU(bool val)
{
	m_randomTexU = val;
}
template <typename T>
void Emittter<T>::setRandomFlipV(bool val)
{
	m_randomTexV = val;
}
template <typename T>
float Emittter<T>::getSpeedSizeX()
{
	if (m_speedSizeX > m_speedSizeXMax && m_speedSizeXMax != 0)
		return m_speedSizeXMax;
	else
		return m_speedSizeX;
}
template <typename T>
float Emittter<T>::getSpeedSizeY()
{
	if (m_speedSizeY > m_speedSizeYMax && m_speedSizeYMax != 0)
		return m_speedSizeYMax;
	else
		return m_speedSizeY;
}
template <typename T>
int Emittter<T>::getOrbitConfig(int dataType, int controlType)
{
	if (dataType == Emittter::OFFSET && controlType == Emittter::SPAWN)
	{
		return m_orbitOffsetSpawn;
	}
	else if (dataType == Emittter::OFFSET && controlType == Emittter::UPDATE)
	{
		return m_orbitOffsetUpdate;
	}
	else if (dataType == Emittter::OFFSET && controlType == Emittter::EMITTER_TIME)
	{
		return m_orbitOffsetEmitterTime;
	}
	else if (dataType == Emittter::ROTATION && controlType == Emittter::SPAWN)
	{
		return m_orbitRotationSpawn;
	}
	else if (dataType == Emittter::ROTATION && controlType == Emittter::UPDATE)
	{
		return m_orbitRotationUpdate;
	}
	else if (dataType == Emittter::ROTATION && controlType == Emittter::EMITTER_TIME)
	{
		return m_orbitRotationEmitterTime;
	}
	else if (dataType == Emittter::ROTATERATE && controlType == Emittter::SPAWN)
	{
		return m_orbitRotationRateSpawn;
	}
	else if (dataType == Emittter::ROTATERATE && controlType == Emittter::UPDATE)
	{
		return m_orbitRotationRateUpdate;
	}
	else if (dataType == Emittter::ROTATERATE && controlType == Emittter::EMITTER_TIME)
	{
		return m_orbitRotationEmitterTime;
	}
	else
	{
		return -1;//assert
	}
}
template <typename T>
float Emittter<T>::getInitAlphaValue()
{
	float alpha = getFloatDistriValue(m_initAlpha);

	if (m_clampAlpha)
	{
		return clampVal(alpha);
	}
	else
		return alpha;
}
template <typename T>
float Emittter<T>::getAlphaOverLifeValue(float parLifeRate)
{
	float alpha = getFloatDistriValue(m_alphaOverLife, parLifeRate);

	if (m_clampAlphaLife)
	{
		return clampVal(alpha);
	}
	else
		return alpha;
}
template <typename T>
bool* Emittter<T>::getModuleMap()
{
	return m_moduleMap;
}

template <typename T>
float Emittter<T>::getEmitterLifeTime()
{
	return m_emitterLifeTime;
}

//change to array
template <typename T>
void* Emittter<T>::getShaderAttribute()
{
	//std::cout << "getShaderAttribute  particleCount--->" << m_particleCount << "attriLength" << sizeof(m_shaderAttribute[0].data) << std::endl;
	/*for (int i = 0; i < m_particleCount; i++)
	{
		std::cout << "attributeSize   " << sizeof(m_shaderAttribute[i].data) << "   float   " << sizeof(float) << std::endl;

		std::cout << "(";
		for (int j = 0; j < sizeof(m_shaderAttribute[i].data) / sizeof(float); j++)
			std::cout << m_shaderAttribute[i].data[j] << ",";

		std::cout << ")" << std::endl;
	}

	std::cout << "sssss" << m_stripeSize << std::endl;*/

	float* p = (float*)(&(m_shaderAttribute[0]));
	/*printf("Attribute address %p\n", p);
	std::cout  << "values" << p[0] << p[1] << std::endl;*/
	return p;
}

template <typename T>
std::string Emittter<T>::getShaderLocAttribute()
{
	/*std::vector<float> posAttribute;
	for (int i = 0; i < m_shaderAttribute.size(); i++)
	{
		posAttribute.push_back(m_shaderAttribute[i].data[0]);
		posAttribute.push_back(m_shaderAttribute[i].data[1]);
		posAttribute.push_back(m_shaderAttribute[i].data[2]);
	}
	float* p = (float*)(&(posAttribute[0]));

	return p;*/

	

	jsonDoc document;

	jsonDoc::AllocatorType& allocator = document.GetAllocator();

	jsonVal posAttributeArray;
	posAttributeArray.SetArray();

	for (int i = 0; i < m_particleCount; i++)
	{
		vec3 pos = m_particleList[i]->getShaderAttriPos();
		posAttributeArray.PushBack(pos.x, allocator);
		posAttributeArray.PushBack(pos.y, allocator);
		posAttributeArray.PushBack(pos.z, allocator);

		vec3 vel = m_particleList[i]->getVelocity();
		posAttributeArray.PushBack(vel.x, allocator);
		posAttributeArray.PushBack(vel.y, allocator);
		posAttributeArray.PushBack(vel.z, allocator);

		posAttributeArray.PushBack(m_particleList[i]->getShaderAttriRot(), allocator);
	}
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	posAttributeArray.Accept(writer);

	std::string str(buffer.GetString());
	return str;
}

template <typename T>
void Emittter<T>::setLocEmitterAttribute(std::string posAttribute)
{
	locEmitterPosData.clear();
	locEmitterVelData.clear();
	locEmitterRotData.clear();

	jsonDoc doc;
	doc.Parse(posAttribute.c_str());

	//locEmitterPosData.SetArray();

	//std::cout << "Size  " << doc.Size() << std::endl;
	/*rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	locEmitterPosData.Accept(writer);

	std::string str(buffer.GetString());
*/
	for (int i = 0; i + 6 < doc.Size(); i += 7)
	{
		vec3 pos = vec3(doc[i].GetFloat(), doc[i + 1].GetFloat(), doc[i + 2].GetFloat());
		locEmitterPosData.push_back(pos);

		//std::cout << "locEmitterPosData.size()  " << locEmitterPosData.size();

		vec3 vel = vec3(doc[i + 3].GetFloat(), doc[i + 4].GetFloat(), doc[i + 5].GetFloat());
		locEmitterVelData.push_back(vel);

		//std::cout << "locEmitterVelData.size()  " << locEmitterVelData.size();

		locEmitterRotData.push_back(doc[i + 6].GetFloat());

		//std::cout << "locEmitterRotData.size()  " << locEmitterRotData.size();
	}

	//std::cout << "data  " << pos.c_str() << std::endl;
}

template<class T>
std::vector<vec3> Emittter<T>::getLocPosAttribute()
{
	return locEmitterPosData;
}

template<class T>
std::vector<vec3> Emittter<T>::getLocVelAttribute()
{
	return locEmitterVelData;
}

template<class T>
std::vector<float> Emittter<T>::getLocRotAttribute()
{
	return locEmitterRotData;
}

template <typename T>
void Emittter<T>::setDirectEmitterAttribute(std::string posAttribute)
{
	directEmitterPosData.clear();

	jsonDoc doc;
	doc.Parse(posAttribute.c_str());

	for (int i = 0; i + 6 < doc.Size(); i += 7)
	{
		vec3 v = vec3(doc[i].GetFloat(), doc[i + 1].GetFloat(), doc[i + 2].GetFloat());
		directEmitterPosData.push_back(v);
	}
}

template<class T>
std::vector<vec3> Emittter<T>::getDirectPosAttribute()
{
	return directEmitterPosData;
}

template<class T>
vec3 Emittter<T>::getInitLocationValue()
{
	if (m_initLocation->dataType() == VectorDistri::CONSTANT || m_initLocation->dataType() == VectorDistri::CONSCURVE)
		return getVectorDistriValue(m_initLocation);
	else
	{
		if (m_locDistriPoint == 0) 
			return getVectorDistriValue(m_initLocation);
		else if (m_locDistriPoint == 1)
		{
			if (m_initLocation->dataType() == VectorDistri::UNIFORM)
				return m_initLocation->max();
			else if (m_initLocation->dataType() == VectorDistri::UNIFORMCURVE)
			{
				getVectorDistriValue(m_initLocation);
				return m_initLocation->m_currentUniformCurveMax;
			}
			else
				return vec3(0.0f);
		}
		else
		{
			if (m_locDistriThreshold == 0)
				return locCal(m_initLocation, m_locDistriPoint);
			else
			{
				if (Random::Instance()->OneFloat() > m_locDistriThreshold)
					return getVectorDistriValue(m_initLocation);
				else
					return locCal(m_initLocation, m_locDistriPoint);
			}
		}
	}
}

template<class T>
vec3 Emittter<T>::getWorldOffsetValue()
{
	//std::cout << "getWorldOffsetValue" << std::endl;
	if (m_worldOffset->dataType() == VectorDistri::CONSTANT || m_worldOffset->dataType() == VectorDistri::CONSCURVE)
		return getVectorDistriValue(m_worldOffset);
	else
	{
		if (m_worldOffsetPoint == 0) 
			return getVectorDistriValue(m_worldOffset);
		else if (m_worldOffsetPoint == 1)
		{
			if (m_worldOffset->dataType() == VectorDistri::UNIFORM)
			return m_worldOffset->max();
			else if (m_worldOffset->dataType() == VectorDistri::UNIFORMCURVE)
			{
				getVectorDistriValue(m_worldOffset);
				return m_worldOffset->m_currentUniformCurveMax;
			}
			else
				return vec3(0.0f);
		}
		else
		{
			if (m_worldOffsetThreshold == 0)
				return locCal(m_worldOffset, m_worldOffsetPoint);
			else
			{
				if (Random::Instance()->OneFloat() > m_worldOffsetThreshold)
					return getVectorDistriValue(m_worldOffset);
				else
					return locCal(m_worldOffset, m_worldOffsetPoint);
			}
		}
	}
}

template<class T>
vec3 Emittter<T>::locCal(VectorDistri * distri, int locPoint)
{
	//std::cout << "locCal" << std::endl;
	vec3 value = getVectorDistriValue(distri);
	vec3 diff = vec3(0.0f);

	if (distri->dataType() == VectorDistri::UNIFORM)
	{
		diff = distri->max() - distri->min();
		value -= distri->min();
	}
	else if (distri->dataType() == VectorDistri::UNIFORMCURVE)
	{
		diff = distri->m_currentUniformCurveMax - distri->m_currentUniformCurveMin;
		value -= distri->m_currentUniformCurveMin;
	}

	vec3 offset = vec3(0.0f);

	int stepCountX = diff.x == 0.0f ? 0 : floor(value.x / (diff.x / (float)locPoint));
	float offPosX = diff.x / ((float)locPoint - 1.0f);
	offset.x = stepCountX * offPosX;

	int stepCountY = diff.y == 0.0f ? 0 : floor(value.y / (diff.y / (float)locPoint));
	float offPosY = diff.y / ((float)locPoint - 1.0f);
	offset.y = stepCountY * offPosY;

	//z 
	/*int stepCountX = diff.x / (float)locPoint == 0 ? 0 || floor(value.x / (diff.x / (float)locPoint));
	float offPosX = diff.x / ((float(locPoint) - 1.0f);
	offset.x = stepCountX * offPosX;*/


	
	if (distri->dataType() == VectorDistri::UNIFORM)
		return offset + distri->min();
	else if (distri->dataType() == VectorDistri::UNIFORMCURVE)
		return offset + distri->m_currentUniformCurveMin;
	else
		return vec3(0.0f);//
}

template<class T>
void Emittter<T>::setTextureSize(float w, float h)
{
	m_textureSize = vec2(w, h);
}

template<class T>
void Emittter<T>::setCanvasSize(float w, float h)
{
	m_canvasSize = vec2(w, h);
}

template<class T>
int Emittter<T>::getLoop()
{
	return m_loop;
}

template<class T>
int Emittter<T>::getLoopCount()
{
	return m_loopCount;
}

template<class T>
void Emittter<T>::setLocParticleIndex(int index)
{
	m_locParticleIndex = index;
}

template<class T>
int Emittter<T>::getLocParticleIndex()
{
	return m_locParticleIndex;
}

template<class T>
void Emittter<T>::updateEmitterWorldPos(float worldPosX, float worldPosY)
{
	m_emitterWorldPosX = worldPosX;
	m_emitterWorldPosY = worldPosY;
}

template<class T>
void Emittter<T>::updateEmitterCurrentMatrix(float num1, float num2, float num3, float num4, float num5, float num6, float num7, float num8, float num9, float num10, float num11, float num12, float num13, float num14, float num15, float num16)
{
	m_currentMat = mat4(num1, num2, num3, num4,
		num5, num6, num7, num8,
		num9, num10, num11, num12,
		num13, num14, num15, num16);
}

template<class T>
void Emittter<T>::updateEmitterCurrentViewScale(float scaleX, float scaleY)
{
	m_currentViewScale = vec2(scaleX, scaleY);
}

template<class T>
std::string Emittter<T>::getFrameData()
{
	return m_frameData;
}


























#include "EmitterData.h"



EmitterData::EmitterData()
{
}

EmitterData::EmitterData(LuaIntf::LuaRef &emitterDataRef)
	: m_particleNum(0)
	//, m_texturePath()
	 
	, m_emitterName("Emitter")
	, m_emitterPosX(0.0f)
	, m_emitterPosY(0.0f)
	, m_emitterWorldPosX(0.0f)
	, m_emitterWorldPosY(0.0f)
	, m_emitterRot(0.0f)

	, m_killOnComplete(false)
	, m_killOnDeactivate(true)

	, m_duration(0)
	, m_durationLow(0)
	, m_useRange(false)
	, m_durationRecal(false)

	, m_loop(-1)

	, m_delay(0)
	, m_delayLow(0)
	, m_delayUseRange(false)
	, m_delayFirstLoop(false)

	, m_maxCount(0)
	, m_countUseMax(false)

	, m_subUVHori(1)
	, m_subUVVerti(1)
	, m_subUVMode(0)
	, m_subUVRandomNum(0)

	, m_clip(false)
	, m_isLocalSpace(true)
	
	, m_flipUV(0)
	, m_flipTexcoordU(false)
	, m_flipTexcoordV(false)
	, m_randomTexU(false)
	, m_randomTexV(false)

	, m_brustNum(0)
	, m_brustNumLow(-1)
	, m_brustTiming(0.0f)
	, m_useBrust(false)

	, m_speedSizeX(1.0f)
	, m_speedSizeY(1.0f)
	, m_speedSizeXMax(0.0f)
	, m_speedSizeYMax(0.0f)

	, m_clampAlpha(false)
	, m_clampAlphaLife(false)
	, m_colorScaleEmitterLife(false)

	, m_coneDirection(0.0f)
	, m_velocityAbsolute(false)

	, m_locDistriPoint(0)
	, m_locDistriThreshold(0.0f)
	, m_worldOffsetPoint(0)
	, m_worldOffsetThreshold(0.0f)

	, m_locEmitterName("")
	, m_locEmitterMode(0)
	, m_locEmitterCount(0)
	, m_inheritSourceVelocity(false)
	, m_inheritSourceRotation(false)
	, m_inheritVelScale(1.0f)
	, m_inheritRotScale(1.0f)
	, m_locDirectEmitterName("")

	, m_spherePositiveX(true)
	, m_sphereNegativeX(true)
	, m_spherePositiveY(true)
	, m_sphereNegativeY(true)
	, m_sphereSurface(false)
	, m_sphereVelocity(false)

	, m_orbitOffsetSpawn(false)
	, m_orbitOffsetUpdate(false)
	, m_orbitOffsetEmitterTime(false)
	, m_orbitRotationSpawn(false)
	, m_orbitRotationUpdate(false)
	, m_orbitRotationEmitterTime(false)
	, m_orbitRotationRateSpawn(false)
	, m_orbitRotationRateUpdate(false)
	, m_orbitRotationRateEmitterTime(false)
	, m_strengthByDistance(false)
	, m_affectBaseVelocity(false)

	, m_lineAttractorPoint1X(0.0f)
	, m_lineAttractorPoint1Y(0.0f)
	, m_lineAttractorPoint2X(0.0f)
	, m_lineAttractorPoint2Y(0.0f)

	, m_killInside(false)
	, m_killFloor(true)

	, m_floorCollisionAxis(0)
	, m_floorCollisionAxisPos(0.0f)
	, m_floorCollisionDelayAmount(0)
	, m_floorCollisionCompleteOpt(0)

	, m_lineCollisionPoint0X(0.0f)
	, m_lineCollisionPoint0Y(0.0f)
	, m_lineCollisionPoint1X(0.0f)
	, m_lineCollisionPoint1Y(0.0f)
	, m_lineCollisionDelayAmount(0)
	, m_lineCollisionCompleteOpt(0)

	, m_rectCollisionPosX(0.0f)
	, m_rectCollisionPosY(0.0f)
	, m_rectCollisionWidth(0.0f)
	, m_rectCollisionHeight(0.0f)
	, m_rectCollisionDelayAmount(0)
	, m_rectCollisionCompleteOpt(0)

	, m_sphereCollisionCenterX(0.0f)
	, m_sphereCollisionCenterY(0.0f)
	, m_sphereCollisionRadius(0.0f)
	, m_sphereCollisionDelayAmount(0)
	, m_sphereCollisionCompleteOpt(0)

	, m_velRotation(false)
	//,m_tangentSpeed(0)

	, m_emission(new FloatDistriData("Emission Rate", 0, 100))
	, m_emissionScale(new FloatDistriData("Emission Scale", 1, 1))
	, m_brustScale(new FloatDistriData("Brust Scale", 2, 1))
	, m_initSize(new FloatDistriData("Init Size", 3, 30))
	, m_sizeLife(new FloatDistriData("Size By Life", 4, 1))
	, m_sizeScale(new FloatDistriData("Size By Scale", 5, 1))
	, m_lifeTime(new FloatDistriData("Lifetime", 6, 1000))
	, m_initColor(new VectorDistriData("Init Color", 7, vec3(255, 255, 255), vec3(0, 0, 0), vec3(255, 255, 255)))
	, m_initAlpha(new FloatDistriData("Init Alpha", 8, 255, 0, 255))
	, m_colorOverLife(new VectorDistriData("Color Over Life", 9, vec3(255, 255, 255), vec3(0, 0, 0), vec3(255, 255, 255)))
	, m_alphaOverLife(new FloatDistriData("Alpha Over Life", 10, 255, 0, 255))
	, m_colorScaleOverLife(new VectorDistriData("Color Scale Over Life", 11, vec3(1, 1, 1), vec3(0, 0, 0), vec3(1, 1, 1)))
	, m_alphaScaleOverLife(new FloatDistriData("Alpha Scale Over Life", 12, 1, 0, 1))
	, m_initVelocity(new VectorDistriData("Init Velocity", 13, vec3(0, 100, 0)))
	, m_initVelocityRadial(new FloatDistriData("Init Velocity Radial", 14))
	, m_velOverLife(new VectorDistriData("Vel Over Life", 35))
	, m_coneVelocityAngle(new FloatDistriData("Velocity Angle", 15, 50))
	, m_coneVelocityVelocity(new FloatDistriData("Velocity Speed", 16, 100, 100, 100))
	, m_initAcceleration(new VectorDistriData("Init Acceleration", 17, vec3(100, 100, 0)))
	, m_drag(new FloatDistriData("Drag", 18, 0.5))
	, m_accelOverLife(new VectorDistriData("Accel Over Life", 19, vec3(50, 50, 0)))
	, m_initRotate(new FloatDistriData("Init Rotate", 20, 90))
	, m_rotateOverLife(new FloatDistriData("Rot Over Life", 21, 90))
	, m_initRotRate(new FloatDistriData("Init Rot Rate", 22, 5))
	, m_rotRateLife(new FloatDistriData("Rot Rate Life", 23, 5))
	, m_initLocation(new VectorDistriData("Init Location", 24))
	, m_worldOffset(new VectorDistriData("World Offset", 25))
	, m_directLocation(new VectorDistriData("Direct Location", 26))
	, m_dirLocationOffset(new VectorDistriData("Dir Location Offset", 27))
	, m_dirLocationScale(new VectorDistriData("Vel Scale", 28))
	, m_sphereRadius(new FloatDistriData("Sphere Radius", 29))
	, m_sphereVelocityScale(new FloatDistriData("Sphere Vel Scale", 30, 1, 1, 1))
	, m_sphereOffset(new VectorDistriData("Sphere Offset", 31))
	, m_triangleHeight(new FloatDistriData("Triangle Height", 32))
	, m_triangleAngle(new FloatDistriData("Triangle Angle", 33))
	, m_triangleOffset(new VectorDistriData("Triangle Offset", 34))
	, m_subUVIndex(new FloatDistriData("SubUV Index", 36))
	, m_orbitOffset(new VectorDistriData("Orbit offset", 37))
	, m_orbitRotation(new VectorDistriData("Orbit Rotation", 38))
	, m_orbitRotationRate(new VectorDistriData("Orbit Rot Rate", 39))
	, m_pointAttractorPosition(new VectorDistriData("Point Attractor Pos", 40))
	, m_pointAttractorRange(new FloatDistriData("Point Attractor Range", 41))
	, m_pointAttractorStrength(new FloatDistriData("Point Attractor Str", 42))
	, m_lineAttractorRange(new FloatDistriData("Line Attractor Range", 43))
	, m_lineAttractorStrength(new FloatDistriData("Line Attractor Str", 44))
	, m_killBoxTopLeft(new VectorDistriData("Box Top Left", 45))
	, m_killBoxLowRight(new VectorDistriData("Box Low Right", 46))
	, m_killHeight(new FloatDistriData("Kill Height", 47))
	, m_floorDampVel(new VectorDistriData("Floor Damp Vel", 48, vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1)))
	, m_floorDampRot(new FloatDistriData("Floor Damp Rot", 49, 1, 1, 1))
	, m_floorMaxCollision(new FloatDistriData("Floor Max Collision", 50, -1, -1, -1))
	, m_lineDampVel(new VectorDistriData("Line Damp Vel", 51, vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1)))
	, m_lineDampRot(new FloatDistriData("Line Damp Rot", 52, 1, 1, 1))
	, m_lineMaxCollision(new FloatDistriData("Line Max Collision", 53, -1, -1, -1))
	, m_rectDampVel(new VectorDistriData("Rect Damp Vel", 54, vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1)))
	, m_rectDampRot(new FloatDistriData("Rect Damp Rot", 55, 1, 1, 1))
	, m_rectMaxCollision(new FloatDistriData("Rect Max Collision", 56, -1, -1, -1))
	, m_sphereDampVel(new VectorDistriData("Sphere Damp Vel", 57, vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1)))
	, m_sphereDampRot(new FloatDistriData("Sphere Damp Rot", 58, 1, 1, 1))
	, m_sphereMaxCollision(new FloatDistriData("Sphere Max Collision", 59, -1, -1, -1))
	, m_particleEvent(nullptr)
{
	auto moduleMapRef = emitterDataRef.get("m_moduleMap");
	
	m_moduleMap[Required] = moduleMapRef.get("Required").toValue<bool>();
	m_moduleMap[Spawn] = moduleMapRef.get("Spawn").toValue<bool>();
	m_moduleMap[InitialSize] = moduleMapRef.get("Initial Size").toValue<bool>();
	m_moduleMap[SizeByScale] = moduleMapRef.get("Size By Scale").toValue<bool>();
	m_moduleMap[SizeByLife] = moduleMapRef.get("Size By Life").toValue<bool>();
	m_moduleMap[SizeBySpeed] = moduleMapRef.get("Size By Speed").toValue<bool>();
	m_moduleMap[Lifetime] = moduleMapRef.get("Lifetime").toValue<bool>();
	m_moduleMap[InitialColor] = moduleMapRef.get("Initial Color").toValue<bool>();
	m_moduleMap[ColorOverLife] = moduleMapRef.get("Color Over Life").toValue<bool>();
	m_moduleMap[ColorScaleLife] = moduleMapRef.get("Color Scale Life").toValue<bool>();
	m_moduleMap[InitialVelocity] = moduleMapRef.get("Initial Velocity").toValue<bool>();
	m_moduleMap[VelocityCone] = moduleMapRef.get("Velocity Cone").toValue<bool>();
	m_moduleMap[VelOverLife] = moduleMapRef.get("Vel Over Life").toValue<bool>();
	m_moduleMap[InitialAccel] = moduleMapRef.get("Initial Accel").toValue<bool>();
	m_moduleMap[Drag] = moduleMapRef.get("Drag").toValue<bool>();
	m_moduleMap[AccelOverLife] = moduleMapRef.get("Accel Over Life").toValue<bool>();
	m_moduleMap[InitRotate] = moduleMapRef.get("Init Rotate").toValue<bool>();
	m_moduleMap[RotateOverLife] = moduleMapRef.get("Rotate Over Life").toValue<bool>();
	m_moduleMap[InitRotRate] = moduleMapRef.get("Init Rot Rate").toValue<bool>();
	m_moduleMap[RotRateLife] = moduleMapRef.get("Rot Rate Life").toValue<bool>();
	m_moduleMap[InitLocation] = moduleMapRef.get("Init Location").toValue<bool>();
	m_moduleMap[WorldOffset] = moduleMapRef.get("World Offset").toValue<bool>();
	m_moduleMap[DirectLocation] = moduleMapRef.get("Direct Location").toValue<bool>();
	m_moduleMap[EmitterInitLoc] = moduleMapRef.get("Emitter Init Loc").toValue<bool>();
	m_moduleMap[EmitterDirectLoc] = moduleMapRef.get("Emitter Direct Loc").toValue<bool>();
	m_moduleMap[Sphere] = moduleMapRef.get("Sphere").toValue<bool>();
	m_moduleMap[Triangle] = moduleMapRef.get("Triangle").toValue<bool>();
	m_moduleMap[SubUV] = moduleMapRef.get("Sub UV").toValue<bool>();
	m_moduleMap[Orbit] = moduleMapRef.get("Orbit").toValue<bool>();
	m_moduleMap[PointAttractor] = moduleMapRef.get("Point Attractor").toValue<bool>();
	m_moduleMap[LineAttractor] = moduleMapRef.get("Line Attractor").toValue<bool>();
	m_moduleMap[KillBox] = moduleMapRef.get("Kill Box").toValue<bool>();
	m_moduleMap[KillHeight] = moduleMapRef.get("Kill Height").toValue<bool>();
	m_moduleMap[CollisionFloor] = moduleMapRef.get("Collision Floor").toValue<bool>();
	m_moduleMap[CollisionLine] = moduleMapRef.get("Collision Line").toValue<bool>();
	m_moduleMap[CollisionRect] = moduleMapRef.get("Collision Rect").toValue<bool>();
	m_moduleMap[CollisionSphere] = moduleMapRef.get("Collision Sphere").toValue<bool>();

	//old version particle data may not has this keys
	if (moduleMapRef.has("Event Generator"))
	{
		m_moduleMap[EventGenerator] = moduleMapRef.get("Event Generator").toValue<bool>();
	}
	if (moduleMapRef.has("Event Receiver"))
	{
		m_moduleMap[EventReceiver] = moduleMapRef.get("Event Receiver").toValue<bool>();
	}



	m_particleNum = Get_Int("m_particleNum", m_particleNum);

	// could be simple respath or pin table map
	if (emitterDataRef.has("m_texturePath") && emitterDataRef.get("m_texturePath").isTable())
	{
		auto m_texturePathRef = emitterDataRef.get("m_texturePath");
		m_texturePathInfo.x = m_texturePathRef.has("x") && (m_texturePathRef.get("x").type() == LuaIntf::LuaTypeID::NUMBER) ? m_texturePathRef.get("x").toValue<float>() : m_texturePathInfo.x;
		m_texturePathInfo.y = m_texturePathRef.has("y") && (m_texturePathRef.get("y").type() == LuaIntf::LuaTypeID::NUMBER) ? m_texturePathRef.get("y").toValue<float>() : m_texturePathInfo.y;
		m_texturePathInfo.width = m_texturePathRef.has("width") && (m_texturePathRef.get("width").type() == LuaIntf::LuaTypeID::NUMBER) ? m_texturePathRef.get("width").toValue<float>() : m_texturePathInfo.width;
		m_texturePathInfo.height = m_texturePathRef.has("height") && (m_texturePathRef.get("height").type() == LuaIntf::LuaTypeID::NUMBER) ? m_texturePathRef.get("height").toValue<float>() : m_texturePathInfo.height;
		m_texturePathInfo.rotated = m_texturePathRef.has("rotated") && (m_texturePathRef.get("rotated").type() == LuaIntf::LuaTypeID::BOOLEAN) ? m_texturePathRef.get("rotated").toValue<bool>() : m_texturePathInfo.rotated;
		m_texturePathInfo.isPinMap = true;
	}
	
	m_emitterName = Get_String("m_emitterName", m_emitterName);
	m_emitterPosX = Get_Float("m_emitterPosX", m_emitterPosX);
	m_emitterPosY = Get_Float("m_emitterPosY", m_emitterPosY);
	m_emitterRot = Get_Float("m_emitterRot", m_emitterRot);
	m_killOnComplete = Get_Boolean("m_killOnComplete", m_killOnComplete);
	m_killOnDeactivate = Get_Boolean("m_killOnDeactivate", m_killOnDeactivate);
	m_duration = Get_Int("m_duration", m_duration);
	m_durationLow = Get_Int("m_durationLow", m_durationLow);
	m_useRange = Get_Boolean("m_useRange", m_useRange);
	m_durationRecal = Get_Boolean("m_durationRecal", m_durationRecal);
	m_loop = Get_Int("m_loop", m_loop);
	m_delay = Get_Int("m_delay", m_delay);
	m_delayLow = Get_Int("m_delayLow", m_delayLow);
	m_delayUseRange = Get_Boolean("m_delayUseRange", m_delayUseRange);
	m_delayFirstLoop = Get_Boolean("m_delayFirstLoop", m_delayFirstLoop);
	m_maxCount = Get_Int("m_maxCount", m_maxCount);
	m_countUseMax = Get_Boolean("m_countUseMax", m_countUseMax);
	m_subUVHori = Get_Int("m_subUVHori", m_subUVHori);
	m_subUVVerti = Get_Int("m_subUVVerti", m_subUVVerti);
	m_subUVMode = Get_Int("m_subUVMode", m_subUVMode);
	m_subUVRandomNum = Get_Int("m_subUVRandomNum", m_subUVRandomNum);
	m_clip = Get_Boolean("m_clip", m_clip);
	m_isLocalSpace = Get_Boolean("m_isLocalSpace", m_isLocalSpace);
	m_flipUV = Get_Int("m_flipUV", m_flipUV);
	m_flipTexcoordU = Get_Boolean("m_flipTexcoordU", m_flipTexcoordU);
	m_flipTexcoordV = Get_Boolean("m_flipTexcoordV", m_flipTexcoordV);
	m_randomTexU = Get_Boolean("m_randomTexU", m_randomTexU);
	m_randomTexV = Get_Boolean("m_randomTexV", m_randomTexV);
	m_brustNum = Get_Int("m_brustNum", m_brustNum);
	m_brustNumLow = Get_Int("m_brustNumLow", m_brustNumLow);
	m_brustTiming = Get_Float("m_brustTiming", m_brustTiming);
	m_brustTiming = m_brustTiming < 0 ? 0 : m_brustTiming;
	m_useBrust = Get_Boolean("m_useBrust", m_useBrust);
	m_speedSizeX = Get_Float("m_speedSizeX", m_speedSizeX);
	m_speedSizeY = Get_Float("m_speedSizeY", m_speedSizeY);
	m_speedSizeXMax = Get_Float("m_speedSizeXMax", m_speedSizeXMax);
	m_speedSizeYMax = Get_Float("m_speedSizeYMax", m_speedSizeYMax);
	m_clampAlpha = Get_Boolean("m_clampAlpha", m_clampAlpha);
	m_clampAlphaLife = Get_Boolean("m_clampAlphaLife", m_clampAlphaLife);
	m_colorScaleEmitterLife = Get_Boolean("m_colorScaleEmitterLife", m_colorScaleEmitterLife);
	m_coneDirection = Get_Float("m_coneDirection", m_coneDirection);
	m_velocityAbsolute = Get_Boolean("m_velocityAbsolute", m_velocityAbsolute);
	m_locDistriPoint = Get_Int("m_locDistriPoint", m_locDistriPoint);
	m_locDistriThreshold = Get_Float("m_locDistriThreshold", m_locDistriThreshold);
	m_worldOffsetPoint = Get_Int("m_worldOffsetPoint", m_worldOffsetPoint);
	m_worldOffsetThreshold = Get_Float("m_worldOffsetThreshold", m_worldOffsetThreshold);
	m_locEmitterName = Get_String("m_locEmitterName", m_locEmitterName);
	m_locEmitterMode = Get_Int("m_locEmitterMode", m_locEmitterMode);
	m_locEmitterCount = Get_Int("m_locEmitterCount", m_locEmitterCount);
	m_inheritSourceVelocity = Get_Boolean("m_inheritSourceVelocity", m_inheritSourceVelocity);
	m_inheritSourceRotation = Get_Boolean("m_inheritSourceRotation", m_inheritSourceRotation);
	m_inheritVelScale = Get_Float("m_inheritVelScale", m_inheritVelScale);
	m_inheritRotScale = Get_Float("m_inheritRotScale", m_inheritRotScale);
	m_locDirectEmitterName = Get_String("m_locDirectEmitterName", m_locDirectEmitterName);
	m_spherePositiveX = Get_Boolean("m_spherePositiveX", m_spherePositiveX);
	m_sphereNegativeX = Get_Boolean("m_sphereNegativeX", m_sphereNegativeX);
	m_spherePositiveY = Get_Boolean("m_spherePositiveY", m_spherePositiveY);
	m_sphereNegativeY = Get_Boolean("m_sphereNegativeY", m_sphereNegativeY);
	m_sphereSurface = Get_Boolean("m_sphereSurface", m_sphereSurface);
	m_sphereVelocity = Get_Boolean("m_sphereVelocity", m_sphereVelocity);
	m_orbitOffsetSpawn = Get_Boolean("m_orbitOffsetSpawn", m_orbitOffsetSpawn);
	m_orbitOffsetUpdate = Get_Boolean("m_orbitOffsetUpdate", m_orbitOffsetUpdate);
	m_orbitOffsetEmitterTime = Get_Boolean("m_orbitOffsetEmitterTime", m_orbitOffsetEmitterTime);
	m_orbitRotationSpawn = Get_Boolean("m_orbitRotationSpawn", m_orbitRotationSpawn);
	m_orbitRotationUpdate = Get_Boolean("m_orbitRotationUpdate", m_orbitRotationUpdate);
	m_orbitRotationEmitterTime = Get_Boolean("m_orbitRotationEmitterTime", m_orbitRotationEmitterTime);
	m_orbitRotationRateSpawn = Get_Boolean("m_orbitRotationRateSpawn", m_orbitRotationRateSpawn);
	m_orbitRotationRateUpdate = Get_Boolean("m_orbitRotationRateUpdate", m_orbitRotationRateUpdate);
	m_orbitRotationRateEmitterTime = Get_Boolean("m_orbitRotationRateEmitterTime", m_orbitRotationRateEmitterTime);

	m_strengthByDistance = Get_Boolean("m_strengthByDistance", m_strengthByDistance);
	m_affectBaseVelocity = Get_Boolean("m_affectBaseVelocity", m_affectBaseVelocity);
	m_lineAttractorPoint1X = Get_Float("m_lineAttractorPoint1X", m_lineAttractorPoint1X);
	m_lineAttractorPoint1Y = Get_Float("m_lineAttractorPoint1Y", m_lineAttractorPoint1Y);
	m_lineAttractorPoint2X = Get_Float("m_lineAttractorPoint2X", m_lineAttractorPoint2X);
	m_lineAttractorPoint2Y = Get_Float("m_lineAttractorPoint2Y", m_lineAttractorPoint2Y);
	m_killInside = Get_Boolean("m_killInside", m_killInside);
	m_killFloor = Get_Boolean("m_killFloor", m_killFloor);
	m_floorCollisionAxis = Get_Int("m_floorCollisionAxis", m_floorCollisionAxis);
	m_floorCollisionAxisPos = Get_Float("m_floorCollisionAxisPos", m_floorCollisionAxisPos);
	m_floorCollisionDelayAmount = Get_Int("m_floorCollisionDelayAmount", m_floorCollisionDelayAmount);
	m_floorCollisionCompleteOpt = Get_Int("m_floorCollisionCompleteOpt", m_floorCollisionCompleteOpt);
	m_lineCollisionPoint0X = Get_Float("m_lineCollisionPoint0X", m_lineCollisionPoint0X);
	m_lineCollisionPoint0Y = Get_Float("m_lineCollisionPoint0Y", m_lineCollisionPoint0Y);
	m_lineCollisionPoint1X = Get_Float("m_lineCollisionPoint1X", m_lineCollisionPoint1X);
	m_lineCollisionPoint1Y = Get_Float("m_lineCollisionPoint1Y", m_lineCollisionPoint1Y);
	m_lineCollisionDelayAmount = Get_Int("m_lineCollisionDelayAmount", m_lineCollisionDelayAmount);
	m_lineCollisionCompleteOpt = Get_Int("m_lineCollisionCompleteOpt", m_lineCollisionCompleteOpt);
	m_rectCollisionPosX = Get_Float("m_rectCollisionPosX", m_rectCollisionPosX);
	m_rectCollisionPosY = Get_Float("m_rectCollisionPosY", m_rectCollisionPosY);
	m_rectCollisionWidth = Get_Float("m_rectCollisionWidth", m_rectCollisionWidth);
	m_rectCollisionHeight = Get_Float("m_rectCollisionHeight", m_rectCollisionHeight);
	m_rectCollisionDelayAmount = Get_Int("m_rectCollisionDelayAmount", m_rectCollisionDelayAmount);
	m_rectCollisionCompleteOpt = Get_Int("m_rectCollisionCompleteOpt", m_rectCollisionCompleteOpt);
	m_sphereCollisionCenterX = Get_Float("m_sphereCollisionCenterX", m_sphereCollisionCenterX);
	m_sphereCollisionCenterY = Get_Float("m_sphereCollisionCenterY", m_sphereCollisionCenterY);
	m_sphereCollisionRadius = Get_Float("m_sphereCollisionRadius", m_sphereCollisionRadius);
	m_sphereCollisionDelayAmount = Get_Int("m_sphereCollisionDelayAmount", m_sphereCollisionDelayAmount);
	m_sphereCollisionCompleteOpt = Get_Int("m_sphereCollisionCompleteOpt", m_sphereCollisionCompleteOpt);

	m_velRotation = Get_Boolean("m_velRotation", m_velRotation);
	//m_tangentSpeed = emitterData["m_tangentSpeed"].IsNumber() ? emitterData["m_tangentSpeed"].GetFloat() : 0.0f;*/

	m_emission = importFloatDistri(emitterDataRef.get("m_emission"));
	m_emissionScale = importFloatDistri(emitterDataRef.get("m_emissionScale"));
	m_brustScale = importFloatDistri(emitterDataRef.get("m_brustScale"));
	m_initSize = importFloatDistri(emitterDataRef.get("m_initSize"));
	m_sizeLife = importFloatDistri(emitterDataRef.get("m_sizeLife"));
	m_sizeScale = importFloatDistri(emitterDataRef.get("m_sizeScale"));
	m_lifeTime = importFloatDistri(emitterDataRef.get("m_lifeTime"));
	m_initColor = importVectorDistri(emitterDataRef.get("m_initColor"));
	m_initAlpha = importFloatDistri(emitterDataRef.get("m_initAlpha"));
	m_colorOverLife = importVectorDistri(emitterDataRef.get("m_colorOverLife"));
	m_alphaOverLife = importFloatDistri(emitterDataRef.get("m_alphaOverLife"));
	m_colorScaleOverLife = importVectorDistri(emitterDataRef.get("m_colorScaleOverLife"));
	m_alphaScaleOverLife = importFloatDistri(emitterDataRef.get("m_alphaScaleOverLife"));
	m_initVelocity = importVectorDistri(emitterDataRef.get("m_initVelocity"));
	m_initVelocityRadial = importFloatDistri(emitterDataRef.get("m_initVelocityRadial"));
	m_velOverLife = importVectorDistri(emitterDataRef.get("m_velOverLife"));
	m_coneVelocityAngle = importFloatDistri(emitterDataRef.get("m_coneVelocityAngle"));
	m_coneVelocityVelocity = importFloatDistri(emitterDataRef.get("m_coneVelocityVelocity"));
	m_initAcceleration = importVectorDistri(emitterDataRef.get("m_initAcceleration"));
	m_drag = importFloatDistri(emitterDataRef.get("m_drag"));
	m_accelOverLife = importVectorDistri(emitterDataRef.get("m_accelOverLife"));
	m_initRotate = importFloatDistri(emitterDataRef.get("m_initRotate"));
	m_rotateOverLife = importFloatDistri(emitterDataRef.get("m_rotateOverLife"));
	m_initRotRate = importFloatDistri(emitterDataRef.get("m_initRotRate"));
	m_rotRateLife = importFloatDistri(emitterDataRef.get("m_rotRateLife"));
	m_initLocation = importVectorDistri(emitterDataRef.get("m_initLocation"));
	m_worldOffset = importVectorDistri(emitterDataRef.get("m_worldOffset"));
	m_directLocation = importVectorDistri(emitterDataRef.get("m_directLocation"));
	m_dirLocationOffset = importVectorDistri(emitterDataRef.get("m_dirLocationOffset"));
	m_dirLocationScale = importVectorDistri(emitterDataRef.get("m_dirLocationScale"));
	m_sphereRadius = importFloatDistri(emitterDataRef.get("m_sphereRadius"));
	m_sphereVelocityScale = importFloatDistri(emitterDataRef.get("m_sphereVelocityScale"));
	m_sphereOffset = importVectorDistri(emitterDataRef.get("m_sphereOffset"));
	m_triangleHeight = importFloatDistri(emitterDataRef.get("m_triangleHeight"));
	m_triangleAngle = importFloatDistri(emitterDataRef.get("m_triangleAngle"));
	m_triangleOffset = importVectorDistri(emitterDataRef.get("m_triangleOffset"));
	m_subUVIndex = importFloatDistri(emitterDataRef.get("m_subUVIndex"));
	m_orbitOffset = importVectorDistri(emitterDataRef.get("m_orbitOffset"));
	m_orbitRotation = importVectorDistri(emitterDataRef.get("m_orbitRotation"));
	m_orbitRotationRate = importVectorDistri(emitterDataRef.get("m_orbitRotationRate"));
	m_pointAttractorPosition = importVectorDistri(emitterDataRef.get("m_pointAttractorPosition"));
	m_pointAttractorRange = importFloatDistri(emitterDataRef.get("m_pointAttractorRange"));
	m_pointAttractorStrength = importFloatDistri(emitterDataRef.get("m_pointAttractorStrength"));
	m_lineAttractorRange = importFloatDistri(emitterDataRef.get("m_lineAttractorRange"));
	m_lineAttractorStrength = importFloatDistri(emitterDataRef.get("m_lineAttractorStrength"));
	m_killBoxTopLeft = importVectorDistri(emitterDataRef.get("m_killBoxTopLeft"));
	m_killBoxLowRight = importVectorDistri(emitterDataRef.get("m_killBoxLowRight"));
	m_killHeight = importFloatDistri(emitterDataRef.get("m_killHeight"));
	m_floorDampVel = importVectorDistri(emitterDataRef.get("m_floorDampVel"));
	m_floorDampRot = importFloatDistri(emitterDataRef.get("m_floorDampRot"));
	m_floorMaxCollision = importFloatDistri(emitterDataRef.get("m_floorMaxCollision"));
	m_lineDampVel = importVectorDistri(emitterDataRef.get("m_lineDampVel"));
	m_lineDampRot = importFloatDistri(emitterDataRef.get("m_lineDampRot"));
	m_lineMaxCollision = importFloatDistri(emitterDataRef.get("m_lineMaxCollision"));
	m_rectDampVel = importVectorDistri(emitterDataRef.get("m_rectDampVel"));
	m_rectDampRot = importFloatDistri(emitterDataRef.get("m_rectDampRot"));
	m_rectMaxCollision = importFloatDistri(emitterDataRef.get("m_rectMaxCollision"));
	m_sphereDampVel = importVectorDistri(emitterDataRef.get("m_sphereDampVel"));
	m_sphereDampRot = importFloatDistri(emitterDataRef.get("m_sphereDampRot"));
	m_sphereMaxCollision = importFloatDistri(emitterDataRef.get("m_sphereMaxCollision"));

	m_particleEvent = new ParticleEventData();

	if (emitterDataRef.has("m_genEvent"))
	{
		auto genEventRef = emitterDataRef.get("m_genEvent");

		for (int i = 1; i <= genEventRef.len(); i++)
		{
			auto eventRef = genEventRef.get(i);

			ParticleEventGeneratorData* generator = new ParticleEventGeneratorData();
			generator->m_name = eventRef.get("name").toValue<std::string>();
			generator->m_frequency = eventRef.get("frequency").toValue<int>();
			generator->m_eventType = eventRef.get("eventType").toValue<int>();

			m_particleEvent->m_generatorList.push_back(generator);
		}
	}

	//std::cout会导致android link报错找不到方法
	if (emitterDataRef.has("m_recevEvent"))
	{
		auto recevEventRef = emitterDataRef.get("m_recevEvent");

		for (int i = 1; i <= recevEventRef.len(); i++)
		{
			auto eventRef = recevEventRef.get(i);

			ParticleEventReceiverData* recevier = new ParticleEventReceiverData();
			recevier->m_name = eventRef.get("name").toValue<std::string>();
			recevier->m_eventType = eventRef.get("eventType").toValue<int>();
			recevier->m_useParticleTime = eventRef.get("useParticleTime").toValue<bool>();
			recevier->m_usePsysLocation = eventRef.get("usePsysLocation").toValue<bool>();
			recevier->m_inheritVal = eventRef.get("inheritVal").toValue<bool>();
			recevier->m_spawnCountDistriData = importFloatDistri(eventRef.get("spawnCount"));
			recevier->m_inheritScaleDistriData = importVectorDistri(eventRef.get("inheritVelScale"));

			m_particleEvent->m_receiverList.push_back(recevier);
		}
	}
}


EmitterData::~EmitterData()
{
}

FloatDistriData * EmitterData::importFloatDistri(LuaIntf::LuaRef floatDistriData)
{
	FloatDistriData *fDis = new FloatDistriData(floatDistriData.get(1).toValue<std::string>(),
		floatDistriData.get(2).toValue<int>(),
		0,
		0,
		0,
		floatDistriData.get(3).toValue<int>(),
		floatDistriData.get(6).toValue<int>(),
		floatDistriData.get(4).toValue<bool>(),
		floatDistriData.get(5).toValue<bool>()
	);

	if (fDis->m_type == CONSTANT)
		fDis->m_cons = floatDistriData.get(7).toValue<float>();
	else if (fDis->m_type == UNIFORM)
	{
		fDis->m_min = floatDistriData.get(7).toValue<float>();
		fDis->m_max = floatDistriData.get(8).toValue<float>();
	}
	else if (fDis->m_type == CONSCURVE)
	{
		auto curveListRef = floatDistriData.get(7);

		if (!curveListRef.isTable())
			return fDis;

		for (int i = 1; i <= curveListRef.len(); i++)
		{
			auto curveRef = curveListRef.get(i);

			if (!curveRef.isTable())
				return fDis;

			FloatConstantCurveData* curvedata = new FloatConstantCurveData(
				curveRef.get(1).toValue<int>(),
				curveRef.get(2).toValue<float>(),
				curveRef.get(3).toValue<float>(),
				curveRef.get(4).toValue<float>(),
				curveRef.get(5).toValue<float>(),
				curveRef.get(6).toValue<int>()
			);

			fDis->m_curveList.push_back(curvedata);
		}
	}
	else if (fDis->m_type == UNIFORMCURVE)
	{
		auto curveListRef = floatDistriData.get(7);

		if (!curveListRef.isTable())
			return fDis;

		for (int i = 1; i <= curveListRef.len(); i++)
		{
			auto curveRef = curveListRef.get(i);

			if (!curveRef.isTable())
				return fDis;

			FloatUniformCurveData* curvedata = new FloatUniformCurveData(
				curveRef.get(1).toValue<int>(),
				curveRef.get(2).toValue<float>(),
				curveRef.get(3).toValue<float>(),
				curveRef.get(4).toValue<float>(),
				curveRef.get(5).toValue<float>(),
				curveRef.get(6).toValue<float>(),
				curveRef.get(7).toValue<float>(),
				curveRef.get(8).toValue<float>(),
				curveRef.get(9).toValue<int>()
			);

			fDis->m_uniformCurveList.push_back(curvedata);
		}
	}

	if (fDis->m_baked)
	{
		//to do
	}

	return fDis;
}

VectorDistriData * EmitterData::importVectorDistri(LuaIntf::LuaRef vectorDistriData)
{
	VectorDistriData *vDis = new VectorDistriData(vectorDistriData.get(1).toValue<std::string>(),
		vectorDistriData.get(2).toValue<int>(),
		vec3(),
		vec3(),
		vec3(),
		vectorDistriData.get(3).toValue<int>(),
		vectorDistriData.get(6).toValue<int>(),
		vectorDistriData.get(4).toValue<bool>(),
		vectorDistriData.get(5).toValue<bool>()
	);

	if (vDis->m_type == CONSTANT)
	{
		auto vecRef = vectorDistriData.get(7);
		vDis->m_cons = vec3(vecRef.get(1).toValue<float>(), vecRef.get(2).toValue<float>(), vecRef.get(3).toValue<float>());
	}
	else if (vDis->m_type == UNIFORM)
	{
		auto vecRefMin = vectorDistriData.get(7);
		auto vecRefMax = vectorDistriData.get(8);
		vDis->m_min = vec3(vecRefMin.get(1).toValue<float>(), vecRefMin.get(2).toValue<float>(), vecRefMin.get(3).toValue<float>());
		vDis->m_max = vec3(vecRefMax.get(1).toValue<float>(), vecRefMax.get(2).toValue<float>(), vecRefMax.get(3).toValue<float>());
	}
	else if (vDis->m_type == CONSCURVE)
	{
		auto curveListRef = vectorDistriData.get(7);

		if (!curveListRef.isTable())
			return vDis;

		for (int i = 1; i <= curveListRef.len(); i++)
		{
			auto curveRef = curveListRef.get(i);
			if (!curveRef.isTable())
				return vDis;
			
			auto outValRef = curveRef.get(3);
			auto arriveTanRef = curveRef.get(4);
			auto leaveTanRef = curveRef.get(5);

			VectorConstantCurveData* curvedata = new VectorConstantCurveData(
				curveRef.get(1).toValue<int>(),
				curveRef.get(2).toValue<float>(),
				vec3(outValRef.get(1).toValue<float>(), outValRef.get(2).toValue<float>(), outValRef.get(3).toValue<float>()),
				vec3(arriveTanRef.get(1).toValue<float>(), arriveTanRef.get(2).toValue<float>(), arriveTanRef.get(3).toValue<float>()),
				vec3(leaveTanRef.get(1).toValue<float>(), leaveTanRef.get(2).toValue<float>(), leaveTanRef.get(3).toValue<float>()),
				curveRef.get(6).toValue<int>()
			);

			vDis->m_curveList.push_back(curvedata);
		}
	}
	else if (vDis->m_type == UNIFORMCURVE)
	{
		auto curveListRef = vectorDistriData.get(7);

		if (!curveListRef.isTable())
			return vDis;

		for (int i = 1; i <= curveListRef.len(); i++)
		{
			auto curveRef = curveListRef.get(i);
			if (!curveRef.isTable())
				return vDis;

			auto outValRef1 = curveRef.get(3);
			auto outValRef2 = curveRef.get(4);
			auto arriveTanRef1 = curveRef.get(5);
			auto arriveTanRef2 = curveRef.get(6);
			auto leaveTanRef1 = curveRef.get(7);
			auto leaveTanRef2 = curveRef.get(8);

			VectorUniformCurveData* curvedata = new VectorUniformCurveData(
				curveRef.get(1).toValue<int>(),
				curveRef.get(2).toValue<float>(),
				vec3(outValRef1.get(1).toValue<float>(), outValRef1.get(2).toValue<float>(), outValRef1.get(3).toValue<float>()),
				vec3(outValRef2.get(1).toValue<float>(), outValRef2.get(2).toValue<float>(), outValRef2.get(3).toValue<float>()),
				vec3(arriveTanRef1.get(1).toValue<float>(), arriveTanRef1.get(2).toValue<float>(), arriveTanRef1.get(3).toValue<float>()),
				vec3(arriveTanRef2.get(1).toValue<float>(), arriveTanRef2.get(2).toValue<float>(), arriveTanRef2.get(3).toValue<float>()),
				vec3(leaveTanRef1.get(1).toValue<float>(), leaveTanRef1.get(2).toValue<float>(), leaveTanRef1.get(3).toValue<float>()),
				vec3(leaveTanRef2.get(1).toValue<float>(), leaveTanRef2.get(2).toValue<float>(), leaveTanRef2.get(3).toValue<float>()),
				curveRef.get(9).toValue<int>()
			);

			vDis->m_uniformCurveList.push_back(curvedata);
		}
	}

	if (vDis->m_baked)
	{
		//todo
	}

	return vDis;
}

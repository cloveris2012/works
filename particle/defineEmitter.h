//
//  defineEmitter.h
//  particle
//
//  Created by 衡黎 on 2021/4/29.
//

#ifndef defineEmitter_h
#define defineEmitter_h


#define ExportEmitter(struct_name,emitter_name)\
.beginClass<Emittter<struct_name>>(emitter_name)\
.addConstructor(LUA_ARGS())\
.addFunction("loadEmitterData", &Emittter<struct_name>::loadEmitterData, LUA_ARGS(std::string))\
.addFunction("loadEmitterDataFromId", &Emittter<struct_name>::loadEmitterDataFromId, LUA_ARGS(std::string))\
.addFunction("update", &Emittter<struct_name>::update, LUA_ARGS(int64_t))\
.addFunction("getAttributeFormat", &Emittter<struct_name>::getAttributeFormat)\
.addFunction("getAttriStripeSize", &Emittter<struct_name>::getAttriStripeSize)\
.addFunction("getParticleCount", &Emittter<struct_name>::getParticleCount)\
.addFunction("getMaxParticleCount", &Emittter<struct_name>::getMaxParticleCount)\
.addFunction("setTextureSize", &Emittter<struct_name>::setTextureSize, LUA_ARGS(float,float))\
.addFunction("setCanvasSize", &Emittter<struct_name>::setCanvasSize,LUA_ARGS(float,float))\
.addFunction("getShaderAttribute", [](Emittter<struct_name>* emitter, lua_State* L) {\
lua_pushlightuserdata(L, (void*)(emitter->getShaderAttribute()));\
return 1;\
})\
.addFunction("getShaderLocAttribute", &Emittter<struct_name>::getShaderLocAttribute)\
.addFunction("setLocEmitterAttribute", &Emittter<struct_name>::setLocEmitterAttribute, LUA_ARGS(std::string))\
.addFunction("setDirectEmitterAttribute", &Emittter<struct_name>::setDirectEmitterAttribute, LUA_ARGS(std::string))\
.addFunction("updateEmitterWorldPos", &Emittter<struct_name>::updateEmitterWorldPos,LUA_ARGS(float,float))\
.addFunction("updateEmitterCurrentMatrix", &Emittter<struct_name>::updateEmitterCurrentMatrix)\
.addFunction("updateEmitterCurrentViewScale", &Emittter<struct_name>::updateEmitterCurrentViewScale)\
.addFunction("clear", &Emittter<struct_name>::clear)\
.addFunction("importFloatDistriByStr", &Emittter<struct_name>::importFloatDistriByStr)\
.addFunction("importVectorDistriByStr", &Emittter<struct_name>::importVectorDistriByStr)\
.addFunction("addParticle", &Emittter<struct_name>::addParticle)\
.addFunction("applyParticleEvent", &Emittter<struct_name>::applyParticleEvent)\
.addFunction("getParticleEventData", &Emittter<struct_name>::getParticleEventData)\
.addFunction("getFrameData", &Emittter<struct_name>::getFrameData)\
.addVariable("m_particleNum",&Emittter<struct_name>::m_particleNum, false)\
.addVariable("m_emitterName",&Emittter<struct_name>::m_emitterName, false)\
.addVariable("m_emitterRunningState",&Emittter<struct_name>::m_emitterRunningState, false)\
.addVariable("m_emitterPosX",&Emittter<struct_name>::m_emitterPosX )\
.addVariable("m_emitterPosY",&Emittter<struct_name>::m_emitterPosY )\
.addVariable("m_emitterRot",&Emittter<struct_name>::m_emitterRot )\
.addVariable("m_killOnComplete",&Emittter<struct_name>::m_killOnComplete )\
.addVariable("m_killOnDeactivate",&Emittter<struct_name>::m_killOnDeactivate )\
.addVariable("m_duration",&Emittter<struct_name>::m_duration )\
.addVariable("m_durationLow",&Emittter<struct_name>::m_durationLow )\
.addVariable("m_useRange",&Emittter<struct_name>::m_useRange )\
.addVariable("m_durationRecal",&Emittter<struct_name>::m_durationRecal )\
.addVariable("m_loop",&Emittter<struct_name>::m_loop )\
.addVariable("m_loopCount",&Emittter<struct_name>::m_loopCount )\
.addVariable("m_delay",&Emittter<struct_name>::m_delay )\
.addVariable("m_delayLow",&Emittter<struct_name>::m_delayLow )\
.addVariable("m_delayUseRange",&Emittter<struct_name>::m_delayUseRange )\
.addVariable("m_delayFirstLoop",&Emittter<struct_name>::m_delayFirstLoop )\
.addVariable("m_subUVMode",&Emittter<struct_name>::m_subUVMode )\
.addVariable("m_subUVHori",&Emittter<struct_name>::m_subUVHori )\
.addVariable("m_subUVVerti",&Emittter<struct_name>::m_subUVVerti )\
.addVariable("m_subUVRandomNum",&Emittter<struct_name>::m_subUVRandomNum )\
.addVariable("m_clip",&Emittter<struct_name>::m_clip )\
.addVariable("m_isLocalSpace",&Emittter<struct_name>::m_isLocalSpace )\
.addVariable("m_countUseMax",&Emittter<struct_name>::m_countUseMax )\
.addVariable("m_maxCount",&Emittter<struct_name>::m_maxCount )\
.addVariable("m_flipUV",&Emittter<struct_name>::m_flipUV )\
.addVariable("m_brustNum",&Emittter<struct_name>::m_brustNum )\
.addVariable("m_brustNumLow",&Emittter<struct_name>::m_brustNumLow )\
.addVariable("m_brustTiming",&Emittter<struct_name>::m_brustTiming )\
.addVariable("m_useBrust",&Emittter<struct_name>::m_useBrust )\
.addVariable("m_speedSizeX",&Emittter<struct_name>::m_speedSizeX )\
.addVariable("m_speedSizeY",&Emittter<struct_name>::m_speedSizeY )\
.addVariable("m_speedSizeXMax",&Emittter<struct_name>::m_speedSizeXMax )\
.addVariable("m_speedSizeYMax",&Emittter<struct_name>::m_speedSizeYMax )\
.addVariable("m_clampAlpha",&Emittter<struct_name>::m_clampAlpha )\
.addVariable("m_clampAlphaLife",&Emittter<struct_name>::m_clampAlphaLife )\
.addVariable("m_colorScaleEmitterLife",&Emittter<struct_name>::m_colorScaleEmitterLife )\
.addVariable("m_coneDirection",&Emittter<struct_name>::m_coneDirection )\
.addVariable("m_velocityAbsolute",&Emittter<struct_name>::m_velocityAbsolute )\
.addVariable("m_locDistriPoint",&Emittter<struct_name>::m_locDistriPoint )\
.addVariable("m_locDistriThreshold",&Emittter<struct_name>::m_locDistriThreshold )\
.addVariable("m_worldOffsetPoint",&Emittter<struct_name>::m_worldOffsetPoint )\
.addVariable("m_worldOffsetThreshold",&Emittter<struct_name>::m_worldOffsetThreshold )\
.addVariable("m_locEmitterName",&Emittter<struct_name>::m_locEmitterName )\
.addVariable("m_locEmitterMode",&Emittter<struct_name>::m_locEmitterMode )\
.addVariable("m_locEmitterCount",&Emittter<struct_name>::m_locEmitterCount )\
.addVariable("m_inheritSourceVelocity",&Emittter<struct_name>::m_inheritSourceVelocity )\
.addVariable("m_inheritSourceRotation",&Emittter<struct_name>::m_inheritSourceRotation )\
.addVariable("m_inheritVelScale",&Emittter<struct_name>::m_inheritVelScale )\
.addVariable("m_inheritRotScale",&Emittter<struct_name>::m_inheritRotScale )\
.addVariable("m_locDirectEmitterName",&Emittter<struct_name>::m_locDirectEmitterName )\
.addVariable("m_spherePositiveX",&Emittter<struct_name>::m_spherePositiveX )\
.addVariable("m_sphereNegativeX",&Emittter<struct_name>::m_sphereNegativeX )\
.addVariable("m_spherePositiveY",&Emittter<struct_name>::m_spherePositiveY )\
.addVariable("m_sphereNegativeY",&Emittter<struct_name>::m_sphereNegativeY )\
.addVariable("m_sphereSurface",&Emittter<struct_name>::m_sphereSurface )\
.addVariable("m_sphereVelocity",&Emittter<struct_name>::m_sphereVelocity )\
.addVariable("m_orbitOffsetSpawn",&Emittter<struct_name>::m_orbitOffsetSpawn )\
.addVariable("m_orbitOffsetUpdate",&Emittter<struct_name>::m_orbitOffsetUpdate )\
.addVariable("m_orbitOffsetEmitterTime",&Emittter<struct_name>::m_orbitOffsetEmitterTime )\
.addVariable("m_orbitRotationSpawn",&Emittter<struct_name>::m_orbitRotationSpawn )\
.addVariable("m_orbitRotationUpdate",&Emittter<struct_name>::m_orbitRotationUpdate )\
.addVariable("m_orbitRotationEmitterTime",&Emittter<struct_name>::m_orbitRotationEmitterTime )\
.addVariable("m_orbitRotationRateSpawn",&Emittter<struct_name>::m_orbitRotationRateSpawn )\
.addVariable("m_orbitRotationRateUpdate",&Emittter<struct_name>::m_orbitRotationRateUpdate )\
.addVariable("m_orbitRotationRateEmitterTime",&Emittter<struct_name>::m_orbitRotationRateEmitterTime )\
.addVariable("m_strengthByDistance",&Emittter<struct_name>::m_strengthByDistance )\
.addVariable("m_affectBaseVelocity",&Emittter<struct_name>::m_affectBaseVelocity )\
.addVariable("m_lineAttractorPoint1X",&Emittter<struct_name>::m_lineAttractorPoint1X )\
.addVariable("m_lineAttractorPoint1Y",&Emittter<struct_name>::m_lineAttractorPoint1Y )\
.addVariable("m_lineAttractorPoint2X",&Emittter<struct_name>::m_lineAttractorPoint2X )\
.addVariable("m_lineAttractorPoint2Y",&Emittter<struct_name>::m_lineAttractorPoint2Y )\
.addVariable("m_killInside",&Emittter<struct_name>::m_killInside )\
.addVariable("m_killFloor",&Emittter<struct_name>::m_killFloor )\
.addVariable("m_floorCollisionAxis",&Emittter<struct_name>::m_floorCollisionAxis )\
.addVariable("m_floorCollisionDelayAmount",&Emittter<struct_name>::m_floorCollisionDelayAmount )\
.addVariable("m_floorCollisionAxisPos",&Emittter<struct_name>::m_floorCollisionAxisPos )\
.addVariable("m_floorCollisionCompleteOpt",&Emittter<struct_name>::m_floorCollisionCompleteOpt )\
.addVariable("m_lineCollisionPoint0X",&Emittter<struct_name>::m_lineCollisionPoint0X )\
.addVariable("m_lineCollisionPoint0Y",&Emittter<struct_name>::m_lineCollisionPoint0Y )\
.addVariable("m_lineCollisionPoint1X",&Emittter<struct_name>::m_lineCollisionPoint1X )\
.addVariable("m_lineCollisionPoint1Y",&Emittter<struct_name>::m_lineCollisionPoint1Y )\
.addVariable("m_lineCollisionDelayAmount",&Emittter<struct_name>::m_lineCollisionDelayAmount )\
.addVariable("m_lineCollisionCompleteOpt",&Emittter<struct_name>::m_lineCollisionCompleteOpt )\
.addVariable("m_rectCollisionPosX",&Emittter<struct_name>::m_rectCollisionPosX )\
.addVariable("m_rectCollisionPosY",&Emittter<struct_name>::m_rectCollisionPosY )\
.addVariable("m_rectCollisionWidth",&Emittter<struct_name>::m_rectCollisionWidth )\
.addVariable("m_rectCollisionHeight",&Emittter<struct_name>::m_rectCollisionHeight )\
.addVariable("m_rectCollisionDelayAmount",&Emittter<struct_name>::m_rectCollisionDelayAmount )\
.addVariable("m_rectCollisionCompleteOpt",&Emittter<struct_name>::m_rectCollisionCompleteOpt )\
.addVariable("m_sphereCollisionCenterX",&Emittter<struct_name>::m_sphereCollisionCenterX )\
.addVariable("m_sphereCollisionCenterY",&Emittter<struct_name>::m_sphereCollisionCenterY )\
.addVariable("m_sphereCollisionRadius",&Emittter<struct_name>::m_sphereCollisionRadius )\
.addVariable("m_sphereCollisionDelayAmount",&Emittter<struct_name>::m_sphereCollisionDelayAmount )\
.addVariable("m_sphereCollisionCompleteOpt",&Emittter<struct_name>::m_sphereCollisionCompleteOpt )\
.addVariableRef("m_emission",&Emittter<struct_name>::m_emission)\
.addVariableRef("m_emissionScale",&Emittter<struct_name>::m_emissionScale)\
.addVariableRef("m_brustScale",&Emittter<struct_name>::m_brustScale)\
.addVariableRef("m_initSize",&Emittter<struct_name>::m_initSize)\
.addVariableRef("m_sizeLife",&Emittter<struct_name>::m_sizeLife)\
.addVariableRef("m_sizeScale",&Emittter<struct_name>::m_sizeScale)\
.addVariableRef("m_lifeTime",&Emittter<struct_name>::m_lifeTime)\
.addVariableRef("m_initColor",&Emittter<struct_name>::m_initColor)\
.addVariableRef("m_initAlpha",&Emittter<struct_name>::m_initAlpha)\
.addVariableRef("m_colorOverLife",&Emittter<struct_name>::m_colorOverLife)\
.addVariableRef("m_alphaOverLife",&Emittter<struct_name>::m_alphaOverLife)\
.addVariableRef("m_colorScaleOverLife",&Emittter<struct_name>::m_colorScaleOverLife)\
.addVariableRef("m_alphaScaleOverLife",&Emittter<struct_name>::m_alphaScaleOverLife)\
.addVariableRef("m_initVelocity",&Emittter<struct_name>::m_initVelocity)\
.addVariableRef("m_initVelocityRadial",&Emittter<struct_name>::m_initVelocityRadial)\
.addVariableRef("m_velOverLife",&Emittter<struct_name>::m_velOverLife)\
.addVariableRef("m_coneVelocityAngle",&Emittter<struct_name>::m_coneVelocityAngle)\
.addVariableRef("m_coneVelocityVelocity",&Emittter<struct_name>::m_coneVelocityVelocity)\
.addVariableRef("m_initAcceleration",&Emittter<struct_name>::m_initAcceleration)\
.addVariableRef("m_drag",&Emittter<struct_name>::m_drag)\
.addVariableRef("m_accelOverLife",&Emittter<struct_name>::m_accelOverLife)\
.addVariableRef("m_initRotate",&Emittter<struct_name>::m_initRotate)\
.addVariableRef("m_rotateOverLife",&Emittter<struct_name>::m_rotateOverLife)\
.addVariableRef("m_initRotRate",&Emittter<struct_name>::m_initRotRate)\
.addVariableRef("m_rotRateLife",&Emittter<struct_name>::m_rotRateLife)\
.addVariableRef("m_initLocation",&Emittter<struct_name>::m_initLocation)\
.addVariableRef("m_worldOffset",&Emittter<struct_name>::m_worldOffset)\
.addVariableRef("m_directLocation",&Emittter<struct_name>::m_directLocation)\
.addVariableRef("m_dirLocationOffset",&Emittter<struct_name>::m_dirLocationOffset)\
.addVariableRef("m_dirLocationScale",&Emittter<struct_name>::m_dirLocationScale)\
.addVariableRef("m_sphereRadius",&Emittter<struct_name>::m_sphereRadius)\
.addVariableRef("m_sphereVelocityScale",&Emittter<struct_name>::m_sphereVelocityScale)\
.addVariableRef("m_sphereOffset",&Emittter<struct_name>::m_sphereOffset)\
.addVariableRef("m_triangleHeight",&Emittter<struct_name>::m_triangleHeight)\
.addVariableRef("m_triangleAngle",&Emittter<struct_name>::m_triangleAngle)\
.addVariableRef("m_triangleOffset",&Emittter<struct_name>::m_triangleOffset)\
.addVariableRef("m_subUVIndex",&Emittter<struct_name>::m_subUVIndex)\
.addVariableRef("m_orbitOffset",&Emittter<struct_name>::m_orbitOffset)\
.addVariableRef("m_orbitRotation",&Emittter<struct_name>::m_orbitRotation)\
.addVariableRef("m_orbitRotationRate",&Emittter<struct_name>::m_orbitRotationRate)\
.addVariableRef("m_pointAttractorPosition",&Emittter<struct_name>::m_pointAttractorPosition)\
.addVariableRef("m_pointAttractorRange",&Emittter<struct_name>::m_pointAttractorRange)\
.addVariableRef("m_pointAttractorStrength",&Emittter<struct_name>::m_pointAttractorStrength)\
.addVariableRef("m_lineAttractorRange",&Emittter<struct_name>::m_lineAttractorRange)\
.addVariableRef("m_lineAttractorStrength",&Emittter<struct_name>::m_lineAttractorStrength)\
.addVariableRef("m_killBoxTopLeft",&Emittter<struct_name>::m_killBoxTopLeft)\
.addVariableRef("m_killBoxLowRight",&Emittter<struct_name>::m_killBoxLowRight)\
.addVariableRef("m_killHeight",&Emittter<struct_name>::m_killHeight)\
.addVariableRef("m_floorDampVel",&Emittter<struct_name>::m_floorDampVel)\
.addVariableRef("m_floorDampRot",&Emittter<struct_name>::m_floorDampRot)\
.addVariableRef("m_floorMaxCollision",&Emittter<struct_name>::m_floorMaxCollision)\
.addVariableRef("m_lineDampVel",&Emittter<struct_name>::m_lineDampVel)\
.addVariableRef("m_lineDampRot",&Emittter<struct_name>::m_lineDampRot)\
.addVariableRef("m_lineMaxCollision",&Emittter<struct_name>::m_lineMaxCollision)\
.addVariableRef("m_rectDampVel",&Emittter<struct_name>::m_rectDampVel)\
.addVariableRef("m_rectDampRot",&Emittter<struct_name>::m_rectDampRot)\
.addVariableRef("m_rectMaxCollision",&Emittter<struct_name>::m_rectMaxCollision)\
.addVariableRef("m_sphereDampVel",&Emittter<struct_name>::m_sphereDampVel)\
.addVariableRef("m_sphereDampRot",&Emittter<struct_name>::m_sphereDampRot)\
.addVariableRef("m_sphereMaxCollision",&Emittter<struct_name>::m_sphereMaxCollision)\
.endClass()\
.beginClass<FloatDistri>("FloatDistri")\
.addConstructor(LUA_SP(std::shared_ptr<FloatDistri>),LUA_ARGS())\
.endClass()\
.beginClass<VectorDistri>("VectorDistri")\
.addConstructor(LUA_SP(std::shared_ptr<VectorDistri>),LUA_ARGS())\
.endClass()\

#endif /* defineEmitter_h */

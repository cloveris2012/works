#include "capi/capi.h"
#include "lua/include.h"
#include "LuaIntf/LuaIntf.h"

#include "common/skel.h"
#include "common/SkelString.h"
#include <iostream>
#include "wrapper/SkeletonWrapper.h"
#include "wrapper/AnimationStateWrapper.h"
#include "wrapper/data/BoneDataWrapper.h"
#include "wrapper/data/EventDataWrapper.h"
#include "wrapper/data/SkeletonDataWrapper.h"
#include "wrapper/data/IkConstraintDataWrapper.h"
#include "wrapper/data/TransformConstraintDataWrapper.h"
#include "wrapper/data/PathConstraintDataWrapper.h"
#include "utils/SkeletonLoader.h"
#include "utils/SkeletonObjectCreator.h"
#include "utils/SkeletonWrapperCreator.h"

#include "wrapper/SlotWrapper.h"
#include "wrapper/BoneWrapper.h"
#include "wrapper/RegionAttachmentWrapper.h"
#include "wrapper/MeshAttachmentWrapper.h"
#include "wrapper/SkinWrapper.h"

#include "wrapper/animations/timelines/AttachmentTimelineWrapper.h"
#include "wrapper/animations/timelines/ColorTimelineWrapper.h"
#include "wrapper/animations/timelines/DeformTimelineWrapper.h"
#include "wrapper/animations/timelines/DrawOrderTimelineWrapper.h"
#include "wrapper/animations/timelines/EventTimelineWrapper.h"
#include "wrapper/animations/timelines/IkConstraintTimelineWrapper.h"
#include "wrapper/animations/timelines/PathConstraintMixTimelineWrapper.h"
#include "wrapper/animations/timelines/PathConstraintPositionTimelineWrapper.h"
#include "wrapper/animations/timelines/PathConstraintSpacingTimelineWrapper.h"
#include "wrapper/animations/timelines/RotateTimelineWrapper.h"
#include "wrapper/animations/timelines/ScaleTimelineWrapper.h"
#include "wrapper/animations/timelines/ShearTimelineWrapper.h"
#include "wrapper/animations/timelines/TransformConstraintTimelineWrapper.h"
#include "wrapper/animations/timelines/TranslateTimelineWrapper.h"
#include "wrapper/animations/timelines/TwoColorTimelineWrapper.h"

#include "EntityCreator.h"
#include "AnimationCreator.h"

using namespace skel;
using namespace LuaIntf;

//namespace LuaIntf
//{
//	LUA_USING_SHARED_PTR_TYPE(std::shared_ptr)
//}

static void register_lua_functions(lua_State* L) {
	
	LuaIntf::LuaRef mod = LuaIntf::LuaRef::createTable(L);

	auto binding = LuaIntf::LuaBinding(mod);
	
	auto skeletonLoader_ = binding.beginClass<SkeletonLoader>("SkeletonLoader");
	skeletonLoader_.addStaticFunction("loadSkeletonData", &SkeletonLoader::loadSkeletonData);
	skeletonLoader_.addStaticFunction("loadSkeletonLiteData", &SkeletonLoader::loadSkeletonLiteData);
	skeletonLoader_.addStaticFunction("cloneSkeletonData", &SkeletonLoader::cloneSkeletonData);
	skeletonLoader_.addStaticFunction("loadSkeletonWrapper", &SkeletonLoader::loadSkeletonWrapper);
	skeletonLoader_.addStaticFunction("loadSkeletonWrapperCache", &SkeletonLoader::loadSkeletonWrapperCache);
	skeletonLoader_.addStaticFunction("loadAnimationState", &SkeletonLoader::loadAnimationState);
	skeletonLoader_.addStaticFunction("deleteSkeleton", &SkeletonLoader::deleteSkeleton);
	//skeletonLoader_.addStaticFunction("removeStatePair", &SkeletonLoader::removeStatePair);
	skeletonLoader_.addStaticFunction("getSkeleDataCacheSize", &SkeletonLoader::getSkeleDataCacheSize);
	


	auto skeleton_ = binding.beginClass<SkeletonExtend>("Skeleton");
	skeleton_.addFunction("computeDrawData", &SkeletonExtend::computeDrawData);
	skeleton_.addFunction("setToSetupPose", &SkeletonExtend::setToSetupPose);
	skeleton_.addFunction("getData", &SkeletonExtend::getData);

	skeleton_.addVariable("gpuInstance", &SkeletonExtend::gpuInstance, true);
	skeleton_.addVariable("width", &SkeletonExtend::width, false);
	skeleton_.addVariable("height", &SkeletonExtend::height, false);
	skeleton_.addVariable("x", &SkeletonExtend::x, false);
	skeleton_.addVariable("y", &SkeletonExtend::y, false);
	skeleton_.addVariable("id", &SkeletonExtend::id, false);

	skeleton_.addFunction("getMatrices", &SkeletonExtend::getMatricesInfo);
	skeleton_.addFunction("getAnimationsInfo", &SkeletonExtend::getAnimationsInfo);
	skeleton_.addFunction("updateWorldTransform", &SkeletonExtend::updateWorldTransform);
	skeleton_.addFunction("setAttachmentLua", &SkeletonExtend::setAttachmentLua);
	skeleton_.addFunction("findBoneLua", &SkeletonExtend::findBoneLua);
	skeleton_.addFunction("getAttachmentLua", &SkeletonExtend::getAttachmentLua);
	skeleton_.addFunction("testCustomData", &SkeletonExtend::testCustomData);
	skeleton_.addFunction("setSkinByName", &SkeletonExtend::setSkinByName);
	skeleton_.addFunction("setSkinBySkin", &SkeletonExtend::setSkinBySkin);
	skeleton_.addFunction("getSkeletonId", &SkeletonExtend::getSkeletonId);
	skeleton_.addFunction("getBoneInfo", &SkeletonExtend::getBoneInfo);
	skeleton_.addFunction("getAttachmentAndSlotInfo", &SkeletonExtend::getAttachmentAndSlotInfo);


	auto animationState_ = binding.beginClass<AnimationStateExtend>("AnimationState");
	animationState_.addFunction("setAnimationByName", &AnimationStateExtend::setAnimationByName);
	animationState_.addFunction("addAnimationByName", &AnimationStateExtend::addAnimationByName);
	animationState_.addFunction("setEmptyAnimation", &AnimationStateExtend::setEmptyAnimation);
	animationState_.addFunction("getAnimationStateId", &AnimationStateExtend::getAnimationStateId);
	animationState_.addFunction("update", &AnimationStateExtend::update);
	animationState_.addFunction("apply", &AnimationStateExtend::apply);
	animationState_.addFunction("setListener", &AnimationStateExtend::setListener);
	animationState_.addVariable("id", &AnimationStateExtend::id, false);
	animationState_.addProperty("time_scale", &AnimationStateExtend::getTimeScale, &AnimationStateExtend::setTimeScale);
	
	
	
	auto _skeleton_ = binding.beginClass<SkeletonWrapper>("_Skeleton");
	_skeleton_.addFunction("computeDrawData", &SkeletonWrapper::computeDrawData);
	_skeleton_.addFunction("setToSetupPose", &SkeletonWrapper::setToSetupPose);
	_skeleton_.addFunction("setBonesToSetupPose", &SkeletonWrapper::setBonesToSetupPose);
	_skeleton_.addFunction("setSlotsToSetupPose", &SkeletonWrapper::setSlotsToSetupPose);
	_skeleton_.addFunction("setData", &SkeletonWrapper::setData);
	_skeleton_.addFunction("getData", &SkeletonWrapper::getData);

	bool SkeletonWrapper::*gpuInstance = &SkeletonExtend::gpuInstance;
	_skeleton_.addVariable("gpuInstance", gpuInstance, true);
	float SkeletonWrapper::*width = &SkeletonExtend::width;
	_skeleton_.addVariable("width", width, false);
	float SkeletonWrapper::*height = &SkeletonExtend::height;
	_skeleton_.addVariable("height", height, false);
	float SkeletonWrapper::*x = &SkeletonExtend::x;
	_skeleton_.addVariable("x", x, false);
	float SkeletonWrapper::*y = &SkeletonExtend::y;
	_skeleton_.addVariable("y", y, false);
	size_t SkeletonWrapper::*skelid = &SkeletonExtend::id;
	_skeleton_.addVariable("id", skelid, false);

	_skeleton_.addFunction("getMatrices", &SkeletonWrapper::getMatricesInfo);
	_skeleton_.addFunction("getAnimationsInfo", &SkeletonWrapper::getAnimationsInfo);
	_skeleton_.addFunction("updateWorldTransform", &SkeletonWrapper::updateWorldTransform);
	_skeleton_.addFunction("setAttachmentLua", &SkeletonExtend::setAttachmentLua);
	_skeleton_.addFunction("findBoneLua", &SkeletonExtend::findBoneLua);
	_skeleton_.addFunction("getAttachmentLua", &SkeletonExtend::getAttachmentLua);
	_skeleton_.addFunction("testCustomData", &SkeletonExtend::testCustomData);
	_skeleton_.addFunction("getBoneByIndex", &SkeletonWrapper::getBoneByIndex);
	_skeleton_.addFunction("getSlotByIndex", &SkeletonWrapper::getSlotByIndex);
	_skeleton_.addFunction("getSkin", &SkeletonWrapper::getSkinWrapper );
	_skeleton_.addFunction("setSkinByName", &SkeletonExtend::setSkinByName);
	_skeleton_.addFunction("setSkinBySkin", &SkeletonWrapper::setSkinBySkin);
	_skeleton_.addFunction("getSkeletonId", &SkeletonExtend::getSkeletonId);
	_skeleton_.addFunction("getBoneInfo", &SkeletonExtend::getBoneInfo);
	_skeleton_.addFunction("getAttachmentAndSlotInfo", &SkeletonExtend::getAttachmentAndSlotInfo);

	_skeleton_.addProperty("time", &SkeletonWrapper::getTime, &SkeletonWrapper::setTime);
	_skeleton_.addProperty("scaleX", &SkeletonWrapper::getScaleX, &SkeletonWrapper::setScaleX);
	_skeleton_.addProperty("scaleY", &SkeletonWrapper::getScaleY, &SkeletonWrapper::setScaleY);

	_skeleton_.addFunction("addBone", &SkeletonWrapper::addBone);
	_skeleton_.addFunction("removeBone", &SkeletonWrapper::removeBone);
	_skeleton_.addFunction("addSlot", &SkeletonWrapper::addSlot);
	_skeleton_.addFunction("removeSlot", &SkeletonWrapper::removeSlot);

	_skeleton_.addFunction("updateCache", &SkeletonWrapper::updateCache);
	_skeleton_.addFunction("updateBonesOrder", &SkeletonWrapper::updateBonesOrder);
	_skeleton_.addFunction("changeDrawOrder", &SkeletonWrapper::changeDrawOrder);



	auto _animationState_ = binding.beginClass<AnimationStateWrapper>("_AnimationState");
	_animationState_.addFunction("setAnimationByName", &AnimationStateWrapper::setAnimationByName);
	_animationState_.addFunction("update", &AnimationStateWrapper::update);
	_animationState_.addFunction("apply", &AnimationStateWrapper::apply);
	_animationState_.addFunction("clearTracks", &AnimationStateWrapper::clearTracks);
	_animationState_.addFunction("setListener", &AnimationStateWrapper::setListener);
	size_t AnimationStateWrapper::*animid = &AnimationStateExtend::id;
	_animationState_.addVariable("id", animid, false);



	auto entityCreator_ = binding.beginClass<EntityCreator>("EntityCreator");
	entityCreator_.addStaticFunction("createBoneData", &EntityCreator::createBoneData);
	entityCreator_.addStaticFunction("createBone", &EntityCreator::createBone);
	entityCreator_.addStaticFunction("createColor", &EntityCreator::createColor);
	entityCreator_.addStaticFunction("createSlotData", &EntityCreator::createSlotData);
	entityCreator_.addStaticFunction("createSlot", &EntityCreator::createSlot);
	entityCreator_.addStaticFunction("createRegionAttachment", &EntityCreator::createRegionAttachment);
	entityCreator_.addStaticFunction("createMeshAttachment", &EntityCreator::createMeshAttachment);
	entityCreator_.addStaticFunction("createEventData", &EntityCreator::createEventData);
	entityCreator_.addStaticFunction("createSkin", &EntityCreator::createSkin);
	entityCreator_.addStaticFunction("createSkeletonData", &EntityCreator::createSkeletonData);
	
	
	
	// data
	auto skeletonData_ = binding.beginClass<SkeletonDataWrapper>("SkeletonData");
	skeletonData_.addFunction("getBoneDataCount", &SkeletonDataWrapper::getBoneDataCount);
	skeletonData_.addFunction("getSlotDataCount", &SkeletonDataWrapper::getSlotDataCount);
	skeletonData_.addFunction("getSkinCount", &SkeletonDataWrapper::getSkinCount);
	skeletonData_.addFunction("getEventDataCount", &SkeletonDataWrapper::getEventDataCount);
	skeletonData_.addFunction("getAnimationCount", &SkeletonDataWrapper::getAnimationCount);
	skeletonData_.addFunction("getIkConstraintDataCount", &SkeletonDataWrapper::getIkConstraintDataCount);
	skeletonData_.addFunction("getTransformConstraintDataCount", &SkeletonDataWrapper::getTransformConstraintDataCount);
	skeletonData_.addFunction("getPathConstraintDataCount", &SkeletonDataWrapper::getPathConstraintDataCount);

	skeletonData_.addFunction("getBoneData", &SkeletonDataWrapper::getBoneData);
	skeletonData_.addFunction("getSlotData", &SkeletonDataWrapper::getSlotData);
	skeletonData_.addFunction("getSkin", &SkeletonDataWrapper::getSkin);
	skeletonData_.addFunction("getEventData", &SkeletonDataWrapper::getEventData);
	skeletonData_.addFunction("getDefaultSkin", &SkeletonDataWrapper::getDefaultSkinWrapper);
	skeletonData_.addFunction("getIkConstraintData", &SkeletonDataWrapper::getIkConstraintData);
	skeletonData_.addFunction("getTransformConstraintData", &SkeletonDataWrapper::getTransformConstraintData);
	skeletonData_.addFunction("getPathConstraintData", &SkeletonDataWrapper::getPathConstraintData);
	skeletonData_.addFunction("getAnimation", &SkeletonDataWrapper::getAnimation);
	skeletonData_.addFunction("findAnimationLua", &SkeletonDataWrapper::findAnimationLua);
	skeletonData_.addFunction("insertBone", &SkeletonDataWrapper::insertBone);

	skeletonData_.addFunction("removeAnimation", &SkeletonDataWrapper::removeAnimation);
	skeletonData_.addFunction("addAnimation", &SkeletonDataWrapper::addAnimation);
	skeletonData_.addFunction("removeEvent", &SkeletonDataWrapper::removeEvent);
	skeletonData_.addFunction("addEvent", &SkeletonDataWrapper::addEvent);

	skeletonData_.addFunction("findBoneLua", &SkeletonDataWrapper::findBoneLua);
	skeletonData_.addFunction("findBoneIndexLua", &SkeletonDataWrapper::findBoneIndexLua);
	skeletonData_.addFunction("findSlotLua", &SkeletonDataWrapper::findSlotLua);
	skeletonData_.addFunction("findSlotIndexLua", &SkeletonDataWrapper::findSlotIndexLua);
	skeletonData_.addFunction("findSkinLua", &SkeletonDataWrapper::findSkinLua);
	skeletonData_.addFunction("findAnimationLua", &SkeletonDataWrapper::findAnimationLua);
	skeletonData_.addFunction("copy", &SkeletonDataWrapper::copy);



	auto boneData_ = binding.beginClass<BoneDataWrapper>("BoneData");
	boneData_.addProperty("x", &BoneDataWrapper::getX, &BoneDataWrapper::setX);
	boneData_.addProperty("y", &BoneDataWrapper::getY, &BoneDataWrapper::setY);
	boneData_.addProperty("length", &BoneDataWrapper::getLength, &BoneDataWrapper::setLength);
	boneData_.addProperty("rotation", &BoneDataWrapper::getRotation, &BoneDataWrapper::setRotation);
	boneData_.addProperty("scaleX", &BoneDataWrapper::getScaleX, &BoneDataWrapper::setScaleX);
	boneData_.addProperty("scaleY", &BoneDataWrapper::getScaleY, &BoneDataWrapper::setScaleY);
	boneData_.addProperty("shearX", &BoneDataWrapper::getShearX, &BoneDataWrapper::setShearX);
	boneData_.addProperty("shearY", &BoneDataWrapper::getShearY, &BoneDataWrapper::setShearY);
	boneData_.addProperty("transformMode", &BoneDataWrapper::getTransformMode, &BoneDataWrapper::setTransformMode);
	boneData_.addProperty("skinRequired", &BoneDataWrapper::isSkinRequired, &BoneDataWrapper::setSkinRequired);
	boneData_.addProperty("name", &BoneDataWrapper::getWrapperName,&BoneDataWrapper::setName);

	boneData_.addPropertyReadOnly("index", &BoneDataWrapper::getIndex); //
	boneData_.addPropertyReadOnly("parent", &BoneDataWrapper::getParentName); 

	boneData_.addFunction("getColor", &BoneDataWrapper::getColor);



	auto slotData_ = binding.beginClass<SlotDataWrapper>("SlotData");
		
	slotData_.addProperty("name", &SlotDataWrapper::getSlotName,&SlotDataWrapper::setSlotName);
	slotData_.addProperty("attachment", &SlotDataWrapper::getAttachmentNameWrapper,&SlotDataWrapper::setAttachmentNameWrapper);

	slotData_.addPropertyReadOnly("boneData", &SlotDataWrapper::getBoneDataWrapper);
	slotData_.addPropertyReadOnly("index", &SlotDataWrapper::getIndex);
	slotData_.addPropertyReadOnly("color", &SlotDataWrapper::getColor);
	slotData_.addPropertyReadOnly("darkColor", &SlotDataWrapper::getDarkColor);
	slotData_.addPropertyReadOnly("blendMode", &SlotDataWrapper::getBlendMode);



	auto eventData_ = binding.beginClass<EventDataWrapper>("EventData");
	eventData_.addProperty("name", &EventDataWrapper::getName, &EventDataWrapper::setName);
	eventData_.addProperty("floatValue", &EventDataWrapper::getFloatValue, &EventDataWrapper::setFloatValue);
	eventData_.addProperty("stringValue", &EventDataWrapper::getStringValue, &EventDataWrapper::setStringValue);
	
	
	auto pathConstraintData_ = binding.beginClass<PathConstraintDataWrapper>("PathConstraintData");
	
	
	
	auto ikConstraintData_ = binding.beginClass<IkConstraintDataWrapper>("IkConstraintData");
	ikConstraintData_.addPropertyReadOnly("name", &IkConstraintDataWrapper::getName);
	ikConstraintData_.addFunction("getBoneDataCount", &IkConstraintDataWrapper::getBoneDataCount);
	ikConstraintData_.addFunction("getBoneData", &IkConstraintDataWrapper::getBoneData);
	ikConstraintData_.addPropertyReadOnly("target", &IkConstraintDataWrapper::getTarget);
	ikConstraintData_.addProperty("softness", &IkConstraintDataWrapper::getSoftness, &IkConstraintDataWrapper::setSoftness);
	ikConstraintData_.addProperty("bendDirection", &IkConstraintDataWrapper::getBendDirection, &IkConstraintDataWrapper::setBendDirection);
	ikConstraintData_.addProperty("mix", &IkConstraintDataWrapper::getMix, &IkConstraintDataWrapper::setMix);
	ikConstraintData_.addProperty("compress", &IkConstraintDataWrapper::getCompress, &IkConstraintDataWrapper::setCompress);
	ikConstraintData_.addProperty("stretch", &IkConstraintDataWrapper::getStretch, &IkConstraintDataWrapper::setStretch);
	ikConstraintData_.addProperty("uniform", &IkConstraintDataWrapper::getUniform, &IkConstraintDataWrapper::setUniform);
	ikConstraintData_.addPropertyReadOnly("skinRequired", &IkConstraintDataWrapper::isSkinRequired);
	ikConstraintData_.addPropertyReadOnly("order", &IkConstraintDataWrapper::getOrder);
	
	
	
	auto transformConstraintData_ = binding.beginClass<TransformConstraintDataWrapper>("TransformConstraintData");
	transformConstraintData_.addPropertyReadOnly("name", &TransformConstraintDataWrapper::getName);
	transformConstraintData_.addPropertyReadOnly("offsetScaleX", &TransformConstraintDataWrapper::getOffsetScaleX);
	transformConstraintData_.addPropertyReadOnly("offsetScaleY", &TransformConstraintDataWrapper::getOffsetScaleY);
	transformConstraintData_.addPropertyReadOnly("offsetShearY", &TransformConstraintDataWrapper::getOffsetShearY);
	transformConstraintData_.addPropertyReadOnly("rotateMix", &TransformConstraintDataWrapper::getRotateMix);
	transformConstraintData_.addPropertyReadOnly("translateMix", &TransformConstraintDataWrapper::getTranslateMix);
	transformConstraintData_.addPropertyReadOnly("scaleMix", &TransformConstraintDataWrapper::getScaleMix);
	transformConstraintData_.addPropertyReadOnly("shearMix", &TransformConstraintDataWrapper::getShearMix);
	transformConstraintData_.addPropertyReadOnly("offsetX", &TransformConstraintDataWrapper::getOffsetX);
	transformConstraintData_.addPropertyReadOnly("offsetY", &TransformConstraintDataWrapper::getOffsetY);
	transformConstraintData_.addPropertyReadOnly("offsetRotation", &TransformConstraintDataWrapper::getOffsetRotation);
	transformConstraintData_.addPropertyReadOnly("skinRequired", &TransformConstraintDataWrapper::isSkinRequired);
	transformConstraintData_.addPropertyReadOnly("target", &TransformConstraintDataWrapper::getTarget);
	transformConstraintData_.addPropertyReadOnly("order", &TransformConstraintDataWrapper::getOrder);

	transformConstraintData_.addFunction("getBoneDataCount", &TransformConstraintDataWrapper::getBoneDataCount);
	transformConstraintData_.addFunction("getBoneData", &TransformConstraintDataWrapper::getBoneData);
	
	
	
	auto bone_ = binding.beginClass<BoneWrapper>("Bone");

	bone_.addFunction("getData", &BoneWrapper::getData);

	bone_.addFunction("update",&BoneWrapper::update);
	bone_.addFunction("updateWorldTransform", &BoneWrapper::updateWorldTransformWrpper);
	bone_.addFunction("updateWorldTransformWith", &BoneWrapper::updateWorldTransformWith);
	bone_.addFunction("updateAppliedTransform", &BoneWrapper::updateAppliedTransform);
	bone_.addFunction("setToSetupPose", &BoneWrapper::setToSetupPose);

	bone_.addFunction("worldToLocal", &BoneWrapper::worldToLocalWrapper);
	bone_.addFunction("localToWorld", &BoneWrapper::localToWorldWrapper);
	bone_.addFunction("worldToLocalRotation", &BoneWrapper::worldToLocalRotation);
	bone_.addFunction("localToWorldRotation", &BoneWrapper::localToWorldRotation);
	bone_.addFunction("rotateWorld", &BoneWrapper::rotateWorld);
		
	bone_.addProperty("x", &BoneWrapper::getX, &BoneWrapper::setX);
	bone_.addProperty("y", &BoneWrapper::getY, &BoneWrapper::setY);
	bone_.addProperty("scaleX", &BoneWrapper::getScaleX, &BoneWrapper::setScaleX);
	bone_.addProperty("scaleY", &BoneWrapper::getScaleY, &BoneWrapper::setScaleY);
	bone_.addProperty("shearX", &BoneWrapper::getShearX, &BoneWrapper::setShearX);
	bone_.addProperty("shearY", &BoneWrapper::getShearY, &BoneWrapper::setShearY);
	bone_.addProperty("rotation", &BoneWrapper::getRotation, &BoneWrapper::setRotation);

	bone_.addProperty("a", &BoneWrapper::getA, &BoneWrapper::setA);
	bone_.addProperty("b", &BoneWrapper::getB, &BoneWrapper::setB);
	bone_.addProperty("c", &BoneWrapper::getC, &BoneWrapper::setC);
	bone_.addProperty("d", &BoneWrapper::getD, &BoneWrapper::setD);

	bone_.addProperty("worldX", &BoneWrapper::getWorldX, &BoneWrapper::setWorldX);
	bone_.addProperty("worldY", &BoneWrapper::getWorldY, &BoneWrapper::setWorldY);
	bone_.addPropertyReadOnly("worldRotationX", &BoneWrapper::getWorldRotationX);
	bone_.addPropertyReadOnly("worldRotationY", &BoneWrapper::getWorldRotationY);
	bone_.addPropertyReadOnly("worldScaleX", &BoneWrapper::getWorldScaleX);
	bone_.addPropertyReadOnly("worldScaleY", &BoneWrapper::getWorldScaleY);
		
	//edit method
	bone_.addFunction("add", &BoneWrapper::add);
	bone_.addFunction("remove", &BoneWrapper::remove);



	auto _bone_ = binding.beginClass<Bone>("_Bone");
	_bone_.addProperty("x", &BoneWrapper::getX, &BoneWrapper::setX);
	_bone_.addProperty("y", &BoneWrapper::getY, &BoneWrapper::setY);
	_bone_.addProperty("worldX", &BoneWrapper::getWorldX, &BoneWrapper::setWorldX);
	_bone_.addProperty("worldY", &BoneWrapper::getWorldY, &BoneWrapper::setWorldY);
	_bone_.addProperty("shearX", &BoneWrapper::getShearX, &BoneWrapper::setShearX);
	_bone_.addProperty("shearY", &BoneWrapper::getShearY, &BoneWrapper::setShearY);
	_bone_.addProperty("rotation", &BoneWrapper::getRotation, &BoneWrapper::setRotation);
	_bone_.addFunction("localToWorldRotation", &Bone::localToWorldRotation);
	_bone_.addFunction("getWorldRotationX", &BoneWrapper::getWorldRotationX);
	_bone_.addFunction("getWorldRotationY", &BoneWrapper::getWorldRotationY);
	_bone_.addFunction("getWorldScaleX", &BoneWrapper::getWorldScaleX);
	_bone_.addFunction("getWorldScaleY", &BoneWrapper::getWorldScaleY);
	_bone_.addFunction("localToWorldX", &BoneWrapper::localToWorldX);
	_bone_.addFunction("localToWorldY", &BoneWrapper::localToWorldY);



	auto slot_ = binding.beginClass<SlotWrapper>("Slot");
	slot_.addFunction("getData",&SlotWrapper::getData);
	slot_.addFunction("getBone", &SlotWrapper::getBone);
	slot_.addFunction("getDeform", &SlotWrapper::getDeform);
	slot_.addFunction("getSkeleton", &SlotWrapper::getSkeleton);
	slot_.addPropertyReadOnly("color", &SlotWrapper::getColor);
	slot_.addPropertyReadOnly("darkColor", &SlotWrapper::getDarkColor);

	slot_.addPropertyReadOnly("attachmentName", &SlotWrapper::getAttachmentName);
	slot_.addFunction("setAttachment", &SlotWrapper::setAttachment);
	slot_.addFunction("clearAttachment", &SlotWrapper::clearAttachment);
	slot_.addFunction("setToSetupPose", &SlotWrapper::setToSetupPose);



	// skin
	auto skin_ = binding.beginClass<SkinWrapper>("Skin");
	skin_.addPropertyReadOnly("name", &SkinWrapper::getSkinName); //
	skin_.addFunction("getAttachments", &SkinWrapper::getAttachmentWrappers);
	skin_.addFunction("addAttachment", &SkinWrapper::addAttachmentWrapper);
	skin_.addFunction("removeAttachment", &SkinWrapper::removeAttachmentWrapper);
	skin_.addFunction("addSlot", &SkinWrapper::addSlot);
	skin_.addFunction("removeSlot", &SkinWrapper::removeSlot);
	skin_.addFunction("addSkin", &SkinWrapper::addSkin);
	skin_.addFunction("copySkin", &SkinWrapper::copySkin);



	auto meshAttachment_ = binding.beginClass<MeshAttachmentWrapper>("MeshAttachment");

	meshAttachment_.addFunction("updateUVs"		, &MeshAttachmentWrapper::updateUVs);
	meshAttachment_.addFunction("computeWorldVertices", &MeshAttachmentWrapper::computeWorldVerticesWrapper);
		
	meshAttachment_.addPropertyReadOnly("tag", &MeshAttachmentWrapper::getTag);
	meshAttachment_.addPropertyReadOnly("name", &MeshAttachmentWrapper::getName2);
	meshAttachment_.addPropertyReadOnly("texName", &MeshAttachment::getTexName);

	meshAttachment_.addProperty("path"		, &MeshAttachmentWrapper::getPath		, &MeshAttachmentWrapper::setPath);
	meshAttachment_.addProperty("width"		, &MeshAttachmentWrapper::getWidth		, &MeshAttachmentWrapper::setWidth);
	meshAttachment_.addProperty("height"		, &MeshAttachmentWrapper::getHeight		, &MeshAttachmentWrapper::setHeight);
	meshAttachment_.addProperty("hull"	, &MeshAttachmentWrapper::getHullLength	, &MeshAttachmentWrapper::setHullLength);
		
	meshAttachment_.addProperty("regionU"	, &MeshAttachmentWrapper::getRegionU	, &MeshAttachmentWrapper::setRegionU);
	meshAttachment_.addProperty("regionV"	, &MeshAttachmentWrapper::getRegionV	, &MeshAttachmentWrapper::setRegionV);
	meshAttachment_.addProperty("regionU2"	, &MeshAttachmentWrapper::getRegionU2	, &MeshAttachmentWrapper::setRegionU2);
	meshAttachment_.addProperty("regionV2"	, &MeshAttachmentWrapper::getRegionV2	, &MeshAttachmentWrapper::setRegionV2);

	meshAttachment_.addProperty("regionWidth", &MeshAttachmentWrapper::getRegionWidth, &MeshAttachmentWrapper::setRegionWidth);
	meshAttachment_.addProperty("regionHeight", &MeshAttachmentWrapper::getRegionHeight, &MeshAttachmentWrapper::setRegionHeight);
	meshAttachment_.addProperty("regionOriWidth", &MeshAttachmentWrapper::getRegionOriginalWidth, &MeshAttachmentWrapper::setRegionOriginalWidth);
	meshAttachment_.addProperty("regionOriHeight", &MeshAttachmentWrapper::getRegionOriginalHeight, &MeshAttachmentWrapper::setRegionOriginalHeight);

	meshAttachment_.addProperty("worldVerticesLength", &MeshAttachmentWrapper::getWorldVerticesLength, &MeshAttachmentWrapper::setWorldVerticesLength);
	meshAttachment_.addProperty("vertices", &MeshAttachmentWrapper::verticesGetter, &MeshAttachmentWrapper::verticesSetter);
	meshAttachment_.addProperty("triangles", &MeshAttachmentWrapper::trianglesGetter, &MeshAttachmentWrapper::trianglesSetter);
	meshAttachment_.addProperty("edges", &MeshAttachmentWrapper::edgesGetter, &MeshAttachmentWrapper::edgesSetter);
	meshAttachment_.addProperty("uvs", &MeshAttachmentWrapper::uvsGetter, &MeshAttachmentWrapper::uvsSetter);
	meshAttachment_.addProperty("regionUVs", &MeshAttachmentWrapper::regionUVsGetter, &MeshAttachmentWrapper::regionUVsSetter);
	meshAttachment_.addProperty("bones", &MeshAttachmentWrapper::bonesGetter, &MeshAttachmentWrapper::bonesSetter); 



	auto regionAttachmentWrapper_ = binding.beginClass<RegionAttachmentWrapper>("RegionAttachmentWrapper");
	regionAttachmentWrapper_.addFunction("setUVs", &RegionAttachmentWrapper::setUVs);
	regionAttachmentWrapper_.addFunction("updateOffset", &RegionAttachmentWrapper::updateOffset);
	regionAttachmentWrapper_.addFunction("getUVs",&RegionAttachmentWrapper::getUVsWrapper);
	regionAttachmentWrapper_.addFunction("getOffset", &RegionAttachmentWrapper::getOffsetWrapper);
	regionAttachmentWrapper_.addFunction("computeWorldVertices", &RegionAttachmentWrapper::computeWorldVerticesWrapper);
		
	regionAttachmentWrapper_.addPropertyReadOnly("tag", &RegionAttachmentWrapper::getTag);
	regionAttachmentWrapper_.addPropertyReadOnly("name", &RegionAttachmentWrapper::getName2);
	regionAttachmentWrapper_.addPropertyReadOnly("texName", &RegionAttachment::getTexName);

	regionAttachmentWrapper_.addProperty("x", &RegionAttachmentWrapper::getX, &RegionAttachmentWrapper::setX);
	regionAttachmentWrapper_.addProperty("y", &RegionAttachmentWrapper::getY, &RegionAttachmentWrapper::setY);
	regionAttachmentWrapper_.addProperty("width", &RegionAttachmentWrapper::getWidth, &RegionAttachmentWrapper::setWidth);
	regionAttachmentWrapper_.addProperty("height", &RegionAttachmentWrapper::getHeight, &RegionAttachmentWrapper::setHeight);
	regionAttachmentWrapper_.addProperty("scaleX", &RegionAttachmentWrapper::getScaleX, &RegionAttachmentWrapper::setScaleX);
	regionAttachmentWrapper_.addProperty("scaleY", &RegionAttachmentWrapper::getScaleY, &RegionAttachmentWrapper::setScaleY);
	regionAttachmentWrapper_.addProperty("rotation", &RegionAttachmentWrapper::getRotation, &RegionAttachmentWrapper::setRotation);

	regionAttachmentWrapper_.addProperty("path", &RegionAttachmentWrapper::getPath, &RegionAttachmentWrapper::setPath);

	regionAttachmentWrapper_.addProperty("regionOffsetX", &RegionAttachmentWrapper::getRegionOffsetX, &RegionAttachmentWrapper::setRegionOffsetX);
	regionAttachmentWrapper_.addProperty("regionOffsetY", &RegionAttachmentWrapper::getRegionOffsetY, &RegionAttachmentWrapper::setRegionOffsetY);
	regionAttachmentWrapper_.addProperty("regionWidth", &RegionAttachmentWrapper::getRegionWidth, &RegionAttachmentWrapper::setRegionWidth);
	regionAttachmentWrapper_.addProperty("regionHeight", &RegionAttachmentWrapper::getRegionHeight, &RegionAttachmentWrapper::setRegionHeight);



	auto event_ = binding.beginClass<Event>("Event");
	event_.addPropertyReadOnly("getIntValue", &Event::getIntValue);
	event_.addPropertyReadOnly("getFloatValue", &Event::getIntValue);
	


	// 动画
	auto animationCreator_ = binding.beginClass<AnimationCreator>("AnimationCreator");
	animationCreator_.addStaticFunction("createAnimation", &AnimationCreator::createAnimation);
	animationCreator_.addStaticFunction("createAttachmentTimeline", &AnimationCreator::createAttachmentTimeline);
	animationCreator_.addStaticFunction("createColorTimeline", &AnimationCreator::createColorTimeline);
	animationCreator_.addStaticFunction("createDeformTimeline", &AnimationCreator::createDeformTimeline);
	animationCreator_.addStaticFunction("createDrawOrderTimeline", &AnimationCreator::createDrawOrderTimeline);
	animationCreator_.addStaticFunction("createEventTimeline", &AnimationCreator::createEventTimeline);
	animationCreator_.addStaticFunction("createIkConstraintTimeline", &AnimationCreator::createIkConstraintTimeline);
	animationCreator_.addStaticFunction("createPathConstraintMixTimeline", &AnimationCreator::createPathConstraintMixTimeline);
	animationCreator_.addStaticFunction("createPathConstraintPositionTimeline", &AnimationCreator::createPathConstraintPositionTimeline);
	animationCreator_.addStaticFunction("createPathConstraintSpacingTimeline", &AnimationCreator::createPathConstraintSpacingTimeline);
	animationCreator_.addStaticFunction("createRotateTimeline", &AnimationCreator::createRotateTimeline);
	animationCreator_.addStaticFunction("createScaleTimeline", &AnimationCreator::createScaleTimeline);
	animationCreator_.addStaticFunction("createShearTimeline", &AnimationCreator::createShearTimeline);
	animationCreator_.addStaticFunction("createTransformConstraintTimeline", &AnimationCreator::createTransformConstraintTimeline);
	animationCreator_.addStaticFunction("createTranslateTimeline", &AnimationCreator::createTranslateTimeline);
	animationCreator_.addStaticFunction("createTwoColorTimeline", &AnimationCreator::createTwoColorTimeline);



	auto animation_ = binding.beginClass<AnimationWrapper>("Animation");
	animation_.addProperty("name", &AnimationWrapper::getName, &AnimationWrapper::setName);
	animation_.addFunction("getTimelineCount", &AnimationWrapper::getTimelineCount);
	animation_.addFunction("getTimelineClassName", &AnimationWrapper::getTimelineClassName);
	animation_.addProperty("duration", &AnimationWrapper::getDuration, &AnimationWrapper::setDuration);
	animation_.addFunction("addTimeline", &AnimationWrapper::addTimeline);
	animation_.addFunction("removeTimeline", &AnimationWrapper::removeTimeline);
	animation_.addFunction("getAttachmentTimeline", &AnimationWrapper::getTimeline<AttachmentTimelineWrapper>);
	animation_.addFunction("getColorTimeline", &AnimationWrapper::getTimeline<ColorTimelineWrapper>);
	animation_.addFunction("getDeformTimeline", &AnimationWrapper::getTimeline<DeformTimelineWrapper>);
	animation_.addFunction("getDrawOrderTimeline", &AnimationWrapper::getTimeline<DrawOrderTimelineWrapper>);
	animation_.addFunction("getEventTimeline", &AnimationWrapper::getTimeline<EventTimelineWrapper>);
	animation_.addFunction("getIkConstraintTimeline", &AnimationWrapper::getTimeline<IkConstraintTimelineWrapper>);
	animation_.addFunction("getPathConstraintMixTimeline", &AnimationWrapper::getTimeline<PathConstraintMixTimelineWrapper>);
	animation_.addFunction("getPathConstraintPositionTimeline", &AnimationWrapper::getTimeline<PathConstraintPositionTimelineWrapper>);
	animation_.addFunction("getPathConstraintSpacingTimeline", &AnimationWrapper::getTimeline<PathConstraintSpacingTimelineWrapper>);
	animation_.addFunction("getRotateTimeline", &AnimationWrapper::getTimeline<RotateTimelineWrapper>);
	animation_.addFunction("getScaleTimeline", &AnimationWrapper::getTimeline<ScaleTimelineWrapper>);
	animation_.addFunction("getShearTimeline", &AnimationWrapper::getTimeline<ShearTimelineWrapper>);
	animation_.addFunction("getTransformConstraintTimeline", &AnimationWrapper::getTimeline<TransformConstraintTimelineWrapper>);
	animation_.addFunction("getTranslateTimeline", &AnimationWrapper::getTimeline<TranslateTimelineWrapper>);
	animation_.addFunction("getTwoColorTimeline", &AnimationWrapper::getTimeline<TwoColorTimelineWrapper>);



	// timeline
	auto timeline_ = binding.beginClass<Timeline>("Timeline");



	auto attachmentTimeline_ = binding.beginClass<AttachmentTimelineWrapper>("AttachmentTimeline");
	attachmentTimeline_.addFunction("getFrameCount", &AttachmentTimelineWrapper::getFrameCount);
	attachmentTimeline_.addFunction("setFrame", &AttachmentTimelineWrapper::setFrame);
	attachmentTimeline_.addFunction("setFrameLua", &AttachmentTimelineWrapper::setFrameLua);
	attachmentTimeline_.addFunction("getFrame", &AttachmentTimelineWrapper::getFrame);
	attachmentTimeline_.addFunction("getFrames", &AttachmentTimelineWrapper::getFrames);
	attachmentTimeline_.addFunction("getAttachmentName", &AttachmentTimelineWrapper::getAttachmentName);
	attachmentTimeline_.addFunction("getAttachmentNames", &AttachmentTimelineWrapper::getAttachmentNames);
	attachmentTimeline_.addProperty("slotIndex", &AttachmentTimelineWrapper::getSlotIndex, &AttachmentTimelineWrapper::setSlotIndex);
	attachmentTimeline_.addFunction("setToSetupPose", &AttachmentTimelineWrapper::setToSetupPose);
	
	
	
	auto colorTimeline_ = binding.beginClass<ColorTimelineWrapper>("ColorTimeline");
	colorTimeline_.addFunction("getFrameCount", &ColorTimelineWrapper::getFrameCount);
	colorTimeline_.addFunction("getFrameData", &ColorTimelineWrapper::getFrameData);
	colorTimeline_.addProperty("slotIndex", &ColorTimelineWrapper::getSlotIndex, &ColorTimelineWrapper::setSlotIndex);
	colorTimeline_.addFunction("setToSetupPose", &ColorTimelineWrapper::setToSetupPose);
	
	
	
	auto deformTimeline_ = binding.beginClass<DeformTimelineWrapper>("DeformTimeline");
	deformTimeline_.addFunction("getFrameCount", &DeformTimelineWrapper::getFrameCount);
	deformTimeline_.addFunction("getFrameData", &DeformTimelineWrapper::getFrameData);
	deformTimeline_.addProperty("slotIndex", &DeformTimelineWrapper::getSlotIndex, &DeformTimelineWrapper::setSlotIndex);
	deformTimeline_.addFunction("setToSetupPose", &DeformTimelineWrapper::setToSetupPose);
	deformTimeline_.addProperty("attachmentName", &DeformTimelineWrapper::getAttachmentName);



	auto drawOrderTimeline_ = binding.beginClass<DrawOrderTimelineWrapper>("DrawOrderTimeline");
	drawOrderTimeline_.addFunction("getFrameCount", &DrawOrderTimelineWrapper::getFrameCount);
	drawOrderTimeline_.addFunction("getFrameData", &DrawOrderTimelineWrapper::getFrameData);
	drawOrderTimeline_.addFunction("setToSetupPose", &DrawOrderTimelineWrapper::setToSetupPose);



	auto eventTimeline_ = binding.beginClass<EventTimelineWrapper>("EventTimeline");
	eventTimeline_.addFunction("getFrameCount", &EventTimelineWrapper::getFrameCount);
	eventTimeline_.addFunction("getFrameData", &EventTimelineWrapper::getFrameData);
	eventTimeline_.addFunction("setToSetupPose", &EventTimelineWrapper::setToSetupPose);



	auto ikConstraintTimeline_ = binding.beginClass<IkConstraintTimelineWrapper>("IkConstraintTimeline");
	ikConstraintTimeline_.addProperty("ikConstraintIndex", &IkConstraintTimelineWrapper::getIkConstraintIndex, &IkConstraintTimelineWrapper::setIkConstraintIndex);
	ikConstraintTimeline_.addFunction("getFrameCount", &IkConstraintTimelineWrapper::getFrameCount);
	ikConstraintTimeline_.addFunction("getFrameData", &IkConstraintTimelineWrapper::getFrameData);
	


	auto pathConstraintMixTimeline_ = binding.beginClass<PathConstraintMixTimelineWrapper>("PathConstraintMixTimeline");
	auto pathConstraintPositionTimeline_ = binding.beginClass<PathConstraintPositionTimelineWrapper>("PathConstraintPositionTimeline");
	auto pathConstraintSpacingTimeline_ = binding.beginClass<PathConstraintSpacingTimelineWrapper>("PathConstraintSpacingTimeline");
	
	
	
	auto rotateTimeline_ = binding.beginClass<RotateTimelineWrapper>("RotateTimeline");
	rotateTimeline_.addFunction("getFrameCount", &RotateTimelineWrapper::getFrameCount);
	rotateTimeline_.addFunction("getFrameData", &RotateTimelineWrapper::getFrameData);
	rotateTimeline_.addProperty("boneIndex", &RotateTimelineWrapper::getBoneIndex, &RotateTimelineWrapper::setBoneIndex);
	rotateTimeline_.addFunction("setToSetupPose", &RotateTimelineWrapper::setToSetupPose);
	
	
	
	auto scaleTimeline_ = binding.beginClass<ScaleTimelineWrapper>("ScaleTimeline");
	scaleTimeline_.addFunction("getFrameCount", &ScaleTimelineWrapper::getFrameCount);
	scaleTimeline_.addFunction("getFrameData", &ScaleTimelineWrapper::getFrameData);
	scaleTimeline_.addProperty("boneIndex", &ScaleTimelineWrapper::getBoneIndex, &ScaleTimelineWrapper::setBoneIndex);
	scaleTimeline_.addFunction("setToSetupPose", &ScaleTimelineWrapper::setToSetupPose);
	
	
	
	auto shearTimeline_ = binding.beginClass<ShearTimelineWrapper>("ShearTimeline");
	shearTimeline_.addFunction("getFrameCount", &ShearTimelineWrapper::getFrameCount);
	shearTimeline_.addFunction("getFrameData", &ShearTimelineWrapper::getFrameData);
	shearTimeline_.addProperty("boneIndex", &ShearTimelineWrapper::getBoneIndex, &ShearTimelineWrapper::setBoneIndex);
	shearTimeline_.addFunction("setToSetupPose", &ShearTimelineWrapper::setToSetupPose);
	
	
	
	auto transformConstraintTimeline_ = binding.beginClass<TransformConstraintTimelineWrapper>("TransformConstraintTimeline");
	transformConstraintTimeline_.addProperty("transformConstraintIndex", &TransformConstraintTimelineWrapper::getTransformConstraintIndex, &TransformConstraintTimelineWrapper::setTransformConstraintIndex);
	transformConstraintTimeline_.addFunction("getFrameCount", &TransformConstraintTimelineWrapper::getFrameCount);
	transformConstraintTimeline_.addFunction("getFrameData", &TransformConstraintTimelineWrapper::getFrameData);
	
	
	
	auto translateTimeline_ = binding.beginClass<TranslateTimelineWrapper>("TranslateTimeline");
	translateTimeline_.addFunction("getFrameCount", &TranslateTimelineWrapper::getFrameCount);
	translateTimeline_.addFunction("getFrameData", &TranslateTimelineWrapper::getFrameData);
	translateTimeline_.addFunction("setToSetupPose", &TranslateTimelineWrapper::setToSetupPose);
	translateTimeline_.addProperty("boneIndex", &TranslateTimelineWrapper::getBoneIndex, &TranslateTimelineWrapper::setBoneIndex);
	
	
	
	auto twoColorTimeline_ = binding.beginClass<TwoColorTimelineWrapper>("TwoColorTimeline");
	twoColorTimeline_.addFunction("getFrameCount", &TwoColorTimelineWrapper::getFrameCount);
	twoColorTimeline_.addFunction("getFrameData", &TwoColorTimelineWrapper::getFrameData);
	twoColorTimeline_.addProperty("slotIndex", &TwoColorTimelineWrapper::getSlotIndex, &TwoColorTimelineWrapper::setSlotIndex);



	// other
	auto color_ = binding.beginClass<Color>("Color");
	color_.addVariable("r", &Color::r, true);
	color_.addVariable("g", &Color::g, true);
	color_.addVariable("b", &Color::b, true);
	color_.addVariable("a", &Color::a, true);
	Color &(Color::*set)(float, float, float, float) = &Color::set;
	color_.addFunction("set", set);
	Color &(Color::*add)(float, float, float, float) = &Color::add;
	color_.addFunction("set", add);



	auto trackEntry_ = binding.beginClass<TrackEntry>("TrackEntry");
	trackEntry_.addFunction("setLoopCount", &TrackEntry::setLoopCount);
	trackEntry_.addFunction("getAnimationEnd", &TrackEntry::getAnimationEnd);
	trackEntry_.addFunction("getAnimationName", &TrackEntry::getAnimationName);
	trackEntry_.addProperty("mix_duration", &TrackEntry::getMixDuration, &TrackEntry::setMixDuration);
	trackEntry_.addProperty("alpha", &TrackEntry::getAlpha, &TrackEntry::setAlpha);


	mod.pushToStack();
}

// 插件的主要入口从这里开始(主线程)
static int skeleton(EPluginMsgType eMsgType, void* param1) {
    switch (eMsgType) {
        case ELuaOnReady:
            // 主线程LUA初始化完毕
            register_lua_functions((lua_State*)param1);
            break;
        case EThreadLuaOnReady:
            // 线程池LUA初始化完毕，在线程池线程中调用。
            register_lua_functions((lua_State*) param1);
            break;
        case EFrameUpdate:
            // 每帧回调
            break;
        case EOnPause:
            // 暂停
            break;
        case EOnResume:
            // 继续
            break;
        case EOnExit:
            // 退出的时候, 基本上没什么用
            break;
        default:
            break;
    }

    return 0;
}


BABE_PLUGIN_ENTRY(skeleton)

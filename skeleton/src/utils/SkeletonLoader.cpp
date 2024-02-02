#include "SkeletonLoader.h"
#include "utils/SkeletonObjectCreator.h"
#include "utils/SkeletonWrapperCreator.h"
#include <iostream>
using namespace skel;
using namespace std;

std::mutex SkeletonLoader::_skeletonStateMutex;
std::size_t SkeletonLoader::_stateIndex = 0;
std::mutex SkeletonLoader::_skeletonDataMutex;
std::size_t SkeletonLoader::_dataIndex = 0;
//std::size_t SkeletonLoader::_animationStateIndex = 0;
//std::map<std::size_t, std::pair<SkeletonExtend*, AnimationStateExtend*>> SkeletonLoader::_skeletonStateMap;
std::map<std::string, std::map<std::string, std::string>> SkeletonLoader::_skinMap;
std::map<std::string, std::pair<SkeletonData*, std::string>> SkeletonLoader::_skeletonDataMap;

SkeletonLoader::SkeletonLoader() {
}

SkeletonLoader::~SkeletonLoader() {
}

SkeletonExtend *SkeletonLoader::_loadSkeletonBySkelData(SkeletonData* skeletonData, SkeletonObjectCreator &creator) {
	if (skeletonData) {
		SkeletonExtend *skeleton = creator.createSkeleton(skeletonData);
		skeleton->id = _stateIndex;
		//insertSkeletonState(skeleton);
		++_stateIndex;
		return skeleton;
	}
	return nullptr;
}

SkeletonExtend *SkeletonLoader::_loadSkeleton(const char *skeletonDataStr, LuaIntf::LuaRef &unitData, SkeletonObjectCreator &creator) {
	Atlas atlas(unitData);
	AtlasAttachmentLoader loader(&atlas);

	SkeletonData *skeletonData = nullptr;
	SkeletonJson json(&loader);

	skeletonData = json.readSkeletonData(skeletonDataStr, creator);
	return _loadSkeletonBySkelData(skeletonData, creator);
}

std::shared_ptr<SkeletonWrapper>SkeletonLoader::loadSkeletonWrapper(const char *skeletonDataStr, LuaIntf::LuaRef &unitData)
{
	SkeletonWrapperCreator creator;
	return std::shared_ptr<SkeletonWrapper>(dynamic_cast<SkeletonWrapper *>(_loadSkeleton(skeletonDataStr, unitData, creator)));
}

std::shared_ptr<SkeletonWrapper> SkeletonLoader::loadSkeletonWrapperCache(std::string index) {
	SkeletonWrapperCreator creator;
	SkeletonData* data = getSkeletonData(index);
	if (data == nullptr) {
		return nullptr;
	}

	return std::shared_ptr<SkeletonWrapper>(dynamic_cast<SkeletonWrapper *>(_loadSkeletonBySkelData(data, creator)));
}

SkeletonDataWrapper *SkeletonLoader::cloneSkeletonData(std::string index, LuaIntf::LuaRef &unitData) {
	const char* jsonStr = getSkeletonJsonStr(index);
	if (jsonStr == nullptr) {
		return nullptr;
	}

	SkeletonWrapperCreator creator;

	Atlas atlas(unitData);
	AtlasAttachmentLoader loader(&atlas);

	SkeletonData *skeletonData = nullptr;
	SkeletonJson json(&loader);

	return dynamic_cast<SkeletonDataWrapper *>(json.readSkeletonData(jsonStr, creator));
}

LuaIntf::LuaRef SkeletonLoader::loadSkeletonData(lua_State* L, const char *skeletonDataStr, LuaIntf::LuaRef &unitData) {
	LuaIntf::LuaState LS(L);

	SkeletonWrapperCreator creator;

	Atlas atlas(unitData);
	AtlasAttachmentLoader loader(&atlas);

	SkeletonData *skeletonData = nullptr;
	SkeletonJson json(&loader);

	skeletonData = json.readSkeletonData(skeletonDataStr, creator);

	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();

	if (skeletonData == NULL)
	{
		String errorInfo;
		errorInfo = json.getError();
		ref.set<std::string, std::string>("error", std::string(errorInfo.buffer()));
	}
	else
	{
		std::string id = insertSkeletonData(skeletonData, skeletonDataStr);
		ref.set<std::string, std::string>("id", id);
		ref.set<std::string, float>("x", skeletonData->getX());
		ref.set<std::string, float>("y", skeletonData->getY());
		ref.set<std::string, float>("width", skeletonData->getWidth());
		ref.set<std::string, float>("height", skeletonData->getHeight());


		auto animations = skeletonData->getAnimations();
		LS.newTable();
		LuaIntf::LuaRef animRef(L, -1);
		LS.pop();
		for (int i = 0; i < animations.size(); i++)
		{
			LS.newTable();
			LuaIntf::LuaRef animObjRef(L, -1);
			LS.pop();

			animObjRef.set<std::string, std::string>("name", std::string(animations[i]->getName().buffer()));
			animObjRef.set<std::string, float>("duration", animations[i]->getDuration());

			animRef.set<int, LuaIntf::LuaRef>(i + 1, animObjRef);
		}
		ref.set<std::string, LuaIntf::LuaRef>("animations", animRef);



		auto boneDatas = skeletonData->getBones();
		LS.newTable();
		LuaIntf::LuaRef boneRef(L, -1);
		LS.pop();
		for (int i = 0; i < boneDatas.size(); i++)
		{
			LS.newTable();
			LuaIntf::LuaRef boneObjRef(L, -1);
			LS.pop();

			boneObjRef.set<std::string, std::string>("name", std::string(boneDatas[i]->getName().buffer()));
			boneObjRef.set<std::string, int>("index", boneDatas[i]->getIndex());
			boneRef.set<int, LuaIntf::LuaRef>(i + 1, boneObjRef);
		}
		ref.set<std::string, LuaIntf::LuaRef>("bones", boneRef);



		auto slotDatas = skeletonData->getSlots();
		LS.newTable();
		LuaIntf::LuaRef slotRef(L, -1);
		LS.pop();
		for (int i = 0; i < slotDatas.size(); i++)
		{
			LS.newTable();
			LuaIntf::LuaRef slotObjRef(L, -1);
			LS.pop();

			slotObjRef.set<std::string, std::string>("name", std::string(slotDatas[i]->getName().buffer()));
			slotObjRef.set<std::string, int>("index", slotDatas[i]->getIndex());

			std::string name = "";

			slotObjRef.set<std::string, std::string>("attachmentName", slotDatas[i]->getAttachmentName().isEmpty() ? "" : slotDatas[i]->getAttachmentName().buffer());
			slotRef.set<int, LuaIntf::LuaRef>(i + 1, slotObjRef);
		}
		ref.set<std::string, LuaIntf::LuaRef>("slots", slotRef);



		auto skins = skeletonData->getSkins();
		LS.newTable();
		LuaIntf::LuaRef skinRef(L, -1);
		LS.pop();
		for (int i = 0; i < skins.size(); i++)
		{
			LS.newTable();
			LuaIntf::LuaRef skinObjRef(L, -1);
			LS.pop();

			skinObjRef.set<std::string, std::string>("name", std::string(skins[i]->getName().buffer()));
			skinRef.set<int, LuaIntf::LuaRef>(i + 1, skinObjRef);
		}
		ref.set<std::string, LuaIntf::LuaRef>("skins", skinRef);
	}

	ref.set<std::string, SkeletonDataWrapper*>("skeletonDataObj", dynamic_cast<SkeletonDataWrapper*>(skeletonData));

	return ref;
}

LuaIntf::LuaRef SkeletonLoader::loadSkeletonLiteData(lua_State* L, LuaIntf::LuaRef &skelDataRef, LuaIntf::LuaRef &skinListRef) {
	
	LuaIntf::LuaState LS(L);

	//获取数据, 拼图信息, 骨骼标识
	std::string skeletonDataStr = skelDataRef.get("jsonStr").toValue<std::string>();
	LuaIntf::LuaRef unitDataRef = skelDataRef.get("unit");
	std::string resId = skelDataRef.get("resId").toValue<std::string>();

	//获取皮肤文件内皮肤的名称, 创建皮肤名称-->皮肤数据的表
	std::map<std::string, std::string> skinNameList;
	for (int i = 1; i <= skinListRef.len(); i++)
	{
		std::string skinStr = skinListRef.get(i).toValue<std::string>();
	    Json* skinJson = new(__FILE__, __LINE__) Json(skinStr.c_str());
		std::string skinName = Json::getString(skinJson, "name", "");
		skinNameList[skinName] = skinStr;
	}

	//检查和合并此骨骼标识的皮肤表, 如果已经都包含则返回缓存id, 如果有没缓存的皮肤, 添加皮肤到表内, 然后返回空后续重建数据对象
	bool cached = checkSkeletonCacheBySkinList(skinNameList, resId);

	SkeletonData *skeletonData = nullptr;
	SkeletonJson *jsonPtr = nullptr;

	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();

	if (cached)
		skeletonData = getSkeletonData(resId);
	else
	{
		SkeletonWrapperCreator creator;

		Atlas atlas(unitDataRef);
		AtlasAttachmentLoader loader(&atlas);

		jsonPtr = new SkeletonJson(&loader);
		skeletonData = jsonPtr->readSkeletonDataWithSkin(skeletonDataStr.c_str(), _skinMap[resId], creator);
		insertSkeletonAndSkinData(skeletonData, skeletonDataStr, resId);

		if (skeletonData == NULL)
		{
			String errorInfo;
			errorInfo = jsonPtr->getError();
			ref.set<std::string, std::string>("error", std::string(errorInfo.buffer()));
		}
	}

	if (skeletonData != NULL)
	{
		ref.set<std::string, std::string>("id", resId);
		ref.set<std::string, float>("x", skeletonData->getX());
		ref.set<std::string, float>("y", skeletonData->getY());
		ref.set<std::string, float>("width", skeletonData->getWidth());
		ref.set<std::string, float>("height", skeletonData->getHeight());

		auto animations = skeletonData->getAnimations();
		LS.newTable();
		LuaIntf::LuaRef animRef(L, -1);
		LS.pop();
		for (int i = 0; i < animations.size(); i++)
		{
			LS.newTable();
			LuaIntf::LuaRef animObjRef(L, -1);
			LS.pop();

			animObjRef.set<std::string, std::string>("name", std::string(animations[i]->getName().buffer()));
			animObjRef.set<std::string, float>("duration", animations[i]->getDuration());
		    
			animRef.set<int, LuaIntf::LuaRef>(i + 1, animObjRef);
		}
		ref.set<std::string, LuaIntf::LuaRef>("animations", animRef);



		auto boneDatas = skeletonData->getBones();
		LS.newTable();
		LuaIntf::LuaRef boneRef(L, -1);
		LS.pop();
		for (int i = 0; i < boneDatas.size(); i++)
		{
			LS.newTable();
			LuaIntf::LuaRef boneObjRef(L, -1);
			LS.pop();

			boneObjRef.set<std::string, std::string>("name", std::string(boneDatas[i]->getName().buffer()));
			boneObjRef.set<std::string, int>("index", boneDatas[i]->getIndex());
			boneRef.set<int, LuaIntf::LuaRef>(i + 1, boneObjRef);
		}
		ref.set<std::string, LuaIntf::LuaRef>("bones", boneRef);



		auto slotDatas = skeletonData->getSlots();
		LS.newTable();
		LuaIntf::LuaRef slotRef(L, -1);
		LS.pop();
		for (int i = 0; i < slotDatas.size(); i++)
		{
			LS.newTable();
			LuaIntf::LuaRef slotObjRef(L, -1);
			LS.pop();

			slotObjRef.set<std::string, std::string>("name", std::string(slotDatas[i]->getName().buffer()));
			slotObjRef.set<std::string, int>("index", slotDatas[i]->getIndex());

			std::string name = "";

			slotObjRef.set<std::string, std::string>("attachmentName", slotDatas[i]->getAttachmentName().isEmpty() ? "" : slotDatas[i]->getAttachmentName().buffer());
			slotRef.set<int, LuaIntf::LuaRef>(i + 1, slotObjRef);
		}
		ref.set<std::string, LuaIntf::LuaRef>("slots", slotRef);



		auto skins = skeletonData->getSkins();
		LS.newTable();
		LuaIntf::LuaRef skinRef(L, -1);
		LS.pop();
		for (int i = 0; i < skins.size(); i++)
		{
			LS.newTable();
			LuaIntf::LuaRef skinObjRef(L, -1);
			LS.pop();

			skinObjRef.set<std::string, std::string>("name", std::string(skins[i]->getName().buffer()));
			skinRef.set<int, LuaIntf::LuaRef>(i + 1, skinObjRef);
		}
		ref.set<std::string, LuaIntf::LuaRef>("skins", skinRef);
	}

	ref.set<std::string, SkeletonDataWrapper*>("skeletonDataObj", dynamic_cast<SkeletonDataWrapper*>(skeletonData));

	//debug
	/*std::map<std::string, std::vector<std::string>>::iterator it;

	std::cout << "currentCachedSkinList====================================" << std::endl;
	for (it = _skinMap.begin(); it != _skinMap.end(); it++)
	{
		std::cout << it->first << std::endl;
		for (std::string i : it->second)
		{
			std::cout << "    " + i << std::endl;;
		}
	}*/

	return ref;
}

bool skel::SkeletonLoader::checkSkeletonCacheBySkinList(std::map<std::string, std::string> &skinList, std::string resId)
{
	std::map<std::string, std::string>::iterator it;
	if (skinList.empty())
		return false;
	
	bool hasAll = true;

	for (it = skinList.begin(); it != skinList.end(); it++)
	{
		std::string skinName = it->first;

		if (_skinMap[resId].find(skinName) == _skinMap[resId].end())
		{
			hasAll = false;
			_skinMap[resId][skinName] = it->second;
		}
	}
	
	return hasAll;
}

void SkeletonLoader::deleteSkeleton(SkeletonWrapper *skelWapper)
{
	delete skelWapper;
}

//void skel::SkeletonLoader::removeStatePair(std::size_t id)
//{
//	std::lock_guard<std::mutex> guard(_skeletonStateMutex);
//	auto iter = _skeletonStateMap.find(id);
//	if (iter == _skeletonStateMap.end())
//	{
//		return;
//	}
//
//	delete iter->second.first;
//	delete iter->second.second;
//
//	_skeletonStateMap.erase(id);
//}

AnimationStateExtend *SkeletonLoader::_loadAnimationState(SkeletonWrapper *skeleton, SkeletonObjectCreator &creator) {
	AnimationStateData *animationStateData = creator.createAnimationStateData(dynamic_cast<SkeletonExtend *>(skeleton)->getData());
	animationStateData->setDefaultMix(0.1);
	AnimationStateExtend *animationState = creator.createAnimationState(animationStateData);
	animationState->id = skeleton->id;
	//insertAnimatonState(animationState);
	return animationState;
}

std::shared_ptr<AnimationStateExtend> SkeletonLoader::loadAnimationState(SkeletonWrapper *skeleton) {
	SkeletonObjectCreator creator;
	return std::shared_ptr<AnimationStateExtend>(_loadAnimationState(skeleton, creator));
}

//void SkeletonLoader::removeStatePair(std::size_t id)
//{
//	auto iter = _skeletonStateMap.find(id);
//	if (iter == _skeletonStateMap.end())
//	{
//		return;
//	}
//
//	delete iter->second.first;
//	delete iter->second.second;
//
//	_skeletonStateMap.erase(id);
//}



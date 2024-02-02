#ifndef Skel_SkeletonLoader_h
#define Skel_SkeletonLoader_h

#include <mutex>
#include "LuaIntf/LuaIntf.h"
#include "common/skel.h"
#include "wrapper/SkeletonWrapper.h"
#include "wrapper/AnimationStateWrapper.h"

namespace skel {

	class SK_API SkeletonLoader {
	public:
		SkeletonLoader();

		~SkeletonLoader();
		
		static LuaIntf::LuaRef loadSkeletonData(lua_State* L, const char *skeletonDataStr, LuaIntf::LuaRef &unitData);
		static LuaIntf::LuaRef loadSkeletonLiteData(lua_State* L, LuaIntf::LuaRef &skelDataRef, LuaIntf::LuaRef &skinListRef);
		static bool checkSkeletonCacheBySkinList(std::map<std::string, std::string> &skinList, std::string resId);
		static SkeletonDataWrapper* cloneSkeletonData(std::string index, LuaIntf::LuaRef &unitData);
		static std::shared_ptr<SkeletonWrapper> loadSkeletonWrapper(const char *skeletonDataStr, LuaIntf::LuaRef &unitData);
		static std::shared_ptr<SkeletonWrapper> loadSkeletonWrapperCache(std::string index);
		static void deleteSkeleton(SkeletonWrapper *skelWapper);
		//static void removeStatePair(std::size_t id);

		static std::shared_ptr<AnimationStateExtend> loadAnimationState(SkeletonWrapper *skeleton);
		static int getSkeleDataCacheSize() { return (int)_skeletonDataMap.size(); }

	private:
		static std::string insertSkeletonData(SkeletonData* data, std::string jsonStr) {
			std::lock_guard<std::mutex> guard(_skeletonDataMutex);
			std::string id = std::to_string(_dataIndex);
			_skeletonDataMap[id] = std::make_pair(data, std::move(jsonStr));
			_dataIndex++;
			return id;
		}

		static std::string insertSkeletonAndSkinData(SkeletonData* data, std::string jsonStr, std::string resId) {
			std::lock_guard<std::mutex> guard(_skeletonDataMutex);
			_skeletonDataMap[resId] = std::make_pair(data, std::move(jsonStr));
			return resId;
		}


		static SkeletonData* getSkeletonData(std::string id) {
			std::lock_guard<std::mutex> guard(_skeletonDataMutex);
			if (_skeletonDataMap.find(id) == _skeletonDataMap.end()) {
				return nullptr;
			}
			return _skeletonDataMap[id].first;
		}

		static const char* getSkeletonJsonStr(std::string id) {
			std::lock_guard<std::mutex> guard(_skeletonDataMutex);
			if (_skeletonDataMap.find(id) == _skeletonDataMap.end()) {
				return nullptr;
			}
			return _skeletonDataMap[id].second.c_str();
		}

		/*static bool removeSkeletonData(int index) {
			std::lock_guard<std::mutex> guard(_skeletonDataMutex);
			auto itor = _skeletonDataMap.find(index);
			if (itor == _skeletonDataMap.end()) {
				return false;
			}

			delete itor->second.first;
			_skeletonDataMap.erase(itor);
			return true;
		}
*/
		//animationState create depends on skeletonState
		/*static void insertSkeletonState(SkeletonExtend* skeleton)
		{
			std::lock_guard<std::mutex> guard(_skeletonStateMutex);
			_skeletonStateMap[skeleton->id] = std::make_pair(skeleton, nullptr);
		}*/

		/*static void insertAnimatonState(AnimationStateExtend* animation)
		{
			std::lock_guard<std::mutex> guard(_skeletonStateMutex);
			auto iter = _skeletonStateMap.find(animation->id);
			if (iter == _skeletonStateMap.end())
			{
				return;
			}

			iter->second.second = animation;
		}*/

	private:
		static std::mutex _skeletonStateMutex;
		static std::size_t _stateIndex;
		static std::mutex _skeletonDataMutex;
		static std::size_t _dataIndex;
		//static std::size_t _animationStateIndex;
		//static std::map<std::size_t, std::pair<SkeletonExtend*, AnimationStateExtend*>> _skeletonStateMap;
		static std::map<std::string, std::map<std::string, std::string>> _skinMap;
		static std::map<std::string, std::pair<SkeletonData*, std::string>> _skeletonDataMap;
		static SkeletonExtend *_loadSkeleton(const char *skeletonDataStr, LuaIntf::LuaRef &unitData, SkeletonObjectCreator &creator);
		static SkeletonExtend *_loadSkeletonBySkelData(SkeletonData* skeletonData, SkeletonObjectCreator &creator);
		static AnimationStateExtend *_loadAnimationState(SkeletonWrapper *skeleton, SkeletonObjectCreator &creator);
	};
}

#endif /* Skel_SkeletonLoader_h */

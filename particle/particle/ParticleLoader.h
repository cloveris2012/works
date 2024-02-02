#pragma once
#include <map>
#include <memory>
#include <mutex>
#include "EmitterData.h"

class ParticleLoader
{
public:
	ParticleLoader();
	~ParticleLoader();
	
	static std::mutex _particleDataMutex;
	static std::map<std::string, std::weak_ptr<EmitterData>> m_emitterDataMap;
	static std::shared_ptr<EmitterData> loadEmitterData(std::string id, LuaIntf::LuaRef emitterDataRef)
	{
		std::lock_guard<std::mutex> guard(_particleDataMutex);
		if (m_emitterDataMap.find(id) != m_emitterDataMap.end() && m_emitterDataMap[id].lock())
		{
			auto wp = m_emitterDataMap[id].lock();
			std::shared_ptr<EmitterData> emitterDataSp(wp);
			return emitterDataSp;
		}
		else
		{
			std::shared_ptr<EmitterData> emitterDataSp(new EmitterData(emitterDataRef));
			std::weak_ptr<EmitterData> emitterDataWp(emitterDataSp);
			m_emitterDataMap[id] = emitterDataWp;
			return emitterDataSp;
		}
	}
	static std::shared_ptr<EmitterData> getEmitterData(std::string id)
	{
		std::lock_guard<std::mutex> guard(_particleDataMutex);

		if (m_emitterDataMap.find(id) == m_emitterDataMap.end() || !m_emitterDataMap[id].lock())
			return{};
		else
		{
			if (auto wp = m_emitterDataMap[id].lock())
			{
				std::shared_ptr<EmitterData> emitterDataSp(wp);
				return emitterDataSp;
			}
		}
	}
};
#pragma once
#include <vector>
#include <map>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "FloatDistri.h"
#include "VectorDistri.h"
#include "ParticleEventData.h"

using jsonDoc = rapidjson::Document;
using jsonVal = rapidjson::Value;

enum ParticleEventType { eSpawn, eDeath, eCollision };

class ParticleEventGenerator
{
public:
	ParticleEventGenerator(jsonVal& generator);
	ParticleEventGenerator(ParticleEventGeneratorData* particleEventGeneratorData);
	~ParticleEventGenerator();
    
	const char* getName();
	int getFrequency();
	ParticleEventType getEventType();

private:
	const char* m_name;
	int m_frequency;
	ParticleEventType m_eventType;
};

class ParticleEventReceiver
{
public:
	ParticleEventReceiver(jsonVal& receiver);
	ParticleEventReceiver(ParticleEventReceiverData* particleEventReceiverData);
	~ParticleEventReceiver();

	const char* getName();

	jsonVal& getSpawnCountJsonObj();
	FloatDistriData* getSpawnCountDistriData();
	void setSpawnCount(FloatDistri* floatDistri);
	FloatDistri* getSpawnCount();
	bool getUseParticleTime();
	bool getUsePsysLocation();
	bool getInheritVal();
	jsonVal& getInheritScaleJsonObj();
	VectorDistriData* getInheritScaleDistriData();
	void setInheritScale(VectorDistri* vectorDistri);
	VectorDistri* getInheritScale();
	ParticleEventType getEventType();

private:
	const char* m_name;
	jsonVal m_spawnCountJsonObj;
	FloatDistriData* m_spawnCountDistriData;
	FloatDistri* m_spawnCount;
	bool m_useParticleTime;
	bool m_usePsysLocation;
	bool m_inheritVal;
	jsonVal m_inheritScaleJsonObj;
	VectorDistriData* m_inheritScaleDistriData;
	VectorDistri* m_inheritScale;
	ParticleEventType m_eventType;
};

class ParticleEvent
{
public:
	ParticleEvent(jsonDoc& eventObj);
	ParticleEvent(ParticleEventData* particleEventData);
	~ParticleEvent();

	std::vector<ParticleEventGenerator*> getGenerators();
	std::vector<ParticleEventReceiver*> getReceivers();
	int getGeneratorsCount();
	int getReceiversCount();
	//bool hasTypeGenerator(ParticleEventType eventType);
	//bool hasTypeReceiver(ParticleEventType eventType);
	ParticleEventGenerator* findGeneratorByName(std::string generatorName);
	ParticleEventReceiver* findReceiverByName(std::string recevierName);

private:
	std::vector<ParticleEventGenerator*> m_genList;
	std::vector<ParticleEventReceiver*> m_revList;
};


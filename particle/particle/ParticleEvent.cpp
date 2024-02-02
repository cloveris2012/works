#include "ParticleEvent.h"

ParticleEventGenerator::ParticleEventGenerator(jsonVal& generator)
{
	m_name = generator["name"].GetString();
	m_frequency = generator["frequency"].GetInt();
	m_eventType = (ParticleEventType)generator["eventType"].GetInt();
}
ParticleEventGenerator::ParticleEventGenerator(ParticleEventGeneratorData* particleEventGeneratorData)
{
	m_name = particleEventGeneratorData->m_name.c_str();
	m_frequency = particleEventGeneratorData->m_frequency;
	m_eventType = static_cast<ParticleEventType>(particleEventGeneratorData->m_eventType);
}
ParticleEventGenerator::~ParticleEventGenerator()
{
}

const char * ParticleEventGenerator::getName()
{
	return m_name;
}

int ParticleEventGenerator::getFrequency()
{
	return m_frequency;
}

ParticleEventType ParticleEventGenerator::getEventType()
{
	return m_eventType;
}

//==================================================================================================================

ParticleEventReceiver::ParticleEventReceiver(jsonVal& receiver)
{
	m_name = receiver["name"].GetString();
	m_eventType = (ParticleEventType)receiver["eventType"].GetInt();
	m_spawnCountJsonObj = receiver["spawnCount"];
	m_useParticleTime = receiver["useParticleTime"].GetBool();
	m_usePsysLocation = receiver["usePsysLocation"].GetBool();
	m_inheritVal = receiver["inheritVel"].GetBool();
	m_inheritScaleJsonObj = receiver["inheritVelScale"];
}

ParticleEventReceiver::ParticleEventReceiver(ParticleEventReceiverData* particleEventReceiverData)
{
	m_name = particleEventReceiverData->m_name.c_str();
	m_eventType = static_cast<ParticleEventType>(particleEventReceiverData->m_eventType);
	m_spawnCountDistriData = particleEventReceiverData->m_spawnCountDistriData;
	m_useParticleTime = particleEventReceiverData->m_useParticleTime;
	m_usePsysLocation = particleEventReceiverData->m_usePsysLocation;
	m_inheritVal = particleEventReceiverData->m_inheritVal;
	m_inheritScaleDistriData = particleEventReceiverData->m_inheritScaleDistriData;
	m_spawnCountJsonObj = "";
	m_inheritScaleJsonObj = "";
}



ParticleEventReceiver::~ParticleEventReceiver()
{
}

const char * ParticleEventReceiver::getName()
{
	return m_name;
}

jsonVal& ParticleEventReceiver::getSpawnCountJsonObj()
{
	return m_spawnCountJsonObj;
}

FloatDistriData* ParticleEventReceiver::getSpawnCountDistriData()
{
	return m_spawnCountDistriData;
}

void ParticleEventReceiver::setSpawnCount(FloatDistri * floatDistri)
{
	m_spawnCount = floatDistri;
}

FloatDistri* ParticleEventReceiver::getSpawnCount()
{
	return m_spawnCount;
}

bool ParticleEventReceiver::getUseParticleTime()
{
	return m_useParticleTime;
}

bool ParticleEventReceiver::getUsePsysLocation()
{
	return m_usePsysLocation;
}

bool ParticleEventReceiver::getInheritVal()
{
	return m_inheritVal;
}

jsonVal& ParticleEventReceiver::getInheritScaleJsonObj()
{
	return m_inheritScaleJsonObj;
}

VectorDistriData* ParticleEventReceiver::getInheritScaleDistriData()
{
	return m_inheritScaleDistriData;
}

void ParticleEventReceiver::setInheritScale(VectorDistri * vectorDistri)
{
	m_inheritScale = vectorDistri;
}

VectorDistri* ParticleEventReceiver::getInheritScale()
{
	return m_inheritScale;
}

ParticleEventType ParticleEventReceiver::getEventType()
{
	return m_eventType;
}

//==================================================================================================================

ParticleEvent::ParticleEvent(jsonDoc& eventObj)
{
	if (eventObj.HasMember("m_genEvent"))
	{
		jsonVal& generatorList = eventObj["m_genEvent"];

		if (generatorList.IsArray())
		{
			for (int i = 0; i < generatorList.Size(); i++)
			{
				jsonVal& generator = generatorList[i];
				ParticleEventGenerator* parGenerator = new ParticleEventGenerator(generator);
				m_genList.push_back(parGenerator);
			}
		}
	}

	if (eventObj.HasMember("m_recevEvent"))
	{
		jsonVal& receiverList = eventObj["m_recevEvent"];

		if (receiverList.IsArray())
		{
			for (int i = 0; i < receiverList.Size(); i++)
			{
				jsonVal& recevier = receiverList[i];
				ParticleEventReceiver* parRecevier = new ParticleEventReceiver(recevier);
				m_revList.push_back(parRecevier);
			}
		}
	}
}

ParticleEvent::ParticleEvent(ParticleEventData* particleEventData)
{
	for (int i = 0; i < particleEventData->m_generatorList.size(); i++)
	{
		auto generator = particleEventData->m_generatorList[i];
		ParticleEventGenerator* parGenerator = new ParticleEventGenerator(generator);
		m_genList.push_back(parGenerator);
	}

	for (int i = 0; i < particleEventData->m_receiverList.size(); i++)
	{
		auto recevier = particleEventData->m_receiverList[i];
		ParticleEventReceiver* parRecevier = new ParticleEventReceiver(recevier);
		m_revList.push_back(parRecevier);
	}
}


ParticleEvent::~ParticleEvent()
{
	for (int i = 0; i < m_genList.size(); i++)
	{
		auto event = m_genList[i];
		
		delete event;
	}

	m_genList.clear();

	for (int i = 0; i < m_revList.size(); i++)
	{
		auto event = m_revList[i];

		delete event;
	}
}

std::vector<ParticleEventGenerator*> ParticleEvent::getGenerators()
{
	return m_genList;
}

std::vector<ParticleEventReceiver*> ParticleEvent::getReceivers()
{
	return m_revList;
}

int ParticleEvent::getGeneratorsCount()
{
	return m_genList.size();
}

int ParticleEvent::getReceiversCount()
{
	return m_revList.size();
}

ParticleEventGenerator * ParticleEvent::findGeneratorByName(std::string generatorName)
{
	for (int i = 0; i < m_genList.size(); i++)
	{
		if (m_genList[i]->getName() == generatorName)
		{
			return m_genList[i];
		}
	}

	return NULL;
}

ParticleEventReceiver * ParticleEvent::findReceiverByName(std::string receiverName)
{
	for (int i = 0; i < m_revList.size(); i++)
	{
		if (m_revList[i]->getName() == receiverName)
		{
			return m_revList[i];
		}
	}

	return NULL;
}

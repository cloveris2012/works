#pragma once
#include "FloatDistriData.h"
#include "VectorDistriData.h"

typedef struct ParticleEventGeneratorData
{
	std::string m_name = "";
	int m_frequency = 1;
	int m_eventType = 1;
} ParticleEventGeneratorData;

typedef struct ParticleEventReceiverData
{
	std::string m_name = "";
	int m_eventType = 1;
	bool m_useParticleTime = false;
	bool m_usePsysLocation = false;
	bool m_inheritVal = false;
	FloatDistriData* m_spawnCountDistriData;
	VectorDistriData* m_inheritScaleDistriData;
} ParticleEventReceiverData;

typedef struct ParticleEventData
{
	std::vector<ParticleEventGeneratorData*> m_generatorList;
	std::vector<ParticleEventReceiverData*> m_receiverList;

} ParticleEventData;

#include "ParticleLoader.h"

std::mutex ParticleLoader::_particleDataMutex;
std::map<std::string, std::weak_ptr<EmitterData>> ParticleLoader::m_emitterDataMap;

ParticleLoader::ParticleLoader()
{
}

ParticleLoader::~ParticleLoader()
{
}



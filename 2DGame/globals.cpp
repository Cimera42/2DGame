#include "globals.h"
#include "logger.h"
#include <pthread.h>

bool shouldExit = false;

std::map<SystemID, System*> systems;
pthread_mutex_t entityMutex = PTHREAD_MUTEX_INITIALIZER;
std::map<EntityID, Entity*> entities;

void addEntity(Entity* inEntity)
{
    EntityID id = inEntity->getID();
    pthread_mutex_lock(&entityMutex);
    entities[id] = inEntity;
    pthread_mutex_unlock(&entityMutex);
}

void deleteEntities()
{
    std::vector<EntityID> toDelete;
    for(std::map<EntityID, Entity*>::iterator entityPair = entities.begin(); entityPair != entities.end(); ++entityPair)
    {
        toDelete.push_back(entityPair->first);
    }

    int entCount = 0;
    for(int i = 0; i < toDelete.size(); i++)
    {
        delete entities[toDelete[i]];
        Logger() << "Entity " << toDelete[i] << " deleted" << std::endl;
        entities.erase(toDelete[i]);
        entCount++;
    }
    Logger() << entCount << " entities deleted" << std::endl;
}

void deleteSystems()
{
    std::vector<SystemID> toDelete;
    for(std::map<SystemID, System*>::iterator systemPair = systems.begin(); systemPair != systems.end(); ++systemPair)
    {
        toDelete.push_back(systemPair->first);
    }

    int sysCount = 0;
    for(int i = 0; i < toDelete.size(); i++)
    {
        delete systems[toDelete[i]];
        Logger() << "System " << toDelete[i] << " deleted" << std::endl;
        systems.erase(toDelete[i]);
        sysCount++;
    }
    Logger() << sysCount << " systems deleted" << std::endl;
}

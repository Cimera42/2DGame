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
        Logger() << "Entity " << toDelete[i] << " deleted1" << std::endl;
    }
        Logger() << "Entityis" << " deleted2" << std::endl;
    Logger() << entCount << " entities deleted" << std::endl;
}

void deleteSystems()
{
    int sysCount = 0;
    for(std::map<SystemID, System*>::iterator systemPair = systems.begin(); systemPair != systems.end(); ++systemPair)
    {
        delete systemPair->second;
        Logger() << "System " << systemPair->first << " deleted" << std::endl;
        systems.erase(systemPair->first);
        sysCount++;
    }
    Logger() << sysCount << " systems deleted" << std::endl;
}

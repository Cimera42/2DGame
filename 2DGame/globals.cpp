#include "globals.h"
#include "logger.h"
#include <pthread.h>

bool shouldExit = false;
bool outputFPS = false;

std::unordered_map<SystemID, System*> systems;
std::unordered_map<ComponentID, Component*> components;
pthread_mutex_t entityMutex = PTHREAD_MUTEX_INITIALIZER;
std::unordered_map<EntityID, Entity*> entities;
std::vector<EntityID> entitiesToDelete;

void addEntity(Entity* inEntity)
{
    EntityID id = inEntity->getID();
    pthread_mutex_lock(&entityMutex);
    entities[id] = inEntity;
    pthread_mutex_unlock(&entityMutex);
}

void deleteEntity(EntityID inID)
{
    entitiesToDelete.push_back(inID);
}

void deleteFlaggedEntities()
{
    int entCount = 0;
    for(int i = 0; i < entitiesToDelete.size(); i++)
    {
        EntityID id = entitiesToDelete[i];
        unsubscribeToSystems(entities[id]);
        delete entities[id];
        Logger() << "Entity " << id << " deleted" << std::endl;
        entities.erase(id);
        entCount++;
    }
    if(entCount)
        Logger() << entCount << " entities deleted" << std::endl;
    std::vector<EntityID>().swap(entitiesToDelete);
}

void deleteAllEntities()
{
    std::vector<EntityID>().swap(entitiesToDelete);
    for(std::unordered_map<EntityID, Entity*>::iterator entityPair = entities.begin(); entityPair != entities.end(); ++entityPair)
    {
        entitiesToDelete.push_back(entityPair->first);
    }
    deleteFlaggedEntities();
}

void deleteAllSystems()
{
    std::vector<SystemID> toDelete;
    for(std::unordered_map<SystemID, System*>::iterator systemPair = systems.begin(); systemPair != systems.end(); ++systemPair)
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

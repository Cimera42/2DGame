#include "globals.h"
#include <iostream>

bool shouldExit = false;

std::map<SystemID, System*> systems;
std::map<EntityID, Entity*> entities;

void addEntity(Entity* inEntity)
{
    EntityID id = inEntity->getID();
    entities[id] = inEntity;
}

void deleteEntities()
{
    int entCount = 0;
    std::vector<EntityID> entityToErase;
    for(std::map<EntityID, Entity*>::iterator entityPair = entities.begin(); entityPair != entities.end(); ++entityPair)
    {
        delete entityPair->second;
        std::cout << "Entity " << entityPair->first << " deleted" << std::endl;
        entityToErase.push_back(entityPair->first);
        entCount++;
    }
    for (int i = 0; i < entityToErase.size(); i++)
        entities.erase(entityToErase[i]);
    std::cout << entCount << " entities deleted" << std::endl;
}

void deleteSystems()
{
    int sysCount = 0;
    std::vector<SystemID> systemToErase;
    for(std::map<SystemID, System*>::iterator systemPair = systems.begin(); systemPair != systems.end(); ++systemPair)
    {
        delete systemPair->second;
        std::cout << "System " << systemPair->first << " deleted" << std::endl;
        systemToErase.push_back(systemPair->first);
        sysCount++;
    }
    for (int i = 0; i < systemToErase.size(); i++)
        systems.erase(systemToErase[i]);
    std::cout << sysCount << " systems deleted" << std::endl;
}

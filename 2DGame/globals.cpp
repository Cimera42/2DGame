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
    for(std::map<EntityID, Entity*>::iterator entityPair = entities.begin(); entityPair != entities.end(); ++entityPair)
    {
        delete entityPair->second;
        std::cout << "Entity " << entityPair->first << " deleted" << std::endl;
        entities.erase(entityPair->first);
        entCount++;
    }
    std::cout << entCount << " entities deleted" << std::endl;
}

void deleteSystems()
{
    int sysCount = 0;
    for(std::map<SystemID, System*>::iterator systemPair = systems.begin(); systemPair != systems.end(); ++systemPair)
    {
        delete systemPair->second;
        std::cout << "System " << systemPair->first << " deleted" << std::endl;
        systems.erase(systemPair->first);
        sysCount++;
    }
    std::cout << sysCount << " systems deleted" << std::endl;
}

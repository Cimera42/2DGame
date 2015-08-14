#include "globals.h"

std::map<SystemID, System*> systems;
std::map<EntityID, Entity*> entities;

void addEntity(Entity* inEntity)
{
    EntityID id = inEntity->getID();
    entities[id] = inEntity;
}

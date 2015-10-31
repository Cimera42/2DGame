#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "entity.h"
#include "component.h"
#include "system.h"
#include <unordered_map>

extern bool shouldExit;
extern bool outputFPS;

extern std::unordered_map<SystemID, System*> systems;
extern std::unordered_map<ComponentID, Component*> components;
extern std::unordered_map<EntityID, Entity*> entities;

void addEntity(Entity*);
void deleteEntity(EntityID);
void deleteFlaggedEntities();
void deleteAllEntities();
void deleteAllSystems();

class Constants
{
public:
    static const float airDensity;
    static const float gravity;
};

#endif // GLOBALS_H_INCLUDED

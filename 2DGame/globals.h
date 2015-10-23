#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "entity.h"
#include "component.h"
#include "system.h"
#include <unordered_map>

extern bool shouldExit;

extern std::unordered_map<SystemID, System*> systems;
extern std::unordered_map<EntityID, Entity*> entities;

void addEntity(Entity*);
void deleteEntity(EntityID);
void deleteFlaggedEntities();
void deleteAllEntities();
void deleteAllSystems();

#endif // GLOBALS_H_INCLUDED

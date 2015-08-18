#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#define DEBUG 1

#include <map>
#include "entity.h"
#include "component.h"
#include "system.h"

extern bool shouldExit;

extern std::map<SystemID, System*> systems;
extern std::map<EntityID, Entity*> entities;

void addEntity(Entity*);
void deleteEntities();
void deleteSystems();

#endif // GLOBALS_H_INCLUDED

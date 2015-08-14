#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#define DEBUG 1

#include <map>
#include "entity.h"
#include "component.h"
#include "system.h"

typedef int SystemID;

extern std::map<SystemID, System*> systems;
extern std::map<EntityID, Entity*> entities;

void addEntity(Entity*);

#endif // GLOBALS_H_INCLUDED

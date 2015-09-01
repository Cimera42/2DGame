#include "system.h"
#include "entity.h"
#include "globals.h"

#include <map>
#include "logger.h"

SystemID System::systemIDIncrementor = 1;
SystemID System::ID;

System::System(){}
System::~System(){}
void System::update(){}

//Check if component is in list
bool System::checkComponent(ComponentID inCompID)
{
    for(int i = 0; i < componentSubList.size(); i++)
    {
        if(componentSubList[i] == inCompID)
            return true;
    }
    return false;
}

//Check if entity has all components required
bool System::checkEntityComponents(Entity* inEntity)
{
    for(int i = 0; i < componentSubList.size(); i++)
    {
        if(!inEntity->hasComponent(componentSubList[i]))
            return false;
    }
    return true;
}

//Check if entity is already subscribed to system
int System::checkEntityAlreadySubscribed(EntityID inEntID)
{
    for(int i = 0; i < subscribedEntities.size(); i++)
    {
        if(subscribedEntities[i] == inEntID)
            return i;
    }
    return -1;
}

bool System::subscribe(Entity* inEntity, ComponentID newCompID)
{
    //Check if newly added component is in list
    if(checkComponent(newCompID))
    {
        //Check if entity is already subscribed to system
        if(checkEntityAlreadySubscribed(inEntity->entityID) == -1)
        {
            //Check entity has all required components
            if(checkEntityComponents(inEntity))
            {
                subscribedEntities.push_back(inEntity->entityID);
                entitySubscribed(inEntity);

                if(DEBUG)
                    Logger() << "Entity " << inEntity->entityID << " subscribed to system " << getID() << std::endl;
                return true;
            }
        }
    }
    return false;
}

bool System::unsubscribe(Entity* inEntity, ComponentID oldCompID)
{
    //Check if newly removed component is in list
    if(checkComponent(oldCompID))
    {
        //Check if entity is already subscribed to system
        int subID = checkEntityAlreadySubscribed(inEntity->entityID);
        if(subID != -1)
        {
            subscribedEntities.erase(subscribedEntities.begin() + subID);
            entityUnsubscribed(inEntity);
            return true;
        }
    }
    return false;
}

//Attempt to subscribe entity to all systems
void subscribeToSystems(Entity* inEntity, ComponentID newCompID)
{
    //Attempt to subscribe entity to all systems
    for(std::map<SystemID,System*>::iterator systemPair = systems.begin(); systemPair != systems.end(); ++systemPair)
    {
        System* system = systemPair->second;

        system->subscribe(inEntity, newCompID);
    }
}

//Attempt to subscribe entity to all systems
void unsubscribeToSystems(Entity* inEntity, ComponentID oldCompID)
{
    //Attempt to subscribe entity to all systems
    for(std::map<SystemID,System*>::iterator systemPair = systems.begin(); systemPair != systems.end(); ++systemPair)
    {
        System* system = systemPair->second;

        system->unsubscribe(inEntity, oldCompID);
    }
}

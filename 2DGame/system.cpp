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

//Add list of components needed for subscription
void System::addSubList(std::vector<ComponentID> inList)
{
    componentSubList.push_back(inList);
    std::vector<EntityID> a;
    subscribedEntities.push_back(a);
}

//Check if component is in list
bool System::checkComponent(ComponentID inCompID, int listID)
{
    for(int i = 0; i < componentSubList[listID].size(); i++)
    {
        if(componentSubList[listID][i] == inCompID)
            return true;
    }
    return false;
}

//Check if entity has all components required
bool System::checkEntityComponents(Entity* inEntity, int listID)
{
    for(int i = 0; i < componentSubList[listID].size(); i++)
    {
        if(!inEntity->hasComponent(componentSubList[listID][i]))
            return false;
    }
    return true;
}

//Check if entity is already subscribed to system
int System::checkEntityAlreadySubscribed(EntityID inEntID, int listID)
{
    for(int i = 0; i < subscribedEntities[listID].size(); i++)
    {
        if(subscribedEntities[listID][i] == inEntID)
            return i;
    }
    return -1;
}

bool System::subscribe(Entity* inEntity, ComponentID newCompID)
{
    bool subbed = false;
    for(int i = 0; i < componentSubList.size(); i++)
    {
        //Check if newly added component is in list
        if(checkComponent(newCompID, i))
        {
            //Check if entity is already subscribed to system
            if(checkEntityAlreadySubscribed(inEntity->entityID, i) == -1)
            {
                //Check entity has all required components
                if(checkEntityComponents(inEntity, i))
                {
                    subscribedEntities[i].push_back(inEntity->entityID);
                    entitySubscribed(inEntity);

                    Logger() << "Entity " << inEntity->entityID << " subscribed to system " << getID() << std::endl;
                    subbed = true;
                }
            }
        }
    }
    return subbed;
}

bool System::unsubscribe(Entity* inEntity, ComponentID oldCompID)
{
    bool subbed = false;
    for(int i = 0; i < componentSubList.size(); i++)
    {
        //Check if newly removed component is in list
        if(checkComponent(oldCompID, i))
        {
            //Check if entity is already subscribed to system
            int subID = checkEntityAlreadySubscribed(inEntity->entityID, i);
            if(subID != -1)
            {
                subscribedEntities[i].erase(subscribedEntities[i].begin() + subID);
                entityUnsubscribed(inEntity);
                return true;
            }
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

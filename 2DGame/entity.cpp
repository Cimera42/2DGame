#include "entity.h"
#include "component.h"
#include "system.h"

#include <stdlib.h>

EntityID Entity::globalEntityIncrementorID = 0;
Entity::Entity()
{
    //Give entity unique id
    entityID = globalEntityIncrementorID++;
}
Entity::~Entity(){}

EntityID Entity::getID()
{
    return entityID;
}

//Add component to entity
bool Entity::addComponent(Component* inComponent)
{
    //Get id of component
    ComponentID compID = inComponent->getID();
    //Check if entity already has component
    if(!hasComponent(compID))
    {
        //Add component
        components[compID] = inComponent;
        //Subscribe to systems
        subscribeToSystems(this, compID);
        return true;
    }
    return false;
}

//Check if component exists in the list
bool Entity::hasComponent(ComponentID compID)
{
    return components.find(compID) != components.end();
}

//Check if component is available for use
bool Entity::canUseComponent(ComponentID compID)
{
    //Check if component exists
    if(hasComponent(compID))
    {
        //Check if component is enabled
        if(getComponent(compID)->enabled)
        {
            return true;
        }
    }
    return false;
}

//Get component from entity
Component* Entity::getComponent(ComponentID compID)
{
    //Check if component exists
    if(hasComponent(compID))
    {
        return components[compID];
    }
    return NULL;
}

//Delete component from entity
bool Entity::deleteComponent(ComponentID compID)
{
    //Check if component exists
    if(hasComponent(compID))
    {
        //Delete object
        delete components[compID];
        //Remove empty pointer from list of components
        components.erase(compID);
    }
    return false;
}

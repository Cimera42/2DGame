#include "impactTerrainSystem.h"
#include "globals.h"

#include "terrainComponent.h"
#include "worldComponent.h"
#include "tempplayerControlComponent.h"

//Unique system ID
SystemID ImpactTerrainSystem::ID;

ImpactTerrainSystem::ImpactTerrainSystem()
{
    std::vector<ComponentID> subList1;
    //Components needed to subscribe to system
    subList1.push_back(WorldComponent::getStaticID());
    subList1.push_back(TerrainComponent::getStaticID());
    addSubList(subList1);
}
ImpactTerrainSystem::~ImpactTerrainSystem(){}

void ImpactTerrainSystem::update()
{
    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        Entity * terrain = entities[subscribedEntities[0][subID]];
        //Get components
        TerrainComponent* terrainComp = static_cast<TerrainComponent*>(terrain->getComponent(TerrainComponent::getStaticID()));

        //Do translations to stop collisions
        for(int i = 0; i < terrainComp->collisionData.size(); i++)
        {
            Entity * collider = entities[terrainComp->collisionData[i]->collisionEntityID];
            WorldComponent * colWorld = static_cast<WorldComponent*>(collider->getComponent(WorldComponent::getStaticID()));
            //add the minimum translation/other info provided by the collision...
            colWorld->position.y+=2;
            if(!collider->hasComponent(PlayerControlComponent::getStaticID()))
                deleteEntity(collider->entityID);
        }
    }
}

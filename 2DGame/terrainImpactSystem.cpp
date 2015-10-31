#include "terrainImpactSystem.h"
#include "globals.h"

#include "colliderComponent.h"
#include "worldComponent.h"

#include "physicsComponent.h"
#include "terrainComponent.h"
#include "logger.h"

//Unique system ID
SystemID TerrainImpactSystem::ID;

TerrainImpactSystem::TerrainImpactSystem()
{
    std::vector<ComponentID> subList1;
    //Components needed to subscribe to system
    subList1.push_back(WorldComponent::getStaticID());
    subList1.push_back(TerrainComponent::getStaticID());
    addSubList(subList1);
}
TerrainImpactSystem::~TerrainImpactSystem(){}

void TerrainImpactSystem::update()
{
    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        //Get terrain component
        Entity * terrainEnt = entities[subscribedEntities[0][subID]];
        TerrainComponent* terrainComp = static_cast<TerrainComponent*>(terrainEnt->getComponent(TerrainComponent::getStaticID()));
        WorldComponent * terrainWorldComp = static_cast<WorldComponent*>(terrainEnt->getComponent(WorldComponent::getStaticID()));

        //Check projectile for collisions
        for(int i = 0; i < terrainComp->collisionData.size(); i++)
        {
            std::shared_ptr<CollisionPair> collision = terrainComp->collisionData[i];
            int terrainPairID = collision->getCollisionPairID(subscribedEntities[0][subID]);//Terrains's CollisionPairID
            int collidingPairID = collision->getOppositePairID(terrainPairID);//The Colliding Ent's CollisionPairID
            Entity * collidingEnt = entities[collision->getCollisionEntityID(collidingPairID)]; //The Colliding Entity

            //Check the type of the collided entity and perform action
            if(collidingEnt->hasComponent(PhysicsComponent::getStaticID()) && collidingEnt->hasComponent(ColliderComponent::getStaticID()))
            {
                glm::vec2 col = collision->getNormal(terrainPairID);
                PhysicsComponent* physicsComp = static_cast<PhysicsComponent*>(collidingEnt->getComponent(PhysicsComponent::getStaticID()));
                //apply an upwards impulse to keep object above ground
                float normalMag = glm::dot(physicsComp->velocity*physicsComp->mass,glm::normalize(col));
                float j = -(1+physicsComp->coefficientRestitution)*normalMag;
                float impulseMag = glm::max(j, 0.0f);
                physicsComp->impulse(impulseMag*glm::normalize(col));
                //apply friction
                /*glm::vec2 dir = -glm::normalize(col);
                glm::vec2 friction = 5.0f * normalMag * glm::vec2(-dir.y,dir.x);
                Logger()<<friction.x<<" "<<friction.y<<std::endl;
                physicsComp->force += friction;*/
            }
        }
    }
}

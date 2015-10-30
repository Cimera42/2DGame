#include "projectileCollideSystem.h"
#include "globals.h"

#include "colliderComponent.h"
#include "worldComponent.h"
#include "projectileComponent.h"

#include "physicsComponent.h"
#include "playerComponent.h"
#include "terrainComponent.h"
#include "logger.h"

//Unique system ID
SystemID ProjectileCollideSystem::ID;

ProjectileCollideSystem::ProjectileCollideSystem()
{
    std::vector<ComponentID> subList1;
    //Components needed to subscribe to system
    subList1.push_back(WorldComponent::getStaticID());
    subList1.push_back(ColliderComponent::getStaticID());
    subList1.push_back(ProjectileComponent::getStaticID());
    addSubList(subList1);
}
ProjectileCollideSystem::~ProjectileCollideSystem(){}

void ProjectileCollideSystem::update()
{
    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        //Get projectile component
        Entity * projectileEnt = entities[subscribedEntities[0][subID]];
        ColliderComponent* projectileCollideComp = static_cast<ColliderComponent*>(projectileEnt->getComponent(ColliderComponent::getStaticID()));
        WorldComponent * projectileWorldComp = static_cast<WorldComponent*>(projectileEnt->getComponent(WorldComponent::getStaticID()));
        PhysicsComponent* projectilePhysicsComp = static_cast<PhysicsComponent*>(projectileEnt->getComponent(PhysicsComponent::getStaticID()));

        //Check projectile for collisions
        for(int i = 0; i < projectileCollideComp->collisionData.size(); i++)
        {
            std::shared_ptr<CollisionPair> collision = projectileCollideComp->collisionData[i];
            int projectilePairID = collision->getCollisionPairID(subscribedEntities[0][subID]);//Projectile's CollisionPairID
            int collidingPairID = collision->getOppositePairID(projectilePairID);//The Colliding Ent's CollisionPairID
            Entity * collidingEnt = entities[collision->getCollisionEntityID(collidingPairID)]; //The Colliding Entity

            //Check the type of the collided entity and perform action
            if(collidingEnt->hasComponent(TerrainComponent::getStaticID()))
            {
                //deleteEntity(projectileEnt->entityID);
            }
            if(collidingEnt->hasComponent(PhysicsComponent::getStaticID()) && !collidingEnt->hasComponent(PlayerComponent::getStaticID()))
            {
                glm::vec2 col = collision->getMinimumTranslation(projectilePairID);
                PhysicsComponent* physicsComp = static_cast<PhysicsComponent*>(collidingEnt->getComponent(PhysicsComponent::getStaticID()));
                //Should 1. Be conserving energy
                //Should 2. Be making sure the velocity is transfered correctly
                //http://gafferongames.com/virtual-go/collision-response-and-coulomb-friction/
                float j = -(1+0)*glm::dot(projectilePhysicsComp->velocity*projectilePhysicsComp->mass,glm::normalize(col)); //projectiles impulse
                float impulseMag = glm::max(j, 0.0f);
                //Logger()<<impulseMag<<std::endl;
                physicsComp->impulse(impulseMag*glm::normalize(-col));
                projectilePhysicsComp->impulse(impulseMag*glm::normalize(col));
            }
        }
    }
}

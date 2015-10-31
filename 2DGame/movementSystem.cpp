#include "movementSystem.h"
#include <glm/glm.hpp>

#include "globals.h"
#include "own_funcs.h"
#include "worldComponent.h"
#include "physicsComponent.h"
#include "logger.h"

#include "playerComponent.h"

SystemID MovementSystem::ID;

MovementSystem::MovementSystem()
{
    std::vector<ComponentID> subList1;
    //Components needed to subscribe to system
    subList1.push_back(WorldComponent::getStaticID());
    subList1.push_back(PhysicsComponent::getStaticID());
    addSubList(subList1);
}
MovementSystem::~MovementSystem(){}

void MovementSystem::update(float inDelta)
{
    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[0][subID]];

        WorldComponent* worldComp = static_cast<WorldComponent*>(entity->getComponent(WorldComponent::getStaticID()));
        PhysicsComponent* movementComp = static_cast<PhysicsComponent*>(entity->getComponent(PhysicsComponent::getStaticID()));
        //gravity
        if(!movementComp->staticObject)
        {
            float gravityForce = movementComp->mass*Constants::gravity;
            movementComp->force += glm::vec2(0,-1) * gravityForce;
        }


        //air resistance
        if(movementComp->velocity.x != 0 || movementComp->velocity.y != 0)
        {
            //crosssectional area depends on shape. currently just use average of scale.x and scale.y
            float crossSection = (worldComp->scale.x+worldComp->scale.y)/2.0f;
            //force = 1/2(air density * v^2 (of object relative to air) * crosssectional area * drag coefficient
            glm::vec2 dragForce = -glm::normalize(movementComp->velocity) //direction
                                *0.5f*Constants::airDensity*(sq(movementComp->velocity.x)+sq(movementComp->velocity.y))*crossSection*movementComp->coefficientDrag; //magnitude
            movementComp->force += dragForce;
        }

        glm::vec2 lastAcceleration = movementComp->acceleration;
        worldComp->position += movementComp->velocity * inDelta + (0.5f * lastAcceleration * sq(inDelta));
        movementComp->acceleration = movementComp->force / movementComp->mass;
        glm::vec2 avg_acceleration = ( lastAcceleration + movementComp->acceleration ) / 2.0f;
        movementComp->velocity += avg_acceleration * inDelta;

        movementComp->force = glm::vec2(0,0);//reset force so we can recalculate for next frame
        if(entity->hasComponent(PlayerComponent::getStaticID()))
        {
            Logger()<<movementComp->velocity.x<<" "<<movementComp->velocity.y<<std::endl;
        }

        //Update matrix since position changed
        worldComp->updateMatrix();
    }
}

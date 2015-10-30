#include "movementSystem.h"
#include <glm/glm.hpp>

#include "globals.h"
#include "own_funcs.h"
#include "worldComponent.h"
#include "physicsComponent.h"
#include "logger.h"

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

        //force = 1/2(air density * v^2 (of object relative to air) * crosssectional area * drag coefficient
        movementComp->velocity *= glm::pow(movementComp->coefficientDrag, inDelta); //Some form of proper deceleration should be part of a force*/
        /*float airResistance = (1.225*(sq(movementComp->velocity.x)+sq(movementComp->velocity.y))*1*movementComp->coefficientDrag)/2;
        Logger()<<movementComp->velocity.x<<" "<<movementComp->velocity.y<<std::endl;
        if(movementComp->velocity.x != 0 && movementComp->velocity.y != 0) //quick fix for 0 length vector
            movementComp->force -= airResistance*glm::normalize(movementComp->velocity);*/

        movementComp->lastAcceleration = movementComp->acceleration;
        worldComp->position += movementComp->velocity * inDelta + (0.5f * movementComp->lastAcceleration * sq(inDelta));
        movementComp->acceleration = movementComp->force / movementComp->mass;
        glm::vec2 avg_acceleration = ( movementComp->lastAcceleration + movementComp->acceleration ) / 2.0f;
        movementComp->velocity += avg_acceleration * inDelta;

        //Update matrix since position changed
        worldComp->updateMatrix();
    }
}

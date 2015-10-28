#include "motionSystem.h"
#include <glm/glm.hpp>

#include "globals.h"
#include "worldComponent.h"
#include "motionComponent.h"

SystemID MotionSystem::ID;

MotionSystem::MotionSystem()
{
    std::vector<ComponentID> subList1;
    //Components needed to subscribe to system
    subList1.push_back(WorldComponent::getStaticID());
    subList1.push_back(MotionComponent::getStaticID());
    addSubList(subList1);
}
MotionSystem::~MotionSystem(){}

void MotionSystem::update(float inDelta)
{
    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[0][subID]];

        WorldComponent* worldComp = static_cast<WorldComponent*>(entity->getComponent(WorldComponent::getStaticID()));
        MotionComponent* motionComp = static_cast<MotionComponent*>(entity->getComponent(MotionComponent::getStaticID()));

        motionComp->velocity += motionComp->acceleration * inDelta;
        //motionComp->acceleration *= motionComp->drag;
        worldComp->position += motionComp->velocity * inDelta;
        motionComp->velocity *= glm::pow(motionComp->drag, inDelta); //Some form of proper deceleration
        //Update matrix since position changed
        worldComp->updateMatrix();
    }
}

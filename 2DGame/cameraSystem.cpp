#include "cameraSystem.h"

#include "globals.h"
#include "worldComponent.h"
#include "cameraComponent.h"

SystemID CameraSystem::ID;

CameraSystem::CameraSystem()
{
    std::vector<ComponentID> subList1;
    //Components needed to subscribe to system
    subList1.push_back(WorldComponent::getStaticID());
    subList1.push_back(CameraComponent::getStaticID());
    addSubList(subList1);

    activeCamera = -1;
}
CameraSystem::~CameraSystem(){}

void CameraSystem::entitySubscribed(Entity* inEntity, int listID)
{
    CameraComponent* cameraComp = static_cast<CameraComponent*>(inEntity->getComponent(CameraComponent::getStaticID()));

    if(cameraComp->activeFlag)
    {
        setActiveCamera(inEntity->entityID);
    }
}

void CameraSystem::update()
{
    if(activeCamera == -1)
    {
        if(subscribedEntities[0].size())
        {
            setActiveCamera(subscribedEntities[0][0]);
        }
    }
    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[0][subID]];

        WorldComponent* worldComp = static_cast<WorldComponent*>(entity->getComponent(WorldComponent::getStaticID()));
        CameraComponent* cameraComp = static_cast<CameraComponent*>(entity->getComponent(CameraComponent::getStaticID()));

        cameraComp->jointMatrix = cameraComp->projectionMatrix * glm::inverse(worldComp->modelMatrix);
    }
}

void CameraSystem::setActiveCamera(EntityID inEntityID)
{
    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[0][subID]];

        CameraComponent* cameraComp = static_cast<CameraComponent*>(entity->getComponent(CameraComponent::getStaticID()));

        if(inEntityID == entity->entityID)
        {
            cameraComp->activeFlag = true;
            activeCamera = entity->entityID;
        }
        else
        {
            cameraComp->activeFlag = false;
        }
    }
}

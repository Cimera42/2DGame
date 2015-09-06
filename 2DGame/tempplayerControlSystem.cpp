#include "tempplayerControlSystem.h"
#include "globals.h"
#include "openGLFunctions.h"

#include "windowComponent.h"
#include "worldComponent.h"
#include "tempplayerControlComponent.h"

SystemID PlayerControlSystem::ID;

PlayerControlSystem::PlayerControlSystem()
{
    std::vector<ComponentID> subList1;
    //Components needed to subscribe to system
    subList1.push_back(WorldComponent::getStaticID());
    subList1.push_back(PlayerControlComponent::getStaticID());
    addSubList(subList1);
}
PlayerControlSystem::~PlayerControlSystem(){}

void PlayerControlSystem::update()
{
    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[0][subID]];

        WorldComponent* worldComp = static_cast<WorldComponent*>(entity->getComponent(WorldComponent::getStaticID()));
        PlayerControlComponent* controlComp = static_cast<PlayerControlComponent*>(entity->getComponent(PlayerControlComponent::getStaticID()));

        //Check each key
        if(glfwGetKey(mainWindow->glfwWindow, controlComp->upKey) == GLFW_PRESS)
        {
            worldComp->position.y += controlComp->speed;
        }
        if(glfwGetKey(mainWindow->glfwWindow, controlComp->downKey) == GLFW_PRESS)
        {
            worldComp->position.y -= controlComp->speed;
        }
        if(glfwGetKey(mainWindow->glfwWindow, controlComp->leftKey) == GLFW_PRESS)
        {
            worldComp->position.x -= controlComp->speed;
        }
        if(glfwGetKey(mainWindow->glfwWindow, controlComp->rightKey) == GLFW_PRESS)
        {
            worldComp->position.x += controlComp->speed;
        }
        //Update matrix since position changed
        worldComp->updateMatrix();
    }
}

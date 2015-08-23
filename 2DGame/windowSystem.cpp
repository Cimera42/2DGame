#include "windowSystem.h"
#include "globals.h"

#include <iostream>
#include "windowComponent.h"
#include "openGLFunctions.h"

SystemID WindowSystem::ID;

WindowSystem::WindowSystem()
{
    componentSubList.push_back(WindowComponent::getStaticID());
}
WindowSystem::~WindowSystem(){}

void WindowSystem::update()
{
    for(int subID = 0; subID < subscribedEntities.size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[subID]];

        WindowComponent* windowComp = static_cast<WindowComponent*>(entity->getComponent(WindowComponent::getStaticID()));
        glfwSwapBuffers(windowComp->glfwWindow);
    }

    glfwSwapBuffers(mainWindow->glfwWindow);
}

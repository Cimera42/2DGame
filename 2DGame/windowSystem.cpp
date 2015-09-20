#include "windowSystem.h"
#include "globals.h"

#include <iostream>
#include "windowComponent.h"
#include "openGLFunctions.h"
#include "keyboardHandler.h"

SystemID WindowSystem::ID;

WindowSystem::WindowSystem()
{
    std::vector<ComponentID> subList1;
    //Components needed to subscribe to system
    subList1.push_back(WindowComponent::getStaticID());
    addSubList(subList1);
}
WindowSystem::~WindowSystem(){}

void WindowSystem::update()
{
    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[0][subID]];

        WindowComponent* windowComp = static_cast<WindowComponent*>(entity->getComponent(WindowComponent::getStaticID()));
        glfwSwapBuffers(windowComp->glfwWindow);
    }

    if(isKeyPressed(GLFW_KEY_ESCAPE))
        shouldExit = true;
    glfwSwapBuffers(mainWindow->glfwWindow);
}

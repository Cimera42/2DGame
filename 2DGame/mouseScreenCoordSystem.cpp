#include "mouseScreenCoordSystem.h"
#include "globals.h"
#include "openGLFunctions.h"

#include "mouseHandler.h"

#include "windowComponent.h"
#include "worldComponent.h"
#include "cameraComponent.h"
#include "cameraSystem.h"

#include "logger.h"

SystemID MouseScreenCoordSystem::ID;

MouseScreenCoordSystem::MouseScreenCoordSystem(){}
MouseScreenCoordSystem::~MouseScreenCoordSystem(){}

void MouseScreenCoordSystem::update()
{
    if(mouseData.processed == false)
    {
        WindowComponent* window = static_cast<WindowComponent*>(mainWindow);
        mouseData.xScreenCoord = 2*mouseData.xScreenPos / window->windowSize.x-1;
        mouseData.yScreenCoord = (1-2*mouseData.yScreenPos / window->windowSize.y);

        mouseData.xScreenCoordChange = 2*mouseData.xScreenChange / window->windowSize.x;
        mouseData.yScreenCoordChange = 1-2*mouseData.yScreenChange / window->windowSize.y;

        mouseData.processed = true;
    }
    else
    {
        mouseData.xScreenChange = 0;
        mouseData.yScreenChange = 0;

        mouseData.xScreenCoordChange = 0;
        mouseData.yScreenCoordChange = 0;

        mouseData.xWorldCoordChange = 0;
        mouseData.yWorldCoordChange = 0;
    }

    CameraSystem* cameraSys = static_cast<CameraSystem*>(systems[CameraSystem::getStaticID()]);
    if(cameraSys->activeCamera != -1)
    {
        WorldComponent* worldComp = static_cast<WorldComponent*>(entities[cameraSys->activeCamera]->getComponent(WorldComponent::getStaticID()));
        CameraComponent* cameraComp = static_cast<CameraComponent*>(entities[cameraSys->activeCamera]->getComponent(CameraComponent::getStaticID()));
        mouseData.xWorldCoord = worldComp->position.x + mouseData.xScreenCoord*cameraComp->zoom;
        mouseData.yWorldCoord = worldComp->position.y + mouseData.yScreenCoord*cameraComp->zoom;

        mouseData.xWorldCoordChange = mouseData.xScreenChange*cameraComp->zoom;
        mouseData.yWorldCoordChange = mouseData.yScreenChange*cameraComp->zoom;

        mouseData.processed = true;
    }

}

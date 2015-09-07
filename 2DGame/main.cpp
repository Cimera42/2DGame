#include "main.h"
#include "globals.h"
#include "entity.h"
#include "component.h"
#include "system.h"
#include "store.h"
#include "loader.h"

#include "openGLFunctions.h"

#include "worldComponent.h"
#include "windowSystem.h"
#include "windowComponent.h"
#include "render2DSystem.h"
#include "render2DComponent.h"
#include "sceneStore.h"
#include "textureStore.h"
#include "terrainComponent.h"
#include "renderTerrainSystem.h"
#include "tempplayerControlSystem.h"
#include "cameraSystem.h"

#include <iostream>
#include <string>
#include <fstream>

int main()
{
    initGLFW();
    initGLEW();

    //Temporary loading place for systems
    systems[WindowSystem::getStaticID()] = new WindowSystem();
    systems[RenderTerrainSystem::getStaticID()] = new RenderTerrainSystem();
    systems[Render2DSystem::getStaticID()] = new Render2DSystem();
    systems[PlayerControlSystem::getStaticID()] = new PlayerControlSystem();
    systems[CameraSystem::getStaticID()] = new CameraSystem();

    //File loading TEST
    SceneStore * scene;
    if(Load<SceneStore>::Object(&scene, "debug/scene.store"))
    {
        int fps = 0;
        double now = glfwGetTime();
        glClearColor(0.55f,0.65f,0.8f,1.0f);
        while(!shouldExit && !glfwGetKey(mainWindow->glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //Temporary system loop
            //Player movement system
            systems[PlayerControlSystem::getStaticID()]->update();
            //Camera matrix calculation system
            systems[CameraSystem::getStaticID()]->update();
            //Terrain rendering system
            systems[RenderTerrainSystem::getStaticID()]->update();
            //2D rendering system
            systems[Render2DSystem::getStaticID()]->update();
            //Should go last, since it updates window buffer
            systems[WindowSystem::getStaticID()]->update();

            glfwPollEvents();

            //Simple fps counter
            fps++;
            if(glfwGetTime() > now + 1.0f)
            {
                Logger() << fps << std::endl;
                now = glfwGetTime();
                fps = 0;
            }
        }

        deleteEntities();
        deleteSystems();
        glfwTerminate();
    }
    return 0;
}

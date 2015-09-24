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
#include "mouseScreenCoordSystem.h"
#include "motionSystem.h"
#include "colliderComponent.h"
#include "collisionSystem.h"
#include "impactTerrainSystem.h"

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
    systems[MouseScreenCoordSystem::getStaticID()] = new MouseScreenCoordSystem();
    systems[MotionSystem::getStaticID()] = new MotionSystem();
    systems[CollisionSystem::getStaticID()] = new CollisionSystem();
    systems[ImpactTerrainSystem::getStaticID()] = new ImpactTerrainSystem();

    //File loading TEST
    SceneStore * scene;
    if(Load<SceneStore>::Object(&scene, "debug/scene.store"))
    {
        int fps = 0;
        double now = glfwGetTime();
        float delta = 0;
        float lastFrame = glfwGetTime();

        glClearColor(0.55f,0.65f,0.8f,1.0f);
        while(!shouldExit)
        {
            delta = (glfwGetTime() - lastFrame);
            lastFrame = glfwGetTime();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //Temporary system loop
            //System to transform mouse movement to different spaces
            systems[MouseScreenCoordSystem::getStaticID()]->update();
            //Player movement system
            systems[PlayerControlSystem::getStaticID()]->update(delta);
            //Motion addition system
            systems[MotionSystem::getStaticID()]->update(delta);
            //Collision system
            systems[CollisionSystem::getStaticID()]->update();
            //Impact systems and final updating
            systems[ImpactTerrainSystem::getStaticID()]->update();
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
                Logger() << "Frametime:" << 1000.0f/fps << " FPS:" << fps << std::endl;
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

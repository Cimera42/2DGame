#include "main.h"
#include "globals.h"
#include "entity.h"
#include "component.h"
#include "system.h"
#include "store.h"
#include "loader.h"

#include "openGLFunctions.h"

#include "windowSystem.h"
#include "render2DSystem.h"
#include "sceneStore.h"
#include "textureStore.h"
#include "renderTerrainSystem.h"
#include "tempplayerControlSystem.h"
#include "cameraSystem.h"
#include "mouseScreenCoordSystem.h"
#include "movementSystem.h"
#include "collisionSystem.h"
#include "projectileCollideSystem.h"
#include "terrainImpactSystem.h"
#include "consoleSystem.h"

#include "cameraComponent.h"
#include "colliderComponent.h"
#include "physicsComponent.h"
#include "render2DComponent.h"
#include "tempplayerControlComponent.h"
#include "terrainComponent.h"
#include "windowComponent.h"
#include "worldComponent.h"
#include "playerComponent.h"
#include "projectileComponent.h"
#include "lifetimeComponent.h"

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
    systems[MovementSystem::getStaticID()] = new MovementSystem();
    systems[CollisionSystem::getStaticID()] = new CollisionSystem();
    systems[ProjectileCollideSystem::getStaticID()] = new ProjectileCollideSystem();
    systems[TerrainImpactSystem::getStaticID()] = new TerrainImpactSystem();
    systems[ConsoleSystem::getStaticID()] = new ConsoleSystem();

    components[CameraComponent::getStaticID()] = new CameraComponent();
    components[ColliderComponent::getStaticID()] = new ColliderComponent();
    components[PhysicsComponent::getStaticID()] = new PhysicsComponent();
    components[Render2DComponent::getStaticID()] = new Render2DComponent();
    components[PlayerControlComponent::getStaticID()] = new PlayerControlComponent();
    components[TerrainComponent::getStaticID()] = new TerrainComponent();
    components[WindowComponent::getStaticID()] = new WindowComponent();
    components[WorldComponent::getStaticID()] = new WorldComponent();
    components[PlayerComponent::getStaticID()] = new PlayerComponent();
    components[ProjectileComponent::getStaticID()] = new ProjectileComponent();
    components[LifetimeComponent::getStaticID()] = new LifetimeComponent();

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
            systems[MovementSystem::getStaticID()]->update(delta);
            //Collision system
            systems[CollisionSystem::getStaticID()]->update();
            //Impact systems and final updating
            systems[ProjectileCollideSystem::getStaticID()]->update();
            systems[TerrainImpactSystem::getStaticID()]->update();
            //Camera matrix calculation system
            systems[CameraSystem::getStaticID()]->update();
            //Terrain rendering system
            systems[RenderTerrainSystem::getStaticID()]->update();
            //2D rendering system
            systems[Render2DSystem::getStaticID()]->update();
            //Should go last, since it updates window buffer
            systems[WindowSystem::getStaticID()]->update();
            //Command console
            systems[ConsoleSystem::getStaticID()]->update();

            //To be done per frame
            //to remove all entities
            //flagged for deletion
            deleteFlaggedEntities();

            glfwPollEvents();

            //Simple fps counter
            fps++;
            if(glfwGetTime() > now + 1.0f)
            {
                if(outputFPS)
                    Logger() << "Frametime:" << 1000.0f/fps << " FPS:" << fps << std::endl;
                now = glfwGetTime();
                fps = 0;
            }
        }

        deleteAllEntities();
        deleteAllSystems();
        glfwTerminate();
    }
    return 0;
}

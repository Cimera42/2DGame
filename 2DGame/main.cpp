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
#include "textureLoadSystem.h"

#include <iostream>
#include <string>
#include <fstream>

System * winSys;
System * renSys;
System * texLoadSys;

int main()
{
    initGLFW();
    initGLEW();

    winSys = new WindowSystem();
    systems[WindowSystem::getStaticID()] = winSys;
    renSys = new Render2DSystem();
    systems[Render2DSystem::getStaticID()] = renSys;
    texLoadSys = new TextureLoadSystem();
    systems[TextureLoadSystem::getStaticID()] = texLoadSys;

    //File loading TEST
    SceneStore * scene;
    if(Load<SceneStore>::Object(&scene, "debug/scene.store"))
    {
        Entity * testEnt = new Entity();
        addEntity(testEnt);
        testEnt->addComponent(new WorldComponent(glm::vec2(0.0f,0.0f)));
        testEnt->addComponent(new Render2DComponent(1,1));

        glClearColor(0.55f,0.65f,0.7f,1.0f);
        while(!shouldExit)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //Temporary system loop
            //Texture loading system
            systems[TextureLoadSystem::getStaticID()]->update();
            //2D rendering system
            systems[Render2DSystem::getStaticID()]->update();
            //Should go last, since it updates window buffer
            systems[WindowSystem::getStaticID()]->update();

            glfwPollEvents();
        }

        deleteEntities();
        deleteSystems();
        glfwTerminate();
    }
    return 0;
}

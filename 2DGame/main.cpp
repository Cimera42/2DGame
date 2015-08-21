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

#include <iostream>
#include <string>
#include <fstream>

#include <pthread.h>

System * winSys;
System * renSys;

int main()
{
    glfwInit();
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
            //2D rendering system
            renSys->update();
            //Should go last, since it updates window buffer
            winSys->update();

            glfwPollEvents();
        }

        deleteEntities();
        deleteSystems();
        glfwTerminate();
    }
    return 0;
}

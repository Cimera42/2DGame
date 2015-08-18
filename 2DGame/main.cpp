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

int main()
{
    //File loading TEST
    SceneStore * scene;
    float r = 0.55f;
    float g = 0.65f;
    float b = 0.7f;
    int winWidth = 800;
    int winHeight = 450;
    if(Load<SceneStore>::Object(&scene, "debug/fileLoaderTest.txt"))
    {
        std::cout<<"Test Chunks: "<<scene->amountOfElements<<std::endl;
        std::cout<<scene->sceneBlock->elements[1]->properties[0]->values[0]<<"\n"<<std::endl;

        r = std::atof(scene->sceneBlock->elements[0]->properties[0]->values[0].c_str());
        g = std::atof(scene->sceneBlock->elements[0]->properties[0]->values[1].c_str());
        b = std::atof(scene->sceneBlock->elements[0]->properties[0]->values[2].c_str());

        winWidth = std::atoi(scene->sceneBlock->elements[0]->properties[1]->values[0].c_str());
        winHeight = std::atoi(scene->sceneBlock->elements[0]->properties[1]->values[1].c_str());
    }

    WindowComponent* win = new WindowComponent("2D Game Window", winWidth, winHeight);
    //GL must be initialised after a window is created
    initGL();

    //Temporary system init
    System * winSys = new WindowSystem();
    systems[WindowSystem::getStaticID()] = winSys;
    System * renSys = new Render2DSystem();
    systems[Render2DSystem::getStaticID()] = renSys;

    Entity * ent = new Entity();
    addEntity(ent);
    ent->addComponent(win);

    Entity * testEnt = new Entity();
    addEntity(testEnt);
    testEnt->addComponent(new WorldComponent(glm::vec2(0.0f,0.0f)));
    testEnt->addComponent(new Render2DComponent(1,1));

    glClearColor(r,g,b,1.0f);
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
    return 0;
}

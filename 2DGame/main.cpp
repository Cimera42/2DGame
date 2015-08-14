#include "main.h"
#include "globals.h"
#include "entity.h"
#include "component.h"
#include "system.h"
#include "store.h"
#include "loader.h"

#include "testSystem.h"
#include "testComponent.h"
#include "sceneStore.h"

#include <iostream>

int main()
{
    //File loading TEST
    SceneStore * scene;
    if(Load<SceneStore>::Object(&scene, "debug/fileLoaderTest.txt"))
    {
        std::cout<<"Test Chunks: "<<scene->amountOfElements<<std::endl;
        std::cout<<scene->sceneBlock->elements[1]->properties[0]->values[0]<<"\n"<<std::endl;
    }

    //ECS TEST
    System * sys = new System();
    systems[System::getStaticID()] = sys;
    System * testSys = new TestSystem();
    systems[TestSystem::getStaticID()] = testSys;

    std::cout << "Static: " << System::getStaticID() << " Standard: " << sys->getID() << std::endl;
    std::cout << "Static: " << TestSystem::getStaticID() << " Standard: " << testSys->getID() << std::endl;

    Entity * ent = new Entity();
    addEntity(ent);
    ent->addComponent(new TestComponent());

    Entity * testEnt = new Entity();
    addEntity(testEnt);
    testEnt->addComponent(new TestComponent());

    sys->update();
    testSys->update();

    return 0;
}

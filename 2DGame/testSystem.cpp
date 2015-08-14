#include "testSystem.h"
#include "globals.h"

#include <iostream>
#include "testComponent.h"

SystemID TestSystem::ID;

TestSystem::TestSystem()
{
    //componentSubList.push_back(TestComponent::getStaticID());
}
TestSystem::~TestSystem(){std::cout << "detroyed" << std::endl;}

void TestSystem::update()
{
    std::cout << "Test System updated" << std::endl;

    for(int subID = 0; subID < subscribedEntities.size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[subID]];

        std::cout << "Entity " << entity->getID() << " is subscribed to Test System" << std::endl;
    }
}

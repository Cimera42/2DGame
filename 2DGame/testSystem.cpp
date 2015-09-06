#include "testSystem.h"
#include "globals.h"

#include "testComponent.h"
#include "logger.h"

SystemID TestSystem::ID;

TestSystem::TestSystem()
{
    //componentSubList.push_back(TestComponent::getStaticID());
}
TestSystem::~TestSystem(){Logger() << "detroyed" << std::endl;}

void TestSystem::update()
{
    Logger() << "Test System updated" << std::endl;

    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[0][subID]];

        Logger() << "Entity " << entity->getID() << " is subscribed to Test System" << std::endl;
    }
}

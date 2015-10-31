#include "tempplayerControlSystem.h"
#include "globals.h"
#include "openGLFunctions.h"

#include "keyboardHandler.h"
#include "mouseHandler.h"
#include "render2DComponent.h"

#include "worldComponent.h"
#include "physicsComponent.h"
#include "projectileComponent.h"
#include "tempplayerControlComponent.h"
#include "colliderComponent.h"
#include "own_funcs.h"

SystemID PlayerControlSystem::ID;

PlayerControlSystem::PlayerControlSystem()
{
    std::vector<ComponentID> subList1;
    //Components needed to subscribe to system
    subList1.push_back(WorldComponent::getStaticID());
    subList1.push_back(PlayerControlComponent::getStaticID());
    addSubList(subList1);
}
PlayerControlSystem::~PlayerControlSystem(){}

float countDown = 0.0f;
void PlayerControlSystem::update(float inDelta)
{
    for(int subID = 0; subID < subscribedEntities[0].size(); subID++)
    {
        Entity * entity = entities[subscribedEntities[0][subID]];

        WorldComponent* worldComp = static_cast<WorldComponent*>(entity->getComponent(WorldComponent::getStaticID()));
        PlayerControlComponent* controlComp = static_cast<PlayerControlComponent*>(entity->getComponent(PlayerControlComponent::getStaticID()));

        glm::vec2 moveDir = glm::vec2(0,0);
        //Check each key
        if(isKeyPressed(controlComp->upKey))
        {
            moveDir.y += 1;
        }
        if(isKeyPressed(controlComp->downKey))
        {
            moveDir.y -= 1;
        }
        if(isKeyPressed(controlComp->leftKey))
        {
            moveDir.x -= 1;
        }
        if(isKeyPressed(controlComp->rightKey))
        {
            moveDir.x += 1;
        }
        if(moveDir.x != 0 && moveDir.y != 0)
            moveDir = glm::normalize(moveDir);

        moveDir = rotateVec2(moveDir, toRad(worldComp->rotation));

        if(entity->canUseComponent(PhysicsComponent::getStaticID()))
        {
            PhysicsComponent* motionComp = static_cast<PhysicsComponent*>(entity->getComponent(PhysicsComponent::getStaticID()));

            motionComp->impulse(moveDir * controlComp->speed * inDelta);
        }
        else
        {
            worldComp->position += moveDir * controlComp->speed * inDelta;//bad!
            worldComp->updateMatrix();
        }

        //Temporary projectile testing
        if(subID == 0)
        {
            if(isButtonPressed(GLFW_MOUSE_BUTTON_1) && countDown <= 0)
            {
                glm::vec2 direction = glm::vec2(mouseData.xWorldCoord,mouseData.yWorldCoord) - worldComp->position;
                glm::vec2 dirNorm = glm::normalize(direction);

                Entity* projectile = new Entity();
                projectile->vanityName = "Projectile";
                addEntity(projectile);
                projectile->addComponent((new ProjectileComponent())->construct());
                projectile->addComponent((new WorldComponent())->construct(glm::vec2(worldComp->position.x,worldComp->position.y), glm::vec2(0.5,0.5), atan2(dirNorm.y, dirNorm.x) * 180/3.1415));
                projectile->addComponent((new Render2DComponent())->construct(glm::vec2(0.875,0), glm::vec2(0.125,0.125)));
                projectile->addComponent((new ColliderComponent())->construct("box", "all", glm::vec2(0,0), 1,1));

                PhysicsComponent* motion = (new PhysicsComponent())->construct(0.5, 0.5, 0.04f);
                motion->velocity = dirNorm * 20.0f;
                projectile->addComponent(motion);

                countDown = 0.3f;
            }
            if(countDown >= 0)
            {
                countDown -= inDelta;
            }
        }
    }
}

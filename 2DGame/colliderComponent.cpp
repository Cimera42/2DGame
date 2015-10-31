#include "colliderComponent.h"
#include "logger.h"

ComponentID ColliderComponent::ID;

ColliderComponent::ColliderComponent(){vanityName = "Collider Component";}
ColliderComponent::~ColliderComponent(){}
ColliderComponent* ColliderComponent::construct(std::string inType, std::string inCollisionType, glm::vec2 inOffsetPos, float inWidth, float inHeight)
{
    offsetPos = inOffsetPos;
    heightY = inHeight;
    widthX = inWidth;
    if (inType == "capsule")
        type = 1;
    else if (inType == "circle")
        type = 2;
    else if (inType == "box")
        type = 0;
    else
        type = 0;

    if (inCollisionType == "terrain" || inCollisionType == "terrains")
        collisionType = 0;
    else if (inCollisionType == "objects" || inCollisionType == "object")
        collisionType = 1;
    else if (inCollisionType == "all")
        collisionType = 2;
    else
        collisionType = 2;

    return this;
}
ColliderComponent* ColliderComponent::construct(std::vector<std::string> inArgs)
{
    return this;
}

CollisionPair::CollisionPair(int inCollisionEntityID, int inCollisionEntityID2)
{
    collisionEntityOne = inCollisionEntityID;
    collisionEntityTwo = inCollisionEntityID2;
}
CollisionPair::~CollisionPair(){}

int CollisionPair::getCollisionPairID(int entityID)
{
    if(entityID == collisionEntityOne)
        return 1;
    else if(entityID == collisionEntityTwo)
        return 2;
    else
    {
        Logger()<<"Error in getCollisionPairID: No entity found - returning 0"<<std::endl;
        return 0;
    }
}

int CollisionPair::getCollisionEntityID(int pairID)
{
    if(pairID == 1)
        return collisionEntityOne;
    else if (pairID == 2)
        return collisionEntityTwo;
    else
    {
        Logger()<<"Error in getCollisionEntityID: No entity found - returning 0"<<std::endl;
        return 0;
    }
}

int CollisionPair::getOppositePairID(int pairID)
{
    if(pairID == 1)
        return 2;
    else if(pairID == 2)
        return 1;
    else
    {
        Logger()<<"Error in getOppositePairID: No pair entity found - returning 0"<<std::endl;
        return 0;
    }
}

int CollisionPair::getOppositeEntityID(int pairID)
{
    if(pairID == 1)
        return collisionEntityTwo;
    if(pairID == 2)
        return collisionEntityOne;
    else
    {
        Logger()<<"Error in getOppositeEntityID: No pair entity found - returnning 0"<<std::endl;
        return 0;
    }
}

glm::vec2 CollisionPair::getMinimumTranslation(int pairID)
{
    if(pairID == 1)
        return minimumTranslation;
    else if (pairID == 2)
        return -minimumTranslation;
    else
    {
        Logger()<<"Error in getMinimumTranslation: No pair entity found - returning 0"<<std::endl;
        return glm::vec2(0,0);
    }
}

glm::vec2 CollisionPair::getNormal(int pairID)
{
    if(pairID == 1)
        return normal;
    else if (pairID == 2)
        return -normal;
    else
    {
        Logger()<<"Error in getNormal: No pair entity found - returning 0"<<std::endl;
        return glm::vec2(0,0);
    }
}

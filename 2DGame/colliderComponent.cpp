#include "colliderComponent.h"

ComponentID ColliderComponent::ID;

ColliderComponent::ColliderComponent(std::string inType, std::string inCollisionType, glm::vec2 inOffsetPos, float inWidth, float inHeight)
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
}
ColliderComponent::~ColliderComponent(){}

CollisionImpact::CollisionImpact(int inCollisionEntityID)
{
    collisionEntityID = inCollisionEntityID;
}
CollisionImpact::~CollisionImpact(){}


#include "render2DComponent.h"

ComponentID Render2DComponent::ID;

Render2DComponent::Render2DComponent(float inWidth, float inHeight)
{
    float halfWidth = inWidth/2;
    float halfHeight = inHeight/2;

    topLeft = glm::vec2(-halfWidth, halfHeight);
    topRight = glm::vec2(halfWidth, halfHeight);

    bottomLeft = glm::vec2(-halfWidth, -halfHeight);
    bottomRight = glm::vec2(halfWidth, -halfHeight);

    /*topLeft = glm::vec2(-1, 1);
    topRight = glm::vec2(1, 1);

    bottomLeft = glm::vec2(-1, -1);
    bottomRight = glm::vec2(1, -1);*/
}
Render2DComponent::~Render2DComponent(){}

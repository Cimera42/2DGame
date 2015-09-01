#include "render2DComponent.h"

ComponentID Render2DComponent::ID;

Render2DComponent::Render2DComponent(glm::vec2 startUV, glm::vec2 endUV)
{
    //UVs for each corner
    topLeftUV = glm::vec2(startUV.x, endUV.y);
    topRightUV = glm::vec2(endUV.x, endUV.y);

    bottomLeftUV = glm::vec2(startUV.x, startUV.y);
    bottomRightUV = glm::vec2(endUV.x, startUV.y);
}
Render2DComponent::~Render2DComponent(){}

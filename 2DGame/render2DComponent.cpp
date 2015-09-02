#include "render2DComponent.h"
#include "logger.h"

ComponentID Render2DComponent::ID;

Render2DComponent::Render2DComponent(glm::vec2 inStartUV, glm::vec2 inSize)
{
    //start position of UV
    startUV = glm::vec2(inStartUV.x, inStartUV.y);

    //Width and height of UV
    UVsize = glm::vec2(inSize.x, inSize.y);
}
Render2DComponent::~Render2DComponent(){}

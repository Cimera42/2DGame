#include "render2DComponent.h"

ComponentID Render2DComponent::ID;

Render2DComponent::Render2DComponent(){vanityName = "Render2D Component";}
Render2DComponent::~Render2DComponent(){}
Render2DComponent* Render2DComponent::construct(glm::vec2 inStartUV, glm::vec2 inSize)
{
    //start position of UV
    startUV = glm::vec2(inStartUV.x, inStartUV.y);

    //Width and height of UV
    UVsize = glm::vec2(inSize.x, inSize.y);

    return this;
}
Render2DComponent* Render2DComponent::construct(std::vector<std::string> inArgs)
{
    this->construct(glm::vec2(0,0),glm::vec2(1,1));

    return this;
}

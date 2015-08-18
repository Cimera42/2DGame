#include "worldComponent.h"

ComponentID WorldComponent::ID;

WorldComponent::WorldComponent(glm::vec2 inPosition)
{
    position = inPosition;
}
WorldComponent::~WorldComponent(){}

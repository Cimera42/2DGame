#include "worldComponent.h"
#include <glm/gtx/transform.hpp>

ComponentID WorldComponent::ID;

WorldComponent::WorldComponent(glm::vec2 inPosition, glm::vec2 inScale)
{
    position = inPosition;
    scale = inScale;

    updateMatrix();
}
WorldComponent::~WorldComponent(){}

void WorldComponent::updateMatrix()
{
    modelMatrix = glm::mat4();
    modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, 1.0f));
}

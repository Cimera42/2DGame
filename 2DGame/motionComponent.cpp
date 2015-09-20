#include "motionComponent.h"

ComponentID MotionComponent::ID;

MotionComponent::MotionComponent(float inSlowRate)
{
    slowRate = inSlowRate;
    velocity = glm::vec2(0,0);
}
MotionComponent::~MotionComponent(){}

#include "motionComponent.h"

ComponentID MotionComponent::ID;

MotionComponent::MotionComponent(float inMass, float inDrag)
{
    drag = inDrag;
    mass = inMass;
    velocity = glm::vec2(0,0);
    acceleration = glm::vec2(0,0);
}
MotionComponent::~MotionComponent(){}

void MotionComponent::impulse(glm::vec2 in)
{
    velocity+= in/mass; //delta v = impulse/mass
}

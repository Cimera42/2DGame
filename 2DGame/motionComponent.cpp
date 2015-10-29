#include "motionComponent.h"

ComponentID MotionComponent::ID;

MotionComponent::MotionComponent(){vanityName = "Motion Component";}
MotionComponent::~MotionComponent(){}
MotionComponent* MotionComponent::construct(float inMass, float inDrag)
{
    drag = inDrag;
    mass = inMass;
    velocity = glm::vec2(0,0);
    acceleration = glm::vec2(0,0);

    return this;
}
MotionComponent* MotionComponent::construct(std::vector<std::string> inArgs)
{
    return this;
}

void MotionComponent::impulse(glm::vec2 in)
{
    velocity+= in/mass; //delta v = impulse/mass
}

#include "physicsComponent.h"

ComponentID PhysicsComponent::ID;

PhysicsComponent::PhysicsComponent(){vanityName = "Motion Component";}
PhysicsComponent::~PhysicsComponent(){}
PhysicsComponent* PhysicsComponent::construct(float inMass, float inRestitution, float inDrag)
{
    mass = inMass;
    coefficientRestitution = inRestitution;
    coefficientDrag = inDrag;
    force = glm::vec2(0,0);
    velocity = glm::vec2(0,0);
    acceleration = glm::vec2(0,0);

    return this;
}
PhysicsComponent* PhysicsComponent::construct(std::vector<std::string> inArgs)
{
    return this;
}

void PhysicsComponent::impulse(glm::vec2 in)
{
    velocity+= in/mass; //delta v = impulse/mass
}

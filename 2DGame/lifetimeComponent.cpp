#include "lifetimeComponent.h"

ComponentID LifetimeComponent::ID;

LifetimeComponent::LifetimeComponent() {vanityName = "Lifetime Component";}
LifetimeComponent::~LifetimeComponent(){}
LifetimeComponent* LifetimeComponent::construct()
{
    return this;
}
LifetimeComponent* LifetimeComponent::construct(std::vector<std::string> inArgs)
{
    return this;
}

#include "projectileComponent.h"

ComponentID ProjectileComponent::ID;

ProjectileComponent::ProjectileComponent(){vanityName = "Projectile Component";}
ProjectileComponent::~ProjectileComponent(){}
ProjectileComponent* ProjectileComponent::construct()
{
    return this;
}
ProjectileComponent* ProjectileComponent::construct(std::vector<std::string> inArgs)
{
    this->construct();

    return this;
}

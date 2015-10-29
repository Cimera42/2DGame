#include "playerComponent.h"

ComponentID PlayerComponent::ID;

PlayerComponent::PlayerComponent() {vanityName = "Player Component";}
PlayerComponent::~PlayerComponent(){}
PlayerComponent* PlayerComponent::construct(int inTeamID)
{
    teamID = inTeamID;

    return this;
}
PlayerComponent* PlayerComponent::construct(std::vector<std::string> inArgs)
{
    return this;
}

#include "playerComponent.h"

ComponentID PlayerComponent::ID;

PlayerComponent::PlayerComponent(int inTeamID)
{
    teamID = inTeamID;
}
PlayerComponent::~PlayerComponent(){}

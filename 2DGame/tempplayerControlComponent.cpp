#include "tempplayerControlComponent.h"

ComponentID PlayerControlComponent::ID;

PlayerControlComponent::PlayerControlComponent(){vanityName = "Player Control Component";}
PlayerControlComponent::~PlayerControlComponent(){}
PlayerControlComponent* PlayerControlComponent::construct(float inSpeed, int inUp, int inDown, int inLeft, int inRight)
{
    speed = inSpeed;
    upKey = inUp;
    downKey = inDown;
    leftKey = inLeft;
    rightKey = inRight;
}
PlayerControlComponent* PlayerControlComponent::construct(std::vector<std::string> inArgs)
{
    return this;
}

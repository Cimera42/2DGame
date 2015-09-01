#include "tempplayerControlComponent.h"

ComponentID PlayerControlComponent::ID;

PlayerControlComponent::PlayerControlComponent(float inSpeed, int inUp, int inDown, int inLeft, int inRight)
{
    speed = inSpeed;
    upKey = inUp;
    downKey = inDown;
    leftKey = inLeft;
    rightKey = inRight;
}
PlayerControlComponent::~PlayerControlComponent(){}

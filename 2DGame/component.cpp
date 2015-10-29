#include "component.h"

ComponentID Component::componentIDIncrementor = 1;
ComponentID Component::ID;

Component::Component(){}
Component::~Component(){}
Component* Component::construct(){}
Component* Component::construct(std::vector<std::string> inArgs){}

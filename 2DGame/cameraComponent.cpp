#include "cameraComponent.h"
#include <glm/gtx/transform.hpp>

ComponentID CameraComponent::ID;

CameraComponent::CameraComponent(){vanityName = "Camera Component";}
CameraComponent::~CameraComponent(){}
CameraComponent* CameraComponent::construct(float inZoom, bool inActive)
{
    zoom = inZoom;
    activeFlag = inActive;

    updateMatrix();
    return this;
}
CameraComponent* CameraComponent::construct(std::vector<std::string> inArgs)
{
    return this;
}

void CameraComponent::updateMatrix()
{
    projectionMatrix = glm::ortho(-zoom, zoom, -zoom, zoom);
}

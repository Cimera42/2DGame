#include "cameraComponent.h"
#include <glm/gtx/transform.hpp>

ComponentID CameraComponent::ID;

CameraComponent::CameraComponent(float inZoom, bool inActive)
{
    zoom = inZoom;
    activeFlag = inActive;

    updateMatrix();
}
CameraComponent::~CameraComponent(){}

void CameraComponent::updateMatrix()
{
    projectionMatrix = glm::ortho(-zoom, zoom, -zoom, zoom);
}

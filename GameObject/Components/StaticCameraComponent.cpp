#include "stdafx.h"

StaticCameraComponent::StaticCameraComponent(vec3 position, vec3 up, float yaw, float pitch) :
	CameraComponent(position, up, yaw, pitch)
{

}

StaticCameraComponent::~StaticCameraComponent()
{

}

void StaticCameraComponent::ProcessKeyboard(eCamera_Movement direction, float deltaTime)
{
}

void StaticCameraComponent::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
}

void StaticCameraComponent::ProcessMouseScroll(float yoffset)
{
}
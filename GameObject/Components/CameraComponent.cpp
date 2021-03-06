#include "stdafx.h"

// public functions
// Constructor with vectors
CameraComponent::CameraComponent(vec3 position, vec3 up, float yaw, float pitch)
{
	m_Position = position;
	m_WorldUp = up;
	m_Yaw = yaw;
	m_Pitch = pitch;

	m_ProjMatrix = new mat4();
	m_ViewMatrix = new mat4();

	UpdateCameraVectors();
	m_ComponentTag = Component_Camera;

	int x, y;
	debug_GetCurrentWindowSize(&x, &y); // temporary
	m_ViewportSize = vec2(x, y);
	UpdateCameraVectors();
}
// Constructor with scalar values
CameraComponent::CameraComponent(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	m_Position = vec3(posX, posY, posZ);
	m_WorldUp = vec3(upX, upY, upZ);
	m_Yaw = yaw;
	m_Pitch = pitch;
	UpdateCameraVectors();

	int x, y;
	debug_GetCurrentWindowSize(&x, &y); // temporary
	m_ViewportSize = vec2(x, y);
	UpdateCameraVectors();
}

CameraComponent::~CameraComponent()
{
	delete m_ViewMatrix;
	delete m_ProjMatrix;
}

void CameraComponent::Setup()
{
	// update child values
	m_Position.x = m_pParent->GetPosition().x;
	m_Position.y = m_pParent->GetPosition().y;
	m_Position.z = m_pParent->GetPosition().z;

	UpdateCameraVectors();
}

mat4* CameraComponent::GetViewMatrix()
{
	return m_ViewMatrix;
}
mat4* CameraComponent::GetProjectionMatrix()
{
	return m_ProjMatrix;
}

void CameraComponent::SetTargetPosition(vec3 position)
{
	m_TargetPosition.x = position.x;
	m_TargetPosition.y = position.y;
	m_TargetPosition.z = position.z;
}

void CameraComponent::UpdateParentPosition(vec3 m_Position)
{
	m_pParent->SetPosition(vec3(m_Position.x, m_Position.y, m_Position.z));
}

void CameraComponent::ProcessMouseScroll(float yoffset)
{
	if (m_Zoom >= 1.0f && m_Zoom <= 45.0f)
		m_Zoom -= yoffset;
	if (m_Zoom <= 1.0f)
		m_Zoom = 1.0f;
	if (m_Zoom >= 45.0f)
		m_Zoom = 45.0f;
}

// private functions
void CameraComponent::UpdateCameraVectors()
{
	// Calculate the new m_Front vector
	/*vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);*/


	// Also re-calculate the m_Right and Up vector
	//m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	//m_CamUp = glm::normalize(glm::cross(m_Right, m_Front));

	// projection
	m_ProjMatrix->CreatePerspectiveHFoV(m_Zoom * 0.5f, m_ViewportSize.x / m_ViewportSize.y, m_CAMNEAR, m_CAMFAR);
	// *m_ProjMatrix = glm::perspective(glm::radians(m_Zoom), m_ViewportSize.x / m_ViewportSize.y, m_CAMNEAR, m_CAMFAR);

	// view
	m_ViewMatrix->CreateLookAtView(m_Position, UP, m_TargetPosition);
	// *m_ViewMatrix = glm::lookAt(m_Position, m_TargetPosition + m_Front, m_CamUp);
}

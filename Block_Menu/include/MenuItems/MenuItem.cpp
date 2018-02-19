#include "stdafx.h"

MenuItem::MenuItem(Mesh* mesh)
{
	m_Mesh = mesh;
}

MenuItem::~MenuItem()
{
}

void MenuItem::Update(glm::vec2 mousePos)
{
	// TODO:: change color better
	glm::vec4 t = glm::vec4(sin((float)(m_OriginalColor.x * glfwGetTime())), cos((float)(m_OriginalColor.y * glfwGetTime())), sin((float)(m_OriginalColor.z * glfwGetTime())), 1.0f);
	m_Color = t;
	DrawOverlays();
}

void MenuItem::Draw()
{
	m_Shader->Use();
	m_Shader->SetUniformMat4("Transform", glm::value_ptr(m_Transform));
	m_Shader->SetUniformFloat4("Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	m_Mesh->Draw();
}

void MenuItem::SetParentWindow(MenuWindow* window)
{
	m_ParentWindow = window;
	UpdateTransform();
}

void MenuItem::SetPosition(glm::vec2 position)
{
	m_Position = position;
}

void MenuItem::SetRotation(float rotation)
{
	m_Rotation = rotation;
}

void MenuItem::SetSize(glm::vec2 size)
{
	m_Size = size;
}

void MenuItem::UpdateTransform()
{
	glm::mat4 temp;

	glm::vec2 parentPosition = m_ParentWindow->GetPosition(); // return screen pos in pixels (bottom left->top right)
	glm::vec2 parentSize = m_ParentWindow->GetSize(); // return pixel size of window

	// rotation
	temp = glm::rotate(temp, glm::radians(m_Rotation), glm::vec3(0, 0, 1));

	// translate
	glm::vec3 finalPos = glm::vec3((m_ParentWindow->GetPosition().x - parentSize.x * 0.5 + parentSize.x * m_Position.x) / m_Resolution.x * 2 - 1,
		(m_ParentWindow->GetPosition().y - parentSize.y * 0.5 + parentSize.y * m_Position.y) / m_Resolution.y * 2 - 1,
		0);

	temp = glm::translate(temp, glm::vec3(finalPos));
	// temp = glm::translate(temp, glm::vec3(0, 0, 0));

	// scale1
	glm::vec3 finalSize = glm::vec3(parentSize.x * m_Size.x * 2.0f / m_Resolution.x, parentSize.y * m_Size.y * 2.0f / m_Resolution.y, 1);

	temp = glm::scale(temp, glm::vec3(finalSize));
	m_Transform = temp;
}
/* Functionality */
void MenuItem::LeftClick()
{
	OutputMessage("\nMenuItem:: LeftClick() Works!");
}
/* Overlay buttons */
void MenuItem::DrawOverlays() // private
{
	if (m_IsHighlighted)
	for (int i = 0; i < m_OverLayButtons.Size(); i++)
	{
		m_OverLayButtons.At(i)->Draw();
	}
}
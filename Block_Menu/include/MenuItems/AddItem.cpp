#include "stdafx.h"

AddButton::AddButton(Mesh* mesh) : MenuItem(mesh)
{
}

AddButton::~AddButton()
{
	MenuItem* item = new MenuItem();
	item->SetMesh(m_Mesh);
	item->SetParentWindow(m_ParentWindow);

	m_ParentWindow->SetDimensions(5, 5);
	m_ParentWindow->AddItem(item);
	m_ParentWindow->UpdateItems();
	// set image as + symbol
}

void AddButton::Draw()
{
	m_Shader->Use();
	m_Shader->SetUniformMat4("Transform", glm::value_ptr(m_Transform));
	m_Shader->SetUniformFloat4("Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	m_Mesh->Draw();
}

void AddButton::LeftClick()
{
	// TODO:: check menu item list size
	MenuItem* item = new MenuItem();
	item->SetMesh(m_Mesh);
	item->SetParentWindow(m_ParentWindow);

	m_ParentWindow->AddItem(item);
	m_ParentWindow->UpdateItems();
	// TODO:: Update menu item list dimensions
}
#include "stdafx.h"

ImageItem::ImageItem(Mesh* mesh) : MenuItem(mesh)
{
}

ImageItem::~ImageItem()
{
}

void ImageItem::Draw()
{
	m_Shader->Use();
	m_Shader->SetUniformMat4("Transform", glm::value_ptr(m_Transform));
	m_Shader->SetupTextures(&m_TextureID, 1);
	m_Mesh->Draw();
}

void ImageItem::LeftClick()
{
	// do something
}
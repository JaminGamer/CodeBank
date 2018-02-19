#include "stdafx.h"

RenderedScene::RenderedScene(MyGLFW* window)
{
	m_MainWindow = window;
	m_pGameCore = debug_GetGameCore();
	// TODO:: Remove test image and use a scene fbo texture
	test_image = (ImTextureID)Load2DTexture("Resources/Textures/FlashHeal.png");
	m_Flags = ImGuiWindowFlags_MenuBar;
	m_Title = "Rendered Scene";
	m_ID = WindowID_RenderedScene;
}
RenderedScene::~RenderedScene()
{
	glDeleteTextures(1, (GLuint*)test_image);
}

void RenderedScene::Draw()
{
	Scene* t_CurrentScene = m_pGameCore->GetSceneManager()->GetCurrentScene();

	// init window
	//ImGui::SetNextWindowSize(window_size);
	if (!ImGui::Begin(m_Title, &m_IsVisible, m_Flags))
	{
		ImGui::End();
		return;
	}
	// Items
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::Button("Pause"))
		{
			if (t_CurrentScene->GetIsPaused())
			{
				t_CurrentScene->SetIsPaused(false);
			}
			else
			{
				t_CurrentScene->SetIsPaused(true);
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Freeze")) // TODO: Freeze prevents window from scaling
		{
			if (t_CurrentScene->GetIsPaused())
			{
				t_CurrentScene->SetIsPaused(false);
			}
			else
			{
				t_CurrentScene->SetIsPaused(true);
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			t_CurrentScene->SaveScene();
		}
		ImGui::SameLine();
		if (ImGui::Button("Load"))
		{
			// TODO: Option to load multiple saves
			t_CurrentScene->LoadScene();
		}
		ImGui::EndMenuBar();
	}

	ImTextureID imageHandle = (ImTextureID)m_pGameCore->RenderSceneToTexture(t_CurrentScene->GetSceneID());

	ImVec2 imageSize = ImVec2(ImGui::GetWindowWidth() - 16, ImGui::GetWindowHeight() - 54);
	ImGui::Image(test_image, imageSize);

	ImGui::End();
}

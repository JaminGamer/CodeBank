#include "stdafx.h"

LightPanel::LightPanel()
{
	m_Scene = debug_GetGameCore()->GetSceneManager()->GetScene(Scene_TestScene);
	m_Factory = debug_GetGameCore()->GetFactory();
	listbox_current_item = 0;
	m_Title = "Light Panel";
	m_ID = WindowID_Lights;
}

LightPanel::~LightPanel()
{
}

void LightPanel::Draw()
{
	if (!ImGui::Begin(m_Title, &m_IsVisible, m_Flags))
	{
		ImGui::End(); // window is collapsed/closed
		return;
	}
	/////////////////////////////
	// add light
	if (ImGui::Button("Add Light"))
	{
		m_Factory->CreateLight(m_Scene, vec3(0,0,0));
	}
	// remove camera
	Linear2LinkedList<GameObject*> t_Lights = m_Scene->GetLightList();
	ImGui::SameLine(); if (ImGui::Button("Remove Light"))
	{
		if (t_Lights.Size() > 1)
		{
			m_Scene->RemoveLight(t_Lights.At(listbox_current_item));
			// Correct current camera
			t_Lights = m_Scene->GetLightList();
			if (listbox_current_item != 0)
			{
				listbox_current_item--;
			}
		}
		else
		{
			lb_error = true;
		}
	}

	// display/edit light position
	float t_CurrentLightPos[3];
	t_CurrentLightPos[0] = t_Lights.At(listbox_current_item)->GetPosition().x;
	t_CurrentLightPos[1] = t_Lights.At(listbox_current_item)->GetPosition().y;
	t_CurrentLightPos[2] = t_Lights.At(listbox_current_item)->GetPosition().z;
	if (ImGui::InputFloat3("Position", t_CurrentLightPos))
	{
		t_Lights.At(listbox_current_item)->SetPosition(vec3(t_CurrentLightPos[0], t_CurrentLightPos[1], t_CurrentLightPos[2])); // Update light position
	}
	// Color
	LightComponent* lightComp = (LightComponent*)t_Lights.At(listbox_current_item)->GetComponent(Component_Light);
	// ambient
	float lightColor[] = { lightComp->GetColour().x, lightComp->GetColour().y, lightComp->GetColour().z };
	if (ImGui::ColorEdit3("Colour", lightColor))
	{
		lightComp->SetColour(vec3(lightColor[0], lightColor[1], lightColor[2]));
		((RenderComponent*)t_Lights.At(listbox_current_item)->GetComponent(Component_Render))->SetColour(vec4(lightColor[0], lightColor[1], lightColor[2], 1.0f));
	}
	// populate light names list
	std::vector<std::string> names;
	for (int i = 0; i < t_Lights.Size(); i++)
	{
		if (t_Lights.At(i) == nullptr) { continue; }
		names.push_back(t_Lights.At(i)->GetName());
	}

	// set list box items to light names
	for (uint i = 0; i < names.size(); i++)
	{
		listbox_items[i] = names.at(i).c_str();
	}

	// set list box text
	const char* lb_text = "";
	if (lb_error)
	{
		lb_text = "Scene requires at\nleast 1 light";
	}
	else
	{
		lb_text = "Lights";
	}

	// setup listbox
	ImGui::ListBox(lb_text, &listbox_current_item, listbox_items, names.size(), itemsVisible); // IM_ARRAYSIZE(listbox_items)

	/* END */
	ImGui::End();
}
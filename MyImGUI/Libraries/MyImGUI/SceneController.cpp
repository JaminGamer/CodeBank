#include "stdafx.h"

SceneController::SceneController()
{
	m_Scene = debug_GetGameCore()->GetSceneManager()->GetScene(Scene_TestScene);
	m_Factory = debug_GetGameCore()->GetFactory();
	m_SceneObjects = m_Scene->GetObjectList(); // initialize object list
	m_Title = "Scene Controller";
	m_ID = WindowID_SceneController;
}

SceneController::~SceneController()
{
}

void SceneController::Draw()
{
	if (!ImGui::Begin(m_Title, &m_IsVisible, m_Flags))
	{
		ImGui::End(); // window is collapsed/closed
		return;
	}

	DrawAddObject();

	SetupObjectList();

	/* END */
	ImGui::End();
}

void SceneController::DrawAddObject()
{
	// add object
	if (ImGui::Button("Add Object"))
	{
		m_Factory->CreateCube(m_Scene, vec3(0, 0, 0));
	}
	// remove object
	ImGui::SameLine(); if (ImGui::Button("Remove Object"))
	{
		// Remove object
		m_Scene->RemoveObjectFromScene(m_Scene->GetGameObject(listbox_current_item.c_str()));

		// Resolve current item
		listbox_current_item = "Bob";
	}
}

void SceneController::EditPosition()
{
	// display/edit game objects
	float t_CurrentCamPos[3];
	t_CurrentCamPos[0] = m_SceneObjects.at(listbox_current_item)->GetPosition().x;
	t_CurrentCamPos[1] = m_SceneObjects.at(listbox_current_item)->GetPosition().y;
	t_CurrentCamPos[2] = m_SceneObjects.at(listbox_current_item)->GetPosition().z;
	ImGui::InputFloat3("Position", t_CurrentCamPos);
	// Update position change
	m_Scene->GetGameObject(listbox_current_item.c_str())->SetPosition(vec3(t_CurrentCamPos[0], t_CurrentCamPos[1], t_CurrentCamPos[2]));
}

void SceneController::SetupObjectList()
{
	// populate object names list
	std::vector<std::string> names;

	// Map doesn't store in order
	int counter = 0; // loop counter variable
	m_SceneObjects = m_Scene->GetObjectList(); // Update changes to list
	for (auto t_LoopVar : m_SceneObjects)
	{
		if (t_LoopVar.second == nullptr) { continue; } // Check if null*
		if (listbox_current_item.compare("Bob") == 0) { listbox_current_item = t_LoopVar.second->GetName(); } // Check if no current object
		if (counter == listbox_current_index) { listbox_current_item = t_LoopVar.second->GetName(); }
		names.push_back(t_LoopVar.second->GetName());
		counter++;
	}
	EditPosition();
	// set list box items to object names
	for (uint i = 0; i < names.size(); i++)
	{
		listbox_items[i] = names.at(i).c_str();
	}

	// setup listbox
	ImGui::ListBox(lb_text, &listbox_current_index, listbox_items, names.size(), itemsVisible); // IM_ARRAYSIZE(listbox_items)

}
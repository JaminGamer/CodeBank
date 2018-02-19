#include "stdafx.h"

ResourceManager* t_ResourceManager = nullptr;

SceneExplorer::SceneExplorer()
{
	t_ResourceManager = debug_GetGameCore()->GetResourceManager();
	m_Scene = debug_GetGameCore()->GetSceneManager()->GetScene(Scene_TestScene);
	m_Factory = debug_GetGameCore()->GetFactory();
	m_SceneObjects = m_Scene->GetObjectList(); // initialize object list
	m_Title = "Scene Explorer";
	m_ID = WindowID_SceneExplorer;
}

SceneExplorer::~SceneExplorer()
{
}

void SceneExplorer::Draw()
{
	if (!ImGui::Begin(m_Title, &m_IsVisible, m_Flags))
	{
		ImGui::End(); // window is collapsed/closed
		return;
	}

	// Object docking
	static bool isDock = true;
	if (ImGui::Begin("imguidock window (Scene Explorer)", &isDock, ImGuiWindowFlags_NoScrollbar)) {
		ImGui::BeginDockspace();
		static char tmp[128];
		for (int i = 0; i<10; i++) {
			sprintf(tmp, "Dock %d", i);
			if (i == 9) ImGui::SetNextDock(ImGuiDockSlot_Bottom);// optional
			if (ImGui::BeginDock(tmp)) {
				ImGui::Text("Content of dock window %d goes here", i);
			}
			ImGui::EndDock();
		}
		ImGui::EndDockspace();
	}
	ImGui::End();
	ImGui::DockDebugWindow();

	DrawAddObject();
	SetupObjectList();

	/* END */
	ImGui::End();
}

void SceneExplorer::DrawAddObject()
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

void SceneExplorer::EditPosition()
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

void SceneExplorer::SetupObjectList()
{
	m_SceneObjects = m_Scene->GetObjectList(); // Update changes to list
	if (m_SceneObjects.size() < 1) { return; }
	// populate object names list
	std::vector<std::string> names;

	// Map doesn't store in order
	int counter = 0; // loop counter variable
	for (auto t_LoopVar : m_SceneObjects)
	{
		if (t_LoopVar.second == nullptr) { continue; } // Check if null*
		if (listbox_current_item.compare("Bob") == 0) { listbox_current_item = t_LoopVar.second->GetName(); } // Check if no current object
		if (counter == listbox_current_index) { listbox_current_item = t_LoopVar.second->GetName(); }
		names.push_back(t_LoopVar.second->GetName());
		counter++;
	}
	// set list box items to object names
	for (uint i = 0; i < names.size(); i++)
	{
		listbox_items[i] = names.at(i).c_str();
	}

	EditPosition();

	// setup listbox
	ImGui::ListBox("Names", &listbox_current_index, listbox_items, names.size(), itemsVisible); // IM_ARRAYSIZE(listbox_items)

	// ImGui::SameLine();
	// ImGui::Text("Type: %i", m_SceneObjects.find("Cube0")->second->GetTag());
}
#include "BLUE_Main.h"

CameraPanel::CameraPanel()
{
	m_Scene = debug_GetGameCore()->GetSceneManager()->GetScene(Scene_TestScene);
	listbox_current_item = m_Scene->GetCurrentCamera();
	m_Title = "Camera Panel";
	m_ID = WindowID_Cameras;
}

CameraPanel::~CameraPanel()
{
}

void CameraPanel::Draw()
{
	if (!ImGui::Begin(m_Title, &m_IsVisible, m_Flags))
	{
		ImGui::End(); // window is collapsed/closed
		return;
	}
	/////////////////////////////
	// add camera
	if (ImGui::Button("Add Camera"))
	{
		m_Factory->CreateFreeCamera(m_Scene, vec3(0,0,0));
	}
	// remove camera
	Linear2LinkedList<GameObject*> t_Cameras = m_Scene->GetCameraList();
	ImGui::SameLine(); if (ImGui::Button("Remove Camera"))
	{
		if (t_Cameras.Size() > 1)
		{
			m_Scene->RemoveCamera(t_Cameras.At(listbox_current_item));
			// Correct current camera
			t_Cameras = m_Scene->GetCameraList();
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

	// display/edit camera position
	float t_CurrentCamPos[3];
	t_CurrentCamPos[0] = t_Cameras.At(listbox_current_item)->GetPosition().x;
	t_CurrentCamPos[1] = t_Cameras.At(listbox_current_item)->GetPosition().y;
	t_CurrentCamPos[2] = t_Cameras.At(listbox_current_item)->GetPosition().z;
	if (ImGui::InputFloat3("Position", t_CurrentCamPos))
	{
		t_Cameras.At(listbox_current_item)->SetPosition(vec3(t_CurrentCamPos[0], t_CurrentCamPos[1], t_CurrentCamPos[2])); // update camera position
		((CameraComponent*)t_Cameras.At(listbox_current_item))->UpdateCameraVectors();
	}

	// populate camera names list
	std::vector<std::string> names;
	for (int i = 0; i < t_Cameras.Size(); i++)
	{
		if (t_Cameras.At(i) == nullptr) { continue; }
		names.push_back(t_Cameras.At(i)->GetName());
	}

	// set list box items to camera names
	for (uint i = 0; i < names.size(); i++)
	{
		listbox_items[i] = names.at(i).c_str();
	}

	// set list box text
	const char* lb_text = "";
	if (lb_error)
	{
		lb_text = "Scene requires at\nleast 1 camera";
	}
	else
	{
		lb_text = "Cameras";
	}

	// setup listbox
	ImGui::ListBox(lb_text, &listbox_current_item, listbox_items, names.size(), itemsVisible); // IM_ARRAYSIZE(listbox_items)

	// update selected camera
	m_Scene->SetCurrentCamera(listbox_current_item);

	/* END */
	ImGui::End();
}
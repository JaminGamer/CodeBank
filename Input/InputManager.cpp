#include "pch.h"

InputManager::InputManager()
{
	if (Win32_Project)
	{
		AssignWin32Keys();
	}
	else if (1)
	{
		AssignGLFWKeys();
	}
	else
	{
		// Other Platforms or default layout
	}

	// Create controllers
	for (int i = 0; i < g_NumPlayers; i++)
	{
		m_Controllers[i] = new Controller(0);
	}

	SetupControllers();
}

InputManager::~InputManager()
{
	for (int i = 0; i < g_NumPlayers; i++)
	{
		delete m_Controllers[i];
	}
}

void InputManager::SetupControllers()
{
	for (int i = 0; i < g_NumPlayers; i++)
	{
		Controller* t_Controller = m_Controllers[i];
		//// Map game actions to controller input ////
		// m_KeyCodes[Button_Ability1] = eKeys[Key_W];
		/* Modifiers */
		t_Controller->SetKeyCode(Button_ModifierCntrl, m_Keys[eKeys_CTRL]);

		/* Mouse */
		t_Controller->SetKeyCode(Button_MouseLeft, m_Keys[eKeys_LeftClick]); // TODO: Add mouse functionality
		t_Controller->SetKeyCode(Button_MouseRight, m_Keys[eKeys_RightClick]);
		t_Controller->SetKeyCode(Button_MouseMiddle, m_Keys[eKeys_MiddleClick]);
		t_Controller->SetKeyCode(Button_MouseMiddle, m_Keys[eKeys_MiddleClick]);

		/* KeyBoard */
		// Menu actions + navigation
		t_Controller->SetKeyCode(Button_MenuUp, m_Keys[eKeys_Up]);
		t_Controller->SetKeyCode(Button_MenuDown, m_Keys[eKeys_Down]);
		t_Controller->SetKeyCode(Button_MenuLeft, m_Keys[eKeys_Left]);
		t_Controller->SetKeyCode(Button_MenuRight, m_Keys[eKeys_Right]);
		t_Controller->SetKeyCode(Button_MenuOpen, m_Keys[eKeys_ESCAPE]);
		t_Controller->SetKeyCode(Button_MenuClose, m_Keys[eKeys_ESCAPE]);

		// Game actions
		t_Controller->SetKeyCode(Button_MoveUp, m_Keys[eKeys_Q]);
		t_Controller->SetKeyCode(Button_MoveDown, m_Keys[eKeys_E]);
		t_Controller->SetKeyCode(Button_MoveLeft, m_Keys[eKeys_A]);
		t_Controller->SetKeyCode(Button_MoveRight, m_Keys[eKeys_D]);
		t_Controller->SetKeyCode(Button_MoveForward, m_Keys[eKeys_W]);
		t_Controller->SetKeyCode(Button_MoveBackward, m_Keys[eKeys_S]);
	}
}
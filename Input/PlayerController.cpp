#include "pch.h"

PlayerController::PlayerController()
{
	Clear(); // set all buttons to unpressed
	// initialize button mapping
	// TODO: Use eKeys to assign to controller input chars.
	/* Modifiers */
	m_Buttons[Button_ModifierCntrl] = GLFW_KEY_LEFT_CONTROL;
	/* Mouse */
	m_Buttons[Button_MouseLeft] = GLFW_MOUSE_BUTTON_LEFT;
	m_Buttons[Button_MouseRight] = GLFW_MOUSE_BUTTON_RIGHT;
	m_Buttons[Button_MouseMiddle] = GLFW_MOUSE_BUTTON_MIDDLE;
	/* KeyBoard */
	m_Buttons[Button_MoveUp] = eKeys_Q;
	m_Buttons[Button_MoveDown] = eKeys_E;
	m_Buttons[Button_MoveLeft] = eKeys_A;
	m_Buttons[Button_MoveRight] = eKeys_D;
	m_Buttons[Button_MoveForward] = eKeys_W;
	m_Buttons[Button_MoveBackward] = eKeys_S;
	// m_Buttons[Button_Ability1] = 'E' && VK_CONTROL;// 'E';
}

PlayerController::~PlayerController()
{
}

void PlayerController::Clear()
{
	for (int i = 0; i < Button_Max; i++)
	{
		m_Buttons[i] = 0;
		m_States[i] = 0;
	}
}

void PlayerController::SetButtonPressed(eGameButtons button)
{
	m_States[button] = 1;
}

void PlayerController::SetButtonReleased(eGameButtons button)
{
	m_States[button] = 0;
}

bool PlayerController::IsButtonPressed(eGameButtons button)
{
	return m_States[button];
}

unsigned short int PlayerController::GetKeyCode(eGameButtons button)
{
	return m_Buttons[button];
}

void PlayerController::SetKeyCode(eGameButtons index, char button)
{
	m_Buttons[index] = button;
}
#include "stdafx.h"
#include "XinputInterface.h"

// setup
XinAPI XinputHandler::XinputHandler(int numPlayers, bool debugging) :
	m_NumPlayers(numPlayers),
	m_Debugging(debugging)
{
	// XInputEnable(true); <-- deprecated
	for (int i = 0; i < numPlayers; i++) // load player list
	{
		XINPUT_STATE temp;
		m_PlayerStates.push_back(temp);
	}
}

// utility
XinAPI void XinputHandler::ResetState(int player)
{
	memset(&m_PlayerStates.at(player), 0, sizeof(XINPUT_STATE)); // clear data
}

XinAPI void XinputHandler::ResetStates()
{
	for (uint i = 0; i < m_PlayerStates.size(); i++)
	{
		memset(&m_PlayerStates.at(i), 0, sizeof(XINPUT_STATE)); // clear data
	}
}

XinAPI bool XinputHandler::UpdatePlayerState(int player)
{
	DWORD result = XInputGetState(player, &m_PlayerStates.at(player)); // XInputGetState(PORT, &ControllerState );
	if (result == ERROR_SUCCESS)
		return true;
	else
	{
		// if (m_Debugging) OutputMessage("\nXinputManager: Error reading gamepad state for Player %i", player);
		return false;
	}
}
// input
XinAPI Vector2 XinputHandler::LeftStick(int player)
{
	Vector2 leftstick = Vector2(m_PlayerStates.at(player).Gamepad.sThumbRX, m_PlayerStates.at(player).Gamepad.sThumbRY);

	float magnitude = leftstick.Length();

	if (magnitude < m_StickDeadZone.x)
	{
		leftstick.Set(0, 0);
	}
	else
	{
		// get the normalized direction vector of the thumbstick
		Vector2 direction = leftstick / magnitude;

		magnitude = (magnitude - m_StickDeadZone.x) / (32767 - m_StickDeadZone.x);

		// clamp the magnitude to 1
		if (magnitude > 1)
			magnitude = 1;

		leftstick = direction * magnitude;
	}
	// if (m_Debugging) OutputMessage("\nController Sticks:%f, %f\r\n", leftstick.x, leftstick.y);
	return Vector2(leftstick.x, leftstick.y);
}

XinAPI Vector2 XinputHandler::RightStick(int player)
{
	Vector2 rightstick = Vector2(m_PlayerStates.at(player).Gamepad.sThumbRX, m_PlayerStates.at(player).Gamepad.sThumbRY);

	float magnitude = rightstick.Length();

	if (magnitude < m_StickDeadZone.y)
	{
		rightstick.Set(0, 0);
	}
	else
	{
		// get the normalized direction vector of the thumbstick
		Vector2 direction = rightstick / magnitude;

		magnitude = (magnitude - m_StickDeadZone.y) / (32767 - m_StickDeadZone.y);

		// clamp the magnitude to 1
		if (magnitude > 1)
			magnitude = 1;

		rightstick = direction * magnitude;
	}
	// if (m_Debugging) OutputMessage("\nController Sticks:%f, %f\r\n", rightstick.x, rightstick.y);
	return Vector2(rightstick.x, rightstick.y);
}

XinAPI Vector2 XinputHandler::Triggers(int player)
{
	// state.Gamepad.bLeftTrigger; // value between 0 and 255
	float leftTrigger = (float)m_PlayerStates.at(player).Gamepad.bLeftTrigger / 255;
	// if (m_Debugging) OutputMessage("Controller LTrigger:%f\n", leftTrigger);

	// state.Gamepad.bRightTrigger; // value between 0 and 255
	float rightTrigger = (float)m_PlayerStates.at(player).Gamepad.bRightTrigger / 255;
	// OutputMessage("Controller RTrigger:%f\n", rightTrigger);
	return Vector2(leftTrigger, rightTrigger);
}
// Face
// TODO:: Find a good naming convention for interface methods
XinAPI bool XinputHandler::AButtonIsDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
}

XinAPI bool XinputHandler::IsBButtonDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
}

XinAPI bool XinputHandler::IsXButtonDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
}

XinAPI bool XinputHandler::IsYButtonDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
}
// DPad
XinAPI bool XinputHandler::IsDPadUpButtonDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
}

XinAPI bool XinputHandler::IsDPadDownButtonDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
}

XinAPI bool XinputHandler::IsDPadLeftButtonDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);
}

XinAPI bool XinputHandler::IsDPadRightButtonDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
}
// Bumper
XinAPI bool XinputHandler::IsBumperLeftButtonDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
}

XinAPI bool XinputHandler::IsBumperRightButtonDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);
}
// Start + Back
XinAPI bool XinputHandler::IsStartButtonDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
}
XinAPI bool XinputHandler::IsBackButtonDown(int player)
{
	return ((m_PlayerStates.at(player).Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0);
}
// tear down
XinAPI XinputHandler::~XinputHandler()
{
}
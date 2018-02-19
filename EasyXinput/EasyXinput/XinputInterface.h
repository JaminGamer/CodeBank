#ifndef __XinputInterface_H__
#define __XinputInterface_H__

#ifdef XinAPI_Export
#define XinAPI __declspec(dllexport)
#else
#define XinAPI __declspec(dllimport)
#endif

// https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xinput_gamepad(v=vs.85).aspx <-- button codes
// https://katyscode.wordpress.com/2013/08/30/xinput-tutorial-part-1-adding-gamepad-support-to-your-windows-game/ <-- reading Xinput
// https://msdn.microsoft.com/en-ca/library/windows/desktop/ee417001(v=vs.85).aspx <- microsoft tutorial
// "The constant XINPUT_GAMEPAD_TRIGGER_THRESHOLD may be used as the value which bLeftTrigger and bRightTrigger must be greater than to register as pressed." - MSDN XINPUT_GAMEPAD structure
// XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
#include <Xinput.h>
// #include Xinput.lib, Xinput9_1_0.lib or other version

/*  HOW TO USE
	XinputHandler newHandler = new XinputHanlder(int playerCount, bool debugEnabled = false);
	...
	newHanlder->ResetStates();
	newHanlder->SetPlayer(0);
	newHanlder->UpdatePlayerState();
	newHanlder->AButtonIsDown();
*/

// TODO:: increase efficiency
// Compare previous frame state to see if face buttons changed.
// If they did, queue an event, otherwise don't waste ram and processor's time
// Add option to disable auto stick+trigger event generation

// TODO:: consider removing dependencies like vec2 and std::vector to make incorporation simpler

// TODO:: Finalize interface.
// Find better variable and function names. Possibly add prefixes like xin_.

#include <vector>
#include <assert.h>
#define MyAssert assert

typedef unsigned int uint;

// TODO: reference additional headers your program requires here
#include "MathHelpers.h"
#include "Vector.h"
#include "XinputInterface.h"

class XinAPI XinputHandler
{
public:
	// setup
	XinputHandler(int numPlayers, bool debugging = false);
	void SetDebugging(bool debugging) { m_Debugging = debugging; };

	// utility
	void ResetState() { ResetState(m_CurrentPlayer); };
	void ResetState(int player);
	void ResetStates();

	void SetPlayer(int player) { m_CurrentPlayer = player; };
	void SetStickDeadZone(int deadzone) { m_StickDeadZone = (float)deadzone; };
	void SetTriggerDeadZone(int deadzone) { m_TriggerDeadZone = deadzone; };

	bool UpdatePlayerState() { return UpdatePlayerState(m_CurrentPlayer); };
	bool UpdatePlayerState(int player);

	//// input
	// Sticks + Triggers
	Vector2 LeftStick() { return LeftStick(m_CurrentPlayer); };
	Vector2 LeftStick(int player);

	Vector2 RightStick() { return RightStick(m_CurrentPlayer); };
	Vector2 RightStick(int player);

	Vector2 Triggers() { return Triggers(m_CurrentPlayer); };
	Vector2 Triggers(int player);
	// Face
	bool AButtonIsDown() { return AButtonIsDown(m_CurrentPlayer); };
	bool AButtonIsDown(int player);

	bool IsBButtonDown() { return IsBButtonDown(m_CurrentPlayer); };
	bool IsBButtonDown(int player);

	bool IsXButtonDown() { return IsXButtonDown(m_CurrentPlayer); };
	bool IsXButtonDown(int player);

	bool IsYButtonDown() { return IsYButtonDown(m_CurrentPlayer); };
	bool IsYButtonDown(int player);
	// DPad
	bool IsDPadUpButtonDown() { return IsDPadUpButtonDown(m_CurrentPlayer); };
	bool IsDPadUpButtonDown(int player);

	bool IsDPadDownButtonDown() { return IsDPadDownButtonDown(m_CurrentPlayer); };
	bool IsDPadDownButtonDown(int player);

	bool IsDPadLeftButtonDown() { return IsDPadLeftButtonDown(m_CurrentPlayer); };
	bool IsDPadLeftButtonDown(int player);

	bool IsDPadRightButtonDown() { return IsDPadRightButtonDown(m_CurrentPlayer); };
	bool IsDPadRightButtonDown(int player);
	// Bumper
	bool IsBumperLeftButtonDown() { return IsBumperLeftButtonDown(m_CurrentPlayer); };
	bool IsBumperLeftButtonDown(int player);

	bool IsBumperRightButtonDown() { return IsBumperRightButtonDown(m_CurrentPlayer); };
	bool IsBumperRightButtonDown(int player);
	// Start + Back
	bool IsStartButtonDown() { return IsStartButtonDown(m_CurrentPlayer); };
	bool IsStartButtonDown(int player);

	bool IsBackButtonDown() { return IsBackButtonDown(m_CurrentPlayer); };
	bool IsBackButtonDown(int player);

	// tear down
	~XinputHandler();

private:
	// functions
	void CompareStates(int player) {};

	// variables
	bool m_Debugging;

	Vector2 m_StickDeadZone;
	int m_TriggerDeadZone;

	unsigned int m_NumPlayers;

	unsigned int m_CurrentPlayer;

	std::vector<XINPUT_STATE> m_PlayerStates;
	std::vector<XINPUT_STATE> m_PreviousStates; // reduce polling by generating events
};

#endif // __XinputInterface_H__
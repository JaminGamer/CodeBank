#ifndef __PLAYERCONTROLLER_H_
#define __PLAYERCONTROLLER_H_

class PlayerController
{
public:
    PlayerController();
    virtual ~PlayerController();

    void Clear();

    void SetButtonPressed(eGameButtons button);
    void SetButtonReleased(eGameButtons button);

    bool IsButtonPressed(eGameButtons button);

	unsigned short int GetKeyCode(eGameButtons button);
	void SetKeyCode(eGameButtons index, char button);

	void SetMousePosition(vec2 position) { m_MousePosition = position; };
	vec2 GetMousePosition() { return m_MousePosition; };

	// TODO: key input events

protected:
	vec2 m_MousePosition = 0;
	unsigned short int m_Buttons[Button_Max];
	bool m_States[Button_Max];
};

#endif //__PLAYERCONTROLLER_H_
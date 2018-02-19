#ifndef __MENU_H_
#define __MENU_H_

class MenuWindow;

class Menu
{
public:
	Menu();
	~Menu();

	void Update(glm::vec2 mousePos);

	void Draw();

	void AddWindow(MenuWindow* window) { m_Windows.push_back(window); };

	void LeftClick(glm::vec2 mousePos);
	void RightClick(glm::vec2 mousePos) {};
	void MiddleClick(glm::vec2 mousePos) {};

private:
	std::vector<MenuWindow*> m_Windows;
	// menu state
	// menu identifier
	// menu interface for things like numWindows
	// menu types like overlay, tooltip, opaque etc
};

#endif // __MENU_H_
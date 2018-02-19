#ifndef __ImGUIWindow_H__
#define __ImGUIWindow_H__

class ImGUIWindow
{
public:
	ImGUIWindow();
	~ImGUIWindow();

	virtual void Draw() = 0;
	bool IsVisible() { return m_IsVisible; };

	const char* GetWindowTitle() { return m_Title; };
	eIMGuiWindowID GetID() { return m_ID; }
	bool* GetIsVisible() { return &m_IsVisible; };

protected:
	eIMGuiWindowID m_ID = WindowID_Invalid;
	ImGuiWindowFlags m_Flags = 0; // Window specific flags for settings
	bool m_IsVisible = true;
	const char* m_Title = nullptr; // Window Name that appears
};

#endif //__ImGUIWindow_H__

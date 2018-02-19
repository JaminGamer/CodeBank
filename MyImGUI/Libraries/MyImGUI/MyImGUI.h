#ifndef __MYIMGUI_H__
#define __MYIMGUI_H__

#include "Libraries\imGUI\imgui.h"

class GameCore;

// Window classes
class RenderedScene;
class NodeGraph;
class CameraPanel;
class ImGUIWindow;
class MyGLFW;

class MyImGUI
{
public:
	MyImGUI();
	~MyImGUI();

	void Init(MyGLFW* window, GameCore* gamecore);

	void NewFrame();
	void Draw();

	// TODO:: Create eWindow enum for specifying windows without handles
	void ShowWindow(bool visible) {}; // toggle window visibility

	void AddWindow(); // (eWindow) or int windowID
	void RemoveWindow() {}; // (eWindow)

	GameCore* GetGameCore() { return m_pGameCore; };
	RenderedScene* GetRenderedScene(eIMGuiWindowID ID) { return (RenderedScene*)m_Windows.at(ID); };

private:
	MyGLFW* m_pWindow = nullptr;
	GameCore* m_pGameCore;

	// other
	bool m_Visible = true;

	ImTextureID test_image = 0;
	ImGuiWindowFlags m_Flags = 0;

	// TODO :: Create Window() base class and have a list of windows.
	// This is nice for multiple instances of the same window.
	// Also consider making SaveWindows() cJSON save functionality.

	/* Functions */
	void CreateWindows();
	void DrawWindowToggle();
	void DrawMainMenuBar();
	void DrawMainWindow();

	void ProcessEvents();

	int m_Event = 0;

	/* Styling */
	const int m_ThemeMax = 3; // number of supported themes
	int m_Theme = 0;
	const float m_GlobalOpacityDefault = 0.95f;
	float m_GlobalOpacity = m_GlobalOpacityDefault;

	void SetTheme(int theme);

	// windows
	std::map<eIMGuiWindowID, ImGUIWindow*> m_Windows;
	bool show_rendered_scene = true;
	bool show_node_graph = true;
	bool show_camera_panel = true;
};

#endif //__MYIMGUI_H__

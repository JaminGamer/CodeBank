#include "stdafx.h"

static void ShowExampleAppCustomNodeGraph(bool* nodeMenu);
extern float g_FrameRate;
extern int g_WindowWidth, g_WindowHeight;

MyImGUI::MyImGUI()
{
}

MyImGUI::~MyImGUI()
{
	ImGui_ImplGlfwGL3_Shutdown();
	for (auto temp: m_Windows)
	{
		delete temp.second;
	}
	m_Windows.clear(); // cleanup windows
}

void MyImGUI::Init(MyGLFW* window, GameCore* gamecore)
{
	m_pWindow = window;

	// Setup ImGui binding
#ifdef _glfw3_h_
	ImGui_ImplGlfwGL3_Init(window->GetWindow(), false); // (GLFWwindow* window, bool install_callbacks)
#else
	OutputMessage("\nImGUI Uninitialized!");
	assert(0);
#endif

	// Load Fonts
	// (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
	//ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyClean.ttf", 13.0f);
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	int width, height;
	window->GetWindowSize(&width, &height);

	// Application init
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = (float)width;
	io.DisplaySize.y = (float)height;
	io.IniFilename = "imgui.ini";
	// io.RenderDrawListsFn = NULL;
	// io.RenderDrawListsFn = my_render_function;  // Setup a render function, or set to NULL and call GetDrawData() after Render() to access the render data.
	// TODO: Fill others settings of the io structure

	// Instantiate window objects
	CreateWindows();

	// Theme
	SetTheme(1);
}

void MyImGUI::CreateWindows()
{
	// Instantiate windows
	ImGUIWindow* temp;

	temp = new RenderedScene(m_pWindow);
	m_Windows[temp->GetID()] = temp;

	temp = new NodeGraph();
	m_Windows[temp->GetID()] = temp;

	temp = new CameraPanel();
	m_Windows[temp->GetID()] = temp;

	temp = new LightPanel();
	m_Windows[temp->GetID()] = temp;

	temp = new SceneController();
	m_Windows[temp->GetID()] = temp;

	temp = new SceneExplorer();
	m_Windows[temp->GetID()] = temp;
}

void MyImGUI::AddWindow()
{
	// Push back a new window into the list
	// list.push_back(new Window());
}

void MyImGUI::NewFrame()
{
	ImGui_ImplGlfwGL3_NewFrame();
	// ImGui::NewFrame();
}

void MyImGUI::Draw()
{
	// Open/close
	DrawWindowToggle();

	if (m_Visible == false)
	{
		ImGui::Render(); // ImGUI Will now draw all the initialized windows
		return;
	}

	/* Main Menu Bar */
	DrawMainMenuBar();

	/* Main Window */
	DrawMainWindow();

	/* Initialize Windows */
	std::map<eIMGuiWindowID, ImGUIWindow*>::iterator it;
	for (it = m_Windows.begin(); it != m_Windows.end(); it++)
	{
		if (it->second->IsVisible())
		{
			// Setup all visible windows
			it->second->Draw();
		}
	}

	ImGui::TestNodeGraphEditor();

	/* ImGUI RENDER CALL */
	ImGui::Render(); // ImGUI Will now draw all the initialized windows

	if (m_Event)
	{
		ProcessEvents();
	}
}

void MyImGUI::DrawWindowToggle()
{
	static bool visible = true;
	if (!ImGui::Begin("IMGUI", &visible, m_Flags))
	{
		ImGui::End();
		return;
	}
	if (ImGui::Button("Hide/Unhind"))
	{
		helpers_Toggle(&m_Visible);
	}
	ImGui::End();
}

void MyImGUI::DrawMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			static bool show_app_metrics = false;
			if (ImGui::MenuItem("Toggle Theme", NULL, &show_app_metrics))
			{
				m_Event = 1;
				m_Theme++;
				if (m_Theme > m_ThemeMax)
				{
					m_Theme = 0;
				}
			}
			ImGui::EndMenu();
		}

		// Toggle open windows/views visibility
		if (ImGui::BeginMenu("Windows"))
		{
			std::map<eIMGuiWindowID, ImGUIWindow*>::iterator it;
			for (it = m_Windows.begin(); it != m_Windows.end(); it++)
			{
				if (ImGui::MenuItem(it->second->GetWindowTitle(), NULL, m_Windows[it->second->GetID()]->GetIsVisible()))
				{
				}
			}
			ImGui::EndMenu();
		}

		// Drag window position
		ImGui::SameLine(0, 10.0f); // spacing 10 to the right
		ImGui::SmallButton("Drag");

		if (ImGui::IsItemActive())
		{
			ImVec2 difference = ImGui::GetMouseDragDelta(0, 0.0f);
			int x, y;
			m_pWindow->GetWindowPosition(&x, &y);
			m_pWindow->SetWindowPosition(x + ((int)difference.x), y + ((int)difference.y));
		}

		ImGui::SameLine(0, 10.0f); // spacing 10 to the right
		ImGui::Text("FPS: %0.2f", g_FrameRate);

		ImGui::SameLine(g_WindowWidth - 60.0f, 0);
		if (ImGui::SmallButton("Close"))
		{
			m_pWindow->RequestClose();
		}

		ImGui::EndMainMenuBar();
	}
}

void MyImGUI::DrawMainWindow()
{
	// init window
	static bool MainMenuVisible = true;
	if (!ImGui::Begin("Main Menu", &MainMenuVisible, m_Flags))
	{
		ImGui::End();
		return;
	}
	// populate active windows button list
	ImGui::Separator();

	ImGui::End();
}

void MyImGUI::ProcessEvents()
{
	if (1) // Change theme
	{
		SetTheme(m_Theme);
	}
	m_Event = 0;
}

void MyImGUI::SetTheme(int theme)
{
	// ImGui::PushStyleColor(testCol, ImVec4(0, 0, 0, 1)); // text colour
	ImGui::SetupImGuiStyle(false, m_GlobalOpacity); // TODO: What is this again?
	std::vector<ImVec4> colors = GetStyleColorArray(theme);
	SetImGUIStyle(colors.data(), colors.size(), m_GlobalOpacity, false);
}
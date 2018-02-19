#include "BLUE_Main.h"

void SetImGUIStyle(ImVec4 a_Colors[], int a_Size, float a_Alpha, bool a_IsDark)
{
	ImGuiStyle& style = ImGui::GetStyle();
	// other values
	// TODO:: Store default values for non-color data
	style.Alpha = a_Alpha;
	style.FrameRounding = 3.0f;
	style.ChildWindowRounding = 3;
	style.WindowRounding = 3;
	style.GrabRounding = 1;
	style.GrabMinSize = 20;
	// Global alpha applies to everything in ImGui
	//WindowPadding = ImVec2(8, 8);      // Padding within a window
	//WindowMinSize = ImVec2(32, 32);    // Minimum window size
	//WindowRounding = 9.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	//WindowTitleAlign = ImVec2(0.0f, 0.5f);// Alignment for title bar text
	//ChildWindowRounding = 0.0f;             // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
	//FramePadding = ImVec2(4, 3);      // Padding within a framed rectangle (used by most widgets)
	//FrameRounding = 0.0f;             // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
	//ItemSpacing = ImVec2(8, 4);      // Horizontal and vertical spacing between widgets/lines
	//ItemInnerSpacing = ImVec2(4, 4);      // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
	//TouchExtraPadding = ImVec2(0, 0);      // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
	//IndentSpacing = 21.0f;            // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	//ColumnsMinSpacing = 6.0f;             // Minimum horizontal spacing between two columns
	//ScrollbarSize = 16.0f;            // Width of the vertical scrollbar, Height of the horizontal scrollbar
	//ScrollbarRounding = 9.0f;             // Radius of grab corners rounding for scrollbar
	//GrabMinSize = 10.0f;            // Minimum width/height of a grab box for slider/scrollbar
	//GrabRounding = 0.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	//ButtonTextAlign = ImVec2(0.5f, 0.5f);// Alignment of button text when button is larger than text.
	//DisplayWindowPadding = ImVec2(22, 22);    // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular windows.
	//DisplaySafeAreaPadding = ImVec2(4, 4);      // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
	//AntiAliasedLines = true;             // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
	//AntiAliasedShapes = true;             // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
	//CurveTessellationTol = 1.25f;            // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.

	// colors
	for (int i = 0; i < a_Size; i++)
	{
		style.Colors[i] = a_Colors[i]; // set color values
	}
	// alpha
	if (a_IsDark) // set alpha opacity
	{
		for (int i = 0; i <= ImGuiCol_COUNT; i++)
		{
			ImVec4& col = style.Colors[i];
			float H, S, V;
			ImGui::ColorConvertRGBtoHSV(col.x, col.y, col.z, H, S, V);

			if (S < 0.1f)
			{
				V = 1.0f - V;
			}
			ImGui::ColorConvertHSVtoRGB(H, S, V, col.x, col.y, col.z);
			if (col.w < 1.00f)
			{
				col.w *= a_Alpha;
			}
		}
	}
	else
	{
		for (int i = 0; i <= ImGuiCol_COUNT; i++)
		{
			ImVec4& col = style.Colors[i];
			if (col.w < 1.00f)
			{
				col.x *= a_Alpha;
				col.y *= a_Alpha;
				col.z *= a_Alpha;
				col.w *= a_Alpha;
			}
		}
	}
}

std::vector<ImVec4> GetStyleColorArray(int style)
{
	// TODO:: Use cJSON file reading/writing
	std::vector<ImVec4> colorList;
	if (style == 0)
	{
		// default
		colorList.push_back(ImVec4(0.90f, 0.90f, 0.90f, 1.00f)); // ImGuiCol_Text
		colorList.push_back(ImVec4(0.60f, 0.60f, 0.60f, 1.00f)); // ImGuiCol_TextDisabled
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 0.70f)); // ImGuiCol_WindowBg
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 0.00f)); // ImGuiCol_ChildWindowBg
		colorList.push_back(ImVec4(0.05f, 0.05f, 0.10f, 0.90f)); // ImGuiCol_PopupBg
		colorList.push_back(ImVec4(0.70f, 0.70f, 0.70f, 0.65f)); // ImGuiCol_Border
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 0.00f)); // ImGuiCol_BorderShadow
		colorList.push_back(ImVec4(0.80f, 0.80f, 0.80f, 0.30f)); // ImGuiCol_FrameBg
		colorList.push_back(ImVec4(0.90f, 0.80f, 0.80f, 0.40f)); // ImGuiCol_FrameBgHovered
		colorList.push_back(ImVec4(0.90f, 0.65f, 0.65f, 0.45f)); // ImGuiCol_FrameBgActive
		colorList.push_back(ImVec4(0.27f, 0.27f, 0.54f, 0.83f)); // ImGuiCol_TitleBg
		colorList.push_back(ImVec4(0.40f, 0.40f, 0.80f, 0.20f)); // ImGuiCol_TitleBgCollapsed
		colorList.push_back(ImVec4(0.32f, 0.32f, 0.63f, 0.87f)); // ImGuiCol_TitleBgActive
		colorList.push_back(ImVec4(0.40f, 0.40f, 0.55f, 0.80f)); // ImGuiCol_MenuBarBg
		colorList.push_back(ImVec4(0.20f, 0.25f, 0.30f, 0.60f)); // ImGuiCol_ScrollbarBg
		colorList.push_back(ImVec4(0.40f, 0.40f, 0.80f, 0.30f)); // ImGuiCol_ScrollbarGrab
		colorList.push_back(ImVec4(0.40f, 0.40f, 0.80f, 0.40f)); // ImGuiCol_ScrollbarGrabHovered
		colorList.push_back(ImVec4(0.80f, 0.50f, 0.50f, 0.40f)); // ImGuiCol_ScrollbarGrabActive
		colorList.push_back(ImVec4(0.20f, 0.20f, 0.20f, 0.99f)); // ImGuiCol_ComboBg
		colorList.push_back(ImVec4(0.90f, 0.90f, 0.90f, 0.50f)); // ImGuiCol_CheckMark
		colorList.push_back(ImVec4(1.00f, 1.00f, 1.00f, 0.30f)); // ImGuiCol_SliderGrab
		colorList.push_back(ImVec4(0.80f, 0.50f, 0.50f, 1.00f)); // ImGuiCol_SliderGrabActive
		colorList.push_back(ImVec4(0.67f, 0.40f, 0.40f, 0.60f)); // ImGuiCol_Button
		colorList.push_back(ImVec4(0.67f, 0.40f, 0.40f, 1.00f)); // ImGuiCol_ButtonHovered
		colorList.push_back(ImVec4(0.80f, 0.50f, 0.50f, 1.00f)); // ImGuiCol_ButtonActive
		colorList.push_back(ImVec4(0.40f, 0.40f, 0.90f, 0.45f)); // ImGuiCol_Header
		colorList.push_back(ImVec4(0.45f, 0.45f, 0.90f, 0.80f)); // ImGuiCol_HeaderHovered
		colorList.push_back(ImVec4(0.53f, 0.53f, 0.87f, 0.80f)); // ImGuiCol_HeaderActive
		colorList.push_back(ImVec4(0.50f, 0.50f, 0.50f, 1.00f)); // ImGuiCol_Column
		colorList.push_back(ImVec4(0.70f, 0.60f, 0.60f, 1.00f)); // ImGuiCol_ColumnHovered
		colorList.push_back(ImVec4(0.90f, 0.70f, 0.70f, 1.00f)); // ImGuiCol_ColumnActive
		colorList.push_back(ImVec4(1.00f, 1.00f, 1.00f, 0.30f)); // ImGuiCol_ResizeGrip
		colorList.push_back(ImVec4(1.00f, 1.00f, 1.00f, 0.60f)); // ImGuiCol_ResizeGripHovered
		colorList.push_back(ImVec4(1.00f, 1.00f, 1.00f, 0.90f)); // ImGuiCol_ResizeGripActive
		colorList.push_back(ImVec4(0.50f, 0.50f, 0.90f, 0.50f)); // ImGuiCol_CloseButton
		colorList.push_back(ImVec4(0.70f, 0.70f, 0.90f, 0.60f)); // ImGuiCol_CloseButtonHovered
		colorList.push_back(ImVec4(0.70f, 0.70f, 0.70f, 1.00f)); // ImGuiCol_CloseButtonActive
		colorList.push_back(ImVec4(1.00f, 1.00f, 1.00f, 1.00f)); // ImGuiCol_PlotLines
		colorList.push_back(ImVec4(0.90f, 0.70f, 0.00f, 1.00f)); // ImGuiCol_PlotLinesHovered
		colorList.push_back(ImVec4(0.90f, 0.70f, 0.00f, 1.00f)); // ImGuiCol_PlotHistogram
		colorList.push_back(ImVec4(1.00f, 0.60f, 0.00f, 1.00f)); // ImGuiCol_PlotHistogramHovered
		colorList.push_back(ImVec4(0.00f, 0.00f, 1.00f, 0.35f)); // ImGuiCol_TextSelectedBg
		colorList.push_back(ImVec4(0.20f, 0.20f, 0.20f, 0.35f)); // ImGuiCol_ModalWindowDarkening
	}
	if (style == 1)
	{
		// Taken from Doug Binks' github file ImGuiUtils.h
		// https://gist.github.com/dougbinks/8089b4bbaccaaf6fa204236978d165a9
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 1.00f)); // ImGuiCol_Text
		colorList.push_back(ImVec4(0.60f, 0.60f, 0.60f, 1.00f)); // ImGuiCol_TextDisabled
		colorList.push_back(ImVec4(0.94f, 0.94f, 0.94f, 0.94f)); // ImGuiCol_WindowBg
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 0.00f)); // ImGuiCol_ChildWindowBg
		colorList.push_back(ImVec4(1.00f, 1.00f, 1.00f, 0.94f)); // ImGuiCol_PopupBg
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 0.39f)); // ImGuiCol_Border
		colorList.push_back(ImVec4(1.00f, 1.00f, 1.00f, 0.10f)); // ImGuiCol_BorderShadow
		colorList.push_back(ImVec4(1.00f, 1.00f, 1.00f, 0.94f)); // ImGuiCol_FrameBg
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 0.40f)); // ImGuiCol_FrameBgHovered
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 0.67f)); // ImGuiCol_FrameBgActive
		colorList.push_back(ImVec4(0.96f, 0.96f, 0.96f, 1.00f)); // ImGuiCol_TitleBg
		colorList.push_back(ImVec4(1.00f, 1.00f, 1.00f, 0.51f)); // ImGuiCol_TitleBgCollapsed
		colorList.push_back(ImVec4(0.82f, 0.82f, 0.82f, 1.00f)); // ImGuiCol_TitleBgActive
		colorList.push_back(ImVec4(0.86f, 0.86f, 0.86f, 1.00f)); // ImGuiCol_MenuBarBg
		colorList.push_back(ImVec4(0.98f, 0.98f, 0.98f, 0.53f)); // ImGuiCol_ScrollbarBg
		colorList.push_back(ImVec4(0.69f, 0.69f, 0.69f, 1.00f)); // ImGuiCol_ScrollbarGrab
		colorList.push_back(ImVec4(0.59f, 0.59f, 0.59f, 1.00f)); // ImGuiCol_ScrollbarGrabHovered
		colorList.push_back(ImVec4(0.49f, 0.49f, 0.49f, 1.00f)); // ImGuiCol_ScrollbarGrabActive
		colorList.push_back(ImVec4(0.86f, 0.86f, 0.86f, 0.99f)); // ImGuiCol_ComboBg
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 1.00f)); // ImGuiCol_CheckMark

		colorList.push_back(ImVec4(0.24f, 0.52f, 0.88f, 1.00f)); // ImGuiCol_SliderGrab
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 1.00f)); // ImGuiCol_SliderGrabActive
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 0.40f)); // ImGuiCol_Button
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 1.00f)); // ImGuiCol_ButtonHovered
		colorList.push_back(ImVec4(0.06f, 0.53f, 0.98f, 1.00f)); // ImGuiCol_ButtonActive
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 0.31f)); // ImGuiCol_Header
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 0.80f)); // ImGuiCol_HeaderHovered
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 1.00f)); // ImGuiCol_HeaderActive

		colorList.push_back(ImVec4(0.39f, 0.39f, 0.39f, 1.00f)); // ImGuiCol_Column
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 0.78f)); // ImGuiCol_ColumnHovered
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 1.00f)); // ImGuiCol_ColumnActive
		colorList.push_back(ImVec4(1.00f, 1.00f, 1.00f, 0.50f)); // ImGuiCol_ResizeGrip
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 0.67f)); // ImGuiCol_ResizeGripHovered
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 0.95f)); // ImGuiCol_ResizeGripActive
		colorList.push_back(ImVec4(0.59f, 0.59f, 0.59f, 0.50f)); // ImGuiCol_CloseButton
		colorList.push_back(ImVec4(0.98f, 0.39f, 0.36f, 1.00f)); // ImGuiCol_CloseButtonHovered
		colorList.push_back(ImVec4(0.98f, 0.39f, 0.36f, 1.00f)); // ImGuiCol_CloseButtonActive

		colorList.push_back(ImVec4(0.39f, 0.39f, 0.39f, 1.00f)); // ImGuiCol_PlotLines
		colorList.push_back(ImVec4(1.00f, 0.43f, 0.35f, 1.00f)); // ImGuiCol_PlotLinesHovered
		colorList.push_back(ImVec4(0.90f, 0.70f, 0.00f, 1.00f)); // ImGuiCol_PlotHistogram
		colorList.push_back(ImVec4(1.00f, 0.60f, 0.00f, 1.00f)); // ImGuiCol_PlotHistogramHovered
		colorList.push_back(ImVec4(0.26f, 0.59f, 0.98f, 0.35f)); // ImGuiCol_TextSelectedBg
		colorList.push_back(ImVec4(0.20f, 0.20f, 0.20f, 0.35f)); // ImGuiCol_ModalWindowDarkening
	}
	else if (style == 2)
	{
		// Taken from enemymouse's github file gistfile1.txt
		// https://gist.github.com/enemymouse/c8aa24e247a1d7b9fc33d45091cbb8f0
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 1.00f));
		colorList.push_back(ImVec4(0.00f, 0.40f, 0.41f, 1.00f));
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 1.00f));
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 0.00f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.65f));
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 0.00f));
		colorList.push_back(ImVec4(0.44f, 0.80f, 0.80f, 0.18f));
		colorList.push_back(ImVec4(0.44f, 0.80f, 0.80f, 0.27f));
		colorList.push_back(ImVec4(0.44f, 0.81f, 0.86f, 0.66f));
		colorList.push_back(ImVec4(0.14f, 0.18f, 0.21f, 0.73f));
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 0.54f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.27f));
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 0.20f));
		colorList.push_back(ImVec4(0.22f, 0.29f, 0.30f, 0.71f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.44f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.74f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 1.00f));
		colorList.push_back(ImVec4(0.16f, 0.24f, 0.22f, 0.60f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.68f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.36f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.76f));
		colorList.push_back(ImVec4(0.00f, 0.65f, 0.65f, 0.46f));
		colorList.push_back(ImVec4(0.01f, 1.00f, 1.00f, 0.43f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.62f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.33f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.42f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.54f));
		colorList.push_back(ImVec4(0.00f, 0.50f, 0.50f, 0.33f));
		colorList.push_back(ImVec4(0.00f, 0.50f, 0.50f, 0.47f));
		colorList.push_back(ImVec4(0.00f, 0.70f, 0.70f, 1.00f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.54f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.74f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 1.00f));
		colorList.push_back(ImVec4(0.00f, 0.78f, 0.78f, 0.35f));
		colorList.push_back(ImVec4(0.00f, 0.78f, 0.78f, 0.47f));
		colorList.push_back(ImVec4(0.00f, 0.78f, 0.78f, 1.00f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 1.00f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 1.00f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 1.00f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 1.00f));
		colorList.push_back(ImVec4(0.00f, 1.00f, 1.00f, 0.22f));
		colorList.push_back(ImVec4(0.04f, 0.10f, 0.09f, 0.51f));
	}
	else if (style == 3)
	{
		// Custom style
		float hue = 0;
		float col_main_sat = 0;
		float col_main_val = 0;
		float col_back_sat = 1;
		float col_back_val = 10;
		float col_area_sat = 0;
		float col_area_val = 0;

		ImVec4 col_text = ImColor::HSV(hue / 255.f, 20.f / 255.f, 235.f / 255.f);
		ImVec4 col_main = ImColor::HSV(hue / 255.f, col_main_sat, col_main_val);
		ImVec4 col_back = ImColor::HSV(hue / 255.f, col_back_sat, col_back_val);
		ImVec4 col_area = ImColor::HSV(hue / 255.f, col_area_sat, col_area_val);

		colorList.push_back(ImVec4(col_text.x, col_text.y, col_text.z, 1.00f));
		colorList.push_back(ImVec4(col_text.x, col_text.y, col_text.z, 0.58f));
		colorList.push_back(ImVec4(col_back.x, col_back.y, col_back.z, 1.00f));
		colorList.push_back(ImVec4(col_area.x, col_area.y, col_area.z, 0.00f));
		colorList.push_back(ImVec4(col_text.x, col_text.y, col_text.z, 0.30f));
		colorList.push_back(ImVec4(0.00f, 0.00f, 0.00f, 0.00f));
		colorList.push_back(ImVec4(col_area.x, col_area.y, col_area.z, 1.00f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.68f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 1.00f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.45f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.35f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.78f));
		colorList.push_back(ImVec4(col_area.x, col_area.y, col_area.z, 0.57f));
		colorList.push_back(ImVec4(col_area.x, col_area.y, col_area.z, 1.00f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.31f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.78f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 1.00f));
		colorList.push_back(ImVec4(col_area.x, col_area.y, col_area.z, 1.00f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.80f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.24f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 1.00f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.44f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.86f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 1.00f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.76f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.86f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 1.00f));
		colorList.push_back(ImVec4(col_text.x, col_text.y, col_text.z, 0.32f));
		colorList.push_back(ImVec4(col_text.x, col_text.y, col_text.z, 0.78f));
		colorList.push_back(ImVec4(col_text.x, col_text.y, col_text.z, 1.00f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.20f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.78f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 1.00f));
		colorList.push_back(ImVec4(col_text.x, col_text.y, col_text.z, 0.16f));
		colorList.push_back(ImVec4(col_text.x, col_text.y, col_text.z, 0.39f));
		colorList.push_back(ImVec4(col_text.x, col_text.y, col_text.z, 1.00f));
		colorList.push_back(ImVec4(col_text.x, col_text.y, col_text.z, 0.63f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 1.00f));
		colorList.push_back(ImVec4(col_text.x, col_text.y, col_text.z, 0.63f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 1.00f));
		colorList.push_back(ImVec4(col_main.x, col_main.y, col_main.z, 0.43f));
		colorList.push_back(ImVec4(0.20f, 0.20f, 0.20f, 0.35f));
	}
	else if (style == 4)
	{
		//
	}

	return colorList;
}
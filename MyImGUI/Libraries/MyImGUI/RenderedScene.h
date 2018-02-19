#ifndef __RenderedScene_H__
#define __RenderedScene_H__

class GameCore;

class RenderedScene : public ImGUIWindow
{
public:
	RenderedScene(MyGLFW* window);
	~RenderedScene();

	void Draw();
	void SetTextureID(GLuint id) { test_image = (ImTextureID)id; };

private:
	GameCore* m_pGameCore = nullptr;
	MyGLFW* m_MainWindow = nullptr;
	ImVec4 test_color = ImColor(114, 144, 154);
	ImTextureID test_image = 0;
	ImVec2 window_size = ImVec2(300, 300);
};

#endif //__RenderedScene_H__

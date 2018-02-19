#include "Main.h"

extern MyGLFW* g_MainWindow = nullptr;
vec2 size = vec2(1920, 1080);
vec2 position = vec2(0, 0);

int main()
{
	g_MainWindow = new MyGLFW("Title", size, position);
	// g_MainWindow->Init();

	GLuint test1;
	GLuint test2;

	glewInit();

	double time = g_MainWindow->GetTime();

	glGenBuffers(1, &test1);
	glGenFramebuffers(1, &test2);
	while (g_MainWindow->CloseRequested() == false)
	{
		if (true)
		{
			int bp = 1;
		}
	}

	int bp = 1; // close

	return 0;
}
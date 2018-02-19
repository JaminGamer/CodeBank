#ifndef __CameraPanel_H__
#define __CameraPanel_H__

class Scene;
class Factory;

static const int maxCams = 15;

class CameraPanel : public ImGUIWindow
{
public:
	CameraPanel();
	~CameraPanel();

	void Draw();

private:
	int listbox_current_item = 0;
	Scene* m_Scene;
	Factory* m_Factory;
	bool lb_error = false;
	int itemsVisible = 10;
	const char* listbox_items[maxCams];
};

#endif //__CameraPanel_H__

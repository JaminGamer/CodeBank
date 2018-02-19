#ifndef __LightPanel_H__
#define __LightPanel_H__

class Scene;
class Factory;

static const int maxLights = 15;

class LightPanel : public ImGUIWindow
{
public:
	LightPanel();
	~LightPanel();

	void Draw();

private:
	int listbox_current_item = 0;
	Scene* m_Scene;
	Factory* m_Factory;
	bool lb_error = false;
	int itemsVisible = 10;
	const char* listbox_items[maxCams];
};

#endif //__LightPanel_H__

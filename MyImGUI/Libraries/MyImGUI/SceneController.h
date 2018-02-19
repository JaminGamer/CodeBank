#ifndef __SceneController_H__
#define __SceneController_H__

class Scene;
class Factory;
class GameObject;

class SceneController : public ImGUIWindow
{
public:
	SceneController();
	~SceneController();

	void Draw();

private:
	std::map<std::string, GameObject*> m_SceneObjects;
	std::string listbox_current_item = "Bob";
	int listbox_current_index = 0; // Used for tracking index of currently selected item
	Scene* m_Scene;
	Factory* m_Factory;
	bool lb_error = false;
	int itemsVisible = 8;
	const char* listbox_items[maxCams];
	const char* lb_text = "Names";

	// functions
	void DrawAddObject();
	void EditPosition();
	void SetupObjectList();
};

#endif //__SceneController_H__
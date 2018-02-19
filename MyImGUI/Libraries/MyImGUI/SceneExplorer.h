#ifndef __SceneExplorer_H__
#define __SceneExplorer_H__

class Scene;
class Factory;
class GameObject;

class SceneExplorer : public ImGUIWindow
{
public:
	SceneExplorer();
	~SceneExplorer();

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

	// functions
	void DrawAddObject();
	void EditPosition();
	void SetupObjectList();
};

#endif //__SceneExplorer_H__
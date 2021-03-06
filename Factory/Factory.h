#ifndef __Factory_H
#define __Factory_H

class ResourceManager;
class GameObject;
class Scene;
class MenuWindow;
class MenuItem;
class Menu;

class BLUE_Box_API Factory
{
public:
	Factory(ResourceManager* resources);
	~Factory();

	void ClearResources();

	/* Object creation */
	// Shapes
	GameObject* CreateCube(Scene* scene, vec3 position);
	GameObject* CreatePlane(Scene* scene, vec3 position);

	// Systems
	GameObject* CreateFreeCamera(Scene* scene, vec3 position);
	GameObject* CreateFirstPersonCamera(Scene* scene, vec3 position);
	GameObject* CreateThirdPersonCamera(Scene* scene, vec3 position);
	GameObject* CreateStaticCamera(Scene* scene, vec3 position);

	// Lighting
	GameObject* CreateLight(Scene* scene, vec3 position);

	// Scenery + Props
	GameObject* CreateSkyBox(Scene* scene, vec3 position);

	// Characters

	// Testing
	GameObject* CreateTestModel(Scene* scene, vec3 position); // Model

	/* Block_Menu */
	// Menus
	Menu* CreatePresetMenu1();
	Menu* CreatePresetMenu2();
	// MenuWindows
	MenuWindow* CreateBasicGridMenuWindow(vec2 size, int numItems);
	MenuWindow* CreateImageGridMenuWindow(vec2 size, int numItems);
	// MenuItems
	MenuItem* CreateBasicMenuItem();
	MenuItem* CreateImageMenuItem();

private:
	// Variables
	int m_Created = 0;
	ResourceManager* m_pResources = nullptr;

	/* Private functions */
	// GameObjects
	GameObject* CreateGameObject(Scene* scene) { return new GameObject(scene); };

	// Block_Menu
	Menu* CreateMenu();
	MenuWindow* CreateMenuWindow();
	MenuItem* CreateMenuItem();

	GameObject* InternalCreateCamera(Scene* scene, vec3 position, eCamType camType);
};

#endif //__Factory_H

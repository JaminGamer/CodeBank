#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

class Scene;
class Component;
class Routine;
class GameObject;

class GameObject
{
public:
	GameObject(Scene* scene);
	~GameObject();

	void Update(double deltatime);
	void Draw(GameObject* camera);

	void AddComponent(Component* component);
	void RemoveComponent(eComponentTags tag) { m_Components.erase(tag); };

	void AddRoutine(Routine* routine);
	void RemoveRoutine(Routine* routine);

	void AddUpdateRoutine(Routine* routine);
	void AddDrawRoutine(Routine* routine);

	void Reset();
	void Activate();
	void Deactivate();

	/* Getters + Setters */
	// getters
	std::string GetName() { return m_Name; };
	vec3 GetPosition() { return m_Position; };
	vec3 GetRotation() { return m_Rotation; };
	vec3 GetScale() { return m_Scale; };
	Component* GetComponent(eComponentTags tag);
	int GetRenderOrder() { return m_RenderOrder; };
	Scene* GetScene() { return m_pScene; };
	Routine* GetFirstUpdateRoutine(eRoutineTypes type); // first by tag
	eGameObjectTags GetTag() { return m_Tag; }

	// setters
	void UpdatePosition(vec3 position) { m_Position = position; }; // box 2d
	void UpdateRotation(vec3 rotation) { m_Rotation = rotation; }; // box 2d
	void SetName(std::string name) { m_Name = name; };
	void SetPosition(vec3 position);
	void SetRotation(vec3 rotation);
	void SetScale(vec3 scale) { m_Scale = scale; };
	void SetRenderOrder(int order) { m_RenderOrder = order; };
	void SetTag(eGameObjectTags tag) { m_Tag = tag; }

private:
	Scene* m_pScene = nullptr;
	std::string m_Name = "Uninitialized";
	eGameObjectTags m_Tag = GO_Tag_Null;

	vec3 m_Position = 0;
	vec3 m_Rotation = 0;
	vec3 m_Scale = 1.0f;

	int m_BaseUpdateListSize = 5;
	std::vector<Routine*> m_UpdateList;
	int m_BaseDrawListSize = 2;
	std::vector<Routine*> m_DrawList;
	int m_RenderOrder = 100;

	std::map<eComponentTags, Component*> m_Components;

	// Direction vectors
	float m_FacingAngle = 0; // Y axis
	vec3 m_Forward = vec3(0,0,1);
	vec3 m_Up = vec3(0, 1, 0);
	vec3 m_Right = vec3(1, 0, 0);
};

#endif //!__GAMEOBJECT_H_

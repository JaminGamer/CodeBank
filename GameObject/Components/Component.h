#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class GameObject;

class Component
{
public:
	virtual ~Component();

	virtual void Reset() {};
	virtual void Activate() {};
	virtual void Deactivate() {};
	//virtual void CleanUp() {};

	/* Getters + Setters */
	// getters
	GameObject* GetParent() { return m_pParent; };
	eComponentTags GetTag() { return m_ComponentTag; };

	// setters
	void SetParent(GameObject* a_Parent) { m_pParent = a_Parent; };
	void SetComponentTag(eComponentTags a_Tag) {	m_ComponentTag = a_Tag; };

protected:
	Component(); // cannot instantiate a Component()
	GameObject* m_pParent = nullptr;
	eComponentTags m_ComponentTag = Component_Null;
};

#endif //__COMPONENT_H__

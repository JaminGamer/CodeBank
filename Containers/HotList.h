#ifndef __HotList_H_
#define __HotList_H_

// HotList<> is a smart container for objects that have different states
// such as enabled/disabled.
// The At() function will return values from the active or "Hot" list.

// This container aids to avoid unnecessary state checks ex.
// for() { if(active) { func();} }

// The inactive or "Cool" list can be accessed by using specific functions
// which handle only the "Cool" list.

template <class HOT_OBJECT>
struct _HotNode
{
	HOT_OBJECT value;
	bool isHot; // Not necessary if properly transition from lists

	_HotNode<HOT_OBJECT>* next = nullptr;
	_HotNode<HOT_OBJECT>* prev = nullptr;

	_HotNode() {}
	_HotNode(HOT_OBJECT value1) { value = value1; }
};

template <class HOT_OBJECT>
class HotList
{
public:
	HotList();
	~HotList();

	HOT_OBJECT HotAt(int index);
	HOT_OBJECT ColdAt(int index);

	HOT_OBJECT FindIfHot(int index) {};
	HOT_OBJECT FindIfCold(int index) {};

	void InsertBeforeHot(int index, HOT_OBJECT item) {};
	void InsertBeforeCold(int index, HOT_OBJECT item) {};

	void PushHotBack() {};
	void PushHotFront() {};

	void PushColdBack() {};
	void PushColdFront() {};

private:
	void Heat() {}; // Move item to active (hot) list
	void Cool() {}; // Move item to inactive (cold) list

	// Hot - Active
	_HotNode<HOT_OBJECT>* m_HotHead = nullptr; // first

	// Cold - Inactive
	_HotNode<HOT_OBJECT>* m_ColdHead = nullptr; // first

	// Utility
	_HotNode<HOT_OBJECT>* _NodeAtIndex(_HotNode<HOT_OBJECT>* head, int index);
};

template <class HOT_OBJECT>
HotList<HOT_OBJECT>::HotList()
{
}

template <class HOT_OBJECT>
HotList<HOT_OBJECT>::~HotList()
{
	// Do not delete objects in Destructor.
	// Stack variables will try to delete their values when
	// you may not want them to. Example...
	// List t_List = Scene->GetList();
	// t_List will try to delete the Scene's list values when
	// it goes out of scope.
	// Better to manually call Clear() in the Scene's Destructor.
}

template <class HOT_OBJECT>
HOT_OBJECT HotList<HOT_OBJECT>::HotAt(int index)
{
	// hot list
	_NodeAtIndex(m_HotHead, index);
}

template <class HOT_OBJECT>
HOT_OBJECT HotList<HOT_OBJECT>::ColdAt(int index)
{
	// cold list
	_NodeAtIndex(m_ColdHead, index);
}
// Utility
template <class HOT_OBJECT>
_HotNode<HOT_OBJECT>* HotList<HOT_OBJECT>::_NodeAtIndex(_HotNode<HOT_OBJECT>* head, int index)
{
	// if (index > m_Count - 1) { OutputMessage("\nMyLinkedList: At(index) index out of range!\n"); assert(0); } // out of range
	_HotNode<HOT_OBJECT>* t_Iterator = head;

	for (int i = 0; i < index; i++)
	{
		t_Iterator = t_Iterator->next;
	}

	return t_Iterator;
}

#endif // __HotList_H_
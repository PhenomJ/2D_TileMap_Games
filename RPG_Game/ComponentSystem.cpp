#include "ComponentSystem.h"
#include "Component.h"

ComponentSystem* ComponentSystem::_instance = NULL;

ComponentSystem::ComponentSystem()
{
	_componentMap.clear();
}

ComponentSystem::~ComponentSystem()
{
	
}

ComponentSystem* ComponentSystem::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new ComponentSystem();
	}
	return _instance;
}

//void ComponentSystem::AddComponent(LPCWSTR name, Component* thisComponent) // LPCWSTR로 하면 왜 안되는지
//{
//	if (thisComponent != NULL)
//	{
//		std::map<LPCWSTR, Component*>::iterator itr = _componentMap.find(name);
//
//		if (itr == _componentMap.end())
//		{
//			_componentMap[name] = thisComponent;
//		}
//	}
//}

void ComponentSystem::AddComponent(std::wstring name, Component* thisComponent)
{
	if (thisComponent != NULL)
	{
		std::map<std::wstring, Component*>::iterator itr = _componentMap.find(name);
	
		if (itr == _componentMap.end())
		{
			_componentMap[name] = thisComponent;
		}
	}
}

void ComponentSystem::RemoveAllComponents()
{
	//for (std::map<LPCWSTR, Component*>::iterator itr = _componentMap.begin(); itr != _componentMap.end(); itr++)
	for (std::map<std::wstring, Component*>::iterator itr = _componentMap.begin(); itr != _componentMap.end(); itr++)
	{
		delete itr->second;
	}
	_componentMap.clear();
}

Component* ComponentSystem::FindComponent(std::wstring name)
{
	{
		std::map<std::wstring, Component*>::iterator itr = _componentMap.find(name);
		if (itr != _componentMap.end())
		{
			return itr->second;
		}

		return 0;
	}
}
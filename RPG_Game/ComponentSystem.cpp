#include "ComponentSystem.h"
#include "Component.h"

ComponentSystem* ComponentSystem::_instance = NULL;

ComponentSystem::ComponentSystem()
{

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

void ComponentSystem::AddComponent(LPCWSTR name, Component* thisComponent)
{

}

void ComponentSystem::RemoveAllComponents()
{

}
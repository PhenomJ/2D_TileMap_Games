#pragma once
#include <Windows.h>
#include <map>
#include <string>


class Component;

class ComponentSystem
{
private:
	static ComponentSystem* _instance;
	ComponentSystem();

public:
	~ComponentSystem();
	static ComponentSystem* GetInstance();
	//void AddComponent(LPCWSTR name,Component* thisComponent);
	void AddComponent(std::wstring name, Component* thisComponent);
	void RemoveAllComponents();
	Component* FindComponent(std::wstring name);

private:
	//std::map<LPCWSTR, Component*> _componentMap;
	std::map<std::wstring, Component*> _componentMap;
};
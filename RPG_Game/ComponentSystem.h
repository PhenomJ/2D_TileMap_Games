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

	void AddComponent(std::wstring name, Component* thisComponent);
	void RemoveAllComponents();
	Component* FindComponent(std::wstring name);
	
	//Message
	void SendMessage(Component* sendComponent, Component* receiveComponent, std::wstring message);
private:
	std::map<std::wstring, Component*> _componentMap;
};
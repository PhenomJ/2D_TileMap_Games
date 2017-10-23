#pragma once
#include <Windows.h>

class Component;

class ComponentSystem
{
private:
	static ComponentSystem* _instance;
	ComponentSystem();

public:
	~ComponentSystem();
	static ComponentSystem* GetInstance();
	void AddComponent(LPCWSTR name,Component* thisComponent);
	void RemoveAllComponents();
};
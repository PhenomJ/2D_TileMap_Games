#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include "ComponentMessage.h"

class Component;
enum eComponentType;

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
	Component* FindComponentInRange(Component* mapComp,Component* chaser, int range, std::vector<eComponentType> typeList);
	void ProcessMessageQueue();
	void Update(float deltaTime);
	//Message
	void SendMsg(const sComponentMsgParam &msgParam);
	void ClearMessageQueue();

private:
	std::map<std::wstring, Component*> _componentMap;
	std::queue<sComponentMsgParam> _msgQueue;
};
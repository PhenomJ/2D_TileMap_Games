#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <vector>

struct sComponentMsgParam;
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
	Component* FindComponentInRange(Component* chaser, int range, std::vector<eComponentType> typeList);

	//Message
	void SendMsg(std::wstring message, Component* receiver, const sComponentMsgParam &msgParam);
private:
	std::map<std::wstring, Component*> _componentMap;
};
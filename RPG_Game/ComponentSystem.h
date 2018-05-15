#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include "ComponentMessage.h"

class Component;
class TileCell;
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
	std::list<TileCell*> ComponentSystem::FindTileCellInRange(Component* mapComp, Component* thisComponent, int range, std::vector<eComponentType> typeList);
	Component* FindComponentInAllMap(Component* mapComp, Component* chaser, std::vector<eComponentType> typeList);
	void ProcessMessageQueue();
	void Update(float deltaTime);

	//Message
	void SendMsg(const sComponentMsgParam &msgParam);
	void ClearMessageQueue();

	//Game of Life
	void RemoveComponent(Component* tileCharacter);

private:
	std::map<std::wstring, Component*> _componentMap;
	std::queue<sComponentMsgParam> _msgQueue;
};
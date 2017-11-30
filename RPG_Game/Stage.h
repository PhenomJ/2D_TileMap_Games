#pragma once
#include <string>
#include <list>

class Component;
class Map;

class Stage
{
public:
	Stage();
	~Stage();

public:
	void Init(std::wstring name);
	void Release();
	void Update(float deltaTime);
	void Render();
	void Reset();
	Map* GetMap() { return _map; }

private:
	std::list<Component*> _componentList;
	Map* _map;

	//Game of Life
public:
	void CreateLifeNPC(Component* comp);

	void DestroyLifeNpc(int tileX, int tileY, Component* tileCharacter);
	void CheckDestoryNPC(Component* tileCharacter);
	void UpdateRemoveComponentList();
	void UpdateCreateComponentList();
private:
	int _lifeNpcCount;
	std::list<Component*> _removeComponentList;
	std::list<Component*> _createBaseComponentList;
};
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
	void CreateLifeNPC(int tileX, int tileY);

	void DestroyLifeNpc(int tileX, int tileY, Component* tileCharacter);

private:
	int _lifeNpcCount;

};
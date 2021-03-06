#pragma once
#include <string>
#include <list>
#include <map>


class TileCell;
class Component;
class Map;
class GameGen;

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
	void UpdateRemoveComponentList();
	void UpdateCreateComponentList();
	void AddStageComponent(Component* component);
	void SetMap(Map* map) { _map = map; }
	void GameSet(std::wstring mapName);
	void AllComponentInit();

private:
	std::list<Component*> _removeComponentList;
	std::list<Component*> _createBaseComponentList;
	GameGen* _game;
	std::map<std::wstring, GameGen*> _gameMapGen;

	// FindingPath
public:
	void CreateFindingPathMark(TileCell* reverseTileCell);

	void CreateMark(TileCell* tileCell);
};
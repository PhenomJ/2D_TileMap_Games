#pragma once
#include <string>

class Stage;
class Component;
class Map;

class GameGen
{
public:
	GameGen(Stage* stage);
	~GameGen();

protected:
	Stage* _stage;
	std::wstring _name;

	int _npcCount;
	Map* _map;

public:
	virtual Component* CreateNpc(std::wstring scriptName, std::wstring textureName) { return NULL; };
	void SetName(std::wstring name);
	virtual void CreateComponents(std::wstring mapName);
};
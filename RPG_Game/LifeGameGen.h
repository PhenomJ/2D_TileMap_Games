#pragma once
#include <string>
#include "GameGen.h"

class Component;

class LifeGameGen : public GameGen
{
public: 
	LifeGameGen(Stage* stage);
	~LifeGameGen();

private:
	int _npcCount;
	std::wstring _name;
	int _lifeNpcCount;
	
public:
	Component* CreateNpc(std::wstring scriptName, std::wstring textureName);
	void CreateComponents(std::wstring mapName);
};
#pragma once
#include <string>
#include "GameGen.h"

class Component;
class Stage;

class LifeGameGen : public GameGen

{
public: 
	LifeGameGen(Stage* stage);
	~LifeGameGen();

private:
	int _npcCount;

public:
	Component* CreateLifeNpc(std::wstring scriptName, std::wstring textureName);
	void CreateComponents();
};
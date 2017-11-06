#pragma once
#include "Character.h"

class Monster : public Character
{
public:
	Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName);
	~Monster();


	//AI
public:
//	void UpdateAI(float deltaTime);
};
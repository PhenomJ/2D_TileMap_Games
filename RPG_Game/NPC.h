#pragma once
#include "Character.h"

class NPC : public Character
{
public:
	NPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName);
	~NPC();

	//void UpdateMove(float deltatime);
	//AI
public:
	//void UpdateAI(float deltaTime);
};
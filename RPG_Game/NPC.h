#pragma once
#include "Character.h"

class NPC : public Character
{
public:
	NPC(LPCWSTR name, LPCWSTR spriteName);
	~NPC();


	//AI
public:
	//void UpdateAI(float deltaTime);
};
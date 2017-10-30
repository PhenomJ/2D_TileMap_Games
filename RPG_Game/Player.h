#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(LPCWSTR name);
	~Player();
	
	//AI
	void UpdateAI(float deltaTime);

	//MOVE
	void UpdateMove(float deltaTime);
};
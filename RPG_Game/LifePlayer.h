#pragma once
#include "Player.h"

class LifePlayer : public Player
{
public:
	LifePlayer(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName);
	~LifePlayer();

	//AI
	void InitState();
};
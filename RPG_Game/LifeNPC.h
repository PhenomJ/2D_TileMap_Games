#pragma once
#include "Character.h"

class LifeNPC : public Character
{
public:
	LifeNPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName);
	~LifeNPC();

public:
	void UpdateAI(float deltaTime);

	void Init(int tileX, int tileY);
	void Update(float deltaTime);
	void Render();
};
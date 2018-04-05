#pragma once
#include "Character.h"

class FindingPathNPC : public Character
{
public:
	FindingPathNPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName);
	~FindingPathNPC();

public:
	void UpdateAI(float deltaTime);

	void Init(int tileX, int tileY);
	void Update(float deltaTime);
	void Render();
};
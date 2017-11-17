#pragma once
#include "Character.h"

class Monster : public Character
{
public:
	Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName);
	~Monster();
	void UpdateAI(float deltaTime);

private:
	Component* Collision(std::list<Component*> &collisionList);
};
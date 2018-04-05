#pragma once
#include "Monster.h"

class Component;

class FindingPathMonster : public Monster
{
public:
	FindingPathMonster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName);
	~FindingPathMonster();

public:
	void UpdateAI(float deltaTime);
	Component* Collision(std::list<Component*> &collisionList);
};
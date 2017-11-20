#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName);
	~Player();
	
	//AI
	void UpdateAI(float deltaTime);


	//Collision
	Component* Collision(std::list<Component*> &collisionList);
	//MOVE
	//void UpdateMove(float deltaTime);
	//void MoveDeltaPosition(float deltaX, float deltaY);
};
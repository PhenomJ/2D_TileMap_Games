#pragma once
#include "State.h"

class Character;
class MoveState : public State
{
public:
	MoveState();
	~MoveState();

public:
	void Init(Character* character);
	void Start();
	void Stop();
	void Update(float deltaTime);

private:
	float _moveDuration;
	
};
#pragma once
#include "State.h"

class AttackState : public State
{
public:
	AttackState();
	~AttackState();

public:
	void Init(Character* character);
	void Update(float deltaTime);

	void Start();
	void Stop();

	void Release();
	void Render();
	void Reset();
};
#pragma once
#include "State.h"

class DeadState : public State
{
public:
	DeadState();
	~DeadState();

public:
	void Init(Character* character);
	void Update(float deltaTime);

	void Start();
	void Stop();

	void Release();
	void Render();
	void Reset();

	void CreateSprite();
};
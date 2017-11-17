#pragma once
#include "State.h"

class DefenseState : public State
{
public:
	DefenseState();
	~DefenseState();

public:
	void Init(Character* character);
	void Update(float deltaTime);

	void Start();
	void Stop();

	void Release();
	void Render();
	void Reset();

};
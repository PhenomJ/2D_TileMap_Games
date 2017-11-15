#pragma once

class Character;
class State
{
public:
	State();
	~State();

public:
	virtual void Init(Character* character);
	virtual void Update(float deltaTime);
	virtual void Start();
	virtual void Stop();


protected:
	Character* _character;
};
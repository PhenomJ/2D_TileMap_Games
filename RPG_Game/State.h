#pragma once
#include <vector>

class Sprite;
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

	virtual void Release();
	virtual void Render();
	virtual void Reset();

protected:
	std::vector<Sprite*> _spriteList;
	Character* _character;
};
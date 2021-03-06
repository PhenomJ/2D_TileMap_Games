#pragma once
#include <vector>
#include "TurnManager.h"

class Sprite;
class Character;
enum eStateType;

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

	virtual void CreateSprite();
	void NextState(eStateType type);


protected:
	std::vector<Sprite*> _spriteList;
	Character* _character;
	eStateType _nextState;
	eStateType _getState;
};
#pragma once
#include "State.h"
#include <stack>
#include <list>

class TileCell;
class Character;

class FindingPathMoveState : public State
{
public:
	FindingPathMoveState();
	~FindingPathMoveState();

public:
	void Init(Character* character);
	void Start();
	void Stop();
	void Update(float deltaTime);

private:
	float _moveDuration;
	std::stack<TileCell*> _pathTileCellStack;

	//test
private:
	std::list<TileCell*> _changeColorInfo;
};
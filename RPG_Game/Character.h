#pragma once
#include <Windows.h>
#include "Component.h"
#include <vector>

class Sprite;
class Character : public Component
{
public:
	Character(LPCWSTR name);
	Character() {}
	~Character();

	enum eDirection
	{
		LEFT, RIGHT, UP, DOWN
	};

public:
	void Init();
	void Deinit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();	

protected:
	std::vector<Sprite*> _spriteList;
	float _x;
	float _y;

protected:
	
	int _map;

	// AI
protected:
	bool _isMoving;
	float _moveSpeed;
	float _movingDuration;

	eDirection _currentDirection;
	
public:
	virtual void UpdateAI(float deltaTime) {};
	void InitMove();
	void MoveStart(eDirection direction);
	virtual void UpdateMove(float deltaTime);
	
	virtual void MoveDeltaPosition(float deltaX, float deltaY);

	//Move
protected:
	float _targetX;
	float _targetY;

	float _moveDistanceperTimeX;
	float _moveDistanceperTimeY;
};
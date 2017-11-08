#pragma once
#include <Windows.h>
#include "Component.h"
#include <vector>
#include <list>
#include <string>

class Sprite;
class Character : public Component
{
public:
	Character(LPCWSTR name, LPCWSTR scriptName ,LPCWSTR spriteName);
	Character() {}
	~Character();

	enum eDirection
	{
		LEFT, RIGHT, UP, DOWN, NONE
	};

public:
	void Init();
	void Deinit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();	

	void SetPosition(float tileX, float tileY);


protected:
	std::vector<Sprite*> _spriteList;
	float _x;
	float _y;

	std::wstring _spriteName;
	std::wstring _scriptName;
protected:
	
	int _map;

protected:
	bool _isMoving;
	float _moveSpeed;
	float _movingDuration;

	eDirection _currentDirection;
	
public:
	void InitMove();
	void MoveStart(eDirection direction);
	virtual void UpdateMove(float deltaTime);
	virtual void MoveDeltaPosition(float deltaX, float deltaY);
	virtual void UpdateAI(float deltaTime);

protected:
	float _targetX;
	float _targetY;

};
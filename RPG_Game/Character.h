#pragma once
#include <Windows.h>
#include "Component.h"
#include <vector>
#include <list>
#include <string>

class Sprite;
class State;

enum eStateType
{
	ET_IDLE,
	ET_MOVE,
};

enum eDirection
{
	LEFT, RIGHT, UP, DOWN, NONE
};

class Character : public Component
{
public:
	Character(LPCWSTR name, LPCWSTR scriptName ,LPCWSTR spriteName);
	Character() {}
	~Character();

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
	State* _state;
	std::wstring _spriteName;
	std::wstring _scriptName;

protected:
	float _moveSpeed;
	

	eDirection _currentDirection;
	
public:
	void InitMove();
	void MoveStart(int newTileX, int newTileY);
	virtual void MoveDeltaPosition(float deltaX, float deltaY);
	virtual void UpdateAI(float deltaTime);
	eDirection GetDirection() {	return _currentDirection; };
	void ReceiveMessage(const sComponentMsgParam &msgParam);
	virtual void Collision(std::list<Component*>& collisionList);
	float GetMoveTime() { return _moveSpeed; };
	void MoveStop();
	void Moving(float deltaTime);
	bool IsMoving();
	void ChangeState(eStateType stateType);
protected:
	float _targetX;
	float _targetY;
	int _attackPoint;
	bool _isMoving;
};
#pragma once
#include <Windows.h>
#include "Component.h"
#include <vector>
#include <list>
#include <string>
#include <map>

class Sprite;
class State;

enum eStateType
{
	ET_IDLE,
	ET_MOVE,
	ET_ATTACK,
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
	float GetMoveTime() { return _moveSpeed; }
	void MoveStop();
	void Moving(float deltaTime);
	bool IsMoving();
	void ChangeState(eStateType stateType);

	std::wstring GetTextureFileName();
	std::wstring GetScriptFileName();

	float GetX() { return _x; }
	float GetY() { return _y; }

	Component* GetTarget() { return _target; }
	int GetAttackPoint() { return _attackPoint; }
	void ResetTarget() { _target = NULL; }
protected:
	float _targetX;
	float _targetY;
	int _attackPoint;
	bool _isMoving;
	Component* _target;

private:
	std::map<eStateType, State*> _stateMap;
};
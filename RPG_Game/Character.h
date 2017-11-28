#pragma once
#include <Windows.h>
#include "Component.h"
#include <vector>
#include <list>
#include <string>
#include <map>

class Sprite;
class State;
class Font;

enum eStateType
{
	ET_IDLE,
	ET_MOVE,
	ET_ATTACK,
	ET_DEFENCE,
	ET_DEAD,
	ET_NONE
};

enum eDirection
{
	UP, DOWN, LEFT, RIGHT, NONE
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

protected:
	State* _state;

	//Move
protected:
	float _moveSpeed;
	eDirection _currentDirection;
	bool _isMoving;

public:
	void InitMove();
	void MoveStart(int newTileX, int newTileY);
	
	float GetMoveTime() { return _moveSpeed; }
	void MoveStop();
	void Moving(float deltaTime);
	bool IsMoving();

	virtual void MoveDeltaPosition(float deltaX, float deltaY);
	virtual void UpdateAI(float deltaTime);

	eDirection GetDirection() {	return _currentDirection; };

	//Message
public:
	void ReceiveMessage(const sComponentMsgParam &msgParam);
	virtual Component* Collision(std::list<Component*>& collisionList);
	void ChangeState(eStateType stateType);


public:
	//Input Name
	std::wstring GetTextureFileName();
	std::wstring GetScriptFileName();

protected:
	std::wstring _spriteName;
	std::wstring _scriptName;

public:
	//Position
	float _x;
	float _y;
	float GetX() { return _x; }
	float GetY() { return _y; }
	void SetPosition(float tileX, float tileY);

	//Attack
public:
	Component* GetTarget() { return _target; }
	int GetAttackPoint() { return _attackPoint; }
	void ResetTarget() { _target = NULL; }

protected:
	int _attackPoint;
	int _attackedPoint;
	Component* _target;
	float _targetX;
	float _targetY;

	// Common
public:
	void DecreaseHP(int attackPoint);
	void IncreaseHP(int recovery);
	int GetAttackedPoint() { return _attackedPoint; }
	void SetTarget(Component* target);

	//CoolDown
public:
	bool IsCoolDown();
	void ResetCoolDown();
	void UpdateAttackCoolDown(float deltaTime);

protected:
	float _attackCoolDownDuration;
	float _attackCoolDown;

private:
	std::map<eStateType, State*> _stateMap;

	//Font
protected:
	Font* _font;

public:
	void UpdateText();

	//Game of Life
public:
	void Init(int tileX, int tileY);
};
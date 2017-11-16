#pragma once
#include <Windows.h>
#include <string>
#include "ComponentMessage.h"

enum eComponentType
{
	CT_PLAYER,
	CT_MONSTER,
	CT_NPC,
	CT_TILEOBJECT,
	CT_NONE
};

class Component
{
public:
	Component() {}
	Component (LPCWSTR name);
	virtual ~Component();

public:
	virtual void Init() = 0;
	virtual void Deinit() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void Reset() = 0;
	virtual void MoveDeltaPosition(float deltaX, float deltaY) {}
	virtual void SetPosition(float posX, float posY) {}

	void SetCanMove(bool canMove) { _canMove = canMove; }
	bool CanMove();

	//
	int GetTileX();
	int GetTileY();



	float GetMoveDeltaX();
	float GetMoveDeltaY();


	eComponentType GetType();

	//Message
	virtual void ReceiveMessage(const sComponentMsgParam &msgParam);

	bool IsLive();
protected:
	LPCWSTR _name;
	
	bool _canMove = false;
	int _tileX;
	int _tileY;
	int _hp;
	float _moveDistanceperTimeX;
	float _moveDistanceperTimeY;
	bool _isLive = true;
	eComponentType _type;
};
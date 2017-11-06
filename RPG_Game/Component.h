#pragma once
#include <Windows.h>
#include <string>

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


	//Message
	virtual void receiveMessage(Component* sendComponent, std::wstring message);
protected:
	LPCWSTR _name;
	
	bool _canMove = false;
	int _tileX;
	int _tileY;
};
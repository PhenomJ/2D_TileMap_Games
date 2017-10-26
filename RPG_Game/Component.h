#pragma once
#include <Windows.h>


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

protected:
	LPCWSTR _name;
};
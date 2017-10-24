#pragma once
#include <Windows.h>
#include "Component.h"

class Sprite;
class Character : public Component
{
public:
	Character(LPCWSTR name);
	~Character();

public:
	void Init();
	void Deinit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
	void Move(int x, int y);

private:
	
	Sprite* _sprite;
	float _x;
	float _y;

private:
	int _tileX;
	int _tileY;
	int _map;
};
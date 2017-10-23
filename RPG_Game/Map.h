#pragma once
#include <Windows.h>
#include <vector>
#include <fstream>
#include "Component.h"

class Sprite;

class Map : public Component
{
public:
	Map(LPCWSTR fileName);
	~Map();

public:
	void Init();
	void Deinit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	void Scroll(float deltaX, float deltaY);

private:
	std::vector<std::vector<Sprite*>> _tileMap;
	float _startX;
	float _startY;
	float _deltaX;
	float _deltaY;
	int _width;
	int _height;

	std::vector<Sprite*> _spriteList;
};
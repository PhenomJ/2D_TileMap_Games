#pragma once
#include <Windows.h>
#include <vector>
#include <fstream>

//#define MAP_HEIGHT 16
//#define MAP_WIDTH 16

class Sprite;
class Map
{
public:
	Map(LPCWSTR fileName);
	~Map();
	void Init();
	void Deinit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
	void Scroll(float deltaX, float deltaY);

private:
	//Sprite* _TileMap[MAP_HEIGHT][MAP_WIDTH];
	std::vector<std::vector<Sprite*>> _tileMap;
	float _startX;
	float _startY;
	float _deltaX;
	float _deltaY;
	int _width;
	int _height;

	std::vector<Sprite*> _spriteList;
};
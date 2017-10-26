#pragma once
#include <Windows.h>
#include <vector>
#include <fstream>
#include "Component.h"

class Sprite;
class TileCell;


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

	float GetPositionX(int tileX, int tileY);
	float GetPositionY(int tileX, int tileY);
	void SetTileComponent(int tileX, int tileY, Component* thisComponent, bool isRender);
	void ResetTileComponent(int _tileX,int _tileY, Component* thisComponent);
	
private:
	
	std::vector<std::vector <TileCell*>> _tileMap;
	float _startX;
	float _startY;
	float _deltaX;
	float _deltaY;
	int _width;
	int _height;
	int _tileSize = 32;
	std::vector<Sprite*> _spriteList;
};
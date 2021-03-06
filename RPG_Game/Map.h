#pragma once
#include <Windows.h>
#include <vector>
#include <fstream>
#include <list>
#include "Component.h"
#include "GlobalType.h"

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
	

	bool CanMoveTileMap(int newTileX, int newTileY);
	bool CanMoveTileMap(TilePosition nextTilePosition) { return CanMoveTileMap(nextTilePosition.x, nextTilePosition.y); };


	bool GetTileCollisionList(int tileX, int tileY, std::list<Component*> &collisionList);
	std::list<Component*> GetTileComponentList(int tileX, int tileY);
	void InitViewer(Component* viewer);

	int GetWidth();
	int GetHeight();

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
	Component* _viewer;

	// Finding Path
public:
	TileCell* GetTileCell(int x, int y) { return _tileMap[y][x]; };
	TileCell* GetTileCell(TilePosition nextTilePos) { return _tileMap[nextTilePos.y][nextTilePos.x]; };

	//Mouse Input

public:
	TileCell* FindTileCellWithMousePosition(int mouseX, int mouseY);

	//Test
};
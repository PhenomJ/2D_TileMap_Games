#include "Map.h"
#include "GameSystem.h"
#include "Sprite.h"
#include "TileCell.h"
#include "TileObject.h"

Map::Map(LPCWSTR name) : Component(name)
{
	_startX = 0;
	_startY = 0;
	_deltaX = 0;
	_deltaY = 0;
	_spriteList.clear();
}

Map::~Map()
{

}

void Map::Init()
{
	int srcX = 0;
	int srcY = 0;


	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			Sprite* sprite = new Sprite(L"MapSprite.png", L"MapSprite.json");
			sprite->Init(srcX, srcY, _tileSize, _tileSize, 1.0f);
			_spriteList.push_back(sprite);
			srcX += _tileSize;
		}

		srcX = 0;
		srcY += _tileSize;
	}
	_width = 16;
	_height = 16;

	// Load Map Script layer1
	{
		int line = 0;
		char record[1024];
		std::ifstream infile("MapData_layer1.csv");
		while (!infile.eof())
		{
			infile.getline(record, 1024);

			char* token = strtok(record, ",");

			switch (line)
			{
			case 0:
				if (NULL != token)
				{
					token = strtok(NULL, ",");
					_width = atoi(token);
					token = strtok(NULL, ",");
					_height = atoi(token);
				}
				break;

			case 1:
				break;

			default:
				//Read Map data
				if (NULL != token)
				{
					std::vector<TileCell*> rowList;
					for (int x = 0; x < _width; x++)
					{
						int index = atoi(token);
						TileCell* tileCell = new TileCell();
						WCHAR componentName[256];
						wsprintf(componentName, L"map_layer1_%d_%d", line, x);
						TileObject* tileObject = new TileObject(componentName, _spriteList[index]);
						tileObject->SetCanMove(true);
						tileCell->AddComponent(tileObject, true);
						rowList.push_back(tileCell);
						token = strtok(NULL, ",");
					}

					_tileMap.push_back(rowList);
				}
				break;
			}
			line++;
		}
	}


	//Load Map Layer2
	{
		int line = 0;
		int row = 0;
		char record[1024];
		std::ifstream infile("MapData_layer2.csv");
		while (!infile.eof())
		{
			infile.getline(record, 1024);

			char* token = strtok(record, ",");

			switch (line)
			{
			case 0:
				break;

			case 1:
				break;

			default:
				//Read Map data
				if (NULL != token)
				{
					std::vector<TileCell*> rowList = _tileMap[row];
					for (int x = 0; x < _width; x++)
					{
						int index = atoi(token);
						if (index >= 0)
						{
							TileCell* tileCell = rowList[x];
							WCHAR componentName[256];
							wsprintf(componentName, L"map_layer2_%d_%d", line, x);
							TileObject* tileObject = new TileObject(componentName, _spriteList[index]);
							tileCell->AddComponent(tileObject, true);
						}
						token = strtok(NULL, ",");
					}

					row++;
				}
				break;
			}
			line++;
		}
	}
}

void Map::Deinit()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[x][y]->Deinit();
			delete _tileMap[y][x];
		}
	}
}

void Map::Update(float deltaTime)
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->MoveDeltaPosition(_deltaX, _deltaY);
			_tileMap[y][x]->Update(deltaTime);
		}
	}
}

void Map::Render()
{
	int midX = GameSystem::GetInstance()->GetClientWidth() / 2;
	int midY = GameSystem::GetInstance()->GetClientHeight() / 2;

	int tileXCount = midX / _tileSize;
	int tileYCount = midY / _tileSize;

	// 최대 최소 렌더링 영역
	int minX = _viewer->GetTileX() - tileXCount - 1;
	int maxX = _viewer->GetTileX() + tileXCount + 1;
	int minY = _viewer->GetTileY() - tileYCount - 1;
	int maxY = _viewer->GetTileY() + tileYCount + 1;

	// 범위 보정
	if (minX < 0)
		minX = 0;

	if (_width <= maxX)
		maxX = _width;

	if (minY < 0)
		minY = 0;

	if (_height <= maxY)
		maxY = _height;

	
	for (int y = minY; y < maxY; y++)
	{
		for (int x = minX; x < maxX; x++)
		{
			_tileMap[y][x]->Render();
		}
	}
}


void Map::Release()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->Release();
		}
	}
}

void Map::Reset()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->Reset();
		}
	}
}

void Map::Scroll(float deltaX, float deltaY)
{
	_deltaX = deltaX;
	_deltaY = deltaY;
}

float Map::GetPositionX(int tileX, int tileY)
{
	return _tileMap[tileY][tileX]->GetPositionX();
}

float Map::GetPositionY(int tileX, int tileY)
{
	return _tileMap[tileY][tileX]->GetPositionY();
}

void Map::SetTileComponent(int tileX, int tileY, Component* thisComponent, bool isRender)
{
	_tileMap[tileY][tileX]->AddComponent(thisComponent, isRender);
}

void Map::ResetTileComponent(int tileX, int tileY, Component* thisComponent)
{
	_tileMap[tileY][tileX]->RemoveComponent(thisComponent);
}

bool Map::CanMoveTileMap(int tileX, int tileY)
{
	if (tileX < 0)
		return false;

	if (_width <= tileX)
		return false;

	if (tileY < 0)
		return false;

	if (_height <= tileY)
		return false;

	return _tileMap[tileY][tileX]->CanMove();
}

void Map::InitViewer(Component* viewer)
{
	_viewer = viewer;
	
	// 뷰어 중심 렌더링 영역
	// outOfSize 보정
	// 뷰어의 위치를 기준으로 시작 픽셀 위치 계산

	int midX = GameSystem::GetInstance()->GetClientWidth() / 2;
	int midY = GameSystem::GetInstance()->GetClientHeight() / 2;
	
	_startX = (-_viewer->GetTileX() * _tileSize) + midX - _tileSize /2;
	_startY = (-_viewer->GetTileY() * _tileSize) + midY - _tileSize /2;

	
	float posX = _startX;
	float posY = _startY;

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->SetPosition(posX, posY);
			posX += _tileSize;
		}
		posX = _startX;
		posY += _tileSize;
	}
}
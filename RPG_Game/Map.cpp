#include "Map.h"
#include "Sprite.h"
#include "TileCell.h"

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

	// Load Map Script
	{
		int line = 0;
		char record[1024];
		std::ifstream infile("MapData.csv");
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
						//rowList.push_back(_spriteLIstList[index]);
						TileCell* tileCell = new TileCell();
						tileCell->SetSprite(_spriteList[index]);
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

	_startX += _deltaX;
	_startY += _deltaY;
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
			_tileMap[y][x]->Update(deltaTime);
		}
	}
}

void Map::Render()
{

	/*_startX += _deltaX;
	_startY += _deltaY;
	float posX = _startX;
	float posY = _startY;
	int tileSize = 32;

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->SetPosition(posX, posY);
			_tileMap[y][x]->Render();
			posX += tileSize;
		}
		posX = _startX;
		posY += tileSize;
	}*/

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->MoveDeltaPosition(_deltaX, _deltaY);
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
	if (isRender == true)
	_tileMap[tileY][tileX]->AddComponent(thisComponent, isRender);
}

void Map::ResetTileComponent(int tileX, int tileY, Component* thisComponent)
{
	_tileMap[tileY][tileX]->RemoveComponent(thisComponent);
}
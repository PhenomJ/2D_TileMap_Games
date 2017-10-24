#include "Character.h"
#include "Sprite.h"
#include "Map.h"
#include "ComponentSystem.h"

Character::Character(LPCWSTR name) : Component(name), _sprite(NULL), _x(0.0f), _y(0.0f)
{
	_map = 32;
}

Character::~Character()
{

}

void Character::Init()
{
	WCHAR textureFilename[256];
	WCHAR scriptFilename[256];
	wsprintf(textureFilename, L"%s.png", _name);
	wsprintf(scriptFilename, L"%s.json", _name);
	_sprite = new Sprite(textureFilename, scriptFilename);
	_sprite->Init();

	{
		//int mapTileSize = 32;
		//int tileX = 2; // 실질적으로 이동할떄
		//int tileY = 2; // 바뀌어야 하는 값

		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		int tileX = 2;
		int tileY = 3;

		_x = map->GetPositionX(tileX, tileY);
		_y = map->GetPositionY(tileX, tileY);
		map->SetTileComponent(tileX, tileY, this);

		//_x = tileX * mapTileSize;
		//_y = tileY * mapTileSize;
	}
}

void Character::Deinit()
{
	if (_sprite != NULL)
	{ 
		_sprite->Deinit();
		delete _sprite;
		_sprite = NULL;
	}
}

void Character::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}

void Character::Render()
{
	_sprite->SetPosition(_x, _y);
	_sprite->Render();
}

void Character::Release()
{
	_sprite->Release();
}

void Character::Reset()
{
	_sprite->Reset();
}

void Character::Move(int x, int y)
{
	_x = _x + x * _map;
	_y = _y + y * _map;
}
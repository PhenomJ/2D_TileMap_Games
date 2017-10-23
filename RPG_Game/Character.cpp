#include "Character.h"
#include "Sprite.h"

Character::Character(LPCWSTR name) : Component(name)
{
	_sprite = NULL;
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
		int mapTileSize = 32;
		int tileX = 2; // 실질적으로 이동할떄
		int tileY = 2; // 바뀌어야 하는 값

		_x = tileX * mapTileSize;
		_y = tileY * mapTileSize;
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

#include "RecoveryItem.h"
#include "Sprite.h"
#include "Map.h"
#include "ComponentSystem.h"

RecoveryItem::RecoveryItem(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFilename) : Component(name)
{
	_type = eComponentType::CT_ITEM;
	_sprite = NULL;
	_scripteFileName = scriptName;
	_textureFilename = textureFilename;
}

RecoveryItem::~RecoveryItem()
{

}

void RecoveryItem::Init()
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");

	while (true)
	{
		if (map->CanMoveTileMap(_tileX, _tileY) == false)
		{
			_tileX = rand() % (map->GetWidth() - 1) + 1;
			_tileY = rand() % (map->GetHeight() - 1) + 1;
		}
			else
		{
			_posX = map->GetPositionX(_tileX, _tileY);
			_posY = map->GetPositionY(_tileX, _tileY);
			break;
		}
	}
		map->SetTileComponent(_tileX, _tileY, this, false);

	WCHAR textureFilename[256];
	wsprintf(textureFilename, L"%s.png", _textureFilename.c_str());

	WCHAR scriptFilename[256];
	{
		wsprintf(scriptFilename, L"%s.json", _scripteFileName.c_str());
		_sprite = new Sprite(textureFilename, scriptFilename);
		_sprite->Init();
	}
	SetCanMove(true);
}

void RecoveryItem::Deinit()
{
	_sprite->Deinit();
}

void RecoveryItem::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}

void RecoveryItem::Render()
{
	_sprite->SetPosition(_posX, _posY);
	_sprite->Render();
}

void RecoveryItem::Release()
{
	_sprite->Release();
}

void RecoveryItem::Reset()
{
	_sprite->Reset();
}

void RecoveryItem::MoveDeltaPosition(float deltaX, float deltaY)
{
	_posX += deltaX;
	_posY += deltaY;
}

void RecoveryItem::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
}
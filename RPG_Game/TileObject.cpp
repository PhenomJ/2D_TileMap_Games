#include "TileObject.h"
#include <d3d9.h>
#include "GameSystem.h"
#include "Sprite.h"

TileObject::TileObject(LPCWSTR name, Sprite* sprite, int tileX, int tileY) : Component(name)
{
	_type = eComponentType::CT_TILEOBJECT;
	_sprite = sprite;
	_tileX = tileX;
	_tileY = tileY;
}

TileObject::~TileObject()
{

}

void TileObject::Init()
{

}

void TileObject::Deinit()
{
	_sprite->Deinit();
}

void TileObject::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}

void TileObject::Render()
{
	_sprite->SetPosition(_posX, _posY);
	_sprite->Render();
}

void TileObject::Release()
{
	_sprite->Release();
}

void TileObject::Reset()
{
	_sprite->Reset();
}

void TileObject::MoveDeltaPosition(float deltaX, float deltaY)
{
	_posX += deltaX;
	_posY += deltaY;
}

void TileObject::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
}

void TileObject::ChangeColor(D3DCOLOR color)
{
	_sprite->ChangeColor(color);
}
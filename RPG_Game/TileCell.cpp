#include "TileCell.h"
#include "Sprite.h"
#include "Component.h"

TileCell::TileCell()
{
	_componentList.clear();
}

TileCell::~TileCell()
{

}

void TileCell::Deinit()
{
	_sprite->Deinit();
}

void TileCell::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}

void TileCell::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
	_sprite->SetPosition(posX, posY);
}

void TileCell::Render()
{
	_sprite->SetPosition(_posX, _posY);
	_sprite->Render();

	for (std::list<Component*>::iterator itr = _renderList.begin(); itr != _renderList.end(); itr++)
	{
		(*itr)->Render();
	}
}

void TileCell::Release()
{
	_sprite->Release();
}

void TileCell::Reset()
{
	_sprite->Reset();
}

void TileCell::SetSprite(Sprite* sprite)
{
	_sprite = sprite;
}

float TileCell::GetPositionX()
{
	return _posX;
}

float TileCell::GetPositionY()
{
	return _posY;
}

void TileCell::MoveDeltaPosition(float deltaX, float deltaY)
{
	_posX += deltaX;
	_posY += deltaY;
	_sprite->SetPosition(_posX, _posY);

	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->MoveDeltaPosition(deltaX, deltaY);
	}
}

void TileCell::AddComponent(Component* thisComponent, bool isRender)
{
	_componentList.push_back(thisComponent);
	
	if (isRender)
	{
		_renderList.push_back(thisComponent);
	}
}

void TileCell::RemoveComponent(Component* thisComponent)
{
	_componentList.remove(thisComponent);
	_renderList.remove(thisComponent);
}
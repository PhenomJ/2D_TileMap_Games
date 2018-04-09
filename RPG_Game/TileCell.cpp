#include "TileCell.h"
#include "TileObject.h"
#include "Component.h"
#include "Sprite.h"

TileCell::TileCell(int tileX, int tileY, Sprite* sprite)
{
	_tileX = tileX;
	_tileY = tileY;
	_sprite = sprite;
	_componentList.clear();
	_distanceWeight = 1.0f;
	
}

TileCell::~TileCell()
{

}

void TileCell::Deinit()
{
	
}

void TileCell::Update(float deltaTime)
{
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->Render();
	}
}

void TileCell::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;

	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->SetPosition(_posX, _posY);
	}
}

void TileCell::Render()
{
	for (std::list<Component*>::iterator itr = _renderList.begin(); itr != _renderList.end(); itr++)
	{
		(*itr)->Render();
	}
}

void TileCell::Release()
{
	
}

void TileCell::Reset()
{
	
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
	
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->MoveDeltaPosition(deltaX, deltaY);
	}
}

void TileCell::AddComponent(Component* thisComponent, bool isRender)
{
	_componentList.push_back(thisComponent);
	
	if (eComponentType::CT_TILEOBJECT == thisComponent->GetType())
	{
		_distanceWeight = ((TileObject*)thisComponent)->GetDistanceWeight();
	}

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

bool TileCell::CanMove()
{
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		if (false == (*itr)->CanMove())
			return false;
	}

	return true;
}

bool TileCell::GetCollisionList(std::list<Component*> &collisionList)
{
	collisionList.clear();

	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		if (false == (*itr)->CanMove())
		{
			collisionList.push_back((*itr));
		}
	}

	if (collisionList.size() == 0)
		return true;

	return false;
}

std::list<Component*> TileCell::GetComponentList()
{
	return _componentList;
}

void TileCell::InitFindingPath()
{
	_isFindingPathMark = false;
	_prevCell = NULL;
	_distanceFromStart = 0.0f;
	_heuristic = 0.0f;
}

void TileCell::FindingPathMark()
{
	TileObject* tileObject = new TileObject(_sprite, _tileX, _tileY);
	tileObject->ChangeColor(D3DCOLOR_ARGB(255, 0, 0, 255));
}

float TileCell::GetHeuristic()
{
	return _heuristic;
}
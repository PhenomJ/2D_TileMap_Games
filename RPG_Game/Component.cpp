#include "Component.h"
#include "ComponentSystem.h"

Component::Component(LPCWSTR name)
{
	_name = name;
	ComponentSystem::GetInstance()->AddComponent(_name, this);
}

Component::~Component()
{

}

bool Component::CanMove()
{
	return _canMove;
}

int Component::GetTileX()
{
	return _tileX;
}

int Component::GetTileY()
{
	return _tileY;
}
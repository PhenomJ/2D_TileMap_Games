#include "Component.h"
#include "ComponentSystem.h"

Component::Component(LPCWSTR name)
{
	_name = name;
	_canMove = false;
	ComponentSystem::GetInstance()->AddComponent(_name, this);
	_moveDistanceperTimeX = 0;
	_moveDistanceperTimeY = 0;
	_type = eComponentType::CT_PLAYER;
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

float Component::GetMoveDeltaX()
{
	return _moveDistanceperTimeX;
}

float Component::GetMoveDeltaY()
{
	return _moveDistanceperTimeY;
}

void Component::receiveMessage(Component* sendComponent, std::wstring message)
{
	if (message == L"Collision Event")
	{
		
	}
}

eComponentType Component::GetType()
{
	return _type;
}
#include "Component.h"
#include "ComponentSystem.h"

Component::Component(LPCWSTR name)
{
	_name = name;
	_canMove = false;
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

void Component::receiveMessage(Component* sendComponent, std::wstring message)
{
	if (message == L"Collision Event")
	{
		
	}
}
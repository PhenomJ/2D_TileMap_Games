#include "Player.h"
#include "GameSystem.h"
#include "ComponentSystem.h"

Player::Player(LPCWSTR name) : Character(name)
{
	_moveSpeed = 0.1f;
}

Player::~Player()
{

}

void Player::UpdateAI(float deltaTime)
{
	if (_isMoving == false) 
	{
		if (GameSystem::GetInstance()->IsKeyDown(VK_UP))
		{
			MoveStart(eDirection::UP);
		}

		if (GameSystem::GetInstance()->IsKeyDown(VK_DOWN))
		{
			MoveStart(eDirection::DOWN);
		}

		if (GameSystem::GetInstance()->IsKeyDown(VK_LEFT))
		{
			MoveStart(eDirection::LEFT);
		}

		if (GameSystem::GetInstance()->IsKeyDown(VK_RIGHT))
		{
			MoveStart(eDirection::RIGHT);
		}
	}
}

void Player::UpdateMove(float deltaTime)
{
	if (_isMoving == false)
		return;

	if (_moveSpeed <= _movingDuration)
	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		_movingDuration = 0.0f;
		_isMoving = false;

		//_x = map->GetPositionX(_tileX, _tileY);
		//_y = map->GetPositionY(_tileX, _tileY);
	}

	else
	{
		_movingDuration += deltaTime;

		float moveDistanceX = _moveDistanceperTimeX * deltaTime;
		float moveDistanceY = _moveDistanceperTimeY * deltaTime;

		//_x += moveDistanceX;
		//_y += moveDistanceY;
	}

}
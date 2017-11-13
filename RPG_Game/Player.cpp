#include "Player.h"
#include "GameSystem.h"
#include "ComponentSystem.h"
#include "Map.h"

Player::Player(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName,spriteName)
{
	_moveSpeed = 0.1f;
	_type = eComponentType::CT_PLAYER;
}

Player::~Player()
{

}

void Player::UpdateAI(float deltaTime)
{
	if (_isLive == false)
		return;

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
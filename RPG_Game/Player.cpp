#include "Player.h"
#include "GameSystem.h"
#include "ComponentSystem.h"
#include "Map.h"
#include "MoveState.h"

Player::Player(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName,spriteName)
{
	_moveSpeed = 0.2f;
	_type = eComponentType::CT_PLAYER;
	_hp = 10;
	_attackPoint = 5;
	_attackCoolDown = 1.0f;
}

Player::~Player()
{

}

void Player::UpdateAI(float deltaTime)
{
	eDirection direction = eDirection::NONE;
	if (GameSystem::GetInstance()->IsKeyDown(VK_UP))
	{
		direction = eDirection::UP;
	}

	if (GameSystem::GetInstance()->IsKeyDown(VK_DOWN))
	{
		direction = eDirection::DOWN;
	}

	if (GameSystem::GetInstance()->IsKeyDown(VK_LEFT))
	{
		direction = eDirection::LEFT;
	}

	if (GameSystem::GetInstance()->IsKeyDown(VK_RIGHT))
	{
		direction = eDirection::RIGHT;
	}
	if (direction != eDirection::NONE)
	{
		_currentDirection = direction;
		_state->NextState(eStateType::ET_MOVE);
	}
}

Component* Player::Collision(std::list<Component*> &collisionList)
{
	for (std::list<Component*>::iterator itr = collisionList.begin(); itr != collisionList.end(); itr++)
	{
		Component* component = (*itr);

		if (component->GetType() == eComponentType::CT_MONSTER || component->GetType() == eComponentType::CT_NPC)
		{
			return (*itr);
		}
	}
	return NULL;
}
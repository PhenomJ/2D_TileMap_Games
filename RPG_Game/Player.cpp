#include "Player.h"
#include "GameSystem.h"
#include "ComponentSystem.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"
#include "MoveState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "DeadState.h"
#include "DefenseState.h"

Player::Player(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName,spriteName)
{
	_moveSpeed = 0.1f;
	_type = eComponentType::CT_PLAYER;
	_hp = 10;
	_attackPoint = 5;
	_attackCoolDown = 1.0f;
	_movePoint = 5;
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

	if (GameSystem::GetInstance()->IsKeyDown(VK_SPACE))
	{
		Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
		std::list<Component*> componentList = map->GetTileComponentList(_tileX, _tileY);

		for (std::list<Component*>::iterator itr = componentList.begin(); itr != componentList.end(); itr++)
		{
			Component* component = (*itr);

			if (eComponentType::CT_ITEM == component->GetType())
			{
				sComponentMsgParam msg;
				msg.message = L"use";
				msg.sender = (Component*)this;
				msg.receiver = component;
				ComponentSystem::GetInstance()->SendMsg(msg);
			}
		}
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
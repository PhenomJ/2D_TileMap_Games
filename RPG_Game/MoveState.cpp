#include "MoveState.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "Character.h"
#include "GameSystem.h"
#include "Stage.h"

MoveState::MoveState()
{

}

MoveState::~MoveState()
{

}

void MoveState::Init(Character* character)
{
	State::Init(character);
	_moveDuration = 0.0f;
}

void MoveState::Start()
{
	State::Start();
	if (_character->IsMoving() == true)
	{
		_nextState = eStateType::ET_IDLE;
		return;
	}
		
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();

	int newTileX = _character->GetTileX();
	int newTileY = _character->GetTileY();
	
	switch (_character->GetDirection())
	{
	case eDirection::LEFT:
		newTileX--;
		break;
	case eDirection::RIGHT:
		newTileX++;
		break;
	case eDirection::UP:
		newTileY--;
		break;
	case eDirection::DOWN:
		newTileY++;
		break;
	}
	
	std::list<Component*> collisionList;

	bool canMove = map->GetTileCollisionList(newTileX, newTileY, collisionList);

	if (canMove == false)
	{
		Component* target = _character->Collision(collisionList);

		if (target != NULL && _character->IsCoolDown())
		{
			_character->ResetCoolDown();
			_character->SetTarget(target);
			_nextState = eStateType::ET_ATTACK;
		}

		else
		{
			_nextState = eStateType::ET_IDLE;
		}
	}
	else
	{
		_character->MoveStart(newTileX, newTileY);
		_character->MoveStop();
		_moveDuration = 0.0f;
	}
}

void MoveState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}

	if (_character->IsLive() == false)
		return;
	/*
	if (_character->IsMoving() == false)
		return;
		
	if (_character->GetMoveTime() <= _moveDuration)
	{
		_moveDuration = 0.0f;
		_character->MoveStop();
		_nextState = eStateType::ET_IDLE;
	}

	else
	{
		_moveDuration += deltaTime;
		_character->Moving(deltaTime);
	}*/

	if (_character->GetMoveTime() <= _moveDuration)
	{
		_nextState = eStateType::ET_IDLE;
	}

	else
	{
		_moveDuration += deltaTime;
	}
}

void MoveState::Stop()
{
	State::Stop();
}
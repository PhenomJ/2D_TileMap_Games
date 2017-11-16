#include "MoveState.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "Character.h"

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
		return;
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");

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
		_character->Collision(collisionList);
		_character->ChangeState(eStateType::ET_IDLE);
		return;
	}

	else
	{
		_character->MoveStart(newTileX, newTileY);
	}
}

void MoveState::Update(float deltaTime)
{
	State::Update(deltaTime);
	if (_character->IsLive() == false)
		return;

	if (_character->IsMoving() == false)
		return;

	if (_character->GetMoveTime() <= _moveDuration)
	{
		_moveDuration = 0.0f;
		
		
		_character->MoveStop();
		_character->ChangeState(eStateType::ET_IDLE);
	}

	else
	{
		_moveDuration += deltaTime;
		_character->Moving(deltaTime);
	}
}

void MoveState::Stop()
{
	State::Stop();
}
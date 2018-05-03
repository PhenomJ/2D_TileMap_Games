#include "FindingPathMoveState.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "Character.h"
#include "GameSystem.h"
#include "Stage.h"
#include "TileCell.h"
#include "GlobalType.h"

FindingPathMoveState::FindingPathMoveState()
{

}

FindingPathMoveState::~FindingPathMoveState()
{

}

void FindingPathMoveState::Init(Character* character)
{
	State::Init(character);
	_moveDuration = 0.0f;
}

void FindingPathMoveState::Start()
{
	State::Start();

	_nextState = eStateType::ET_NONE;
	_moveDuration = 0.0f;

	_pathTileCellStack = _character->GetPathTileCellStack();

	if (_pathTileCellStack.size() != 0)
	{
		_pathTileCellStack.pop();
	}
}

void FindingPathMoveState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}

	if (_character->IsLive() == false)
		return;
	
	//if (_character->GetMoveTime() <= _moveDuration)
	{
		_moveDuration = 0.0f;
		if (_pathTileCellStack.size() != 0)
		{
			TileCell* tileCell = _pathTileCellStack.top();
			_pathTileCellStack.pop();

			//µµÂø
			TilePosition to;
			to.x = tileCell->GetTileX();
			to.y = tileCell->GetTileY();

			//Ãâ¹ß
			TilePosition from;
			from.x = _character->GetTileX();
			from.y = _character->GetTileY();

			eDirection direction = GetDirection(to, from);
			if (direction != eDirection::NONE)
				_character->SetDirection(direction);
			
			{
				_character->MoveStart(tileCell->GetTileX(), tileCell->GetTileY());
				_character->MoveStop();
				_moveDuration = 0.0f;
			}
		}

		else
		{
			_nextState = eStateType::ET_IDLE;
		}
	}

	/*else
	{
		_moveDuration += deltaTime;
	}*/
}

void FindingPathMoveState::Stop()
{
	State::Stop();
	_character->GetPathTileCellStack();
	_character->ClearPathTileCellStack();
	TurnManager::GetInstance()->ChangeTurn();
}

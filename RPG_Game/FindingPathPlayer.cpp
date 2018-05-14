#include "FindingPathPlayer.h"
#include "FindingPathState.h"
#include "FindingPathMoveState.h"
#include "FindingPathImmediateState.h"
#include "FindingPathMoveRangeState.h"
#include "IdleState.h"
#include "GameSystem.h"
#include "TurnManager.h"
#include "Stage.h"
#include "Map.h"

FindingPathPlayer::FindingPathPlayer(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Player (name, scriptName, spriteName)
{
	beforeMouseX = 0;
	beforeMouseY = 0;
	_movePoint = 10;
	_pathfindingType = ePathFindingType::DISTANCE;
	_type = eComponentType::CT_PLAYER;
}

FindingPathPlayer::~FindingPathPlayer()
{

}

void FindingPathPlayer::UpdateAI(float deltaTime)
{
	// Mouse Input
	if (TurnManager::GetInstance()->IsPlayerTurn() && GameSystem::GetInstance()->IsMouseDown())
	//if (GameSystem::GetInstance()->IsMouseDown())
	{
		int mouseX = GameSystem::GetInstance()->GetMouseX();
		int mouseY = GameSystem::GetInstance()->GetMouseY();

		TileCell* targetTileCell = GameSystem::GetInstance()->GetStage()->GetMap()->FindTileCellWithMousePosition(mouseX, mouseY);
		
		if (targetTileCell != NULL)
		{
			if ((targetTileCell->GetTileX() == _tileX && targetTileCell->GetTileY() == _tileY))
			{
				_state->NextState(eStateType::ET_MOVERANGE);
				return;
			}

			else if (targetTileCell->GetClickable() && targetTileCell->CanMove())
			{
				SetTargetCell(targetTileCell);
				return;
			}

			else if (targetTileCell->GetAttackable())
			{
				Attack(targetTileCell);
				return;
			}
		}
	}
}

TileCell* FindingPathPlayer::GetTileCell()
{
	return _tileCell;
}

void FindingPathPlayer::InitState()
{
	Player::InitState();
	ReplaceState(eStateType::ET_MOVERANGE, new FindingPathMoveRangeState());
	ReplaceState(eStateType::ET_MOVE, new FindingPathMoveState());
	ReplaceState(eStateType::ET_FINDINGPATH, new FindingPathImmediateState());
}
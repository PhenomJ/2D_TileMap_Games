#include "FindingPathPlayer.h"
#include "FindingPathState.h"
#include "FindingPathMoveState.h"
#include "FindingPathImmediateState.h"
#include "FindingPathMoveRangeState.h"
#include "IdleState.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"

FindingPathPlayer::FindingPathPlayer(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Player (name, scriptName, spriteName)
{
	beforeMouseX = 0;
	beforeMouseY = 0;
	_movableCount = 16;
	_pathfindingType = ePathFindingType::DISTANCE;
}

FindingPathPlayer::~FindingPathPlayer()
{

}

void FindingPathPlayer::UpdateAI(float deltaTime)
{
	// Mouse Input
	if (GameSystem::GetInstance()->IsMouseDown())
	{
		int mouseX = GameSystem::GetInstance()->GetMouseX();
		int mouseY = GameSystem::GetInstance()->GetMouseY();

		TileCell* targetTileCell = GameSystem::GetInstance()->GetStage()->GetMap()->FindTileCellWithMousePosition(mouseX, mouseY);
		
		if (targetTileCell->GetTileX() == this->GetTileX() && targetTileCell->GetTileY() == this->GetTileY())
		{
			_state->NextState(eStateType::ET_MOVERANGE);
		}

		if (targetTileCell->GetClickable())
		{
			SetTargetCell(targetTileCell);
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
#include "FindingPathPlayer.h"
#include "FindingPathState.h"
#include "FindingPathMoveState.h"
#include "FindingPathImmediateState.h"
#include "IdleState.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"

FindingPathPlayer::FindingPathPlayer(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Player (name, scriptName, spriteName)
{
	beforeMouseX = 0;
	beforeMouseY = 0;
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	//_tileCell = map->GetTileCell(_charcter, _tileY);
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

		if (beforeMouseX != mouseX && beforeMouseY != mouseY)
		{
			TileCell* targetTileCell = GameSystem::GetInstance()->GetStage()->GetMap()->FindTileCellWithMousePosition(mouseX, mouseY);

			if (targetTileCell != NULL)
			{
				beforeMouseX = mouseX;
				beforeMouseY = mouseY;
				SetTargetCell(targetTileCell);
			}

			if (targetTileCell == this->GetTileCell())
			{
				//CallMoveableRange(targetTileCell);
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
	ReplaceState(eStateType::ET_MOVE, new FindingPathMoveState());
	ReplaceState(eStateType::ET_FINDINGPATH, new FindingPathImmediateState());
}
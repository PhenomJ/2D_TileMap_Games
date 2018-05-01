#include "FindingPathMoveRangeState.h"
#include "Character.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"

FindingPathMoveRangeState::FindingPathMoveRangeState()
{
	
}

FindingPathMoveRangeState::~FindingPathMoveRangeState()
{

}

void FindingPathMoveRangeState::Start()
{
	_character->SetPathFindingType(ePathFindingType::DISTANCE);
	_character->SetTarget(NULL);
	_nextState = eStateType::ET_FINDINGPATH;
}

void FindingPathMoveRangeState::InputClick()
{

}
#include "FindingPathState.h"
#include "Map.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Character.h"
#include "GlobalType.h"

FindingPathState::FindingPathState()
{
	_targetTileCell = NULL;
}

FindingPathState::~FindingPathState()
{

}
void FindingPathState::Init(Character* character)
{
	State::Init(character);
}

void FindingPathState::Start()
{
	State::Start();

	_targetTileCell = _character->GetTargetCell();

	// ��� Ÿ�ϼ� ��ã�� �Ӽ� �ʱ�ȭ 
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	int height = map->GetHeight();
	int width = map->GetWidth();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			TileCell* tileCell = map->GetTileCell(x, y);
			tileCell->InitFindingPath();
		}
	}

	TileCell* startTileCell = map->GetTileCell(_character->GetTileX(), _character->GetTileY());

	sPathCommand newCommand;
	newCommand.heuristic = 0.0f;
	newCommand.tileCell = startTileCell;

	_findingPathTileQueue.push(newCommand);

	_updateState = eUpdateState::FINDINGPATH;
}

void FindingPathState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}

	switch (_updateState)
	{
	case eUpdateState::FINDINGPATH:
		UpdateFindingPath();
		break;

	case eUpdateState::BUILD_PATH:
		UpdateBuildPath();
		break;
	}
}

void FindingPathState::Stop()
{
	State::Stop();

	while (_findingPathTileQueue.size() != 0)
		_findingPathTileQueue.pop();
}

void FindingPathState::UpdateFindingPath()
{
	// ��ã�� ����
	if (_findingPathTileQueue.size() >= 0)
	{
		// ù ��带 ������ �˻�
		sPathCommand command = _findingPathTileQueue.top();
		_findingPathTileQueue.pop();

		if (command.tileCell->IsFindingPathMarked() == false)
		{
			command.tileCell->FindingPathMarking();

			if (_character->GetPathFindingType() != ePathFindingType::DISTANCE)
			{
				// ��ǥ Ÿ���̸� ����
				if (command.tileCell->GetTileX() == _targetTileCell->GetTileX() && command.tileCell->GetTileY() == _targetTileCell->GetTileY())
				{
					_updateState = eUpdateState::BUILD_PATH;
					_reverseTileCell = _targetTileCell;

					return;
				}
			}

			if (command.tileCell->GetDistanceFromStart() > _character->GetMovePoint())
			{
				_reverseTileCell = command.tileCell;
				_nextState = eStateType::ET_IDLE;
				return;
			}

			// �ֺ� Ÿ�� �˻�
			for (int direction = 0; direction < eDirection::NONE; direction++)
			{
				TilePosition currentTilePosition;
				currentTilePosition.x = command.tileCell->GetTileX();
				currentTilePosition.y = command.tileCell->GetTileY();

				TilePosition nextTilePos = GetNextTilePosition(currentTilePosition, (eDirection)direction);

				Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
				TileCell* nextTileCell = map->GetTileCell(nextTilePos);

				if (_character->GetPathFindingType() == ePathFindingType::DISTANCE)
				{
					Stage* stage = GameSystem::GetInstance()->GetStage();
					stage->CreateMark(nextTileCell);
				}

				// �˻� ��Ÿ������ && �̵� ������ Ÿ�� ���� && ���� ���� ����� Ÿ���� Ȥ�� ����? -> �����丵�ϰ�ʹ٤���
				if ((map->CanMoveTileMap(nextTilePos) == true && nextTileCell->IsFindingPathMarked() == false))
				{
					float distanceFromStart = command.tileCell->GetDistanceFromStart() + command.tileCell->GetDistanceWeight() + 1;
					float heuristic = CalcHeuristic(_character->GetPathFindingType(), distanceFromStart, command.tileCell, nextTileCell, _targetTileCell);

					if (nextTileCell->GetPrevCell() == NULL)
					{
						nextTileCell->SetDistanceFromStart(distanceFromStart);
						nextTileCell->SetHeuristic(heuristic);
						nextTileCell->SetPrevCell(command.tileCell);

						sPathCommand newCommand;
						newCommand.heuristic = heuristic;
						newCommand.tileCell = nextTileCell;
						_findingPathTileQueue.push(newCommand);
					}
				}
			}
		}
	}
}

void FindingPathState::UpdateBuildPath()
{
	// �Ųٷ� ���� ����
	if (_reverseTileCell != NULL)
	{
		if (_targetTileCell != NULL || _targetTileCell->CanMove() == false)
		{
			if (_reverseTileCell->GetTileX() != _targetTileCell->GetTileX() || _reverseTileCell->GetTileY() != _targetTileCell->GetTileY())
			{
				_character->PushPathTileCellStack(_reverseTileCell);
			}
		}

		else
		{
			_character->PushPathTileCellStack(_reverseTileCell);
		}
		
		_reverseTileCell = _reverseTileCell->GetPrevCell();
		
	}

	else
	{
		_nextState = eStateType::ET_MOVECHASE;
	}
}

float FindingPathState::CalcSimpleHeuristic(TileCell* tileCell, TileCell* nextTileCell, TileCell* targetTileCell)
{
	float heuristic = 0.0f;

	int diffFromCurrent = 0;
	int diffFromNext = 0;

	{
		diffFromCurrent = tileCell->GetTileX() - targetTileCell->GetTileX();
		if (diffFromCurrent < 0)
			diffFromCurrent = -diffFromCurrent;

		diffFromNext = nextTileCell->GetTileX() - targetTileCell->GetTileX();
		if (diffFromNext < 0)
			diffFromNext = -diffFromNext;

		if (diffFromNext < diffFromCurrent)
		{
			heuristic -= 1.0f;
		}

		else if (diffFromNext > diffFromCurrent)
		{
			heuristic += 1.0f;
		}

		if (nextTileCell->GetDistanceWeight() < tileCell->GetDistanceWeight())
		{
			heuristic -= 1.0f;
		}

		else if (nextTileCell->GetDistanceWeight() > tileCell->GetDistanceWeight())
		{
			heuristic += 1.0f;
		}
	}

	{
		diffFromCurrent = tileCell->GetTileY() - targetTileCell->GetTileY();
		if (diffFromCurrent < 0)
			diffFromCurrent = -diffFromCurrent;

		diffFromNext = nextTileCell->GetTileY() - targetTileCell->GetTileY();
		if (diffFromNext < 0)
			diffFromNext = -diffFromNext;

		if (diffFromNext < diffFromCurrent)
		{
			heuristic -= 1.0f;
		}

		else if (diffFromNext > diffFromCurrent)
		{
			heuristic += 1.0f;
		}

		if (nextTileCell->GetDistanceWeight() < tileCell->GetDistanceWeight())
		{
			heuristic -= 1.0f;
		}

		else if (nextTileCell->GetDistanceWeight() > tileCell->GetDistanceWeight())
		{
			heuristic += 1.0f;
		}
	}

	return heuristic;
}

float FindingPathState::CalcComplexHeuristic(TileCell* nextTileCell, TileCell* targetTileCell)
{
	int distanceW = nextTileCell->GetTileX() - targetTileCell->GetTileX();
	int distanceH = nextTileCell->GetTileY() - targetTileCell->GetTileY();

	distanceW = distanceW * distanceW;
	distanceH = distanceH * distanceH;

	float distance = (float)((double)distanceW+ (double)distanceH);

	return distance;
}

float FindingPathState::CalcAStarHeuristic(float distanceFromStart, TileCell* nextTileCell, TileCell* targetTileCell)
{
	return distanceFromStart + CalcComplexHeuristic(nextTileCell, targetTileCell);
}

float FindingPathState::CalcHeuristic(ePathFindingType type, float distance, TileCell* tileCell, TileCell* nextTileCell, TileCell* targetTileCell)
{
	switch (type)
	{
	case ePathFindingType::DISTANCE:
		return distance;

	case ePathFindingType::SIMPLE:
		return CalcSimpleHeuristic(tileCell, nextTileCell, targetTileCell);

	case ePathFindingType::COMPLEX:
		return CalcComplexHeuristic(nextTileCell, targetTileCell);

	case ePathFindingType::ASTAR:
		return CalcAStarHeuristic(distance, nextTileCell, targetTileCell);

	default:
		return 0;
	}
}
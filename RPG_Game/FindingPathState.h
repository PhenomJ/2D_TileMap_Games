#pragma once
#include "State.h"
#include "TileCell.h"
#include "GlobalType.h"
#include <queue>

class Character;

class FindingPathState : public State
{
public:
	enum eUpdateState { FINDINGPATH, BUILD_PATH };

	typedef struct _sPathCommand
	{
		float heuristic;
		TileCell* tileCell;
	} sPathCommand;

	struct compare
	{
		//bool operator() (TileCell* a, TileCell* b)
		bool operator() (sPathCommand& a, sPathCommand& b)
		{
			//return a->GetDistanceFromStart() > b->GetDistanceFromStart();
			return a.heuristic > b.heuristic;
		}
	};

public:
	FindingPathState();
	~FindingPathState();

public:
	void Init(Character* character);
	void Update(float deltaTime);
	void Start();
	void Stop();
	void UpdateFindingPath();

protected:
	std::priority_queue<sPathCommand, std::vector<sPathCommand>, compare> _findingPathTileQueue;
	TileCell* _targetTileCell;
	TileCell* _reverseTileCell;
	eUpdateState _updateState;
	int count = 0;

public:
	void UpdateBuildPath();

	float CalcHeuristic(ePathFindingType type, float distance, TileCell* tileCell, TileCell* nextTileCell, TileCell* targetTileCell);

	// Simple
	float CalcSimpleHeuristic(TileCell* tileCell, TileCell* nextTileCell, TileCell* targetTileCell);

	// Complex
	float CalcComplexHeuristic(TileCell* nextTileCell, TileCell* targetTileCell);

	// A*
	float CalcAStarHeuristic(float distanceFromStart, TileCell* nextTileCell, TileCell* targetTileCell);
};
#include "FindingPathImmediateState.h"

FindingPathImmediateState::FindingPathImmediateState()
{

}

FindingPathImmediateState::~FindingPathImmediateState()
{

}

void FindingPathImmediateState::Start()
{
	FindingPathState::Start();

	while (_findingPathTileQueue.size() != 0)
	{
		if (_updateState == eUpdateState::BUILD_PATH)
			break;

		UpdateFindingPath();
	}

	while (_reverseTileCell != NULL)
	{
		UpdateBuildPath();
	}
}
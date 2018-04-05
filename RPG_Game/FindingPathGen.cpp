#include "FindingPathGen.h"
#include "Stage.h"
#include "Map.h"
#include "Component.h"
#include "FindingPathPlayer.h"
#include "FindingPathMonster.h"
#include "Player.h"
#include "NPC.h"
#include "TileObject.h"

FindingPathGen::FindingPathGen(Stage* stage) : GameGen(stage)
{

}

FindingPathGen::~FindingPathGen()
{

}

void FindingPathGen::CreateComponents(std::wstring mapName)
{
	GameGen::CreateComponents(mapName);

	// 1개의 몬스터 생성
	WCHAR name[256];
	int monsterCount = 0;
	wprintf(name, L"findingPathMonster_%d", monsterCount);
	Component* monster = new FindingPathMonster(name, L"monster", L"monster");
	_stage->AddStageComponent(monster);

	Player* player = new FindingPathPlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(player);

	// 뷰어를 맵 중간에 타일 오브젝트로 셋팅
	int midTileX = _stage->GetMap()->GetWidth() / 2;
	int midTileY = _stage->GetMap()->GetHeight() / 2;

	std::list<Component*> comList = _stage->GetMap()->GetTileComponentList(midTileX, midTileY); // -> 새로 셋팅되는것이 가장 맨 앞에 있으므로

	_stage->GetMap()->InitViewer(comList.front()); // -> 여기서 front()를 넣어준다
}

Component* FindingPathGen::CreateNpc(std::wstring scriptName, std::wstring textureName)
{
	SetName(L"NPC_");
	_npcCount++;
	Component* component = new NPC(_name.c_str(), scriptName.c_str(), textureName.c_str());
	_stage->AddStageComponent(component);

	return component;
}
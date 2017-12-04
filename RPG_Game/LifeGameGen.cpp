#include "LifeGameGen.h"
#include "LifeNPC.h"
#include "Stage.h"
#include "LifePlayer.h"

LifeGameGen::LifeGameGen(Stage* stage) : GameGen(stage)
{
	_npcCount = 100;
}

LifeGameGen::~LifeGameGen()
{

}

Component* LifeGameGen::CreateLifeNpc(std::wstring scriptName, std::wstring textureName)
{
	SetName(L"lifeNpc_");
	_count++;
	Component* component  = new LifeNPC(_name.c_str(), scriptName.c_str(), textureName.c_str());
	_stage->AddStageComponent(component);

	return component;
}

void LifeGameGen::CreateComponents()
{
	for (int i = 0; i < _npcCount; i++)
	{
		Component* component = CreateLifeNpc(L"npc", L"npc");
	}
	LifePlayer* player = new LifePlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(player);
}
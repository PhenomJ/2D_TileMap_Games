#include "DefaultGameGen.h"
#include "Stage.h"
#include "RecoveryItem.h"
#include "PosionItem.h"
#include "NPC.h"
#include "Monster.h"
#include "Player.h"

DefaultGameGen::DefaultGameGen(Stage* stage) : GameGen(stage)
{

}

DefaultGameGen::~DefaultGameGen()
{

}

void DefaultGameGen::CreateComponents()
{
	Component* component = CreateNpc(L"npc", L"npc");
	component = CreateMonster(L"monster", L"monster");
	component = CreateRecoveryItem(L"Recovery_Item", L"item");
	component = CreatePoisionItem(L"Poision_item", L"item");
	Player* player = new Player(L"player", L"player", L"player");

	_stage->AddStageComponent(player);
}

Component* DefaultGameGen::CreateNpc(std::wstring scriptName, std::wstring textureName)
{
	SetName(L"Npc_");
	_count++;
	Component* component = new NPC(_name.c_str(), scriptName.c_str(), textureName.c_str());
	_stage->AddStageComponent(component);

	return component;
}

Component* DefaultGameGen::CreateMonster(std::wstring scriptName, std::wstring textureName)
{
	SetName(L"Monster_");
	_count++;
	Component* component = new Monster(_name.c_str(), scriptName.c_str(), textureName.c_str());
	_stage->AddStageComponent(component);

	return component;
}

Component* DefaultGameGen::CreateRecoveryItem(std::wstring scriptName, std::wstring textureName)
{
	SetName(L"RecoveryItem_");
	_count++;
	Component* component = new RecoveryItem(_name.c_str(), scriptName.c_str(), textureName.c_str());
	_stage->AddStageComponent(component);

	return component;
}

Component* DefaultGameGen::CreatePoisionItem(std::wstring scriptName, std::wstring textureName)
{
	SetName(L"PosionItem_");
	_count++;
	Component* component = new PosionItem(_name.c_str(), scriptName.c_str(), textureName.c_str());
	_stage->AddStageComponent(component);

	return component;
}
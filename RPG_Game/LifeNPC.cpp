#include "LifeNPC.h"
#include "Map.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Font.h"
#include "State.h"

LifeNPC::LifeNPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Character(name, scriptName, spriteName)
{
	_type = eComponentType::CT_NPC;
}

LifeNPC::~LifeNPC()
{

}

void LifeNPC::UpdateAI(float deltaTime)
{

}

void LifeNPC::Init(int tileX, int tileY)
{
	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);

	_font = new Font(L"Arial", 15, color);
	_font->SetRect(100, 100, 400, 100);

	{
		Map* map = GameSystem::GetInstance()->GetStage()->GetMap();

		_tileX = tileX;
		_tileY = tileY;

		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);

		map->SetTileComponent(_tileX, _tileY, this, false);
	}


	InitMove();
	InitState();

	ChangeState(eStateType::ET_IDLE);
}

void LifeNPC::Update(float deltaTime)
{
	UpdateAttackCoolDown(deltaTime);
	_state->Update(deltaTime);
}

void LifeNPC::Render()
{
	_state->Render();
}
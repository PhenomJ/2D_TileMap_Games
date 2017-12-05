#include "LifePlayer.h"
#include "GameSystem.h"
#include "ComponentSystem.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"
#include "AttackState.h"
#include "MoveState.h"
#include "DeadState.h"
#include "DefenseState.h"
#include "IdleState.h"
#include "Font.h"

LifePlayer::LifePlayer(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Player(name, scriptName, spriteName)
{
	_moveSpeed = 0.1f;
	_type = eComponentType::CT_PLAYER;
	_hp = 10;
	_attackPoint = 5;
	_attackCoolDown = 1.0f;
}

LifePlayer::~LifePlayer()
{

}

void LifePlayer::InitState()
{
	Player::InitState();
	ReplaceState(eStateType::ET_ATTACK, new IdleState());
}

void LifePlayer::Init()
{
	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);

	_font = new Font(L"Arial", 15, color);
	_font->SetRect(100, 100, 400, 100);

	{
		Map* map = GameSystem::GetInstance()->GetStage()->GetMap();

		while (true)
		{
			if (map->CanMoveTileMap(_tileX, _tileY) == false)
			{
				_tileX = rand() % (map->GetWidth() - 1) + 1;
				_tileY = rand() % (map->GetHeight() - 1) + 1;
			}

			else
			{
				_x = map->GetPositionX(_tileX, _tileY);
				_y = map->GetPositionY(_tileX, _tileY);
				break;
			}
		}

		map->SetTileComponent(_tileX, _tileY, this, false);
	}


	InitMove();
	InitState();

	ChangeState(eStateType::ET_IDLE);
}

void LifePlayer::Update(float deltaTime)
{
	UpdateAttackCoolDown(deltaTime);
	_state->Update(deltaTime);
}

void LifePlayer::Render()
{
	_state->Render();
}
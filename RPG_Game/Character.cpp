#include "Character.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Sprite.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "ComponentMessage.h"
#include "State.h"
#include "MoveState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "DefenseState.h"
#include "DeadState.h"
#include "Font.h"
#include <time.h>

Character::Character(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Component(name), _x(0.0f), _y(0.0f)
{
	_state = NULL;
	_targetX = 0;
	_targetY = 0;
	_moveDistanceperTimeX = 0;
	_moveDistanceperTimeY = 0;
	_moveSpeed = 0.3f;
	_spriteName = spriteName;
	_scriptName = scriptName;
	_attackPoint = 5;
	_attackCoolDownDuration = 0.0f;
	_attackCoolDown = 2.0f;
}

Character::~Character()
{
	delete _font;
}

void Character::Init()
{
	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);

	_font = new Font(L"Arial", 15, color);
	_font->SetRect(100, 100, 400, 100);
	
	UpdateText();

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

void Character::Deinit()
{
	std::map<eStateType, State*>::iterator itr = _stateMap.begin();

	while (_stateMap.end() != itr)
	{
		State* state = itr->second;
		delete state;
		itr++;
	}

	_stateMap.clear();
}

void Character::Update(float deltaTime)
{
	UpdateAttackCoolDown(deltaTime);
	_state->Update(deltaTime);
	UpdateText();
}

void Character::Render()
{
	_state->Render();
	_font->SetPosition(_x - 200, _y - 50);
	_font->Render();
}

void Character::Release()
{
	
	_state->Release();
}

void Character::Reset()
{
	
	_state->Reset();
}

void Character::SetPosition(float tileX, float tileY)
{
	_x = tileX;
	_y = tileY;
}

void Character::InitMove()
{
	_isMoving = false;
	_currentDirection = eDirection::DOWN;
}

void Character::MoveStart(int newTileX, int newTileY)
{
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	map->ResetTileComponent(_tileX, _tileY, this);
	_tileX = newTileX;
	_tileY = newTileY;

		{
			map->SetTileComponent(_tileX, _tileY, this,false);

			_targetX = map->GetPositionX(_tileX, _tileY);
			_targetY = map->GetPositionY(_tileX, _tileY);

			float distanceX = _targetX - _x;
			float distanceY = _targetY - _y;

			_moveDistanceperTimeX = distanceX / _moveSpeed;
			_moveDistanceperTimeY = distanceY / _moveSpeed;	
		}

	_isMoving = true;
}

void Character::MoveDeltaPosition(float deltaX, float deltaY)
{
	_x += deltaX;
	_y += deltaY;
}

void Character::UpdateAI(float deltaTime)
{
	_currentDirection = (eDirection)(rand() % 4);
	_state->NextState(eStateType::ET_MOVE);
}

void Character::ChangeState(eStateType stateType)
{
	if (_state != NULL)
		_state->Stop();

	_state = _stateMap[stateType];
	_state->Start();
}

void Character::ReceiveMessage(const sComponentMsgParam &msgParam)
{
	if (msgParam.message == L"Attack")
	{
		_attackedPoint = msgParam.attackPoint;
		_state->NextState(eStateType::ET_DEFENCE);
	}
}

Component* Character::Collision(std::list<Component*>& collisionList)
{
	return NULL;
}

void Character::MoveStop()
{
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	
	_x = map->GetPositionX(_tileX, _tileY);
	_y = map->GetPositionY(_tileX, _tileY);

	_moveDistanceperTimeX = 0.0f;
	_moveDistanceperTimeY = 0.0f;

	_isMoving = false;
}

void Character::Moving(float deltaTime)
{
	float moveDistanceX = _moveDistanceperTimeX * deltaTime;
	float moveDistanceY = _moveDistanceperTimeY * deltaTime;

	_x += moveDistanceX;
	_y += moveDistanceY;
}
bool Character::IsMoving()
{
	return _isMoving;
}

std::wstring Character::GetTextureFileName()
{
	return _spriteName;
}

std::wstring Character::GetScriptFileName()
{
	return _scriptName;
}

void Character::DecreaseHP(int attackPoint)
{
	_hp -= attackPoint;

	if (_hp <= 0)
	{
		_hp = 0;
		_isLive = false;
	}
}

void Character::SetTarget(Component* target)
{
	_target = target;
}

bool Character::IsCoolDown()
{
	if (_attackCoolDown <= _attackCoolDownDuration)
	{
		return true;
	}

	return false;
}

void Character::ResetCoolDown()
{
	_attackCoolDownDuration = 0.0f;
}

void Character::UpdateAttackCoolDown(float deltaTime)
{
	if (_attackCoolDownDuration < _attackCoolDown)
	{
		_attackCoolDownDuration += deltaTime;
	}

	else
	{
		_attackCoolDownDuration = _attackCoolDown;
	}
}

void Character::UpdateText()
{
	int coolDown = (int)(_attackCoolDownDuration * 1000.0f);

	WCHAR text[256];
	wsprintf(text, L"HP : %d\n Attack : %d \n", _hp, coolDown );
	_font->SetText(text);
}

void Character::IncreaseHP(int recovery)
{
	_hp += recovery;

	if (_hp >= 100)
	{
		_hp = 100;
	}
}

void Character::Init(int tileX, int tileY)
{
	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);

	_font = new Font(L"Arial", 15, color);
	_font->SetRect(100, 100, 400, 100);

	UpdateText();

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

void Character::InitState()
{
	ReplaceState(eStateType::ET_IDLE, new IdleState());
	ReplaceState(eStateType::ET_ATTACK, new AttackState());
	ReplaceState(eStateType::ET_DEAD, new DeadState());
	ReplaceState(eStateType::ET_DEFENCE, new DefenseState());
	ReplaceState(eStateType::ET_MOVE, new MoveState());
}

void Character::ReplaceState(eStateType type, State* replaceState)
{
	_changeType = type;

	{
		std::map<eStateType, State*>::iterator itr = _stateMap.find(_changeType);
		if (itr != _stateMap.end())
		{
			delete itr->second;
			_stateMap.erase(_changeType);
		}

		State* state = replaceState;
		state->Init(this);
		_stateMap[_changeType] = state;
	}
}
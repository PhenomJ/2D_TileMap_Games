#include "Character.h"
#include "GameSystem.h"
#include "Sprite.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "ComponentMessage.h"
#include "State.h"
#include "MoveState.h"
#include "IdleState.h"
#include <time.h>

Character::Character(LPCWSTR name, LPCWSTR scriptName, LPCWSTR spriteName) : Component(name), _spriteList(NULL), _x(0.0f), _y(0.0f)
{
	_state = new IdleState();
	_targetX = 0;
	_targetY = 0;
	_moveDistanceperTimeX = 0;
	_moveDistanceperTimeY = 0;
	_moveSpeed = 1.0f;
	_spriteName = spriteName;
	_scriptName = scriptName;
	_attackPoint = 1;
}

Character::~Character()
{
	delete _state;
}

void Character::Init()
{
	WCHAR textureFilename[256];
	wsprintf(textureFilename, L"%s.png", _spriteName.c_str());

	WCHAR scriptFilename[256];
	{
		wsprintf(scriptFilename, L"%s_01.json", _scriptName.c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_02.json", _scriptName.c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_03.json", _scriptName.c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_04.json", _scriptName.c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	
	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		
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

	_state->Init(this);
	InitMove();
}

void Character::Deinit()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Deinit();
		delete _spriteList[i];
	}
	_spriteList.clear();
}

void Character::Update(float deltaTime)
{
	_spriteList[(int)_currentDirection]->Update(deltaTime);
	_state->Update(deltaTime);
}

void Character::Render()
{
	_spriteList[(int)_currentDirection]->SetPosition(_x, _y);
	_spriteList[(int)_currentDirection]->Render();
}

void Character::Release()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Release();
	}
	_spriteList.clear();
}

void Character::Reset()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Reset();
	}
	_spriteList.clear();
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
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
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
	ChangeState(eStateType::ET_MOVE);
}

void Character::ChangeState(eStateType stateType)
{
	if (_state != NULL)
	{
		_state->Stop();
		delete _state;
	}

	switch (stateType)
	{
	case eStateType::ET_IDLE:
		_state = new IdleState();
		break;

	case eStateType::ET_MOVE:
		_state = new MoveState();
		break;
	}

	_state->Init(this);
	_state->Start();
}

void Character::ReceiveMessage(const sComponentMsgParam &msgParam)
{
	if (msgParam.message == L"Attack")
	{
		int attackPoint = msgParam.attackPoint;
		_hp -= attackPoint;

		if (_hp < 0)
		{
			//dead
			_isLive = false;
			SetCanMove(false);

			//stop
			_moveDistanceperTimeX = 0;
			_moveDistanceperTimeY = 0;
		}
	}
}

void Character::Collision(std::list<Component*>& collisionList)
{
	for (std::list<Component*>::iterator itr = collisionList.begin(); itr != collisionList.end(); itr++)
	{
		sComponentMsgParam msgParam;
		msgParam.sender = this;
		msgParam.receiver = (*itr);
		msgParam.message = L"Collision";
		ComponentSystem::GetInstance()->SendMsg(msgParam);
	}
}

void Character::MoveStop()
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
	
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
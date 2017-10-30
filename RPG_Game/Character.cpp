#include "Character.h"
#include "Sprite.h"
#include "Map.h"
#include "ComponentSystem.h"

Character::Character(LPCWSTR name) : Component(name), _spriteList(NULL), _x(0.0f), _y(0.0f)
{
	_map = 32;
	_targetX = 0;
	_targetY = 0;
	_moveDistanceperTimeX = 0;
	_moveDistanceperTimeY = 0;
	_moveSpeed = 0.5f;
}

Character::~Character()
{

}

void Character::Init()
{
	WCHAR textureFilename[256];
	WCHAR scriptFilename[256];
	
	{
		wsprintf(textureFilename, L"%s.png", _name);
		wsprintf(scriptFilename, L"%s_01.json", _name);
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(textureFilename, L"%s.png", _name);
		wsprintf(scriptFilename, L"%s_02.json", _name);
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(textureFilename, L"%s.png", _name);
		wsprintf(scriptFilename, L"%s_03.json", _name);
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(textureFilename, L"%s.png", _name);
		wsprintf(scriptFilename, L"%s_04.json", _name);
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	
	InitMove();

	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		_tileX = 2;
		_tileY = 3;
		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);
		map->SetTileComponent(_tileX, _tileY, this, false);
	}
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
	UpdateAI(deltaTime);
	UpdateMove(deltaTime);
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

void Character::InitMove()
{
	_isMoving = false;
	
	_movingDuration = 0.0f;
	_currentDirection = eDirection::DOWN;
}

void Character::MoveStart(eDirection direction)
{
	if (_isMoving == true)
		return;

	_currentDirection = direction;

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
	map->ResetTileComponent(_tileX, _tileY, this);

	switch (direction)
	{
	case eDirection::LEFT: // left
		_tileX--;
		if (_tileX < 0)
			_tileX = 0;
		break;
	case eDirection::RIGHT: // right
		_tileX++;
		if (_tileX > 49)
			_tileX = 49;
		break;

		case eDirection::UP: // up
			_tileY--;
			if (_tileY < 0)
				_tileY = 0;
			break;
		case eDirection::DOWN: // down
			_tileY++;
			if (_tileY > 30)
				_tileY = 30;
			break;
		}
		
		// 이동을 위한 보간작업.
		{
			map->SetTileComponent(_tileX, _tileY, this,false);

			// 이동 거리를 구하기 위한 목적지.
			_targetX = map->GetPositionX(_tileX, _tileY);
			_targetY = map->GetPositionY(_tileX, _tileY);

			float distanceX = _targetX - _x;
			float distanceY = _targetY - _y;

			//최소 이동거리
			_moveDistanceperTimeX = distanceX / _moveSpeed;
			_moveDistanceperTimeY = distanceY / _moveSpeed;

			
		}

		_isMoving = true;
}

void Character::UpdateMove(float deltaTime)
{
	if (_isMoving == false)
		return;

	if (_moveSpeed <= _movingDuration)
	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		_movingDuration = 0.0f;
		_isMoving = false;
		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);
	}

	else
	{
		_movingDuration += deltaTime;

		float moveDistanceX = _moveDistanceperTimeX * deltaTime;
		float moveDistanceY = _moveDistanceperTimeY * deltaTime;

		_x += moveDistanceX;
		_y += moveDistanceY;
	}
}

void Character::MoveDeltaPosition(float deltaX, float deltaY)
{
	_x += deltaX;
	_y += deltaY;
}
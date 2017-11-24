#include "PosionItem.h"
#include "Sprite.h"
#include "Map.h"
#include "ComponentSystem.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Character.h"

PosionItem::PosionItem(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFilename) : Component(name)
{
	_type = eComponentType::CT_ITEM;
	_sprite = NULL;
	_scripteFileName = scriptName;
	_textureFilename = textureFilename;
}

PosionItem::~PosionItem()
{

}

void PosionItem::Init()
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
			_posX = map->GetPositionX(_tileX, _tileY);
			_posY = map->GetPositionY(_tileX, _tileY);
			break;
		}
	}
	map->SetTileComponent(_tileX, _tileY, this, false);

	int rotate = rand() % 361;

	WCHAR textureFilename[256];
	wsprintf(textureFilename, L"%s.png", _textureFilename.c_str());

	WCHAR scriptFilename[256];
	{
		wsprintf(scriptFilename, L"%s.json", _scripteFileName.c_str());
		_sprite = new Sprite(textureFilename, scriptFilename, rotate);
		_sprite->Init();
	}
	SetCanMove(true);
}

void PosionItem::Deinit()
{
	_sprite->Deinit();
}

void PosionItem::Update(float deltaTime)
{
	if (_isLive == true)
	{
		_sprite->Update(deltaTime);
	}
}

void PosionItem::Render()
{
	if (_isLive == true)
	{
		_sprite->SetPosition(_posX, _posY);
		_sprite->Render();
	}
}

void PosionItem::Release()
{
	_sprite->Release();
}

void PosionItem::Reset()
{
	_sprite->Reset();
}

void PosionItem::MoveDeltaPosition(float deltaX, float deltaY)
{
	_posX += deltaX;
	_posY += deltaY;
}

void PosionItem::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
}

void PosionItem::ReceiveMessage(const sComponentMsgParam &msgParam)
{
	if (msgParam.message == L"use")
	{
		Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
		Component* sender = msgParam.sender;
		switch (sender->GetType())
		{
		case eComponentType::CT_PLAYER:
			((Character*)sender)->DecreaseHP(1000);
			map->ResetTileComponent(_tileX, _tileY, this);
			_isLive = false;
			break;

		case eComponentType::CT_MONSTER:
			break;

		case eComponentType::CT_NPC:
			break;
		}
	}
}
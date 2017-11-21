#include "State.h"
#include "Character.h"
#include "Sprite.h"

State::State()
{

}

State::~State()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Deinit();
		delete _spriteList[i];
	}
	_spriteList.clear();
}

void State::Init(Character* character)
{
	_character = character;
	CreateSprite();
}

void State::Update(float deltaTime)
{
	_spriteList[(int)_character->GetDirection()]->Update(deltaTime);
}

void State::Start()
{
	_nextState = eStateType::ET_NONE;
}

void State::Stop()
{

}

void State::Release()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Release();
	}
	_spriteList.clear();
}

void State::Render()
{
	_spriteList[(int)_character->GetDirection()]->SetPosition(_character->GetX(), _character->GetY());
	_spriteList[(int)_character->GetDirection()]->Render();
}

void State::Reset()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Reset();
	}
	_spriteList.clear();
}

void State::CreateSprite()
{
	_spriteList.clear();

	WCHAR textureFilename[256];
	wsprintf(textureFilename, L"%s.png", _character->GetTextureFileName().c_str());

	WCHAR scriptFilename[256];
	{
		wsprintf(scriptFilename, L"%s_01.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_02.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_03.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_04.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
}

void State::NextState(eStateType type)
{
	_nextState = type;
}

eStateType State::GetState()
{


	return _getState;
}
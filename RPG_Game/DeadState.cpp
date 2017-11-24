#include "DeadState.h"
#include "Character.h"
#include "Sprite.h"

DeadState::DeadState()
{

}

DeadState::~DeadState()
{

}

void DeadState::Init(Character* character)
{
	State::Init(character);
}

void DeadState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}
}

void DeadState::Start()
{
	State::Start();
}

void DeadState::Stop()
{
	State::Stop();
}

void DeadState::Release()
{
	State::Release();
}

void DeadState::Render()
{
	State::Render();
}

void DeadState::Reset()
{
	State::Reset();
}

void DeadState::CreateSprite()
{
	_spriteList.clear();

	WCHAR textureFilename[256];
	wsprintf(textureFilename, L"%s.png", _character->GetTextureFileName().c_str());

	WCHAR scriptFilename[256];

	{
		wsprintf(scriptFilename, L"%s_Right_dead.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_Left_dead.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_Up_dead.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}

	{
		wsprintf(scriptFilename, L"%s_Down_dead.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
}
#include "Sprite.h"
#include "GameSystem.h"
#include "Frame.h"
#include "Texture.h"
#include "ResourceManager.h"

Sprite::Sprite() : _currnetFrame(0), _frameTime(0.0f), _srcTexture(NULL)
{

}

Sprite::~Sprite()
{

}

void Sprite::Init()
{	
	_device3d = GameSystem::GetInstance()->GetDevice3d();
	_sprite = GameSystem::GetInstance()->GetSprite();
	
	_srcTexture = new Texture();
	_srcTexture->Init(L"character_sprite.png");

	{
		Frame* frame = new Frame();
		frame->Init(_srcTexture, 32*0, 0, 32, 32, 0.2f);
		_frameList.push_back(frame);
	}

	{
		Frame* frame = new Frame();
		frame->Init(_srcTexture, 32*2, 0, 32, 32, 0.2f);
		_frameList.push_back(frame);
	}
	_currnetFrame = 0;
	_frameTime = 0.0f;

	_srcTexture = ResourceManager::GetInstance()->LoadTexture(L"character_sprite.png");
}

void Sprite::Deinit()
{	
	std::vector<Frame*>::iterator itr = _frameList.begin();
	for (itr = _frameList.begin(); itr != _frameList.end(); itr++)
	{
		Frame* frame = (*itr);
		frame->Deinit();
		delete frame;
	}
	_frameList.clear();

	if (_srcTexture != NULL)
	{
		_srcTexture->Deinit();
		delete _srcTexture;
		_srcTexture = NULL;
	}
}

void Sprite::Render()
{
	if (_currnetFrame < _frameList.size())
	_frameList[_currnetFrame]->Render();
}

void Sprite::Reset()
{
	Init();
	std::vector<Frame*>::iterator itr = _frameList.begin();
	for (itr = _frameList.begin(); itr != _frameList.end(); itr++)
	{
		Frame* frame = (*itr);
		frame->Reset();
	}
}

void Sprite::Release()
{
	std::vector<Frame*>::iterator itr = _frameList.begin();
	for (itr = _frameList.begin(); itr != _frameList.end(); itr++)
	{
		Frame* frame = (*itr);
		frame->Release();
	}
	_srcTexture->Release();
}

void Sprite::Update(float deltaTime)
{
	_frameTime += deltaTime;
	if (_frameList[_currnetFrame]->GetFrameDelay() <= _frameTime)
	{
		_frameTime = 0.0f;
		_currnetFrame = (_currnetFrame + 1) % _frameList.size();
	}
}
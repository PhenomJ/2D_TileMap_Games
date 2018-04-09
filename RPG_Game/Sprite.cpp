#include <fstream>
#include <reader.h>

#include "Sprite.h"
#include "GameSystem.h"
#include "Frame.h"
#include "Texture.h"
#include "ResourceManager.h"


Sprite::Sprite(LPCWSTR texturefileName, LPCWSTR scriptfileName, float rotate) : _currnetFrame(0), _frameTime(0.0f), _srcTexture(NULL),
_texturefileName(texturefileName), _scriptfileName(scriptfileName), _rotate(rotate)
{
	
}

Sprite::~Sprite()
{

}

void Sprite::Init(int srcX, int srcY, int x, int y, float frameDelay, D3DCOLOR color)
{
	_device3d = GameSystem::GetInstance()->GetDevice3d();
	_sprite = GameSystem::GetInstance()->GetSprite();

	_srcTexture = ResourceManager::GetInstance()->LoadTexture(_texturefileName);

	{
		Frame* frame = new Frame();
		frame->Init(_srcTexture, srcX, srcY, x, y, _rotate,frameDelay, color);
		_frameList.push_back(frame);
	}

	_currnetFrame = 0;
	_frameTime = 0.0f;
}

void Sprite::Init()
{	
	_device3d = GameSystem::GetInstance()->GetDevice3d();
	_sprite = GameSystem::GetInstance()->GetSprite();
	
	_srcTexture = ResourceManager::GetInstance()->LoadTexture(_texturefileName);

	//json Parsing
	{
		std::vector<std::string> script = ResourceManager::GetInstance()->LoadScript(_scriptfileName);

		for (int i = 0 ; i < script.size(); i++)
		{
			std::string record = script[i];

			Json::Value root;
			Json::Reader reader;
			bool isSuccess = reader.parse(record, root);

			if (isSuccess)
			{
				std::string texture = root["texture"].asString();
				int x = root["x"].asInt();
				int y = root["y"].asInt();
				int width = root["width"].asInt();
				int height = root["height"].asInt();
				double framedelay = root["framedelay"].asDouble();

				if (_rotate == 0)
					_rotate = root["rotate"].asInt();

				Frame* frame = new Frame();
				frame->Init(_srcTexture, x, y, width, height, _rotate,framedelay, D3DCOLOR_ARGB(255, 255, 255, 255));
				_frameList.push_back(frame);
			}
		}
	}

	_currnetFrame = 0;
	_frameTime = 0.0f;
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

	_srcTexture = NULL;
}

void Sprite::Render()
{
	if (_currnetFrame < _frameList.size())
	{
		_frameList[_currnetFrame]->SetPosition(_x, _y);
		_frameList[_currnetFrame]->Render();
	}
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

void Sprite::SetPosition(float posX, float posY)
{
	_x = posX;
	_y = posY;
}

void Sprite::ChangeColor(D3DCOLOR color)
{
	std::vector<Frame*>::iterator itr = _frameList.begin();
	for (itr = _frameList.begin(); itr != _frameList.end(); itr++)
	{
		Frame* frame = (*itr);
		frame->ChangeColor(color);
		frame->Render();
	}
}
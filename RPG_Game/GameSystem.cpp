#include "GameSystem.h"
#include "GameTimer.h"
#include "Sprite.h"
#include <stdio.h>
#include <string>

GameSystem* GameSystem::_instance = NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (VK_ESCAPE == wParam)
			DestroyWindow(hwnd);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello World", L"Hello", MB_OK);
		break;

	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

GameSystem::GameSystem()
{
	_isFullScreen = false;
	//testSpriteList = NULL;
	//_testSpriteList.clear();
	
}

GameSystem::~GameSystem()
{
	RELEASE_COM(_device3d);
	RELEASE_COM(_sprite);

	//if (_testSprite != NULL)
	//{
	//	_testSprite->Deinit();
	//	_testSprite->Release();
	//	_testSprite = NULL;
	//}

	/*for (int i = 0; i < _testSpriteList.size(); i++)
	{
		_testSpriteList[i]->Deinit();
		delete _testSpriteList[i];
	}

	_testSpriteList.clear();*/

	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_testTileMap[x][y]->Deinit();
			delete _testTileMap[x][y];
		}
	}
}

GameSystem* GameSystem::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new GameSystem();
	}
	return _instance;
}

bool GameSystem::InitSystem(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASS  wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc; // 
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"Base"; // 윈도우를 나타내는 이름, 받아올때 사용

	if (!RegisterClass(&wc)) // 등록
	{
		return false;
	}
	DWORD style;
	if (_isFullScreen)
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	
	else
	{
		style = WS_OVERLAPPEDWINDOW;
	}

	// 윈도우 생성
	_hMainWnd = CreateWindow(L"Base", L"Test", style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

	if (_isFullScreen == false)
	{
		RECT clientRect;
		GetClientRect(_hMainWnd, &clientRect);
		
		int addWidth = _clientWidth- clientRect.right;
		int addHeight = _clientHeight - clientRect.bottom;
		int finalwidth = _clientWidth + addWidth;
		int finalheight = _clientHeight + addHeight;

		MoveWindow(_hMainWnd, 0, 0, finalwidth, finalheight, TRUE);
	}

	// 윈도우 출력
	ShowWindow(_hMainWnd, nCmdShow);

	// 윈도우 업데이트
	UpdateWindow(_hMainWnd);

	if (false == InitDirect3D())
	{
		return false;
	}

	/*_testSprite = new Sprite(L"character_sprite.png", L"jsontest.json");
	_testSprite->Init();*/

	/*{
		Sprite* sprite = new Sprite(L"character_sprite.png", L"char_sprite_01.json");
		sprite->Init();
		_testSpriteList.push_back(sprite);
	}

	{
		Sprite* sprite = new Sprite(L"character_sprite.png", L"char_sprite_02.json");
		sprite->Init();
		_testSpriteList.push_back(sprite);
	}

	{
		Sprite* sprite = new Sprite(L"character_sprite.png", L"char_sprite_03.json");
		sprite->Init();
		_testSpriteList.push_back(sprite);
	}

	{
		Sprite* sprite = new Sprite(L"character_sprite.png", L"char_sprite_04.json");
		sprite->Init();
		_testSpriteList.push_back(sprite);
	}*/

	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			Sprite* sprite;
			int randValue = rand() % 4;
			switch (randValue)
			{
			case 0:
				sprite = new Sprite(L"character_sprite.png", L"char_sprite_01.json");
				break;
			case 1:
				sprite = new Sprite(L"character_sprite.png", L"char_sprite_02.json");
				break;
			case 2:
				sprite = new Sprite(L"character_sprite.png", L"char_sprite_03.json");
				break;
			case 3:
				sprite = new Sprite(L"character_sprite.png", L"char_sprite_04.json");
				break;
			default:
				break;
			}

			sprite->Init();
			_testTileMap[x][y] = sprite;
		}
	}

	return true;
}

int GameSystem::UpdateSystem()
{
	MSG msg;
	msg.message = { 0 };
	_gameTimer = new GameTimer();
	_gameTimer->Reset();
	
	_frameduration = 0;

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			// 윈도우 메시지 처리
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else // Message가 정상적으로 들어올때
		{
			_gameTimer->Update();
			float deltaTime = _gameTimer->GetDeltaTime();
			
			float frameTime = 1.0f / 60.0f;
			
			_frameduration += deltaTime;

			//_testSprite->Update(deltaTime);
			//_testSpriteList[2]->Update(deltaTime);
			for (int y = 0; y < 16; y++)
			{
				for (int x = 0; x < 16; x++)
				{
					_testTileMap[x][y]->Update(deltaTime);
				}
			}

			if (frameTime <= _frameduration) // 프레임이 훨씬 더 중요한 경우에는 delta값이 이부분 안에 들어옴.
			{
				wchar_t time[256];
				swprintf(time, L"deltaTime : %f\n", _frameduration);
				OutputDebugString(time);

				_frameduration = 0.0f;
				_device3d->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(53, 41, 42), 0.0f, 0);
				_device3d->BeginScene();
				// Sprite는 _sprite begin-end 사이에 존재해야함.
				
				_sprite->Begin(D3DXSPRITE_ALPHABLEND);
				
				//_testSprite->Render();
				//_testSpriteList[2]->Render();

				float startX = 0.0f;
				float startY = 0.0f;
				float posX = startX;
				float posY = startY;
				int tileSize = 32;

				for (int y = 0; y < 16; y++)
				{
					for (int x = 0; x < 16; x++)
					{
						_testTileMap[x][y]->SetPosition(posX, posY);
						_testTileMap[x][y]->Render();
						posX += 32;						
					}
					posX = startX;
					posY += tileSize;
				}

				_sprite->End();
				

				_device3d->EndScene();

				CheckDeviceLost();
				_device3d->Present(NULL, NULL, NULL, NULL);
			}
			
			
			// 대기영역 -> 게임 처리
			
		}
	}

	return (int)msg.wParam;
}

bool GameSystem::InitDirect3D() // COM interface
{
	LPDIRECT3D9 direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
	{
		MessageBox(0, L"Error", L"Error", MB_OK);
		return false;
	}

	ZeroMemory(&_d3dpp, sizeof(_d3dpp));
	_d3dpp.BackBufferWidth = _clientWidth;
	_d3dpp.BackBufferHeight = _clientHeight;	

	if (_isFullScreen)
	{
		_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}

	else
	{
		_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	}
	_d3dpp.BackBufferCount = 1;
	_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	_d3dpp.hDeviceWindow = _hMainWnd;
	_d3dpp.Windowed = (!_isFullScreen);
	_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	D3DCAPS9 caps;
	HRESULT hr = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if (FAILED(hr))
	{
		MessageBox(0, L"Error", L"Error", MB_OK);
		return false;
	}

	DWORD behavior;
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0  || caps.VertexShaderVersion < D3DVS_VERSION(1,1))
	{
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	
	else
	{
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	hr = direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hMainWnd, behavior, &_d3dpp, &_device3d);
	if (FAILED(hr))
	{
		MessageBox(0, L"Error", L"Error", MB_OK);
		return false;
	}

	hr = D3DXCreateSprite(_device3d, &_sprite);
	if (FAILED(hr))
	{
		MessageBox(0, L"Error", L"Error", MB_OK);
		return false;
	}

	// Texture
	{
		//파일 정보 가져오기
		
		//HRESULT hr = D3DXGetImageInfoFromFile(L"character_sprite.png", &_textureInfo);

		if (FAILED(hr))
		{
			MessageBox(0, L"Image Load Error", L"Image Load Error", MB_OK);
			return false;
		}

		//Texture 생성
		


	}
	
	return true;
}

void GameSystem::CheckDeviceLost()
{
	HRESULT hr = _device3d->TestCooperativeLevel();
		//D3DERR_DEVICENOTRESET : 디바이스 재시동 가능
		//D3DERR_DEVICELOST : 디바이스 로스트 상태라 현재 복구 불가능.

	if (FAILED(hr))
	{
		if (hr == D3DERR_DEVICELOST)
		{
			Sleep(100);
			return;
		}

		else if (hr == D3DERR_DEVICENOTRESET)
		{
			/*for (int i = 0; i < _testSpriteList.size(); i++)
			{
				_testSpriteList[i]->Deinit();
				delete _testSpriteList[i];
			}

			_testSpriteList.clear();*/

			for (int y = 0; y < 16; y++)
			{
				for (int x = 0; x < 16; x++)
				{
					_testTileMap[x][y]->Deinit();
					delete _testTileMap[x][y];
				}
			}

			//_testSprite->Release();
			//RELEASE_COM(_texture);
			InitDirect3D();
			hr = _device3d->Reset(&_d3dpp);

			//_testSprite->Reset();
			/*for (int i = 0 ; i < _testSpriteList.size(); i++)
				_testSpriteList[i]->Reset();*/

			for (int y = 0; y < 16; y++)
			{
				for (int x = 0; x < 16; x++)
				{
					_testTileMap[x][y]->Reset();
				}
			}

			/*
			hr = D3DXCreateTextureFromFileEx
			(
				_device3d,
				L"character_sprite.png",
				_textureInfo.Width,
				_textureInfo.Height,
				1,
				0,
				D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				D3DCOLOR_ARGB(255, 255, 255, 255),
				&_textureInfo,
				NULL,
				&_texture
			);

			_srcTextureRect.left = 0;
			_srcTextureRect.top = 0;
			_srcTextureRect.right = _textureInfo.Width;
			_srcTextureRect.bottom = _textureInfo.Height;
			_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
			*/
		}
	}
}

int GameSystem::GetClientWidth()
{
	return _clientWidth;
}

int GameSystem::GetClientHeight()
{
	return _clientHeight;
}

LPD3DXSPRITE GameSystem::GetSprite()
{
	return _sprite;
}

LPDIRECT3DDEVICE9 GameSystem::GetDevice3d()
{
	return _device3d;
}
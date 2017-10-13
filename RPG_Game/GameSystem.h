#pragma once
#include <d3dx9.h>
#include <Windows.h>

#define RELEASE_COM(x) {if (x != NULL) {x->Release(); x = NULL;}}
#define SAFE_DELETE(x) {if(x) {delete x; x = NULL;}}

class GameTimer;
class Sprite;

class GameSystem
{
private:
	GameSystem();
	static GameSystem* _instance;

public:
	~GameSystem();
	static GameSystem* GetInstance();
	bool InitSystem(HINSTANCE hInstance, int nCmdShow);
	int UpdateSystem();
	
	// Direct3D
public:
	bool InitDirect3D();
	void CheckDeviceLost();

private:
	HWND _hMainWnd;
	GameTimer* _gameTimer;
	float _frameduration;

	LPDIRECT3DDEVICE9 _device3d;
	LPD3DXSPRITE _sprite;

	//Texture
	Sprite* _testSprite;
	
	D3DPRESENT_PARAMETERS _d3dpp;

	bool _isFullScreen;

	int _clientWidth = 1920;
	int _clientHeight = 1080;	

public:
	int GetClientWidth();
	int GetClientHeight();
	LPD3DXSPRITE GetSprite();
	LPDIRECT3DDEVICE9 GetDevice3d();
};
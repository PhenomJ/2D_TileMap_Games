#pragma once
#include <string>
#include <d3dx9.h>

class Font
{
public:
	Font(std::wstring font,int fontSize, D3DCOLOR color);
	~Font();

public:
	void SetRect(int x, int y, int width, int height);
	void SetText(std::wstring text);
	void Render();
	void SetPosition(int x, int y);

private:
	ID3DXFont* _font;
	D3DXCOLOR _color;
	std::wstring _text;

	int _x;
	int _y;
	int _width;
	int _height;
};
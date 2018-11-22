#pragma once

#include <wincodec.h>
#include "Graphics.h"
#include <iostream>

class SpriteSheet
{
private:
	Graphics* gfx;
	ID2D1Bitmap* bmp;
	const float a;

public:
	SpriteSheet(LPCWSTR filename, Graphics* gfx, float a);
	~SpriteSheet();
	void Draw();

};
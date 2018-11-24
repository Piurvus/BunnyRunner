#pragma once

#include <wincodec.h>
#include "Graphics.h"
#include <iostream>

class SpriteSheet
{

private:
	Graphics* gfx;
	ID2D1Bitmap* bmp;
	float a;
	int spriteWidth, spriteHeight;
	int spritesAccross;

public:
	SpriteSheet(LPCWSTR filename, Graphics* gfx, float a);
	SpriteSheet(LPCWSTR filename, Graphics* gfx, float a, int spriteWidth, int spriteHeight);

	~SpriteSheet();

	void Draw(float a);
	void Draw(int index, int x, int y);
};
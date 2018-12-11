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
	void Draw(float x, float y, double size);
	void Draw(float x, float y, double size, double a, bool cuzitwontworkwithoutkappa);
	void Draw(int index, int x, int y, double size);
};
#pragma once

#include "Graphics.h"
#include <random>
#include <iostream>
#include "SpriteSheet.h"
#include <vector>


class Obstacle {

private:

	SpriteSheet* stone;
	SpriteSheet* stone2;
	SpriteSheet* trunk;

	Graphics* gfx;
	
	std::vector<int> spriteHeights;

	float size;
	float x;
	float y = 435;
	bool ownSprite = false;

public:

	void setGfx(Graphics* gfx);

	float width = 0;
	float height = 0;

	D2D_RECT_F rect;
	SpriteSheet* sprite;

	Obstacle(Graphics* gfx);
	Obstacle(Graphics* gfx, LPCWSTR name);
	~Obstacle();

	void show();
	void update(double speed);
	void renew();
	D2D_RECT_F returnPos();

};
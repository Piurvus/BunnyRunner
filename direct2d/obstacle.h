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
	
	std::vector<int> spriteHeights;

	float size;
	bool ownSprite = false;

protected:

	Graphics* gfx;

	float x;
	float y = 435;

public:

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

	friend int setX(Obstacle &obj);
};
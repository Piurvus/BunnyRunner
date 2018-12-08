#pragma once

#include "Graphics.h"
#include <random>
#include <iostream>
#include "SpriteSheet.h"

class Obstacle {
	
	
private:

	Graphics* gfx;
	float x;
	float y = 435;
	bool ownSprite = false;

public:

	float width, height;

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
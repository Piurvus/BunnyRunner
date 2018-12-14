#pragma once
#include "SpriteSheet.h"

class Fox {

	SpriteSheet* fox;
	SpriteSheet* fox2;
	Graphics* gfx;
	D2D1_RECT_F rect;

	float height = 140;
	float width = 153.33333f;
	float x, y, frame, foxSpeed, foxFrame;
	float size = 1.5;

	bool changeDirection = false;
	int directionlatency = 0;

public:

	Fox(Graphics* gfx);
	~Fox();

	void changeDir();

	void show();
	void update(double speed);
	void renew();
	D2D1_RECT_F returnPos();
};
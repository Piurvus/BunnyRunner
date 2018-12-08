#pragma once
#include "SpriteSheet.h"

class Fox {

	SpriteSheet* fox;
	Graphics* gfx;
	D2D1_RECT_F rect;

	float height = 140;
	float width = 153.33333f;
	float x, y, frame, foxSpeed, foxFrame;
	float size = 1.5;

public:

	Fox(Graphics* gfx);
	~Fox();

	void show();
	void update(double speed);
	void renew();
	D2D1_RECT_F returnPos();
};
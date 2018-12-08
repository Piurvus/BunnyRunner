#pragma once

#include "Graphics.h"
#include <random>
#include <iostream>

class Obstacle {

	Graphics* gfx;
	D2D_RECT_F rect;
	
private:
	
	float width, height;
	float x;
	float y = 435;

public:

	Obstacle(Graphics* gfx);
	~Obstacle();

	void show();
	void update(double speed);
	void renew();
	D2D_RECT_F returnPos();

};
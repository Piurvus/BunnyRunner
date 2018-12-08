#pragma once
#include "obstacle.h"
#include "Graphics.h"

class Carrot : public Obstacle {

	float size = 0.15;

public:
	using Obstacle::Obstacle;

	D2D_RECT_F returnPos();
	void show();

};
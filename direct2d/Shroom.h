#pragma once
#include "obstacle.h"
#include <random>
#include "SpriteSheet.h"

class Shroom : public Obstacle {

	SpriteSheet* shroom;
	SpriteSheet* shroom2;

	void renew();

	bool broom = false;

public:
	
	Shroom(Graphics* gfx);
	~Shroom();

	void update(double speed);
	void show();
	bool isBroom();
};
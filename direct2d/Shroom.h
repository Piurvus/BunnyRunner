#pragma once
#include "obstacle.h"

class Shroom : public Obstacle {

	SpriteSheet* blueShroom; 
	SpriteSheet* purpleShroom;

public:
	Shroom(Graphics* gfx);
	~Shroom();
};

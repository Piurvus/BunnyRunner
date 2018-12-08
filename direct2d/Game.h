#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"
#include <ctime>
#include "Bunny.h"
#include "obstacle.h"

class Game {

	SpriteSheet* sprites;
	Bunny* bunny;
	Graphics* gfx;
	Obstacle* obj;

public:
	
	Game(Graphics* gfx);
	~Game();

	void Run();
	void UpdateModel();
	void ComposeFrame();

private:

	double speed = 1.0f;
	double refreshRate = 1/30;
	std::clock_t clock;
	double charge = 0;
	bool checkCollision(D2D1_RECT_F rect1, D2D1_RECT_F rect2); 

};
#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"
#include <ctime>
#include "Bunny.h"
#include "obstacle.h"
#include "Carrot.h"
#include "Fox.h"

class Game {
	
	Fox* fox;
	Carrot* carrot;
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

	int carrots = 0;
	double speed = 1.0f;
	double refreshRate = 1/30;
	std::clock_t clock;
	double charge = 0;
	bool checkCollision(D2D1_RECT_F rect1, D2D1_RECT_F rect2); 

};
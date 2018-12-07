#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"
#include <ctime>
#include "Bunny.h"

class Game {

	SpriteSheet* sprites;
	Bunny* bunny;
	Graphics* gfx;

public:
	
	Game(Graphics* gfx);
	~Game();

	void Run();
	void UpdateModel();
	void ComposeFrame();


private:

	double refreshRate = 1/30;
	std::clock_t clock;
	double charge = 0;

};
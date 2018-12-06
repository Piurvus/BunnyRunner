#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"
#include <ctime>

class Game {

	SpriteSheet* sprites;
	SpriteSheet* rabbit;

	Graphics* gfx;

public:
	
	Game(Graphics* gfx);
	~Game();

	void Run();
	void UpdateModel();
	void ComposeFrame();


private:

	double frame = 0;
	double rabbitSpeed = 0.1;
	double refreshRate = 1/30;
	std::clock_t clock;
	bool loading = true;
	float y = 0.0;
	float ySpeed = 0.0;

};
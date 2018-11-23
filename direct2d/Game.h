#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"

class Game {

	SpriteSheet* sprites;
	Graphics* gfx;

public:
	
	Game(Graphics* gfx);
	~Game();

	void Run();
	void UpdateModel();
	void ComposeFrame();

private:

	bool loading = true;
	float y = 0.0;
	float ySpeed = 0.0;

};
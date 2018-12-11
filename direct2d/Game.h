#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"
#include <ctime>
#include "Bunny.h"
#include "obstacle.h"
#include "Carrot.h"
#include "Fox.h"
#include "Water.h"
#include <fstream>


class Game {

	Fox* fox;
	Water* water;
	Carrot* carrot;
	SpriteSheet* sprites;
	Bunny* bunny;
	Graphics* gfx;
	Obstacle* obj; 
	std::ofstream outfile;
	std::ifstream infile;

public:
	
	Game(Graphics* gfx);
	~Game();

	void Run();
	void UpdateModel();
	void ComposeFrame();

private:

	double xScreen1, xScreen2, xScreen3;

	D2D1_RECT_F bottom = D2D1::Rect(0, 451, 1600, 600);
	D2D1_COLOR_F color = D2D1::ColorF(50, 50, 255);

	wchar_t distanceCountText[256];
	wchar_t carrotCountText[256];
	float distanceCount = 0.0f;

	int carrots = 0;
	double speed = 1.0;
	double refreshRate = 1/30;

	std::clock_t clock;
	std::clock_t carrotsTimer = 0;
	
	std::string highscore;
	wchar_t highscoree[100];

	double charge = 0;
	bool checkCollision(D2D1_RECT_F rect1, D2D1_RECT_F rect2); 

};
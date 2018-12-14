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
#include "Background.h"
#include "Shroom.h"

class Game {

	Fox* fox;
	Water* water;
	Carrot* carrot;
	Bunny* bunny;
	Graphics* gfx;
	Obstacle* obj; 
	Background* background;
	Shroom* shroom;
	std::ofstream outfile;
	std::ifstream infile;

public:
	
	Game(Graphics* gfx);
	~Game();

	void Run();
	void UpdateModel();
	void ComposeFrame();

private:

	D2D1_RECT_F bottom = D2D1::Rect(0, 471, 1600, 600);
	D2D1_COLOR_F color = D2D1::ColorF(50, 50, 255);

	wchar_t distanceCountText[256];
	wchar_t carrotCountText[256];
	float distanceCount = 0.0f;

	int carrots = 0;
	double speed = 1.0;
	double refreshRate = 1/30;

	std::clock_t clock;
	std::clock_t carrotsTimer = 0;
	
	std::string highscoreString;
	wchar_t highscoreWchar[100];
	int highscoreInt = 0;
	void updateHighscore();

	double charge = 0;
	bool checkCollision(D2D1_RECT_F rect1, D2D1_RECT_F rect2); 

};
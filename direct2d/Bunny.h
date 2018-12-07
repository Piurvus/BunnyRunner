#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"

class Bunny {

	Graphics* gfx;
	SpriteSheet* bunny;

	double frame;
	double bunnySpeed;
	float x, y;
	double sizeX, sizeY;
	double speedY;


public:

	Bunny(Graphics * gfx);
	~Bunny();

	void showBunny();
	void updateBunny();
	void jump(double charge);

	void die();
	
	//void crouch();


};
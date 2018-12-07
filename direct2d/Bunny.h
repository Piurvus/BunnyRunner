#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"

class Bunny {

	Graphics* gfx;
	SpriteSheet* bunny;
	SpriteSheet* deadBunny;

	double frame;
	double bunnySpeed;
	float x, y;
	double sizeX, sizeY;
	double speedY;
	double height;
	bool isDead = false;

public:

	Bunny(Graphics * gfx);
	~Bunny();

	void showBunny();
	void updateBunny();
	void jump(double charge);
	bool onGround();
	void die();
	
	//void crouch();


};
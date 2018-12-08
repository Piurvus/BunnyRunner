#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"

class Bunny {

	Graphics* gfx;
	SpriteSheet* bunny;
	SpriteSheet* deadBunny;
	D2D1_RECT_F rect;

	double frame;
	double bunnySpeed;
	float x, y;
	float sizeX, sizeY;
	double speedY;
	double height;
	bool isDead = false;

public:

	Bunny(Graphics * gfx);
	~Bunny();

	void showBunny();
	void updateBunny(double speed);
	void jump(double charge);
	bool onGround();
	void die();
	D2D1_RECT_F returnPos();
	
	//void crouch();


};
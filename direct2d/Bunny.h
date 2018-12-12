#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"

class Bunny {

	Graphics* gfx;
	SpriteSheet* bunny;
	SpriteSheet* deadBunny;
	SpriteSheet* puff;
	D2D1_RECT_F rect;

	float puffi = 0;
	float puffiX, puffiY;

	double frame;
	double bunnySpeed;
	float x, y;
	float sizeX, sizeY;
	double speedY;
	double height;
	bool dead = false;

public:

	Bunny(Graphics * gfx);
	~Bunny();

	void showBunny();
	void updateBunny(double speed);
	void jump(double charge);
	bool onGround();
	bool isDead();
	void die();
	D2D1_RECT_F returnPos();
	
	//void crouch();


};
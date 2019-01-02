#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"

class Bunny {

	Graphics* gfx;

	//	Das Bild mit den verschiedenen Hasen
	SpriteSheet* bunny;
	//	Das Bild mit den verschiedenen Hasen mit einer Karotte im Mund
	SpriteSheet* bunnyCarrot;
	//	toter Hase
	SpriteSheet* deadBunny;
	//	Jump-Wolke
	SpriteSheet* puff;
	//	Wolke
	SpriteSheet* cloudy;
	D2D1_RECT_F rect;

	//	Werte der Jump-Wolke
	float puffi = 0;
	float puffiX, puffiY;

	double frame;
	double bunnySpeed;
	float x, y;
	float sizeX, sizeY;
	double speedY;
	double height;
	bool dead = false;

	bool crouched = false;
	int crouchLatency = 3;

	bool up = false;
	bool clouded = false;
	int cloudTimer;

public:

	Bunny(Graphics * gfx);
	~Bunny();

	void showBunny(bool carrot);
	void updateBunny(double speed);
	void jump(double charge);
	void jump(double charge, bool cloud);
	bool onGround();
	bool isDead();
	void die();
	void crouch();
	bool isCrouched();
	void getClouded();
	bool isClouded();

	D2D1_RECT_F returnPos();
	
	//void crouch();


};
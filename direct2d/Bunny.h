// Header Datei für den Hasen
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

	double frame;	//	die Ganzzahl davon steht für das jeweilige Bild von der Animation
	double bunnySpeed;	//	die Änderungsrate der verschiedenen Animationsbilder
	float x, y;	//	Position
	float sizeX, sizeY;	//	Grösse
	double speedY;	//	die momentane Fallgeschwindigkeit
	double height;	//	die maximale Höhe eines Sprunges
	bool dead = false;

	bool crouched = false;
	int crouchLatency = 3;

	bool up = false;	//	wird nicht mehr verwendet

	//	Die Wolke
	bool clouded = false;
	int cloudTimer;

public:

	Bunny(Graphics * gfx);
	~Bunny();

	void showBunny(bool carrot);
	void updateBunny(double speed);
	void jump(double charge);
	void jump(double charge, bool cloud);
	void getClouded();
	void die();
	void crouch();

	bool onGround();
	bool isDead();
	bool isCrouched();
	bool isClouded();

	D2D1_RECT_F returnPos();
	
	//void crouch();


};
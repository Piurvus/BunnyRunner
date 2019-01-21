//	Header Datei f�r den Fuchs
#pragma once
#include "SpriteSheet.h"

class Fox {
	//	Bilder vom vorw�rts/r�ckw�rts -rennenden Fuchs
	SpriteSheet* fox;
	SpriteSheet* fox2;

	Graphics* gfx;
	D2D1_RECT_F rect;

	//	Gr�sse einer Frame im Bild
	float height = 140;
	float width = 153.33333f;

	//	Position, Animationsbild, Geschwindigkeit sowie Geschwindigkeit der Bewegung
	float x, y, frame, foxSpeed, foxFrame;

	//	Gr�sse des Fuchses
	float size = 1.5;

	bool changeDirection = false;	//	Richtung in die der Fuchs sich bewegt
	int directionlatency = 20;	//	Verz�gerung zwischen dem Richtungswechsel damit der Fuchs nicht in einem Objekt bleibt

public:

	Fox(Graphics* gfx);
	~Fox();

	void changeDir();
	void show();
	void update(double speed);
	void renew();
	D2D1_RECT_F returnPos();
};
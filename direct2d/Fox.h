//	Header Datei für den Fuchs
#pragma once
#include "SpriteSheet.h"

class Fox {
	//	Bilder vom vorwärts-/ rückwärts- rennenden Fuchs
	SpriteSheet* fox;
	SpriteSheet* fox2;

	Graphics* gfx;

	//	Hitbox
	D2D1_RECT_F rect;

	//	Grösse einer Frame im Bild
	float height = 140;
	float width = 153.33333f;

	//	Position, Animationsbild, Geschwindigkeit sowie Geschwindigkeit der Bewegung
	float x, y, frame, foxSpeed, foxFrame;

	//	Grösse des Fuchses
	float size = 1.5;

	bool changeDirection = false;	//	Richtung in die der Fuchs sich bewegt
	int directionlatency = 20;		//	Verzögerung zwischen dem Richtungswechsel damit der Fuchs nicht in einem Objekt hängen bleibt

public:

	Fox(Graphics* gfx);
	~Fox();

	void changeDir();				//	Richtungswechsel
	void show();					//	Anzeigen des Fuchses
	void update(double speed);		//	Aktualisieren des Fuchses
	void renew();					//	Fuchs kriegt eine neue x Position 
	D2D1_RECT_F returnPos();		//	Hitbox wird weitergegeben
};
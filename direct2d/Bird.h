//	Header Datei für den Vogel
#pragma once
#include "SpriteSheet.h"


class Bird {
	//	Bilder vom Vogel
	SpriteSheet* bird;
	Graphics* gfx;
	//	Hitbox
	D2D1_RECT_F rect;

	//	Grösse einer Frame im Bild
	float height = 145;
	float width = 224;

	//	Position, Animationsbild, Geschwindigkeit sowie Geschwindigkeit der Bewegung
	float x, y, frame, birdSpeed, birdFrame;

	//	Grösse des Vogels
	float size = 0.8;

public:

	Bird(Graphics* gfx);
	~Bird();
	void show();					//	Anzeigen des Vogels
	void update(double speed);		//	Aktualisieren des Vogels
	void renew();					//	Vogel kriegt eine neue x Position 
	D2D1_RECT_F returnPos();		//	Hitbox wird weitergegeben
};

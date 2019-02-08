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
	float height = 140;
	float width = 153.33333f;

	//	Position, Animationsbild, Geschwindigkeit sowie Geschwindigkeit der Bewegung
	float x, y, frame, birdSpeed, birdFrame;

	//	Grösse des Fuchses
	float size = 1.5;

public:

	Bird(Graphics* gfx);
	~Bird();
			//	Richtungswechsel
	void show();					//	Anzeigen des Fuchses
	void update(double speed);		//	Aktualisieren des Fuchses
	void renew();					//	Fuchs kriegt eine neue x Position 
	D2D1_RECT_F returnPos();		//	Hitbox wird weitergegeben
};

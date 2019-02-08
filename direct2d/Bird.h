//	Header Datei f�r den Vogel
#pragma once
#include "SpriteSheet.h"


class Bird {
	//	Bilder vom Vogel
	SpriteSheet* bird;
	Graphics* gfx;
	//	Hitbox
	D2D1_RECT_F rect;

	//	Gr�sse einer Frame im Bild
	float height = 140;
	float width = 153.33333f;

	//	Position, Animationsbild, Geschwindigkeit sowie Geschwindigkeit der Bewegung
	float x, y, frame, birdSpeed, birdFrame;

	//	Gr�sse des Fuchses
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

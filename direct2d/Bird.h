//	Header Datei für den Vogel
/*
	Der Vogel funktioniert ähnlich wie auch der Fuchs und auch der Hase.
	Mithilfe von SpriteSheet lassen sich die verschiedenen Animations Bilder des Vogels laden, welche dann nach einander
	dargestellt werden. Die Variable frame bestimmt welches Bild aktuell angezeigt werden soll. Die Variablen birdSpeed und birdFrame
	bestimmen die Geschwindigkeit der x Achsen Aktualisierung, sprich die eigentliche Geschwindigkeit des Vogels, sowie die Aktualisierungsrate
	der frame Variable, also wie schnell der Vogel schlussendlich flattert.
	Der Vogel besitzt noch Variablen wie x und y, welche einfach seine Position im Fenster angeben, sowie eines Vierecks D2D1_RECT_F rect,
	welches die Hitbox des Vogels bestimmt.
	Diese Hitbox wird in der Gameschlaufe immer wieder auf Kollision mit dem Hasen überprüft.
*/
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

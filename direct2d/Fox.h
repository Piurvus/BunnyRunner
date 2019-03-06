//	Header Datei für den Fuchs
/*
	Der Fuchs funktioniert ähnlich wie der Hase und der Vogel.
	Wie auch die anderen beiden Lebewesen besitzt der Fucks Animationsbilder, welche mit einer Variable frame jeweils dargestellt werden
	können. Anders als bei den anderen beiden Lebewesen ist, dass der Fuchs auch noch gespiegelte Animationsbilder besitzt, damit
	er auch in die andere Richtung rennen kann. Dies ist notwendig da, sobald der Fuchs in ein Objekt hineinrennt seine Richtung wechselt.
	Damit der Fuchs aber nicht in einem Objekt stecken bleiben kann, wurde eine directionlatency eingeführt, welche den Fuchs so lange daran
	hindert seine Richtung zu ändern, bis genug Zeit verstrichen ist.
	Wie auch der Hase und Vogel besitzt der Fuchs ein eigenes Rechteck, welches als Hitbox dient und mithilfe der Grösse des Fuchses und der
	x, sowie y Koordinaten berechnet wird. Zusätzlich bekommen die Variablen foxSpeed und foxFrame zufällige Werte, so dass der Fuchs nie genau
	gleich schnell ist.
*/



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
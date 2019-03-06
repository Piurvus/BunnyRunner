//	Header Datei f�r den Fuchs
/*
	Der Fuchs funktioniert �hnlich wie der Hase und der Vogel.
	Wie auch die anderen beiden Lebewesen besitzt der Fucks Animationsbilder, welche mit einer Variable frame jeweils dargestellt werden
	k�nnen. Anders als bei den anderen beiden Lebewesen ist, dass der Fuchs auch noch gespiegelte Animationsbilder besitzt, damit
	er auch in die andere Richtung rennen kann. Dies ist notwendig da, sobald der Fuchs in ein Objekt hineinrennt seine Richtung wechselt.
	Damit der Fuchs aber nicht in einem Objekt stecken bleiben kann, wurde eine directionlatency eingef�hrt, welche den Fuchs so lange daran
	hindert seine Richtung zu �ndern, bis genug Zeit verstrichen ist.
	Wie auch der Hase und Vogel besitzt der Fuchs ein eigenes Rechteck, welches als Hitbox dient und mithilfe der Gr�sse des Fuchses und der
	x, sowie y Koordinaten berechnet wird. Zus�tzlich bekommen die Variablen foxSpeed und foxFrame zuf�llige Werte, so dass der Fuchs nie genau
	gleich schnell ist.
*/



#pragma once
#include "SpriteSheet.h"

class Fox {
	//	Bilder vom vorw�rts-/ r�ckw�rts- rennenden Fuchs
	SpriteSheet* fox;
	SpriteSheet* fox2;

	Graphics* gfx;

	//	Hitbox
	D2D1_RECT_F rect;

	//	Gr�sse einer Frame im Bild
	float height = 140;
	float width = 153.33333f;

	//	Position, Animationsbild, Geschwindigkeit sowie Geschwindigkeit der Bewegung
	float x, y, frame, foxSpeed, foxFrame;

	//	Gr�sse des Fuchses
	float size = 1.5;

	bool changeDirection = false;	//	Richtung in die der Fuchs sich bewegt
	int directionlatency = 20;		//	Verz�gerung zwischen dem Richtungswechsel damit der Fuchs nicht in einem Objekt h�ngen bleibt

public:

	Fox(Graphics* gfx);
	~Fox();

	void changeDir();				//	Richtungswechsel
	void show();					//	Anzeigen des Fuchses
	void update(double speed);		//	Aktualisieren des Fuchses
	void renew();					//	Fuchs kriegt eine neue x Position 
	D2D1_RECT_F returnPos();		//	Hitbox wird weitergegeben
};
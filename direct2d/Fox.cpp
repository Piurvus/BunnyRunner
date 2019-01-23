//	Diese Datei macht einen Feind, den Fuchs.

#include "Fox.h"
//	Um Zufallszahlen zu generieren
#include <random>
//	Cin und Cout.
#include <iostream> 



Fox::Fox(Graphics * gfx):
	gfx(gfx)
{
	//	Füchse werden erstellt (in beide Richtungen)
	fox = new SpriteSheet(L"fox.png", gfx, 1.0f, width, height);
	fox2 = new SpriteSheet(L"fox2.png", gfx, 1.0f, width, height);

	y = 248;
	frame = 0;
	foxFrame = 0.3;

	//	Zufällige Zahl zwischen 4000 und 8000
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4000, 8000);

	//	Zufällige Werte werden zugewiesen
	foxSpeed = (float)(dist(rng) % 20)/10 + 0.8;
	x = dist(rng) - width;
	foxFrame = 0.075*foxSpeed;
}

Fox::~Fox()
{
	//	Aufräumen
	delete fox;
	delete fox2;
	delete gfx;
	delete &rect;
}

void Fox::changeDir()
{
	//	Falls er nicht gerade erst seine Richtung gewechselt hat
	if (!directionlatency) {
		changeDirection = !changeDirection;		//	Gibt an in welche Richtung der Fuchs rennt
		directionlatency = 60;					//	Verzögerung zwischen Richtungswechsel
	}
}

void Fox::show()
{
	//	Für beide Richtungen das Zeichnen des Fuchses
	if (changeDirection) {
		fox2->Draw((int)(frame) % 6, x, y, size);	//	Die "frame" gibt an, welches Animationsbild dargestellt wird
	}
	else {
		fox->Draw((int)(frame) % 6, x, y, size);	//	Die "frame" gibt an, welches Animationsbild dargestellt wird
	}
}

void Fox::update(double speed)
{
	//	Verzögerung des Richtungswechsels wird kleiner
	if (directionlatency)
		directionlatency--;

	//	X Position Änderung in eine Richtung
	if (changeDirection) {
		x += -speed * 5 + 5 * foxSpeed;
	}
	else {
		x -= speed * 5 + 5 * foxSpeed;
	}

	//	Damit er nicht für immer davon rennt
	if (x >= 1800){
		changeDirection = false;
	}

	//	Aktualisieren des Bildes
	frame += speed * foxFrame;	

	//	Erneuern des Fuchses, falls dieser aus dem Bild rennt
	if (x + width < 0) {
		renew();
	}

	//	Anpassen der Hitbox
	rect = { x+10, y+130, x + width+50, y + height+50 };
}

void Fox::renew()
{
	//	Zufall
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4000, 8000);

	//	Fuchs wird zufällig verändert
	x = dist(rng) - width;	
	foxSpeed = (float)(dist(rng) % 20) / 10 + 0.8;
	foxFrame = 0.075*foxSpeed;
}

D2D1_RECT_F Fox::returnPos()
{
	return rect;
}



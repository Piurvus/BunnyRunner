//	Diese Datei macht einen Feind, den Vogel.
#include "Bird.h"
//	Um Zufallszahlen zu generieren
#include <random>
Bird::Bird(Graphics * gfx) :
	gfx(gfx)
{
	//	Vögel werden erstellt (in beide Richtungen)
	bird = new SpriteSheet(L"Birdy.png", gfx, 1.0f, width, height); // Bird

	y = 150;
	frame = 0;
	birdFrame = 0.3;

	//	Zufällige Zahl zwischen 4000 und 8000
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4000, 8000);

	//	Zufällige Werte werden zugewiesen
	birdSpeed = 2;
	x = dist(rng) - width;
	birdFrame = 0.075*birdSpeed;
}

Bird::~Bird()
{
	//	Aufräumen
	delete bird;
	delete gfx;
	delete &rect;
}

void Bird::show()
{
	//	Zeichen des Vogels
	bird->Draw((int)(frame) % 8, x, y, size);	//	Die "frame" gibt an, welches Animationsbild dargestellt wird
	//gfx->DrawRectangle(rect);
}

void Bird::update(double speed)
{

	//	X Position Änderung in eine Richtung
	x -= speed * 5 + 5 * birdSpeed;

	//	Aktualisieren des Bildes
	frame += speed * birdFrame;

	//	Erneuern des Vogels, falls dieser aus dem Bild rennt
	if (x + width < 0) {
		renew();
	}

	//	Anpassen der Hitbox
	rect = { x+40 , y+25, x + width-40, y+height-25};
}

void Bird::renew()
{
	//	Zufall
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4000, 8000);

	//	Vogels wird zufällig verändert
	x = dist(rng) - width;
	birdSpeed = 2;
	birdFrame = 0.075 *birdSpeed;
}

D2D1_RECT_F Bird::returnPos()
{
	return rect;
}
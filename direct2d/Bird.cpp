//	Diese Datei macht einen Feind, den Vogel.
#include "Bird.h"
//	Um Zufallszahlen zu generieren
#include <random>
Bird::Bird(Graphics * gfx) :
	gfx(gfx)
{
	//	V�gel werden erstellt (in beide Richtungen)
	bird = new SpriteSheet(L"Birdy.png", gfx, 1.0f, width, height); // Bird

	y = 248;
	frame = 0;
	birdFrame = 0.3;

	//	Zuf�llige Zahl zwischen 4000 und 8000
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4000, 8000);

	//	Zuf�llige Werte werden zugewiesen
	birdSpeed = (float)(dist(rng) % 20) / 10 + 0.8;
	x = dist(rng) - width;
	birdFrame = 0.075*birdSpeed;
}

Bird::~Bird()
{
	//	Aufr�umen
	delete bird;
	delete gfx;
	delete &rect;
}

void Bird::show()
{
	//	Zeichen des Vogels
	bird->Draw((int)(frame) % 8, x, y, size);	//	Die "frame" gibt an, welches Animationsbild dargestellt wird
	gfx->DrawRectangle(rect);
}

void Bird::update(double speed)
{

	//	X Position �nderung in eine Richtung
	x -= speed * 5 + 5 * birdSpeed;

	//	Aktualisieren des Bildes
	frame += speed * birdFrame;

	//	Erneuern des Vogels, falls dieser aus dem Bild rennt
	if (x + width < 0) {
		renew();
	}

	//	Anpassen der Hitbox
	rect = { x+30 , y, x + width-30, y+height};
}

void Bird::renew()
{
	//	Zufall
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4000, 8000);

	//	Vogels wird zuf�llig ver�ndert
	x = dist(rng) - width;
	birdSpeed = (float)(dist(rng) % 20) / 10 + 0.8;
	birdSpeed = 0.075*birdSpeed;
}

D2D1_RECT_F Bird::returnPos()
{
	return rect;
}
#include "Bunny.h"

Bunny::Bunny(Graphics * gfx):
	gfx(gfx)
{
	deadBunny = new SpriteSheet(L"deadle.png", gfx, 1.0f);
	bunny = new SpriteSheet(L"rabbit.png", gfx, 1.0f, 8.233333 * 40, 80 * 4);
	bunnyCarrot = new SpriteSheet(L"rabbitcarrot.png", gfx, 1.0f, 8.233333 * 40, 80 * 4);
	puff = new SpriteSheet(L"puff.png", gfx, 1.0f);
	cloudy = new SpriteSheet(L"cloud.png", gfx, 1.0f);
	
	x = 50;
	y = 300;
	sizeX = 0.5;
	frame = 0;
	bunnySpeed = 0.1;
	speedY = 0;
} 

Bunny::~Bunny()
{
	delete deadBunny;
	delete bunny;
	delete cloudy;
}

void Bunny::showBunny(bool carrot)
{
	//	Falls auf Wolke
	if (clouded) {
		if (carrot) {
			bunnyCarrot->Draw((int)(frame) % 6, (int)x, (int)y, sizeX);	//	Hase mit Karotte (Bild abh�ngig von frame) wird gezeichnet
		}
		else {
			bunny->Draw((int)(frame) % 6, (int)x, (int)y, sizeX);	//	Hase (Bild abh�ngig von frame) wird gezeichnet
		}
		cloudy->Draw(x-100, y+70, 0.4, cloudTimer/(30.0*15.0)+0.3, true);	//	Die Wolke wird abh�ngig von dem cloudTimer st�rker oder schw�cher gezeichnet
	}
	if (!dead) {	//	else if nicht m�glich
		if (carrot) {
			bunnyCarrot->Draw((int)(frame) % 6, (int)x, (int)y, sizeX);
		}
		else {
			bunny->Draw((int)(frame) % 6, (int)x, (int)y, sizeX);
		}
	}
	else {
		deadBunny->Draw(x-100, y-50, sizeX);	//	toter Hase wird gezeichnet
	}
	if (puffi) {
		puff->Draw(puffiX, puffiY, 0.5, puffi/100, true);	//	Jump-Wolke wird gezeichnet
	}
}

void Bunny::updateBunny(double speed)
{
	//	Falls auf Wolke
	if (clouded) {
		cloudTimer--;

		// Fallgeschwindigkeit wird verringert
		if (GetAsyncKeyState(VK_UP))
			speedY -= 0.5;

		// Fallgeschwindigkeit wird erh�ht
		else if (GetAsyncKeyState(VK_DOWN))
			speedY += 0.5;
		else speedY += 0.2;
		y += speedY;

		if (y >= 800)	//	Falls ausserhalb des Bildes
			die();
		if (!cloudTimer)	//	Zeitlimite
			clouded = false;

	}
	else {
		if (crouchLatency) {
			crouchLatency--;
		}
		else {
			crouched = false;
		}
		if (puffi)	//	Timer der Jump-Wolke
			puffi--;

		//	Animation Jump
		if (y < 300 && y > 300 - height && speedY < 0) {
			frame = 3;
		}
		else if (y < 300 - height && speedY < 0) {
			frame = 4;
		}
		else if (y < 300 - 2 * height && speedY >0) {
			frame = 5;
		}
		else if (y < 300 - height && speedY > 0) {
			frame = 0;
		}
		else if (y < 300 && y > 300 - height && speedY > 0) {
			frame = 1;
		}

		//	Bewegung des Hasens abh�ngig von seiner Geschwindigkeit
		frame += bunnySpeed * speed;

		//	Gravitiy
		if (speedY != 0) {
			speedY += 0.2;
		}

		//	Crouch
		if (crouched) {
			speedY += 0.7;
		}

		//	Jump
		y += speedY;

		//	Bewegung der Jump-Wolke abh�ngig von Geschwindigkeit
		puffiX -= 5 * speed;

		//	Der Boden ist nicht durchl�ssig (sozusagen anti-leporidaepermeable)
		if (y >= 300.0f) {
			speedY = 0;
			y = 300.0f;
		}
	}
}

void Bunny::jump(double charge)
{
	//	Falls mehrfachsprung -> Sprung-Wolke
	if (!onGround()) {
		puffi = 100;
		puffiX = x;
		puffiY = y+130;
	}

	//	maximal
	if (charge >= 60)
		charge = 60;

	charge *= 2;

	//	notwendig f�r Jumpanimation (max H�he des Sprungs)
	height = charge / 0.6;

	//	die Anfangsgeschwindigkeit des Sprungs
	speedY = - sqrt(charge);
}

//	jump falls Kollision mit Pilz
void Bunny::jump(double charge, bool cloud)
{
	if (charge >= 60)
		charge = 60;

	charge *= 2;

	height = charge / 0.6;

	speedY = -sqrt(charge);
}

bool Bunny::onGround()
{
	if (y == 300)
		return true;

	return false;
}

bool Bunny::isDead()
{
	if (dead)
		return true;
	return false;
}

void Bunny::die()
{
	clouded = false;
	dead = true;
	if (speedY < 1)
		speedY = 10;
}

void Bunny::crouch()
{
	crouched = true;
	crouchLatency = 3;
}

bool Bunny::isCrouched()
{
	if (crouched)
		return true;
	return false;
}

void Bunny::getClouded()
{
	frame = 4;
	clouded = true;
	cloudTimer = 30 * 15;
}

bool Bunny::isClouded()
{
	return clouded;
}

D2D1_RECT_F Bunny::returnPos()
{
	rect = { x + 65, y + 25, x -25 + 8.233333f * 40 * sizeX, y - 25 + 80 * 4 * sizeX };
	return rect;
}



#include "Bunny.h"

Bunny::Bunny(Graphics * gfx):
	gfx(gfx)
{
	deadBunny = new SpriteSheet(L"deadle.png", gfx, 1.0f);
	bunny = new SpriteSheet(L"rabbit.png", gfx, 1.0f, 8.233333 * 40, 80 * 4);
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

}

void Bunny::showBunny()
{
	if (!isDead) {
		bunny->Draw((int)(frame) % 6, x, y, sizeX);
	}
	else {
		deadBunny->Draw(x-100, y-50, sizeX);
	}

}

void Bunny::updateBunny()
{
	if (!isDead) {
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

		frame += bunnySpeed;

		//	Gravitiy
		if (speedY != 0) {
			speedY += 0.1;
		}

		//	Jump
		y += speedY;

		if (y >= 300.0f) {
			speedY = 0;
			y = 300.0f;
		}
	}
}

void Bunny::jump(double charge)
{
	if (charge >= 60)
		charge = 60;

	height = charge / 0.6;

	speedY = - sqrt(charge);
}

bool Bunny::onGround()
{
	if (y == 300)
		return true;

	return false;
}

void Bunny::die()
{
	isDead = true;
}



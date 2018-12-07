#include "Bunny.h"

Bunny::Bunny(Graphics * gfx):
	gfx(gfx)
{

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
	delete bunny;
}

void Bunny::showBunny()
{

	bunny->Draw((int)(frame) % 6, x, y, sizeX);

}

void Bunny::updateBunny()
{
	if (y < 300 && y > 300 - height && speedY < 0) {
		if (changer) {
			changer = !changer;
			frame = 3;
		}
		else {
			changer = !changer;
			frame = 2;
		}
	}
	else if (y < 300 - height && speedY < 0) {
		if (changer) {
			changer = !changer;
			frame = 4;
		}
		else {
			changer = !changer;
			frame = 5;
		}
	}
	else if (y < 300 - height && speedY > 0) {
		if (changer) {
			changer = !changer;
			frame = 5;
		}
		else {
			changer = !changer;
			frame = 0;
		}
	}
	else if (y < 300 && y > 300 - height && speedY > 0) {
		if (changer) {
			changer = !changer;
			frame = 1;
		}
		else {
			changer = !changer;
			frame = 0;
		}
	}


	frame += bunnySpeed;


	if (speedY != 0) {
		speedY += 0.1;
	}

	y += speedY;

	if (y >= 300.0f) {
		speedY = 0;
		y = 300.0f;
	}



	/*
	if (GetAsyncKeyState(VK_CONTROL)) {
		bunnySpeed += 0.001;
	}
	else
		bunnySpeed = 0.1;
	*/
}

void Bunny::jump(double charge)
{

	if (charge >= 60)
		charge = 60;

	height = charge / 0.4;

	speedY = - sqrt(charge);



}



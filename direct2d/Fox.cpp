#include "Fox.h"
#include <random>
#include <iostream>



Fox::Fox(Graphics * gfx):
	gfx(gfx)
{
	fox = new SpriteSheet(L"fox.png", gfx, 1.0f, width, height);
	fox2 = new SpriteSheet(L"fox2.png", gfx, 1.0f, width, height);


	y = 248;
	frame = 0;
	foxFrame = 0.3;


	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4000, 8000);

	foxSpeed = (float)(dist(rng) % 20) / 10+ 0.8;
	x = dist(rng) - width;

	foxFrame = 0.075*foxSpeed;
}

Fox::~Fox()
{
	delete fox;
	delete gfx;
	delete &rect;
}

void Fox::changeDir()
{
	if (!directionlatency) {
		changeDirection = !changeDirection;
		directionlatency = 60;
	}
}

void Fox::show()
{
	if (changeDirection) {
		fox2->Draw((int)(frame) % 6, x, y, size);
	}
	else {
		fox->Draw((int)(frame) % 6, x, y, size);
	}
}

void Fox::update(double speed)
{
	if (directionlatency)
		directionlatency--;
	if (changeDirection) {
		x += -speed * 5 + 5 * foxSpeed;
	}
	else {
		x -= speed * 5 + 5 * foxSpeed;
	}
	if (x >= 1800){
		changeDirection = false;
	}

	frame += speed * foxFrame;
	if (x + width < 0) {
		renew();
	}

	rect = { x+10, y+130, x + width+50, y + height+50 };
}

void Fox::renew()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4000, 8000);
	x = dist(rng) - width;	
	foxSpeed = (float)(dist(rng) % 20) / 10 + 0.8;
	foxFrame = 0.075*foxSpeed;
}

D2D1_RECT_F Fox::returnPos()
{
	return rect;
}



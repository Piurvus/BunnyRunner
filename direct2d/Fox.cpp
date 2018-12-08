#include "Fox.h"
#include <random>
#include <iostream>



Fox::Fox(Graphics * gfx):
	gfx(gfx)
{
	fox = new SpriteSheet(L"fox.png", gfx, 1.0f, width, height);

	y = 248;
	frame = 0;
	foxFrame = 0.3;
	foxSpeed = 1.3;

	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4000, 8000);

	x = dist(rng) - width;

	foxFrame = 0.2*foxSpeed;
}

Fox::~Fox()
{
	delete fox;
	delete gfx;
	delete &rect;
}

void Fox::show()
{
	fox->Draw((int)(frame) % 6, x, y, size);
}

void Fox::update(double speed)
{
	x -= speed * 5 * foxSpeed;
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
	
	foxFrame = 0.3*foxSpeed;
}

D2D1_RECT_F Fox::returnPos()
{
	return rect;
}



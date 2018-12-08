#include "obstacle.h"
#include <random>

Obstacle::Obstacle(Graphics * gfx):
	gfx(gfx)
{

	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 600);

	while (width < 20 || height < 20) {
		width = dist(rng) % 100;
		height = dist(rng) % 200;
	}

	x = 800 - width;
}

Obstacle::~Obstacle()
{
	delete &rect;
	delete gfx;
}

void Obstacle::show()
{

	gfx->DrawRectangle(rect);

}

void Obstacle::update(double speed)
{
	x -= speed*5;
	if (x + width <= 0) {
		renew();
	}
	rect = { x, y - height, x + width, y };
}

void Obstacle::renew()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 600);

	float widtha = width;
	float heighta = height;

	while (width < 20 || height < 20 || widtha==width || heighta == height) {
		width = dist(rng) % 100;
		height = dist(rng) % 200;
	}

	x = 800 - width;
}

D2D_RECT_F Obstacle::returnPos()
{
	int a = rect.bottom;
	rect.bottom = rect.top;
	rect.top = a;

	return rect;
}

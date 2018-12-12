#include "obstacle.h"
#include <random>

Obstacle::Obstacle(Graphics * gfx):
	gfx(gfx)
{

	spriteHeights.push_back(547);	//	Stone
	spriteHeights.push_back(403);	//	Trunk
	spriteHeights.push_back(320);	//	Stone2

	renew();
	
}

Obstacle::Obstacle(Graphics * gfx, LPCWSTR name):
	gfx(gfx)
{
	ownSprite = true;
	sprite = new SpriteSheet(name, gfx, 1.0f);
	height = 80;
	width = 80;
}

Obstacle::~Obstacle()
{
	delete sprite;
	delete &rect;
	delete gfx;
}

void Obstacle::show()
{

	if (stone != NULL)
		stone->Draw(x, y - height + 50*size, size);
	if (stone2 != NULL)
		stone2->Draw(x, y - height + 170*size, size);
	if (trunk != NULL)
		trunk->Draw(x, y - height - 50*size, size);
	// gfx->DrawRectangle(rect);

}

void Obstacle::update(double speed)
{
	x -= speed*5;
	if (x + width <= 0) {
		renew();
	}
	if (!ownSprite) {
		if(stone)
			rect = { x+170*size , y - height+50*size, x + width - 150*size, y };
		if(stone2)
			rect = { x + 120 * size , y - height + 220 * size, x + width - 150 * size, y };
		if(trunk)
			rect = { x + 200 * size , y - height + 100 * size, x + width - 150 * size, y };
	}
	else {
		rect = { x, (y - height / 2) - 200 , x + width, (y + height / 2) - 200 };
	}

}

void Obstacle::renew()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1600, 2400);

	float heighta = height;
	
	if (!ownSprite) {
		
		switch (dist(rng) % 3) {
		case 0:
			size = float(dist(rng) %5)/10 + 0.25f;
			stone = new SpriteSheet(L"stone.png", gfx, 1.0f);
			width = 640 * size;
			height = spriteHeights[0] * size;
			stone2 = NULL;
			trunk = NULL;
			break;
		case 1:
			size = float(dist(rng) % 6) / 10 + 0.3f;
			height = spriteHeights[1] * size;
			stone = NULL;
			width = 640 * size;
			stone2 = new SpriteSheet(L"stone2.png", gfx, 1.0f);
			trunk = NULL;
			break;
		case 2:
			size = float(dist(rng) % 3) / 10 + 0.15f;
			width = 840 * size;
			height = spriteHeights[2] * size;
			stone = NULL;
			stone2 = NULL;
			trunk = new SpriteSheet(L"trunk.png", gfx, 1.0f);
			break;
		default:
			break;
			//EEEEEEEEEERROR
		}

	}

	x = dist(rng) - width;
}

D2D_RECT_F Obstacle::returnPos()
{
	/*int a = rect.bottom;
	rect.bottom = rect.top;
	rect.top = a;
	*/
	return rect;
}

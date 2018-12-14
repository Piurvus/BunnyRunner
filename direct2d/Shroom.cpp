#include "Shroom.h"

Shroom::Shroom(Graphics * gfx):
	Obstacle(gfx)
{
	shroom = new SpriteSheet(L"mushroom1.png", gfx, 1.0f);
	shroom2 = new SpriteSheet(L"mushroom2.png", gfx, 1.0f);
	renew();
}

Shroom::~Shroom()
{
	delete shroom;
	delete shroom2;
}

void Shroom::renew()
{
	if (setX(*this) == 0)
		broom = true;
	else
		broom = false;
}

void Shroom::update(double speed)
{
	x -= speed * 5;
	if (x + width <= 0) {
		renew();
	}
	if (broom)
		rect = { x, y - 50, x + 50, y };
	else
		rect = { x, y - 50, x + 50, y };
}

void Shroom::show()
{
	if (broom)
		shroom->Draw(x, y-50, 0.025);
	else
		shroom2->Draw(x, y-50, 0.035);
}

bool Shroom::isBroom()
{
	return broom;
}

#include "Water.h"

Water::Water(Graphics * gfx):
	gfx(gfx)
{
	r = 0;
	g = 0.5f;
	b = 1.0f;

	for (int i = 0; i <= count; i++) {
		waves.push_back(Wave());
	}
}

Water::Water(Graphics * gfx, int count):
	gfx(gfx), count(count)
{
	r = 0;
	g = 0.5f;
	b = 1.0f;

	for (int i = 0; i <= count; i++) {
		waves.push_back(Wave());
	}
}

Water::~Water()
{
	delete gfx;
}

void Water::updateWaves()
{
	for (int i = 0; i < waves.size(); i++) {
		waves[i].x += waves[i].speed -gameSpeed;
		if (waves[i].x >= 1600) {
			waves[i].x = 0;
		}
		else if (waves[i].x <= 0) {
			waves[i].x = 1600;
		}
	}
}

void Water::showWaterArea(const D2D1_RECT_F & rect, double speed)
{
	gameSpeed = speed/10;
	gfx->fillRect(rect, r, g, b);
	
	for (int i = 0; i < waves.size(); i++) {
		gfx->DrawWaterLine(waves[i].x, waves[i].y + waves[i].vec.y, waves[i].x + waves[i].vec.x, waves[i].y + waves[i].vec.y, waves[i].r, waves[i].g, waves[i].b, waves[i].thickness + 2.0f);

		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1800);

		if (dist(rng) % 2 == 1) {
			waves[i].vec.y += (dist(rng) % 11) / 10;
		}
		else {
			waves[i].vec.y -= (dist(rng) % 11) / 10;
		}
	}
	updateWaves();
}

Water::Wave::Wave()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1800);

	thickness = (dist(rng) % 20) / 10;

	r = (dist(rng) % 5) / 10;
	g = (dist(rng) % 8) / 10 + 0.3f;
	b = (dist(rng) % 5) / 10 + 0.5f;

	x = dist(rng);
	y = (dist(rng) % 200) + 400;
	
	if (dist(rng) % 2 == 1) {
		vec.y = dist(rng) % 20;
	}
	else {
		vec.y = -dist(rng) % 20;
	}

	vec.x = 0;
	while (vec.x <= 50) {
		vec.x = dist(rng) % 200;
	}

	speed = 0;

	while (speed == 0) {
		speed = (dist(rng) % 40) / 10;
	}

}

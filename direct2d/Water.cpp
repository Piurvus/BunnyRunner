// Diese Datei ist für den Vordergrund.

#include "Water.h"



Water::Water(Graphics * gfx):
	gfx(gfx)
{
	//	Farben
	r = 0;
	g = 0.5f;
	b = 1.0f;

	//	Anzahl der Stämmen
	for (int i = 0; i <= count; i++) {
		waves.push_back(Wave(gfx));
	}

	//	sortieren der Stämmen nach deren y-Werten
	std::sort(waves.begin(), waves.end());
}

std::vector<Water::Wave> Water::SortWaveBySize()
{
	std::vector< Wave > waves_copy = waves;
	std::sort(waves_copy.begin(), waves_copy.end());
	return waves_copy;
}

Water::Water(Graphics * gfx, int count):
	gfx(gfx), count(count)
{
	//	Farben
	r = 0;
	g = 0.5f;
	b = 1.0f;

	//	Anzahl der Stämmen
	for (int i = 0; i < count; i++) {
		waves.push_back(Wave(gfx));
	}

	//	sortieren der Stämmen nach deren y-Werten
	std::sort(waves.begin(), waves.end());
}

Water::~Water()
{
	delete gfx;
}

void Water::updateWaves()
{
	for (int i = 0; i < waves.size(); i++) {
		//	Bewegung der Stämme
		waves[i].x += (waves[i].speed - (float)gameSpeed);
		
		//	Erneuerung der Stämme falls diese ausserhalb des Fensters sind
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
	//	Geschwindigkeit des Wassers wird neu gesetzt
	gameSpeed = speed/10;

	//	Wasserbereich wird eingefärbt
	gfx->fillRect(rect, r, g, b);
	
	//	jeder Stamm wird dargestellt
	for (int i = 0; i < waves.size(); i++) {
		//gfx->DrawWaterLine(waves[i].x, waves[i].y + waves[i].vec.y, waves[i].x + waves[i].vec.x, waves[i].y + waves[i].vec.y, waves[i].r, waves[i].g, waves[i].b, waves[i].thickness + 2.0f);
		if (waves[i].log1)
			waves[i].log1->Draw(waves[i].x, waves[i].y, waves[i].vec.x);
		else if (waves[i].log2)
			waves[i].log2->Draw(waves[i].x, waves[i].y, waves[i].vec.x);

	}
	updateWaves();
}

Water::Wave::Wave(Graphics* gfx):
	gfx(gfx)
{
	//	random Zahl
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1800);

	random = dist(rng) % 2;

	/*
	thickness = (dist(rng) % 20) / 10;

	r = ((float)(dist(rng) % 5)) / 10;
	g = ((float)(dist(rng) % 8)) / 10 + 0.3f;
	b = ((float)(dist(rng) % 5)) / 10 + 0.5f;
	*/

	//	zufällige Position
	x = dist(rng);
	y = (dist(rng) % 200) + 450;
	
	//	falls nicht im Bereich -> neue Position wählen
	while (y > 535 || y < 420) {
		y = (dist(rng) % 200) + 400;
	}

	/*
	if (dist(rng) % 2 == 1) {
		vec.y = dist(rng) % 20;
	}
	else {
		vec.y = -dist(rng) % 20;
	}
	*/

	//	Grössenskalierungswert
	vec.x = ((float)(dist(rng) % 10)) / 100 + 0.2;

	//	Stämme werden zufällig erstellt
	if (random == 0) {
		log1 = new SpriteSheet(L"log1.PNG", gfx, 1.0f);
		yWithSize = y + vec.x * 237.0f;
	}
	else if (random == 1) {
		log2 = new SpriteSheet(L"log2.PNG", gfx, 1.0f);
		yWithSize = y + vec.x * 367.0f;
	}

	//	Der Stamm bekommt eine Geschwindigkeit
	speed = 0;
	while (speed == 0) {
		speed = ((float)(dist(rng) % 40)) / 10;
	}

}

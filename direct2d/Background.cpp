//	Diese Datei macht einen dynamischen Hintergrund.

#include "Background.h"

void Background::draw()
{
	//	Das Bild wird an den drei verschiedenen x Positionen gezeichnet
	sprites->Draw((int)xScreen1, -10.0f, 0.6, 1.0, true);
	sprites->Draw((int)xScreen2, -10.0f, 0.6, 1.0, true);
	sprites->Draw((int)xScreen3, -10.0f, 0.6, 1.0, true);

	//	Das Grass wird an zwei verschiedenen x Positionen gezeichnet
	grass->Draw(xgScreen1, 320.0f, 1.0);
	grass->Draw(xgScreen2, 320.0f, 1.0);
	//grass->Draw(xgScreen3, 320.0f, 1.0);
}

void Background::update(double speed)
{
	//	Falls das Bild im Fenster nicht mehr sichtbar ist, wird es nach rechts verschoben
	if (xScreen1 + 1224.0 <= 0) {
		xScreen1 = xScreen1 + 3 * 1224.0;
	}
	else if (xScreen2 + 1224.0 <= 0) {
		xScreen2 = xScreen2 + 3 * 1224.0;
	}
	else if (xScreen3 + 1224.0 <= 0) {
		xScreen3 = xScreen3 + 3 * 1224.0;
	}

	//	Bild wird abhängig von der Gamegeschwindigkeit nach links verschoben
	xScreen1 -= speed;
	xScreen2 -= speed;
	xScreen3 -= speed;	

	//	Falls das Bild im Fenster nicht mehr sichtbar ist, wird es nach rechts verschoben
	if (xgScreen1 + 4080.0 <= 0) {
		xgScreen1 = xgScreen1 + 2 * 4080.0;
	}
	else if (xgScreen2 + 4080.0 <= 0) {
		xgScreen2 = xgScreen2 + 2 * 4080.0;
	}/*
	else if (xgScreen3 + 4080.0 <= 0) {
		xgScreen3 = xgScreen3 + 3 * 2040.0;
	}*/

	//	Bild wird abhängig von der Gamegeschwindigkeit nach links verschoben
	xgScreen1 -= 5.0 * speed;
	xgScreen2 -= 5.0 * speed;
	//xgScreen3 -= 5.0 * speed;
}

Background::Background(Graphics * gfx):
	gfx(gfx)
{
	//	Die beiden Bilder werden geladen
	grass = new SpriteSheet(L"grass.png", gfx, 1.0f);
	sprites = new SpriteSheet(L"backgroundnew.png", gfx, 1.0f);
	
	//	Alle Bilder kriegen ihre Position auf der x Achse
	xScreen1 = -3.0;
	xScreen2 = 1221.0;
	xScreen3 = 2.0 * xScreen2 + 3.0;
	xgScreen1 = -0.1;
	xgScreen2 = 4079.9;
	//xgScreen3 = 2.0 * xgScreen2 + 0.1;
}

Background::~Background()
{
	delete sprites;
	delete grass;
}

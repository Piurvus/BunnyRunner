// Diese Datei macht die Powerups Pilze.

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
	//	Aufräumen
	delete shroom;
	delete shroom2;
}

void Shroom::renew()
{
	//	setX() ist ein friend der Objekt Superklasse, welche erlaubt die protected Positionswerte zu ändern; bestimmt auch welcher Pilz angezeigt wird
	if (setX(*this) == 0)
		broom = true;
	else
		broom = false;
}

void Shroom::update(double speed)
{
	//	Bewegt sich passend zur Spielgeschwindigkeit gegen vorne
	x -= speed * 5;

	//	Falls ausserhalb des Fensters
	if (x + width <= 0) {
		renew();
	}

	//	Hitbox je nach Pilz unterschiedlich
	if (broom)
		rect = { x, y - 50, x + 50, y };
	else
		rect = { x, y - 50, x + 50, y };
}

void Shroom::show()
{
	//	Pilze werden gezeichnet
	if (broom)
		shroom->Draw(x, y-50, 0.025);
	else
		shroom2->Draw(x, y-50, 0.035);
}

bool Shroom::isBroom()
{
	return broom;
}

//	Header Datei für die Hindernisse
#pragma once

#include "Graphics.h"
#include <random> //	Um Zufallszahlen zu generieren
#include <iostream>
#include "SpriteSheet.h"
#include <vector> //	Um Vektoren zu erstellen


class Obstacle {

private:

	//	Die verschiedenen Objekte (Bilder)
	SpriteSheet* stone;
	SpriteSheet* stone2;
	SpriteSheet* trunk;
	
	//	Höhen der Objekte
	std::vector<int> spriteHeights;

	float size;				
	bool ownSprite = false;	//	Wichtig für Karotte

protected:

	Graphics* gfx;

	//	Position
	float x;
	float y = 435;

public:

	//	Grösse des Objekts
	float width = 0;
	float height = 0;

	//	Hitbox
	D2D_RECT_F rect;

	SpriteSheet* sprite;

	Obstacle(Graphics* gfx);				//	Konstruktor für den Rest
	Obstacle(Graphics* gfx, LPCWSTR name);	//	Konstruktor der Karotte
	~Obstacle();

	//	Anzeigen des Objekts
	void show();			
	//	Aktualisieren des Objekts
	void update(double speed);

	//	Erneuerung falls das Objekt ausser Sicht ist
	void renew();
	//	Gibt Hitbox zurück
	D2D_RECT_F returnPos();

	//	Setzt ein neues x und gibt 1 oder 0 zurück; Wird in der Klasse Shroom verwendet
	friend int setX(Obstacle &obj);	//	wichtig für die Klasse Shroom
};
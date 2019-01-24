//	Header Datei f�r die Hindernisse
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
	
	//	H�hen der Objekte
	std::vector<int> spriteHeights;

	float size;				
	bool ownSprite = false;	//	Wichtig f�r Karotte

protected:

	Graphics* gfx;

	//	Position
	float x;
	float y = 435;

public:

	//	Gr�sse des Objekts
	float width = 0;
	float height = 0;

	//	Hitbox
	D2D_RECT_F rect;

	SpriteSheet* sprite;

	Obstacle(Graphics* gfx);				//	Konstruktor f�r den Rest
	Obstacle(Graphics* gfx, LPCWSTR name);	//	Konstruktor der Karotte
	~Obstacle();

	//	Anzeigen des Objekts
	void show();			
	//	Aktualisieren des Objekts
	void update(double speed);

	//	Erneuerung falls das Objekt ausser Sicht ist
	void renew();
	//	Gibt Hitbox zur�ck
	D2D_RECT_F returnPos();

	//	Setzt ein neues x und gibt 1 oder 0 zur�ck; Wird in der Klasse Shroom verwendet
	friend int setX(Obstacle &obj);	//	wichtig f�r die Klasse Shroom
};
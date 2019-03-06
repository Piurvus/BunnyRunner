//	Header Datei f�r die Hindernisse
/*
	Diese Klasse ist f�r die ganzen Objekte, welche im Wege stehen.
	Mit SpriteSheet.h ist es m�glich verschiedene Bilder darzustellen.
	Das Objekt, sowie seine Dimensionen werden zuf�llig ausgew�hlt. 
	Jedes Objekt besitzt ihre eigene Hitbox und Koordinaten. Sobald ein Objekt aus dem Fenster ger�t wird ein
	neues Objekt zuf�llig gew�hlt und die Restlichen werden auf null gesetzt. So weiss man immer welches Bild 
	angezeigt werden muss.
*/



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
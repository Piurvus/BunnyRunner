//	Diese Klasse ist verantwortlich für die Bilder und Animationen des Spiels
/*
	Mithilfe der Graphics Klasse und einem Dateinamen kann diese Klasse Bilder einlesen und darstellen.
	Das Bild wird in einer Bitmap gespeichert. Nun kann es an verschiedenen Orten und in verschiedenen Grössen
	dargestellt werden. Falls es ein Animationsbild ist, können auch verschiedene Teile des Bildes (einzelne Animationsbilder) dargestellt werden.
	Damit dies jedoch funktioniert müssen bei der Initialisierung des SpriteSheet Objektes auch noch die Dimensionen der einzelnen Sprites
	angegeben werden, damit diese nachher mithilfe von frame(index) und einer Modulorechnung dargestellt werden können.
*/

#pragma once

#include <wincodec.h>	//	wincodec ist die Windows Bilder Komponente, wir brauchen es um die Spritesheets anzuzeigen
#include "Graphics.h"
#include <iostream>

class SpriteSheet
{

private:
	Graphics* gfx;
	ID2D1Bitmap* bmp;				//	Ein Bild Dateiformat

	float a;						//	Alpha
	int spriteWidth, spriteHeight;	//	Grösse der Sprites
	int spritesAccross;				//	Wieviele Sprites sich in einer Reihe befinden

public:
	
	SpriteSheet(LPCWSTR filename, Graphics* gfx, float a);										//	Normales Bild mit Deckkraft (a)
	SpriteSheet(LPCWSTR filename, Graphics* gfx, float a, int spriteWidth, int spriteHeight);	//	Ladet ein Bild mit vielen Animationsbilder, welche danach einzeln aufgerufen werden können

	~SpriteSheet();

	void Draw(float a);																	//	Zeichnet das Bild mit variablen Deckkraft
	void Draw(float x, float y, double size);											//	Zeichnet das Bild an einer variablen Position mit einer variablen Grösse
	void Draw(float x, float y, double size, double a, bool cuzitwontworkwithoutkappa); //	Das Selbe wie Draw oben, einfach mit zusätzlicher variablen Deckkraft
	void Draw(int index, int x, int y, double size);									//	Zeichnet das gewählte (index) Animationsbild an variabler Position und Grösse
};
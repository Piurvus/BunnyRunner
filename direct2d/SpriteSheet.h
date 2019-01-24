//	Diese Klasse ist verantwortlich f�r die Bilder und Animationen des Spiels
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
	int spriteWidth, spriteHeight;	//	Gr�sse der Sprites
	int spritesAccross;				//	Wieviele Sprites sich in einer Reihe befinden

public:
	
	SpriteSheet(LPCWSTR filename, Graphics* gfx, float a);										//	Normales Bild mit Deckkraft (a)
	SpriteSheet(LPCWSTR filename, Graphics* gfx, float a, int spriteWidth, int spriteHeight);	//	Ladet ein Bild mit vielen Animationsbilder, welche danach einzeln aufgerufen werden k�nnen

	~SpriteSheet();

	void Draw(float a);																	//	Zeichnet das Bild mit variablen Deckkraft
	void Draw(float x, float y, double size);											//	Zeichnet das Bild an einer variablen Position mit einer variablen Gr�sse
	void Draw(float x, float y, double size, double a, bool cuzitwontworkwithoutkappa); //	Das Selbe wie Draw oben, einfach mit zus�tzlicher variablen Deckkraft
	void Draw(int index, int x, int y, double size);									//	Zeichnet das gew�hlte (index) Animationsbild an variabler Position und Gr�sse
};
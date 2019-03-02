//	Header Datei f�r das Wasser im Vordergrund

/*
	In der Wasser Klasse befindet sich noch die Klasse der St�mme.
	Jeder Stamm ist ein Objekt der Wasser Klasse und die Menge der St�mme kann im Konstruktor von Water gew�hlt werden.
	Jeder einzelne Stamm kriegt eigene zuf�llige Werte f�r Gr�sse, Geschwindigkeit sowie Position.
	Welcher Stamm es ist wird auch zuf�llig gew�hlt.
	Mit updateWaves() wird jeder einzelne Stamm aktualisiert und falls er sich ausserhalb des Fensters befindet wird er wieder zum Anfang des 
	Fensters geschoben. Mit showWaterArea() wird das ganze Wasser mit all den St�mmen dargestellt. Die St�mme m�ssen hierf�r sortiert werden,
	damit sie sich, falls sie sich �berlagern, richtig �berlagern.
*/


#pragma once
#include "Graphics.h"
#include <vector>
#include <random>
#include <iostream>
#include "SpriteSheet.h"
#include <algorithm> //	Sortieralgorithmus

class Water {

	Graphics* gfx;

	//	Wave ist eine Schablone f�r die St�mme im Wasser
	class Wave {

		Graphics* gfx;
		int random;

	public:
		//	Die beiden verschiedenen Stamm Arten
		SpriteSheet* log1 = NULL;
		SpriteSheet* log2 = NULL;

		float thickness;	//	thickness wird nicht gebraucht
		float r, g, b;		//	Farben werden nicht gebraucht

		float x, y;			//	Position des Stammes
		float yWithSize;	//	Gr�sse
		float speed;		//	Jeweilige Geschwindigkeit
		
		D2D_VECTOR_2F vec = {};

		Wave(Graphics * gfx);

		//	Dient zur Ordnung der St�mme nach deren y-Werten (damit die St�mme in der richtigen Reihenfolge gezeichnet werden und sich nicht falsch �bermalen)
		bool operator< (const Wave &other) const {
			return yWithSize < other.yWithSize;
		}


	};

	float r, g, b;			//	Farben des Wassers
	int count = 30;			//	Anzahl St�mme (default Wert)

	//	Sortierter und unsortierter Vektor der St�mmen
	std::vector<Wave> waves;
	std::vector<Wave> SortWaveBySize();

	double gameSpeed;		//	Geschwindigkeit des Wassers

public:

	//	Konstruktor mit und ohne Anzahl St�mme im Wasser
	Water(Graphics* gfx);				
	Water(Graphics* gfx, int count);
	~Water();

	//	Aktualisiert die St�mme
	void updateWaves();
	//	Anzeigen des Wassers und der St�mme
	void showWaterArea(const D2D1_RECT_F &rect, double speed);

};
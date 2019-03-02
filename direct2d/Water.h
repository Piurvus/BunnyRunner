//	Header Datei für das Wasser im Vordergrund

/*
	In der Wasser Klasse befindet sich noch die Klasse der Stämme.
	Jeder Stamm ist ein Objekt der Wasser Klasse und die Menge der Stämme kann im Konstruktor von Water gewählt werden.
	Jeder einzelne Stamm kriegt eigene zufällige Werte für Grösse, Geschwindigkeit sowie Position.
	Welcher Stamm es ist wird auch zufällig gewählt.
	Mit updateWaves() wird jeder einzelne Stamm aktualisiert und falls er sich ausserhalb des Fensters befindet wird er wieder zum Anfang des 
	Fensters geschoben. Mit showWaterArea() wird das ganze Wasser mit all den Stämmen dargestellt. Die Stämme müssen hierfür sortiert werden,
	damit sie sich, falls sie sich überlagern, richtig überlagern.
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

	//	Wave ist eine Schablone für die Stämme im Wasser
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
		float yWithSize;	//	Grösse
		float speed;		//	Jeweilige Geschwindigkeit
		
		D2D_VECTOR_2F vec = {};

		Wave(Graphics * gfx);

		//	Dient zur Ordnung der Stämme nach deren y-Werten (damit die Stämme in der richtigen Reihenfolge gezeichnet werden und sich nicht falsch übermalen)
		bool operator< (const Wave &other) const {
			return yWithSize < other.yWithSize;
		}


	};

	float r, g, b;			//	Farben des Wassers
	int count = 30;			//	Anzahl Stämme (default Wert)

	//	Sortierter und unsortierter Vektor der Stämmen
	std::vector<Wave> waves;
	std::vector<Wave> SortWaveBySize();

	double gameSpeed;		//	Geschwindigkeit des Wassers

public:

	//	Konstruktor mit und ohne Anzahl Stämme im Wasser
	Water(Graphics* gfx);				
	Water(Graphics* gfx, int count);
	~Water();

	//	Aktualisiert die Stämme
	void updateWaves();
	//	Anzeigen des Wassers und der Stämme
	void showWaterArea(const D2D1_RECT_F &rect, double speed);

};
//	Header Datei für das Wasser im Vordergrund
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
		float r, g, b;	//	Farben werden nicht gebraucht

		float x, y;	//	Position des Stammes
		float yWithSize;	//	Grösse
		float speed;	//	jeweilige Geschwindigkeit
		
		D2D_VECTOR_2F vec = {};

		Wave(Graphics * gfx);

		//	dient zur Ordnung der Stämme nach deren y-Werten
		bool operator< (const Wave &other) const {
			return yWithSize < other.yWithSize;
		}


	};

	float r, g, b;	//	Farben des Wassers
	int count = 30;	//	Anzahl Stämme

	//	sortierter und unsortierter Vektor der Stämmen
	std::vector<Wave> waves;
	std::vector<Wave> SortWaveBySize();

	double gameSpeed;	//	Geschwindigkeit des Wassers

public:

	Water(Graphics* gfx);
	Water(Graphics* gfx, int count);
	~Water();

	void updateWaves();
	void showWaterArea(const D2D1_RECT_F &rect, double speed);

};
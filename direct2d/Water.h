#pragma once
#include "Graphics.h"
#include <vector>
#include <random>
#include <iostream>
#include "SpriteSheet.h"
#include <algorithm>

class Water {

	Graphics* gfx;

	class Wave {

		Graphics* gfx;

	public:

		SpriteSheet* log1 = NULL;
		SpriteSheet* log2 = NULL;
		float thickness;
		float r, g, b;
		float x, y;
		float yWithSize;
		float speed;
		D2D_VECTOR_2F vec = {};
		Wave(Graphics * gfx);

		bool operator< (const Wave &other) const {
			return yWithSize < other.yWithSize;
		}


	};

	float r, g, b;
	int count = 30;


	std::vector<Wave> waves;
	std::vector<Wave> SortWaveBySize();

	double gameSpeed;

public:

	Water(Graphics* gfx);
	Water(Graphics* gfx, int count);
	~Water();

	void updateWaves();
	void showWaterArea(const D2D1_RECT_F &rect, double speed);

};
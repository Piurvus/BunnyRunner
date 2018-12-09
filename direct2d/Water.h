#pragma once
#include "Graphics.h"
#include <vector>
#include <random>
#include <iostream>

class Water {

	class Wave {

	public:
		float thickness;
		float r, g, b;
		int x, y;
		float speed;
		D2D_VECTOR_2F vec = {};
		Wave();
	};

	Graphics* gfx;
	float r, g, b;
	int count = 30;

	std::vector<Wave> waves;
	double gameSpeed;

public:

	Water(Graphics* gfx);
	Water(Graphics* gfx, int count);
	~Water();

	void updateWaves();
	void showWaterArea(const D2D1_RECT_F &rect, double speed);

};
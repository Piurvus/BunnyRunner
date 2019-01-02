#pragma once
#include "SpriteSheet.h"
#include "Graphics.h"

class Background {

	Graphics* gfx;

	//	Eigentliche Hintergrund
	SpriteSheet* sprites;
	//	Grass
	SpriteSheet* grass;

	//	Grass und Hintergrund besitzen jeweils drei verschiedene x Werte
	double xScreen1, xScreen2, xScreen3;
	double xgScreen1, xgScreen2, xgScreen3;

public:

	Background(Graphics* gfx);
	~Background();

	void draw();
	void update(double speed);

};
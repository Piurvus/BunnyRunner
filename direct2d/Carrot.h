//	Header Datei für die Karotte
#pragma once
#include "obstacle.h"
#include "Graphics.h"

class Carrot : public Obstacle {

	float size = 0.15;	//	Grösse von der Karotte

public:
	using Obstacle::Obstacle;	//	Konstruktor von Obstacle wird verwendet, welcher einen anderen y Wert gibt

	D2D_RECT_F returnPos();
	void show();

};
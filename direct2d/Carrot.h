//	Header Datei für die Karotte
/*
	Die Karotten Klasse erbt von der Obstacle Klasse. Der einzige Unterschied zu einem üblichen Objekt ist der, dass die Karotte einen
	fixen y Wert und eine fixe Grösse hat.
*/
#pragma once
#include "obstacle.h"
#include "Graphics.h"

class Carrot : public Obstacle {

	float size = 0.15;			//	Grösse von der Karotte

public:
	using Obstacle::Obstacle;	//	Konstruktor von Obstacle wird verwendet, welcher einen anderen y Wert gibt

	D2D_RECT_F returnPos();		//	Hitbox der Karotte
	void show();				//	Darstellen der Karotte

};
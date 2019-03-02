//	Header Datei f�r die Karotte
/*
	Die Karotten Klasse erbt von der Obstacle Klasse. Der einzige Unterschied zu einem �blichen Objekt ist der, dass die Karotte einen
	fixen y Wert und eine fixe Gr�sse hat.
*/
#pragma once
#include "obstacle.h"
#include "Graphics.h"

class Carrot : public Obstacle {

	float size = 0.15;			//	Gr�sse von der Karotte

public:
	using Obstacle::Obstacle;	//	Konstruktor von Obstacle wird verwendet, welcher einen anderen y Wert gibt

	D2D_RECT_F returnPos();		//	Hitbox der Karotte
	void show();				//	Darstellen der Karotte

};
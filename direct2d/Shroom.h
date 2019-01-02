#pragma once
#include "obstacle.h"
#include <random>
#include "SpriteSheet.h"

class Shroom : public Obstacle {

	//	Die beiden Pilzarten
	SpriteSheet* shroom;
	SpriteSheet* shroom2;

	//	zufällige Entscheidung welcher Pilz und wo sich dieser befindet
	void renew();

	//	je nach dem ob true oder false ist es der eine oder andere Pilz
	bool broom = false;

public:
	
	Shroom(Graphics* gfx);
	~Shroom();

	void update(double speed);
	void show();

	//	gibt zurück welcher Pilz es ist; wichtig für Kollision
	bool isBroom();
};
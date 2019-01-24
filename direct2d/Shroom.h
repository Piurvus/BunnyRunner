//	Header Datei f�r die Pilze
#pragma once
#include "obstacle.h"
#include <random>
#include "SpriteSheet.h"

class Shroom : public Obstacle {

	//	Die beiden Pilzarten (Bilder)
	SpriteSheet* shroom;
	SpriteSheet* shroom2;

	//	Zuf�llige Entscheidung welcher Pilz und wo sich dieser befindet
	void renew();

	//	Je nach dem ob true oder false, ist es der eine oder andere Pilz
	bool broom = false;

public:
	
	//	Gibt gfx an die Superklasse �ber, ladet die beiden Bilder der Pilze und ruft renew() auf
	Shroom(Graphics* gfx);
	~Shroom();

	//	Aktualisieren der Position
	void update(double speed);
	//	Anzeigen des Pilzes
	void show();

	//	Gibt zur�ck welcher Pilz es ist (violett oder blau); wichtig f�r Kollision 
	bool isBroom();
};
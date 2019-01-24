//	Header Datei für die Pilze
#pragma once
#include "obstacle.h"
#include <random>
#include "SpriteSheet.h"

class Shroom : public Obstacle {

	//	Die beiden Pilzarten (Bilder)
	SpriteSheet* shroom;
	SpriteSheet* shroom2;

	//	Zufällige Entscheidung welcher Pilz und wo sich dieser befindet
	void renew();

	//	Je nach dem ob true oder false, ist es der eine oder andere Pilz
	bool broom = false;

public:
	
	//	Gibt gfx an die Superklasse über, ladet die beiden Bilder der Pilze und ruft renew() auf
	Shroom(Graphics* gfx);
	~Shroom();

	//	Aktualisieren der Position
	void update(double speed);
	//	Anzeigen des Pilzes
	void show();

	//	Gibt zurück welcher Pilz es ist (violett oder blau); wichtig für Kollision 
	bool isBroom();
};
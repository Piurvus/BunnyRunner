//	Header Datei f�r die Pilze
/*
	Wie auch die Klasse der Karotten erbt auch diese Klasse der Pilze von der Klasse Obstacle.
	Um die x und y Werte, welche protected sind, zu �ndern wird die setX() friend Methode in Obstacle verwendet.
	Ansonsten funktioniert auch diese Klasse fast genau gleich wie die Obstacle Klasse.
	Es wird zuf�llig zwischen zwei Pilzen gew�hlt und je nach dem welcher Pilz gew�hlt wurde, wird sein Bild dargestellt
	und das SpriteSheet vom anderen Pilz ist auf null. Je nach dem welcher Pilz mit dem Hasen kollidiert passieren unterschiedliche 
	Dinge. Um herauszufinden welcher Pilz der Momentane ist, wird isBroom() verwendet.
*/


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
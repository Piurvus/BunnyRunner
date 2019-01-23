//	Header Datei für den Gameflow
#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"
#include <ctime> //	Timer
#include "Bunny.h"
#include "obstacle.h"
#include "Carrot.h"
#include "Fox.h"
#include "Water.h"
#include <fstream> //	In eine Datei schreiben und lesen.
#include "Background.h"
#include "Shroom.h"

class Game {

	//	Alle Objekte im Spiel
	Fox* fox;
	Water* water;
	Carrot* carrot;
	Bunny* bunny;
	Graphics* gfx;
	Obstacle* obj; 
	Background* background;
	Shroom* shroom;
	std::ofstream outfile;
	std::ifstream infile;

public:
	
	Game(Graphics* gfx);
	~Game();

	//	Die Funktion, welche in main.cpp ausgeführt wird
	void Run();

	//	Die Funktionen, welche in Run() ausgeführt werden
	//	Aktualisierung der Logik
	void UpdateModel();
	//	Aktualisierung der Graphik
	void ComposeFrame();

private:
	//	Das Wasserfeld im unterem Fensterbereich
	D2D1_RECT_F bottom = D2D1::Rect(0, 471, 1600, 600);
	D2D1_COLOR_F color = D2D1::ColorF(50, 50, 255);

	float distanceCount = 0.0f;			//	Gerannte Distanz
	int highscoreInt = 0;
	int carrots = 0;					//	Anzahl Karotten
	double speed = 1.0;					//	Geschwindigkeit des Spiels/Hasens
	double refreshRate = 1.0 / 80.0;	//	GameFlow
	double frameRate = 1.0 / 165.0;		//	FPS
	double charge = 0;					//	Momentane Sprungstärke des Hasens

	//	Uhren um die Geschwindigkeit des Spiels im Blick zu halten
	std::clock_t clockR;
	std::clock_t clockFPS;
	//	Verhindert dass man zu schnell hintereinander Springen kann
	std::clock_t carrotsTimer = 0;
	
	//	Der Text, welcher im Spiel angezeigt wird
	std::string highscoreString;
	wchar_t distanceCountText[256];
	wchar_t carrotCountText[256];
	wchar_t highscoreWchar[100];
	
	bool checkCollision(D2D1_RECT_F rect1, D2D1_RECT_F rect2); 
	void updateHighscore();
};
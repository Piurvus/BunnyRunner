// Diese Datei ist verantwortlich für den GameFlow.

#include "Game.h"
#include "SpriteSheet.h"
//	Für die Timer
#include <ctime>
#include "Bunny.h"
#include "Carrot.h"
#include "Fox.h"
//	Für strings
#include <string>
//  Standartlibrary
#include <stdio.h>
//	Ausgaben
#include <fstream>
#include <iostream>
#include "Shroom.h"

Game::Game(Graphics * gfx) :
	gfx(gfx)
{

	//-------Sprites-----------

	//	gfx muss jeweils als Referenz mitgegeben werden, damit die Objekte dargestellt werden können	
	//	Erzeugt das Wasserfeld mit 5 Stämmen (waves Objekte in der Water Klasse)
	water = new Water(gfx, 5);	
	fox = new Fox(gfx);
	bird = new Bird(gfx);
	//	L"carrot.png" ist das Bild von der Karotte, welches benutzt wird
	carrot = new Carrot(gfx, L"carrot.png");
	bunny = new Bunny(gfx);
	obj = new Obstacle(gfx);
	background = new Background(gfx);
	shroom = new Shroom(gfx);
	//-------------------------



	//---------Read File----------------

	//	Zuerst werden alte Punktzahlen eingelesen und die beste wird gewählt
	infile.open("Highscore.txt");
	int compare = 0;
	while (std::getline(infile, highscoreString)) {
		compare = std::stoi(highscoreString, nullptr, 10);
		if (compare >= highscoreInt) {
			highscoreInt = compare;
		}
	}
	//	Danach wird eine "neue" Output Datei erstellt, welche die besten Punktzahlen speichert
	outfile.open("Highscore.txt");
	outfile << highscoreInt << std::endl;
	//	Der Highscore darf kein int sein, damit er später dargestellt werden kann
	swprintf_s(highscoreWchar, L"%d", highscoreInt);
	//----------------------------------

}

Game::~Game()
{
	//	Aufräumen
	delete shroom;
	delete water;
	delete carrot;
	delete fox;
	delete background;
	delete bunny;
	delete obj;
	delete bird;
	outfile.close();
}

void Game::Run()
{
	gfx->BeginDraw();

	//	Mit den beiden if's wird eine konstante Framerate erzielt
	if ((std::clock() - clockR) / (double)CLOCKS_PER_SEC >= refreshRate)
		UpdateModel();
	if ((std::clock() - clockFPS) / (double)CLOCKS_PER_SEC >= frameRate)
		ComposeFrame();
	
	gfx->EndDraw();
	
	/*
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	*/
}

void Game::UpdateModel()
{
	if (bunny->isDead()) {
		speed = 1.0;
	}

	//	Falls der Hase noch lebt
	if (!bunny->isDead())
	{
		//	Erneuerung der Karotten, falls diese zu nah an einem Objekt sind
		if (abs(obj->returnPos().left - carrot->returnPos().left) < 100) {
			carrot->renew();
		}

		//	Falls der Hase nicht auf der Wolke ist, um schneller hinunter zu gelangen
		if (GetAsyncKeyState(VK_DOWN) && !bunny->isClouded()) {
			bunny->crouch();
		}

		//	Sprung aufladen, falls der Hase auf dem Boden ist
		if (GetAsyncKeyState(VK_UP) && bunny->onGround() && !bunny->isClouded())
			charge += 1.5;

		//	Mehrfach Sprung, falls der Hase nicht auf dem Boden ist, er Karotten hat und er genug lange seit dem letzten Sprung in der Luft gewartet hat(carrotsTimer)
		if (GetAsyncKeyState(VK_UP) && !bunny->onGround() && carrots && (std::clock() - carrotsTimer) / (double)CLOCKS_PER_SEC >= 0.5f && !bunny->isClouded()) {
			carrotsTimer = clockR;	//	Der Timer wird erneuert
			carrots--;				//	Karotte wird benutzt
			charge = 0;				//	Die momentane Sprungstärke wird auf 0 gesetzt
			bunny->jump(30);		//	Der Hase macht einen Sprung mit bereits festgelegter Höhe
		}

		//	Normaler Sprung, falls der Sprung bereits aufgeladen wurde(charge) und sich der Hase auf dem Boden befindet
		if (!GetAsyncKeyState(VK_UP) && charge != 0 && bunny->onGround() && !bunny->isClouded()) {
			bunny->jump(charge);	//	Der Hase springt mit einer Höhe, welche von dem charge Wert abhängt
			charge = 0;				//	Zurücksetzen der Sprungstärke
		}

		//	Kollision zwischen Hase und Objekt
		if (checkCollision(bunny->returnPos(), obj->returnPos())) {
			bunny->die();			//	Der Hase stirbt
			distanceCount -= speed;	//	Distanz wird um einen Tick angepasst, damit die richtige Punktzahl als Highscore angezeigt wird
			updateHighscore();		//	Highscore wird aktualisiert
		}

		//	Kollision zwischen Objekt und Pilz
		if (checkCollision(obj->returnPos(), shroom->returnPos())) {
			obj->renew();			//	Das Objekt wird an einem anderen Ort hingestellt, da es sich auf einem Pilz befand
		}

		//	Kollision zwischen Hase und Fuchs
		if (checkCollision(bunny->returnPos(), fox->returnPos())) {
			bunny->die();			//	Der Hase stirbt
			distanceCount -= speed;	//	Distanz wird um einen Tick angepasst, damit die richtige Punktzahl als Highscore angezeigt wird
			updateHighscore();		//	Highscore wird aktualisiert
		}

		//	Kollision zwischen Hase und Vogel
		if (checkCollision(bunny->returnPos(), bird->returnPos())) {
			bunny->die();			//	Der Hase stirbt
			distanceCount -= speed;	//	Distanz wird um einen Tick angepasst, damit die richtige Punktzahl als Highscore angezeigt wird
			updateHighscore();		//	Highscore wird aktualisiert
		}
		
		//	Kollision zwischen Hase und Karotte
		if (checkCollision(bunny->returnPos(), carrot->returnPos())) {
			if (speed <= 3.0)		//	Falls der Hase nochnicht seine maximale Geschwindigkeit erreicht hat
				speed += 0.1;		//	Die Geschwindigkeit wird erhöht
			carrots++;				//	Der Karottenzähler wird um eins erhöht
			carrot->renew();		//	Es wird eine "neue" Karotte platziert
		}

		//	Kollision zwischen Hase und Pilz
		if (checkCollision(bunny->returnPos(), shroom->returnPos())) {
			if (shroom->isBroom()) {	//	Falls es ein violetter Pilz war
				bunny->jump(60, false);	//	Der Hase springt einen fixen Wert ohne eine Jumpwolke zu hinterlassen
			}
			else {
				bunny->jump(60, false);	//	Falls es ein blauer Pilz war
				bunny->getClouded();	//	Der Hase springt einen fixen Wert ohne eine Jumpwolke zu hinterlassen
			}
		}

		//	Kollision zwischen Fuchs und Objekt
		if (checkCollision(fox->returnPos(), obj->returnPos())) {
			fox->changeDir();		//	Der Fuchs ändert seine Richtung
		}

		//	(Aktualisierung) Umwandlung der Anzeigevariablen (int kann nicht als Text dargestellt werden)
		swprintf_s(distanceCountText, L"%d", (int)distanceCount);
		swprintf_s(carrotCountText, L"%d", carrots);

		distanceCount += speed;		//	Aktualisieren der gerannter Distanz

		//	Aktualisierung der Objekte (abhängig von der Geschwindigkeit des Hasens, damit alles sich gleich schnell bewegt)
		carrot->update(speed);
		fox->update(speed);
		bird->update(speed);
		obj->update(speed);
		bunny->updateBunny(speed);
		background->update(speed);
		shroom->update(speed);

		//	Aktualisierung der Uhr
		clockR = std::clock();
	}
	else if (bunny->isDead()) {		//	Falls der Hase tot ist
		bunny->updateBunny(speed);	//	Der Hase fällt noch zu Boden
		fox->update(speed);	//	Fuchs rennt weiter
		bird->update(speed);	//	Vogel fliegt weiter

		//	Kollision zwischen Fuchs und Objekt
		if (checkCollision(fox->returnPos(), obj->returnPos())) {
			fox->changeDir();		//	Der Fuchs ändert seine Richtung
		}
	}

	//	Neustart
	if (GetAsyncKeyState(VK_F9) & 1) {
		//	Alles wird auf die Defaultwerte zurückgesetzt
		Sleep(10);
		water = new Water(gfx, 5);
		bunny = new Bunny(gfx);
		obj = new Obstacle(gfx);
		carrot = new Carrot(gfx, L"carrot.png");
		fox = new Fox(gfx);
		bird = new Bird(gfx);
		speed = 1.0f;
		carrots = 0;
		distanceCount = 0.0f;
	}

}

void Game::ComposeFrame()
{
	//	Fenster auf weiss
	gfx->ClearScreen(255, 255, 255);

	//	Zeichnen der verschiedenen Elemente
	background->draw();
	obj->show();
	shroom->show();
	water->showWaterArea(bottom, speed);
	fox->show();
	bird->show();
	obj->show();
	carrot->show();

	/*
	D2D1_RECT_F a = bunny->returnPos();
	D2D1_RECT_F b = shroom->returnPos();
	gfx->DrawRectangle(a);
	gfx->DrawRectangle(b);
	*/

	/*
	if (bunny->isCrouched())
		gfx->DrawTEXT(&D2D1::Rect(50, 500, 500, 500), 50, L"Crouched");
	*/

	//	Anzeigen von dem Hasen, abhängig von Karotten
	bunny->showBunny(carrots > 0);

	//  Anzeige von den Texten
	gfx->DrawTEXT(&D2D1::Rect(50, 10, 500, 500), 50, L"Score:");
	gfx->DrawTEXT(&D2D1::Rect(250, 10, 500, 500), 50, distanceCountText);
	//mbstowcs(outpuet, output, strlen(output + 1));
	//if((std::stoi(highscore)) >=0 )
	gfx->DrawTEXT(&D2D1::Rect(1100, 10, 1600, 500), 50, L"Highscore:");
	gfx->DrawTEXT(&D2D1::Rect(1300, 10, 1600, 500), 50, highscoreWchar);
	gfx->DrawTEXT(&D2D1::Rect(50, 60, 500, 500), 50, L"Carrots:");
	gfx->DrawTEXT(&D2D1::Rect(250, 60, 500, 500), 50, carrotCountText);

	//	Aktualisierung der Uhr
	clockFPS = std::clock();
	//}

}

void Game::updateHighscore()
{
	//	Aufrunden des Punktestandes
	distanceCount += 0.5;

	//	Falls der aktuelle Highscore höher als der damalige ist, wird dieser aktualisiert
	if ((int)distanceCount >= highscoreInt) {
		outfile << (int)distanceCount << std::endl;
		highscoreInt = (int)distanceCount;
	}
	swprintf_s(highscoreWchar, L"%d", highscoreInt);
	outfile.flush();
}

bool Game::checkCollision(D2D1_RECT_F a, D2D1_RECT_F b)
{
	return (b.top <= a.bottom && b.bottom >= a.top && b.left <= a.right && b.right >= a.left);
}

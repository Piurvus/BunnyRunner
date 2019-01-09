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
// Standartlibrary
#include <stdio.h>
//	Ausgaben
#include <fstream>
#include <iostream>
#include "Shroom.h"

Game::Game(Graphics * gfx) :
	gfx(gfx)
{

	//-------Sprites-----------
	water = new Water(gfx, 5);
	fox = new Fox(gfx);
	carrot = new Carrot(gfx, L"carrot.png");
	bunny = new Bunny(gfx);
	obj = new Obstacle(gfx);
	background = new Background(gfx);
	shroom = new Shroom(gfx);
	//-------------------------


	//---------Read File----------------
	infile.open("Highscore.txt");
	int compare = 0;
	while (std::getline(infile, highscoreString)) {
		compare = std::stoi(highscoreString, nullptr, 10);
		if (compare >= highscoreInt) {
			highscoreInt = compare;
		}
	}
	outfile.open("Highscore.txt");
	outfile << highscoreInt << std::endl;

	swprintf_s(highscoreWchar, L"%d", highscoreInt);
	//----------------------------------

}

Game::~Game()
{
	delete shroom;
	delete water;
	delete carrot;
	delete fox;
	delete background;
	delete bunny;
	delete obj;
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

	if (!bunny->isDead())
	{
		//	Erneuerung der Karotten
		if (abs(obj->returnPos().left - carrot->returnPos().left) < 100) {
			carrot->renew();
		}

		if (GetAsyncKeyState(VK_DOWN) && !bunny->isClouded()) {
			bunny->crouch();
		}

		//	Sprung aufladen
		if (GetAsyncKeyState(VK_UP) && bunny->onGround() && !bunny->isClouded())
			charge += 1.5;

		//	Mehrfach Sprung
		if (GetAsyncKeyState(VK_UP) && !bunny->onGround() && carrots && (std::clock() - carrotsTimer) / (double)CLOCKS_PER_SEC >= 0.5f && !bunny->isClouded()) {
			carrotsTimer = clockR;
			carrots--;
			charge = 0;
			bunny->jump(30);
		}

		//	normale Sprung
		if (!GetAsyncKeyState(VK_UP) && charge != 0 && bunny->onGround() && !bunny->isClouded()) {
			bunny->jump(charge);
			charge = 0;
		}

		//	Kollision mit Objekt
		if (checkCollision(bunny->returnPos(), obj->returnPos())) {
			bunny->die();
			distanceCount -= speed;
			updateHighscore();
		}

		//	Kollision zwischen Objekt und Pilz
		if (checkCollision(obj->returnPos(), shroom->returnPos())) {
			obj->renew();
		}

		//	Kollision mit Fuchs
		if (checkCollision(bunny->returnPos(), fox->returnPos())) {
			bunny->die();
			distanceCount -= speed;
			updateHighscore();
		}

		//	Kollision mit Karotte
		if (checkCollision(bunny->returnPos(), carrot->returnPos())) {
			if (speed <= 3.0)
				speed += 0.1;
			carrots++;
			carrot->renew();
		}

		//	Kollision mit Pilz
		if (checkCollision(bunny->returnPos(), shroom->returnPos())) {
			if (shroom->isBroom()) {
				bunny->jump(60, false);
			}
			else {
				bunny->jump(60, false);
				bunny->getClouded();
			}
		}

		//	Kollision zwischen Fuchs und Objekt
		if (checkCollision(fox->returnPos(), obj->returnPos())) {
			fox->changeDir();
		}

		//	Aktualisierung der Anzeige
		swprintf_s(distanceCountText, L"%d", (int)distanceCount);
		swprintf_s(carrotCountText, L"%d", carrots);

		distanceCount += speed;

		//	Aktualisierung der Objekte
		carrot->update(speed);
		fox->update(speed);
		obj->update(speed);
		bunny->updateBunny(speed);
		background->update(speed);
		shroom->update(speed);

		//	Aktualisierung der Uhr
		clockR = std::clock();
	}
	else if (bunny->isDead()) {
		bunny->updateBunny(speed);
	}

	//	Neustart
	if (GetAsyncKeyState(VK_F9)) {
		Sleep(10);
		water = new Water(gfx, 5);
		bunny = new Bunny(gfx);
		obj = new Obstacle(gfx);
		carrot = new Carrot(gfx, L"carrot.png");
		fox = new Fox(gfx);
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

	//	Anzeigen von dem Hasen abhängig von Karotten
	bunny->showBunny(carrots > 0);

	// Anzeige von den Texten
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

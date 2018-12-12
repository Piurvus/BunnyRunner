#include "Game.h"
#include "SpriteSheet.h"
#include <ctime>
#include "Bunny.h"
#include "Carrot.h"
#include "Fox.h"
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>

Game::Game(Graphics * gfx):
	gfx(gfx)
{
	xScreen1 = 0;
	xScreen2 = 1224;
	xScreen3 = 2*xScreen2;

	//-------Sprites-----------
	water = new Water(gfx, 5);
	sprites = new SpriteSheet(L"background.png", gfx, 1.0f);
	fox = new Fox(gfx);
	carrot = new Carrot(gfx, L"carrot.png");
	bunny = new Bunny(gfx);
	obj = new Obstacle(gfx); 
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
	delete water;
	delete carrot;
	delete fox;
	delete sprites;
	delete bunny;
	delete obj;
	outfile.close();
}

void Game::Run()
{
	gfx->BeginDraw();
	UpdateModel();
	ComposeFrame();
	gfx->EndDraw();
}
//float a = 0.0f;

void Game::UpdateModel()
{
	if (bunny->isDead()) {
		speed = 1.0;
	}

	if ((std::clock() - clock) / (double)CLOCKS_PER_SEC >= refreshRate && !bunny->isDead())
	{
		
		if (abs(obj->returnPos().left - carrot->returnPos().left) < 100) {
			carrot->renew();
		}

		if (GetAsyncKeyState(VK_SPACE) && bunny->onGround())
			charge += 1.5;

		if (GetAsyncKeyState(VK_SPACE) && !bunny->onGround() && carrots && 	(std::clock() - carrotsTimer) / (double)CLOCKS_PER_SEC >= 0.5f) {
			carrotsTimer = clock;
			carrots--;
			charge = 0;
			bunny->jump(30);
		}

		if (!GetAsyncKeyState(VK_SPACE) && charge != 0 && bunny->onGround()) {
			bunny->jump(charge);
			charge = 0;
		}

		if (checkCollision(bunny->returnPos(), obj->returnPos())) {
			bunny->die();
			distanceCount -= speed;
			updateHighscore();
		}
		if (checkCollision(bunny->returnPos(), fox->returnPos())) {
			bunny->die();
			distanceCount -= speed;
			updateHighscore();
		}
		
		if (checkCollision(bunny->returnPos(), carrot->returnPos())) {
			speed += 0.1;
			carrots++;
			carrot->renew();
		}

		if (xScreen1 + 1224.0 <= 0) {
			xScreen1 = 2 * 1224-0.1;
		}
		else if (xScreen2 + 1224.0 <= 0) {
			xScreen2 = 2 * 1224.0-0.1;
		}
		else if (xScreen3 + 1224.0 <= 0) {
			xScreen3 = 2 * 1224.0-0.1;
		}

		xScreen1 -= 2*(int)speed; 
		xScreen2 -= 2*(int)speed;
		xScreen3 -= 2*(int)speed;

		swprintf_s(distanceCountText, L"%d", (int)distanceCount);
		swprintf_s(carrotCountText, L"%d", carrots);

		distanceCount += speed;

		carrot->update(speed);
		fox->update(speed);
		obj->update(speed);
		bunny->updateBunny(speed);

		clock = std::clock();
	}
	else if (bunny->isDead()) {
		bunny->updateBunny(speed);
	}

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
	if ((std::clock() - clock) / (double)CLOCKS_PER_SEC >= refreshRate)
	{

		gfx->ClearScreen(255, 255, 255);

		sprites->Draw(xScreen1, -10.0f, 0.6f, 1.0f, true);
		sprites->Draw(xScreen2, -10.0f, 0.6f, 1.0f, true);
		sprites->Draw(xScreen3, -10.0f, 0.6f, 1.0f, true);

		water->showWaterArea(bottom, speed);

		fox->show();
		obj->show();

		//gfx->DrawLine(0, 435, 1600, 435);
		
		carrot->show();


		/*
		D2D1_RECT_F a = bunny->returnPos();
		D2D1_RECT_F b = fox->returnPos();
		gfx->DrawRectangle(a);
		gfx->DrawRectangle(b);
		*/

		bunny->showBunny();
		gfx->DrawTEXT(&D2D1::Rect(50, 10, 500, 500), 50, L"Score:");
		gfx->DrawTEXT(&D2D1::Rect(250, 10, 500, 500), 50, distanceCountText);

		//mbstowcs(outpuet, output, strlen(output + 1));
		//if((std::stoi(highscore)) >=0 )
		gfx->DrawTEXT(&D2D1::Rect(1100, 10, 1600, 500), 50, L"Highscore:");
		gfx->DrawTEXT(&D2D1::Rect(1300, 10, 1600, 500), 50, highscoreWchar);
		gfx->DrawTEXT(&D2D1::Rect(50, 60, 500, 500), 50, L"Carrots:");
		gfx->DrawTEXT(&D2D1::Rect(250, 60, 500, 500), 50, carrotCountText);
	}
	


	//}
	
}

void Game::updateHighscore()
{
	distanceCount += 0.5;

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

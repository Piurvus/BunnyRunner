#include "Game.h"
#include "SpriteSheet.h"
#include <ctime>
#include "Bunny.h"
#include "Carrot.h"
#include "Fox.h"
#include <string>
#include <stdio.h>

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

}

Game::~Game()
{
	delete carrot;
	delete fox;
	delete sprites;
	delete bunny;
	delete obj;
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

		if (GetAsyncKeyState(VK_SPACE) && !bunny->onGround() && carrots) {
			carrots--;
			bunny->jump(30);
		}

		if (!GetAsyncKeyState(VK_SPACE) && charge != 0 && bunny->onGround()) {
			bunny->jump(charge);
			charge = 0;
		}

		if (checkCollision(bunny->returnPos(), obj->returnPos())) {
			bunny->die();
		}
		if (checkCollision(bunny->returnPos(), fox->returnPos())) {
			bunny->die();
		}
		
		if (checkCollision(bunny->returnPos(), carrot->returnPos())) {
			speed += 0.1;
			carrots++;
			carrot->renew();
		}

		if (xScreen1 + 1224 <= 0) {
			xScreen1 = 2 * 1224-0.1;
		}
		else if (xScreen2 + 1224 <= 0) {
			xScreen2 = 2 * 1224-0.1;
		}
		else if (xScreen3 + 1224 <= 0) {
			xScreen3 = 2 * 1224-0.1;
		}

		xScreen1 -= 2*(int)speed; 
		xScreen2 -= 2*(int)speed;
		xScreen3 -= 2*(int)speed;

		distanceCount += speed;
		swprintf_s(distanceCountText, L"%d", (int)distanceCount);
		swprintf_s(carrotCountText, L"%d", (int)carrots);

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

	gfx->ClearScreen(255, 255, 255);

	sprites->Draw(xScreen1, -10.0f, 0.6f, 1.0f, true);
	sprites->Draw(xScreen2, -10.0f, 0.6f, 1.0f, true);
	sprites->Draw(xScreen3, -10.0f, 0.6f, 1.0f, true);

	water->showWaterArea(bottom, speed);

	if ((std::clock() - clock) / (double)CLOCKS_PER_SEC >= refreshRate)
	{
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
		gfx->DrawTEXT(&D2D1::Rect(50, 60, 500, 500), 50, L"Carrots:");
		gfx->DrawTEXT(&D2D1::Rect(250, 60, 500, 500), 50, carrotCountText);
	}
	


	//}
	
}

bool Game::checkCollision(D2D1_RECT_F a, D2D1_RECT_F b)
{
	

	return (b.top <= a.bottom && b.bottom >= a.top && b.left <= a.right && b.right >= a.left);
}

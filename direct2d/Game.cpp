#include "Game.h"
#include "SpriteSheet.h"
#include <ctime>
#include "Bunny.h"
#include "Carrot.h"
#include "Fox.h"

Game::Game(Graphics * gfx):
	gfx(gfx)
{

	//-------------------------
	//sprites = new SpriteSheet(L"test.png", gfx, 0.4f);
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



		carrot->update(speed);
		fox->update(speed);
		obj->update(speed);
		
		bunny->updateBunny(speed);


		clock = std::clock();
	}
	else if (bunny->isDead()) {
		bunny->updateBunny(speed);
	}

	if (GetAsyncKeyState(VK_F10)) {
		Sleep(10);
		bunny = new Bunny(gfx);
		obj = new Obstacle(gfx);
		carrot = new Carrot(gfx, L"carrot.png");
		fox = new Fox(gfx);
		speed = 1.0f;
		carrots = 0;
	}

}

void Game::ComposeFrame()
{

	gfx->ClearScreen(255, 255, 255);
	sprites->Draw(0, -10, 0.6);
	sprites->Draw(1220, -10, 0.6);

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
	}


	//}
	
}

bool Game::checkCollision(D2D1_RECT_F a, D2D1_RECT_F b)
{
	

	return (b.top <= a.bottom && b.bottom >= a.top && b.left <= a.right && b.right >= a.left);
}

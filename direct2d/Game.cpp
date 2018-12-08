#include "Game.h"
#include "SpriteSheet.h"
#include <ctime>


Game::Game(Graphics * gfx):
	gfx(gfx)
{

	//-------------------------
	//sprites = new SpriteSheet(L"test.png", gfx, 0.4f);
	bunny = new Bunny(gfx);
	obj = new Obstacle(gfx);
	//-------------------------

}

Game::~Game()
{
	
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

	if ((std::clock() - clock) / (double)CLOCKS_PER_SEC >= refreshRate)
	{
		if (GetAsyncKeyState(VK_SPACE) && bunny->onGround())
			charge += 0.75;

		if (!GetAsyncKeyState(VK_SPACE) && charge != 0 && bunny->onGround()) {
			bunny->jump(charge);
			charge = 0;
		}

		if (checkCollision(bunny->returnPos(), obj->returnPos())) {
			bunny->die();
		}

		bunny->updateBunny(speed);


		obj->update(speed);

		
		/*
		if (GetAsyncKeyState(VK_SHIFT)&1)
			speed += 0.1;
		*/


		clock = std::clock();
	}
}

void Game::ComposeFrame()
{
	if ((std::clock() - clock) / (double)CLOCKS_PER_SEC >= refreshRate)
	{
		gfx->ClearScreen(255, 255, 255);
		obj->show();
		gfx->DrawLine(0, 435, 800, 435);

		bunny->showBunny();
	}


	//}
	
}

bool Game::checkCollision(D2D1_RECT_F rect1, D2D1_RECT_F rect2)
{
	return false;
}

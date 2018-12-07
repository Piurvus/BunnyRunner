#include "Game.h"
#include "SpriteSheet.h"
#include <ctime>


Game::Game(Graphics * gfx):
	gfx(gfx)
{

	//-------------------------
	sprites = new SpriteSheet(L"test.png", gfx, 0.4f);
	bunny = new Bunny(gfx);
	//-------------------------

}

Game::~Game()
{
	
	delete sprites;

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

		if (GetAsyncKeyState(VK_CONTROL)) {
			bunny->die();
		}

		bunny->updateBunny();

		/*
		ySpeed += 1.0f;
		y += ySpeed;
		if (y > 600) {
			y = 600;
			ySpeed = -30.0f;
		}
		if (GetAsyncKeyState(VK_CONTROL) & 1) {
			loading = !loading;
		}
		a += 0.2f;
		if (a >= 0.8f) a = 0;
		*/

		clock = std::clock();
	}
}

void Game::ComposeFrame()
{
	if ((std::clock() - clock) / (double)CLOCKS_PER_SEC >= refreshRate)
	{
		gfx->ClearScreen(255, 255, 255);
		gfx->DrawLine(0, 435, 800, 435);

		bunny->showBunny();
	}


	//}
	
}

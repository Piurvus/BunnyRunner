#include "Game.h"
#include "SpriteSheet.h"

Game::Game(Graphics * gfx):
	gfx(gfx)
{

	//-------------------------
	sprites = new SpriteSheet(L"test.png", gfx, 0.4f);
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

void Game::UpdateModel()
{

	/*ySpeed += 1.0f;
	y += ySpeed;
	if (y > 600) {
		y = 600;
		ySpeed = -30.0f;
	}*/

}

void Game::ComposeFrame()
{

	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	sprites->Draw();
	gfx->DrawCircle(375.0f, y, 50.0f, 255, 255, 0, 0.5);

}

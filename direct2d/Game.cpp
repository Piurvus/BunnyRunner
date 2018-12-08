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
	if ((std::clock() - clock) / (double)CLOCKS_PER_SEC >= refreshRate && !bunny->isDead())
	{
		if (GetAsyncKeyState(VK_SPACE) && bunny->onGround())
			charge += 1    ;

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
	else if (bunny->isDead() && GetAsyncKeyState(VK_F10) & 1) {
		bunny = new Bunny(gfx);
		obj = new Obstacle(gfx);
	}
	else if (bunny->isDead()) {
		bunny->updateBunny(speed);
	}
}

void Game::ComposeFrame()
{
	if ((std::clock() - clock) / (double)CLOCKS_PER_SEC >= refreshRate)
	{
		gfx->ClearScreen(255, 255, 255);
		
		obj->show();
		gfx->DrawLine(0, 435, 800, 435);
		
		
		D2D1_RECT_F a = bunny->returnPos();
		D2D1_RECT_F b = obj->returnPos();
		gfx->DrawRectangle(a);
		gfx->DrawRectangle(b);
		

		bunny->showBunny();
	}


	//}
	
}

bool Game::checkCollision(D2D1_RECT_F a, D2D1_RECT_F b)
{
	

	return (b.top <= a.bottom && b.bottom >= a.top && b.left <= a.right && b.right >= a.left);
}

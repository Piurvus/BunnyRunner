/*
Datum: 09.01.2019
Projektname: Bunny Runner
von: Florian Kaufmannm, Yann Huynh, Philipp Scherer
main, Background, Bunny, Carrot, Fox, Graphics, obstacle, SpriteSheet, Water von Philipp
Background, Shroom, Water, Fox von Florian
obstacle, Carrot, Fox, Bunny von Yann


Window.h um ein Fenster zu erstellen.
iostream um eine Konsolen Ausgabe zu machen.
*/
#include <Windows.h>
#include "Graphics.h"
#include "SpriteSheet.h"
#include <iostream>
#include "Game.h"



//	Die beiden wichtigen Objekte
Graphics* graphics;
Game* myGame;


//	Message Handling
LRESULT CALLBACK WindowProc(HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{

	//	Programm Ende
	if (uMsg == WM_DESTROY) {

		//	exit(0);
		delete myGame;
		delete graphics;
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//	Einstiegspunkt des Programms
int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow)
{

	//	Das erstellen der Windowklasse für das Fenster
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));

	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = L"MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowclass);

	RECT rect = { 0, 0, 1600, 600 };	//	Damit der INHALT des Fensters die gewünschte Auflösung besitzt
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		L"MainWindow",
		L"D2d",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		0);

	if (!windowHandle)
		return -1;

	graphics = new Graphics();

	if (!graphics->Init(windowHandle)) {
		delete graphics;
		return -1;
	}

	ShowWindow(windowHandle, nCmdShow); // Fenster anzeigen.

	MSG message;

	message.message = WM_NULL;

	myGame = new Game(graphics);

	//	Die Schleife des Fensters	
	while (message.message != WM_QUIT)
	{
		
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&message);
		}

		//graphics->BeginDraw();

		//	Das eigentliche Spiel:
		myGame->Run();
		
		//graphics->EndDraw();
	}

	delete myGame;
	delete graphics;
	return 0;

}
#include <Windows.h>
#include "Graphics.h"
#include "SpriteSheet.h"
#include <iostream>
#include "Game.h"

Graphics* graphics;

LRESULT CALLBACK WindowProc(HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	if (uMsg == WM_DESTROY) {
		PostQuitMessage(0);
		return 0;
	}

	/*if (uMsg == WM_PAINT){
		graphics->BeginDraw();

		graphics->ClearScreen(0, 255, 255);
		graphics->DrawCircle(100, 100, 50, 255, 0, 0, 1);

		graphics->EndDraw();
	}*/

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow)
{

	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));

	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = L"MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowclass);

	RECT rect = { 0, 0, 800, 600 };
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

	ShowWindow(windowHandle, nCmdShow);


	MSG message;
	/*while (GetMessage(&message, NULL, 0, 0))
	{
		DispatchMessage(&message);
	}*/

	message.message = WM_NULL;

	Game* myGame;
	myGame = new Game(graphics);

	while (message.message != WM_QUIT)
	{

		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&message);
		}

		//graphics->BeginDraw();
		
		myGame->Run();

		//graphics->EndDraw();
	}

	delete myGame;
	delete graphics;
	return 0;

}
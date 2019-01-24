/*
Datum: 09.01.2019
Projektname: Bunny Runner
von: Florian Kaufmann, Yann Huynh, Philipp Scherer
Hauptquellen: MSDN https://docs.microsoft.com/en-us/windows/desktop/api/index
main, Background, Bunny, Carrot, Fox, Graphics, obstacle, SpriteSheet, Water von Philipp
Background, Shroom, Water, Fox von Florian
obstacle, Carrot, Fox, Bunny von Yann

Man braucht die DirectX SDK.
Man muss das Projekt neuausrichten.

Windows.h um ein Fenster zu erstellen.
iostream um eine Konsolen Ausgabe zu machen.

Es ist die Main Datei.
*/
#include <Windows.h>
#include "Graphics.h"
#include "SpriteSheet.h"
#include <iostream>
#include "Game.h"



//	Die beiden wichtigen Objekte
//	Zuständig für Grafik
Graphics* graphics;
//	Das eigentliche "Game"
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

	//	Default Handling von den Nachrichten
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//	Einstiegspunkt des Programms
int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow)
{

	//	Das Erstellen der Windowklasse für das Fenster
	WNDCLASSEX windowclass;

	//	Den benötigten Speicher frei machen
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));

	//	Die verschiedenen Klassenelemente werden gesetzt
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = L"MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	//	Registrieren der Window-Klasse damit diese anschliessend verwendet werden kann
	RegisterClassEx(&windowclass);

	//	Damit der INHALT des Fensters die gewünschte Auflösung besitzt
	RECT rect = { 0, 0, 1600, 600 };	
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	//	Handle des Fensters
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

	//	Fehler im Programm abfangen
	if (!windowHandle)
		return -1;

	graphics = new Graphics();

	//	Abfangen von Fehlern bei der Initialisierung der Grafik
	if (!graphics->Init(windowHandle)) {
		delete graphics;
		return -1;
	}

	// Fenster anzeigen
	ShowWindow(windowHandle, nCmdShow); 

	MSG message;
	message.message = WM_NULL;

	//	Der Konstruktor der Game Klasse wird mit einer Referenz zum Grafikobjekt aufgerufen, damit die verschiedenen Elemente des Spiels initialisiert werden können
	myGame = new Game(graphics);

	//	Die Schleife des Fensters	
	while (message.message != WM_QUIT)
	{
		//	Falls eine neue Message ankommt, wird diese bearbeitet
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&message);
		}

		//	Das eigentliche Spiel:
		myGame->Run();
	}

	delete myGame;
	delete graphics;
	return 0;

}
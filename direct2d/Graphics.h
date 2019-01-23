//	Headerdatei für Grafiken
//	Windows.h um ein Fenster zu erstellen
//	<d2d1.h> direct2D Bibliothek für Grafische Darstellungen

#pragma once
#include <Windows.h>
#include <d2d1.h>

class Graphics
{

private:
	ID2D1Factory* factory;					//	Wird dazu benötigt renderTarget zu initialisieren
	ID2D1HwndRenderTarget* renderTarget;	//	Ort im Ram, wohin gerendert wird.
	ID2D1SolidColorBrush* brush;			//	Pinsel für die Farbe

public:
	Graphics();
	~Graphics();

	//	Damit Spritesheet als eigene Klasse stehen kann wird renderTarget zurückgegeben
	ID2D1RenderTarget* GetRenderTarget() {
		return renderTarget;
	}
	
	//	Initialisieren der obigen Objekte
	bool Init(const HWND windowHandle);

	//	Die beiden Funktionen, welche bei jeder Frame wichtig sind
	void BeginDraw();
	void EndDraw();

	//	Alle Zeichnungsfunktionen
	void fillRect(const D2D_RECT_F & rect, float r, float g, float b);
	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float  radius, float r, float g, float b, float a);
	void DrawLine(float x, float y, float x2, float y2);
	void DrawWaterLine(float x, float y, float x2, float y2, float r, float g, float b, float thickness);
	void DrawTEXT(D2D1_RECT_F* rect, float size, const wchar_t text[]);
	void DrawRectangle(D2D_RECT_F & rect);
};
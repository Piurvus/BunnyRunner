#pragma once
#include <Windows.h>
#include <d2d1.h>

class Graphics
{

private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;	//place in ram to render to
	ID2D1SolidColorBrush* brush;

public:
	Graphics();
	~Graphics();

	ID2D1RenderTarget* GetRenderTarget() {
		return renderTarget;
	}

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
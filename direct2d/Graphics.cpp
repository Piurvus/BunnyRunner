#include "Graphics.h"
#include <d2d1_1.h>
#include <dwrite.h>
#include <d2d1_2.h>
#include <d2d1_3.h>
#include <string>
#include <cwchar>

Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
}

Graphics::~Graphics()
{
	if (factory)
		factory->Release();
	if (renderTarget)
		renderTarget->Release();
	if (brush)
		brush->Release();
}

bool Graphics::Init(const HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK)
		return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (res != S_OK)
		return false;

	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK)
		return false;

	return true;

}

void Graphics::BeginDraw()
{
	renderTarget->BeginDraw();
}

void Graphics::EndDraw()
{
	renderTarget->EndDraw();
}

void Graphics::fillRect(const D2D_RECT_F & rect, float r , float g, float b)
{
	brush->SetColor(D2D1::ColorF(r, g, b));
	renderTarget->FillRectangle(rect, brush);
}

void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}

void Graphics::DrawLine(float x, float y, float x2, float y2)
{
	brush->SetColor(D2D1::ColorF(0, 0, 0));
	renderTarget->DrawLine(D2D1::Point2F(x, y), D2D1::Point2F(x2, y2), brush, 3.0f);
}

void Graphics::DrawWaterLine(float x, float y, float x2, float y2, float r, float g, float b, float thickness)
{
	brush->SetColor(D2D1::ColorF(r, g, b));
	renderTarget->DrawLine(D2D1::Point2F(x, y), D2D1::Point2F(x2, y2), brush, thickness);
}

void Graphics::DrawTEXT(D2D1_RECT_F* rect, float size, const wchar_t text[])
{

	HRESULT hr;
	IDWriteTextFormat* textformat;
	IDWriteFactory* writeFactory;
	
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&writeFactory)
	);
	
	hr = writeFactory->CreateTextFormat(
		L"Gabriola",
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		size,
		L"en-us",
		&textformat
	);

	brush->SetColor(D2D1::ColorF(0, 0, 0));
	renderTarget->DrawTextW(text, std::wcslen(text), textformat, rect, brush, D2D1_DRAW_TEXT_OPTIONS_NO_SNAP, DWRITE_MEASURING_MODE_NATURAL);

}

void Graphics::DrawRectangle(D2D_RECT_F & rect)
{
	brush->SetColor(D2D1::ColorF(0, 0, 0));
	renderTarget->DrawRectangle(rect, brush, 3.0f);
}


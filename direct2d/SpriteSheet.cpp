#include "SpriteSheet.h"


SpriteSheet::SpriteSheet(LPCWSTR filename, Graphics * gfx, float a) :
	gfx(gfx),
	a(a)
{
	//LPCWSTR filename = L"test.png";

	//	bmp wird initialisiert

	bmp = NULL;
	HRESULT hr;

	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter * wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);

	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp);

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();

	//	Standartwerte werden zugewiesen
	spriteWidth = bmp->GetSize().width;
	spriteHeight = bmp->GetSize().height;
	spritesAccross = 1;

}

SpriteSheet::SpriteSheet(LPCWSTR filename, Graphics * gfx, float a, int spriteWidth, int spriteHeight):
	SpriteSheet(filename, gfx, a)
{
	//	Werte werden zugewiesen
	this->spriteHeight = spriteHeight;
	this->spriteWidth = spriteWidth;
	this->spritesAccross = (int)bmp->GetSize().width / spriteWidth;
}

SpriteSheet::~SpriteSheet()
{
		//if (bmp) bmp->Release();	
}



void SpriteSheet::Draw(float a)
{
	//	Bild wird an Position (0, 0) gezeichnet
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(0.0f, 0.0f,
		bmp->GetSize().width, bmp->GetSize().height),
		a,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f,
		bmp->GetSize().width, bmp->GetSize().height));

}

void SpriteSheet::Draw(float x, float y, double size)
{

	//	Position in dem Fenster
	D2D_RECT_F dest = D2D1::RectF(
		x, y,
		x + spriteWidth * size, y + spriteHeight * size);

	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f,
		bmp->GetSize().width, bmp->GetSize().height));
}

void SpriteSheet::Draw(float x, float y, double size, double a, bool cuzitwontworkwithoutkappa)
{
	//	Position in dem Fenster
	D2D_RECT_F dest = D2D1::RectF(
		x, y,
		x + spriteWidth * size, y + spriteHeight * size);

	//	je nach a stärker oder weniger stark sichtbar
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,
		a,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f,
		bmp->GetSize().width, bmp->GetSize().height));
}

void SpriteSheet::Draw(int index, int x, int y, double size)
{
	
	//	Position im Bild
	D2D_RECT_F src = D2D1::RectF(
		(float)((index % spritesAccross) * spriteWidth),
		(float)((index / spritesAccross) * spriteHeight),
		(float)((index % spritesAccross) * spriteWidth) + spriteWidth,
		(float)((index / spritesAccross) * spriteHeight) + spriteHeight);

	//	Position in dem Fenster
	D2D_RECT_F dest = D2D1::RectF(
		x, y,
		x + spriteWidth*size, y + spriteHeight*size);

	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		src);
}


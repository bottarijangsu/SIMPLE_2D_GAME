#include "iGraphics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "iStd.h"

iGraphics::iGraphics() {
	bitmap = NULL;
	g = NULL;
}

iGraphics::~iGraphics() {
	if (bitmap) {
		delete bitmap;
		delete g;
	}
}

static iGraphics* instance = NULL;
iGraphics* iGraphics::share() {
	if (instance == NULL)
		instance = new iGraphics();
	return instance;
}

void iGraphics::init(iSize size) {
	if (bitmap) {
		delete bitmap;
		delete g;
	}

	bitmap = new Bitmap(size.width, size.height, PixelFormat32bppARGB);
	g = Graphics::FromImage(bitmap);
	g->Clear(Color(0, 0, 0, 0));
	initGraphics();
}

Texture* iGraphics::getTexture() {
	if (bitmap) {
		uint32 width, height;
		uint8* rgba = bmp2rgba(bitmap, width, height);
		Texture* tex = createImageWidthRGBA(rgba, width, height);

		delete bitmap;
		bitmap = NULL;
		delete g;

		return tex;
	}

	return NULL;
}

void iGraphics::initGraphics() {
	g->SetPageUnit(UnitPixel);
	g->SetPixelOffsetMode(PixelOffsetModeHalf);
	g->SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
	g->SetSmoothingMode(SmoothingModeAntiAlias8x8);
	g->SetInterpolationMode(InterpolationModeHighQualityBicubic);
}

void iGraphics::drawLine(int sx, int sy, int ex, int ey) {
	float fr, fg, fb, fa;
	getRGBA(fr, fg, fb, fa);
	Pen pen(
			Color(float2byte(fa), float2byte(fr), float2byte(fg),
					float2byte(fb)));

	pen.SetWidth(1);
	g->DrawLine(&pen, sx, sy, ex, ey);
}

void iGraphics::drawRect(int x, int y, int width, int height, int lineWidth,
		int radius) {
	float fr, fg, fb, fa;
	getRGBA(fr, fg, fb, fa);
	Pen pen(
			Color(float2byte(fa), float2byte(fr), float2byte(fg),
					float2byte(fb)));
	pen.SetWidth(lineWidth);

	GraphicsPath path;
	path.AddLine(x + radius, y, x + width - (radius * 1), y);
	path.AddArc(x + width - (radius * 1), y, radius * 1, radius * 1, 270, 90);
	path.AddLine(x + width, y + radius, x + width, y + height - (radius * 1));
	path.AddArc(x + width - (radius * 1), y + height - (radius * 1), radius * 1,
			radius * 1, 0, 90);
	path.AddLine(x + width - (radius * 1), y + height, x + radius, y + height);
	path.AddArc(x, y + height - (radius * 1), radius * 1, radius * 1, 90, 90);
	path.AddLine(x, y + height - (radius * 1), x, y + radius);
	path.AddArc(x, y, radius * 1, radius * 1, 180, 90);
	path.CloseFigure();

	g->DrawPath(&pen, &path);
}

void iGraphics::drawRect(iPoint leftTop, int width, int height, int lineWidth,
		int radius) {
	float fr, fg, fb, fa;
	getRGBA(fr, fg, fb, fa);
	Pen pen(
			Color(float2byte(fa), float2byte(fr), float2byte(fg),
					float2byte(fb)));
	int x = leftTop.x, y = leftTop.y;
	pen.SetWidth(lineWidth);

	GraphicsPath path;
	path.AddLine(x + radius, y, x + width - (radius * 1), y);
	path.AddArc(x + width - (radius * 1), y, radius * 1, radius * 1, 270, 90);
	path.AddLine(x + width, y + radius, x + width, y + height - (radius * 1));
	path.AddArc(x + width - (radius * 1), y + height - (radius * 1), radius * 1,
			radius * 1, 0, 90);
	path.AddLine(x + width - (radius * 1), y + height, x + radius, y + height);
	path.AddArc(x, y + height - (radius * 1), radius * 1, radius * 1, 90, 90);
	path.AddLine(x, y + height - (radius * 1), x, y + radius);
	path.AddArc(x, y, radius * 1, radius * 1, 180, 90);
	path.CloseFigure();

	g->DrawPath(&pen, &path);
}

void iGraphics::drawRect(int x, int y, int width, int height, int lineWidth,
		int topLeft, int topRight, int bottomRight, int bottomLeft) {
	float fr, fg, fb, fa;
	getRGBA(fr, fg, fb, fa);
	Pen pen(
			Color(float2byte(fa), float2byte(fr), float2byte(fg),
					float2byte(fb)));
	pen.SetWidth(lineWidth);

	GraphicsPath path;
	//TOP|HCENTER
	path.AddLine(x + topLeft, y, x + width - (topRight * 1), y);
	//TOP|RIGHT
	path.AddArc(x + width - (topRight * 1), y, topRight * 1, topRight * 1, 270,
			90);
	//VCENTER|RIGHT
	path.AddLine(x + width, y + topRight, x + width,
			y + height - (bottomRight * 1));
	//BOTTOM|RIGHT
	path.AddArc(x + width - (bottomRight * 1), y + height - (bottomRight * 1),
			bottomRight * 1, bottomRight * 1, 0, 90);
	//BOTTOM|HCENTER
	path.AddLine(x + width - (bottomRight * 1), y + height, x + bottomLeft,
			y + height);
	//BOTTOM|LEFT
	path.AddArc(x, y + height - (bottomLeft * 1), bottomLeft * 1,
			bottomLeft * 1, 90, 90);
	//VCENTER|LEFT
	path.AddLine(x, y + height - (bottomLeft * 1), x, y + topLeft);
	//TOP|LEFT
	path.AddArc(x, y, topLeft * 1, topLeft * 1, 180, 90);
	path.CloseFigure();

	g->DrawPath(&pen, &path);
}

void iGraphics::fillRect(int x, int y, int width, int height, int radius) {
	float fr, fg, fb, fa;
	getRGBA(fr, fg, fb, fa);
	SolidBrush brush(
			Color(float2byte(fa), float2byte(fr), float2byte(fg),
					float2byte(fb)));

	GraphicsPath path;
	path.AddLine(x + radius, y, x + width - (radius * 1), y);
	path.AddArc(x + width - (radius * 1), y, radius * 1, radius * 1, 270, 90);
	path.AddLine(x + width, y + radius, x + width, y + height - (radius * 1));
	path.AddArc(x + width - (radius * 1), y + height - (radius * 1), radius * 1,
			radius * 1, 0, 90);
	path.AddLine(x + width - (radius * 1), y + height, x + radius, y + height);
	path.AddArc(x, y + height - (radius * 1), radius * 1, radius * 1, 90, 90);
	path.AddLine(x, y + height - (radius * 1), x, y + radius);
	path.AddArc(x, y, radius * 1, radius * 1, 180, 90);
	path.CloseFigure();

	g->FillPath(&brush, &path);
}

void iGraphics::fillRect(int x, int y, int width, int height, int topLeft,
		int topRight, int bottomRight, int bottomLeft) {
	float fr, fg, fb, fa;
	getRGBA(fr, fg, fb, fa);
	SolidBrush brush(
			Color(float2byte(fa), float2byte(fr), float2byte(fg),
					float2byte(fb)));

	GraphicsPath path;
	//TOP|HCENTER
	path.AddLine(x + topLeft, y, x + width - (topRight * 1), y);
	//TOP|RIGHT
	path.AddArc(x + width - (topRight * 1), y, topRight * 1, topRight * 1, 270,
			90);
	//VCENTER|RIGHT
	path.AddLine(x + width, y + topRight, x + width,
			y + height - (bottomRight * 1));
	//BOTTOM|RIGHT
	path.AddArc(x + width - (bottomRight * 1), y + height - (bottomRight * 1),
			bottomRight * 1, bottomRight * 1, 0, 90);
	//BOTTOM|HCENTER
	path.AddLine(x + width - (bottomRight * 1), y + height, x + bottomLeft,
			y + height);
	//BOTTOM|LEFT
	path.AddArc(x, y + height - (bottomLeft * 1), bottomLeft * 1,
			bottomLeft * 1, 90, 90);
	//VCENTER|LEFT
	path.AddLine(x, y + height - (bottomLeft * 1), x, y + topLeft);
	//TOP|LEFT
	path.AddArc(x, y, topLeft * 1, topLeft * 1, 180, 90);
	path.CloseFigure();

	g->FillPath(&brush, &path);
}

wchar_t* utf8_to_utf16(const char* str);
igImage* iGraphics::createIgImage(const char* szFormat, ...) {
	va_list args;
	va_start(args, szFormat);

	char szText[1024];
	_vsnprintf(szText, sizeof(szText), szFormat, args);

	va_end(args);

	wchar_t* path = utf8_to_utf16(szText);
	Image* img = Image::FromFile(path, false);
	free(path);

	return img;
}

void iGraphics::freeIgImage(igImage* img) {
	delete (Image*) img;
}

int iGraphics::getIgImageWidth(igImage* img) {
	return ((Image*) img)->GetWidth();
}

int iGraphics::getIgImageHeight(igImage* img) {
	return ((Image*) img)->GetHeight();
}

void iGraphics::drawIgImage(igImage* _img, int x, int y, int ix, int iy,
		int idx, int idy, // src
		float rateX, float rateY, int xyz, int degree, int anc) {
	Image* img = (Image*) _img;
	float dx = img->GetWidth() * rateX;
	float dy = img->GetHeight() * rateY;

	switch (anc) {
	case TOP | LEFT:
		break;
	case TOP | HCENTER:
		x -= dx / 2;
		break;
	case TOP | RIGHT:
		x -= dx;
		break;
	case VCENTER | LEFT:
		y -= dy / 2;
		break;
	case VCENTER | HCENTER:
		x -= dx / 2;
		y -= dy / 2;
		break;
	case VCENTER | RIGHT:
		x -= dx;
		y -= dy / 2;
		break;
	case BOTTOM | LEFT:
		y -= dy;
		break;
	case BOTTOM | HCENTER:
		x -= dx / 2;
		y -= dy;
		break;
	case BOTTOM | RIGHT:
		x -= dx;
		y -= dy;
		break;
	}

	iPoint destPoint[3] = { { x, y }, { x + dx, y }, { x, y + dy } };
	iPoint t = iPointMake(x + dx / 2, y + dy / 2);
	if (xyz == 0) // x축
			{
		destPoint[0].y = destPoint[1].y = y + dy / 2 - dy / 2 * _cos(degree);
		destPoint[2].y = y + dy / 2 + dy / 2 * _cos(degree);
	} else if (xyz == 1) // y축
			{
		destPoint[0].x = destPoint[2].x = x + dx / 2 - dx / 2 * _cos(degree);
		destPoint[1].x = x + dx / 2 + dx / 2 * _cos(degree);

	} else // if( xyz==2 )// z축
	{
		for (int i = 0; i < 3; i++)
			destPoint[i] = iPointRotate(destPoint[i], t, degree);
	}

	float a = getAlpha();
	ColorMatrix matrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, a, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f };
	ImageAttributes attr;
	attr.SetColorMatrix(&matrix, ColorMatrixFlagsDefault,
			ColorAdjustTypeBitmap);

	g->DrawImage(img, (PointF*) destPoint, 3, ix, iy, idx, idy, UnitPixel,
			&attr);
}

void iGraphics::drawIgImage(igImage* _img, int x, int y, int anc) {
	Image* img = (Image*) _img;
	drawIgImage(img, x, y, 0, 0, img->GetWidth(), img->GetHeight(), 1.0f, 1.0f,
			2, 0, anc);
}

void iGraphics::drawIgImage(igImage* _img, int x, int y, int width, int height,
		int anc) {
	Image* img = (Image*) _img;
	float w = img->GetWidth();
	float h = img->GetHeight();
	drawIgImage(img, x, y, 0, 0, w, h, width / w, height / h, 2, 0, anc);
}

uint8* iGraphics::bmp2rgba(Bitmap* bmp, uint32& width, uint32& height) {
	width = bmp->GetWidth();
	height = bmp->GetHeight();
	Rect rect(0, 0, width, height);
	BitmapData bmpData;
	bmp->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &bmpData);

	int stride = bmpData.Stride / 4;
	uint8* bgra = (uint8*) bmpData.Scan0;
	int potWidth = nextPOT(width);
	int potHeight = nextPOT(height);
	uint8* rgba = (uint8*) calloc(sizeof(uint8), 4 * potWidth * potHeight);
	uint32 i, j;
	uint8 *dst, *src;
	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			dst = &rgba[4 * potWidth * j + 4 * i];
			src = &bgra[4 * stride * j + 4 * i];
			dst[0] = src[2];
			dst[1] = src[1];
			dst[2] = src[0];
			dst[3] = src[3];
		}
	}
	bmp->UnlockBits(&bmpData);

	return rgba;
}


uint8 float2byte(float f) {
	return (uint8) (f * 0xff);
}

Texture* createImageWidthRGBA(uint8* rgba, float width, float height) {
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	applyTexParameters();

	int potWidth = nextPOT(width);
	int potHeight = nextPOT(height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, potWidth, potHeight, 0, GL_RGBA,
	GL_UNSIGNED_BYTE, rgba);

	Texture* tex = (Texture*) malloc(sizeof(Texture));
	tex->texID = texID;
	tex->width = width;
	tex->height = height;
	tex->potWidth = potWidth;
	tex->potHeight = potHeight;
	tex->retainCount = 1;

	return tex;
}


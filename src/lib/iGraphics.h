#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gdiplus.h>

#include "iType.h"

typedef struct _Texture
{
	uint32 texID;
	int width, height;
	int potWidth, potHeight;
	int retainCount; // 참조된 개수
} Texture;

using namespace Gdiplus;

typedef void igImage;

class iGraphics
{
private:
	iGraphics();
public:
	~iGraphics();

public:
	static iGraphics* share();
	void init(iSize size);
	Texture* getTexture();

	void initGraphics();
	void drawLine(int sx, int sy, int ex, int ey); // start, end
	void drawRect(int x, int y, int width, int height, int lineWidth, int radius);
	void drawRect(iPoint leftTop, int width, int height, int lineWidth, int radius);
	void drawRect(int x, int y, int width, int height, int lineWidth, int topLeft, int topRight,
			int bottomRight, int bottomLeft);
	void fillRect(int x, int y, int width, int height, int radius);
	void fillRect(int x, int y, int width, int height, int topLeft, int topRight,
			int bottomRight, int bottomLeft);

	static igImage* createIgImage(const char* szFormat, ...);
	static void freeIgImage(igImage*);
	static int getIgImageWidth(igImage* img);
	static int getIgImageHeight(igImage* img);
	void drawIgImage(igImage* img, int x, int y, int ix, int iy, int idx, int idy, // src
			float rateX, float rateY, int xyz, int degree, int anc);
	void drawIgImage(igImage* img, int x, int y, int anc);
	void drawIgImage(igImage* img, int x, int y, int width, int height, int anc);

	static uint8* bmp2rgba(Bitmap* bmp, uint32& width, uint32& height);

public:
	Bitmap* bitmap;
	Graphics* g;

private:
};

uint8 float2byte(float f);

Texture* createImageWidthRGBA(uint8* rgba, float width, float height);
void checkFontFamily(FontFamily* ff, int& fontStyle);


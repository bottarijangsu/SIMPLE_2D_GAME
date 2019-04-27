#pragma once

#include "iGraphics.h"
#include "iType.h"

#include "iImage.h"
#include "iPopup.h"

#include "iOpengl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <math.h>
#include <time.h>

#define DEV_WIDTH 1024
#define DEV_HEIGHT 1024

extern iSize monitorSize;
extern iSize wndSize;
extern iSize devSize;
extern iRect viewport;

typedef enum _iKeyState {
	iKeyStateBegan = 0,
	iKeyStateMoved,
	iKeyStateEnded,
	iKeyStateCancel
} iKeyState;

#define TOP 	0
#define VCENTER 1
#define BOTTOM	2
#define LEFT	4
#define HCENTER	8
#define RIGHT	16

#define REVERSE_NONE 0
#define REVERSE_WIDTH 1
#define REVERSE_HEIGHT 2

void loadLib(iSize devSize);
void freeLib();
typedef void (*DRAW_METHOD)(float);
void drawLib(void* hdc, DRAW_METHOD method);
void keyLib(iKeyState stat, int c);

typedef enum _keyboard_key {
	keyboard_left = 1,		// 1 << 0
	keyboard_right = 2,		// 1 << 1
	keyboard_top = 4,		// 1 << 2
	keyboard_bottom = 8,	// 1 << 3
	keyboard_return = 16,	// 1 << 4
	keyboard_space = 32,	// 1 << 5
} keyboard_key;

uint32 getKeyDown();
uint32 getKeyStat();

void setRGBA(float r, float g, float b, float a);
void getRGBA(float& r, float& g, float& b, float& a);
void setAlpha(float a);
float getAlpha();
void setRGB(float r, float g, float b);
void getRGB(float& r, float& g, float& b);

void setDotSize(float size);
void drawDot(int x, int y);
void drawDot(iPoint p);
void drawDots(iPoint* p, int pNum);

void setLineWidth(float width);
void setLineSmooth(bool enable);
void drawLine(iPoint sp, iPoint ep);
void drawLine(int sx, int sy, int ex, int ey);

void drawRect(iRect rect);
void drawRect(int x, int y, int width, int height, int radius=0);
void fillRect(iRect rect);
void fillRect(int x, int y, int width, int height, int radius=0);
void drawPoly(iPoint* p, int pNum, bool fill);

void setClip(float x, float y, float dx, float dy);

Texture* createImage(const char* szFormat, ...);

void freeImage(Texture* tex);
void drawImage(Texture* tex,
		float x, float y,
		float ix, float iy, float idx, float idy,
		float rateX, float rateY,
		int xyz, int degree,
		int anc, int reverse=0);
void drawImage(Texture* tex, int x, int y, int anc);
void drawImage(Texture* tex, int x, int y, int width, int height, int anc);

iSize sizeOfString(const char* szFormat, ...);
iRect rectOfString(const char* szFormat, ...);

void randomize();
int random();

float _sin(float degree);
float _cos(float degree);

float linear(float rate, float start, float end);
float easeIn(float rate, float start, float end);
float easeOut(float rate, float start, float end);
float easeInOut(float rate, float start, float end);







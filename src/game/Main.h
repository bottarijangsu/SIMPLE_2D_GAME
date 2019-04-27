#pragma once

#include "iStd.h"
#include "mainObject.h"

void loadMain();
void freeMain();
void drawMain(float dt);
void updateMain(float dt);
void drawObject(float dt);
void keyMain(iKeyState stat, iPoint point);

//////////////////////////////////////
// MENU POPUP
//////////////////////////////////////
extern iPopup* popMenu;

void createPopMenu();
void freePopMenu();
void showPopMenu(bool show);
void drawPopMenu(float dt);
bool keyPopMenu(iKeyState stat, iPoint point);

//////////////////////////////////////////////////////
// iFont
//////////////////////////////////////////////////////
class iFont
{
public:
	iFont();
	virtual ~iFont();

public:
	iSize sizeOfString(float rate, const char* szFormat, ...);
	void drawString(float x, float y, int anc, float rate, const char* szFormat, ...);

public:
	Texture** texs;
	float gap;
};

extern iFont* f;


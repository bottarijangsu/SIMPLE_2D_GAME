#pragma once

#include "iGraphics.h"
#include "iType.h"

class iImage;
typedef void (*iImage_Method)(iImage* parm);

class iImage
{
public:
	iImage();
	virtual ~iImage();

public:
	static void cbFree(void* parm);

	iImage* copy();

	void addObject(Texture* tex);
	void setTexAtIndex(int index);
	Texture* getTexAtIndex(int index);

	iRect touchRect(iPoint point);

	void paint(float dt, iPoint position=iPointZero, float scale=1.0f,float deg=0, int anc=0|4);
	void update(float dt);

	void startAnimation(iImage_Method method=NULL);
	void stopAnimation(bool init=false);
public:
	iArray* imgList;
	uint8 imgIndex;
	Texture* tex;
	iPoint position;
	int8 leftRight;// 0:left 1:right

	// button
	bool selected;
	float selectedSize;
	float selectedDt;

	// animation
	bool animation;
	float intervalDt, _intervalDt;// 0.15 ~ 0.25
	uint8 repeatNum, _repeatNum;// _repeatNum 0 : infinite
	bool lastTex;
	iImage_Method methodAnimation;
};
#define _selectedSize 0.9f
#define _selectedDt 0.1f

#define _ani_intervalDt 0.2f


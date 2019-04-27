#pragma once

#include "iType_iPoint.h"
#include "iType_iSize.h"

struct iRect
{
	iPoint origin;
	iSize size;
};

iRect iRectMake(float x, float y, float width, float height);
bool containPoint(const iPoint& point, const iRect& rect);
bool intersectRect(const iRect& src, const iRect& dst);
bool containRect(const iRect& src, const iRect& dst);

#define iRectZero iRectMake(0,0,0,0)





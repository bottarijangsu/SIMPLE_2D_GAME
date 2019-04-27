#include "iType_iRect.h"

iRect iRectMake(float x, float y, float width, float height)
{
	iRect r = {x, y, width, height};

	return r;
}

bool containPoint(const iPoint& point, const iRect& rect)
{
	if( point.x < rect.origin.x ||
		point.x > rect.origin.x + rect.size.width ||
		point.y < rect.origin.y ||
		point.y > rect.origin.y + rect.size.height )
		return false;
	return true;
}

bool intersectRect(const iRect& src, const iRect& dst)
{
	if( src.origin.x + src.size.width < dst.origin.x ||
		src.origin.x > dst.origin.x + dst.size.width ||
		src.origin.y + src.size.height < dst.origin.y ||
		src.origin.y > dst.origin.y + dst.size.height )
		return true;
	return false;
}

bool containRect(const iRect& src, const iRect& dst)
{
	return !intersectRect(src, dst);
}

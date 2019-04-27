#include "iType_iPoint.h"

#include <math.h>
bool iPoint::operator == (const iPoint& p)
{
	return (x==p.x && y==p.y);
	//return (fabsf(x-p.x)<0.00001f && fabsf(y-p.y)<0.00001f);
}

bool iPoint::operator != (const iPoint& p)
{
	//return !(x==p.x && y==p.y);
	return (x!=p.x || y!=p.y);
}

iPoint iPoint::operator + (const iPoint& p)
{
	iPoint r;
	r.x = x + p.x;
	r.y = y + p.y;
	return r;
}

iPoint iPoint::operator += (const iPoint& p)
{
	x += p.x;
	y += p.y;
	return (*this);
}

iPoint iPoint::operator - (const iPoint& p)
{
	iPoint r;
	r.x = x - p.x;
	r.y = y - p.y;
	return r;
}
iPoint iPoint::operator -= (const iPoint& p)
{
	x -= p.x;
	y -= p.y;
	return (*this);
}

iPoint iPoint::operator * (const iPoint& p)
{
	iPoint r;
	r.x = x * p.x;
	r.y = y * p.y;
	return r;
}
iPoint iPoint::operator *= (const iPoint& p)
{
	x *= p.x;
	y *= p.y;
	return (*this);
}

iPoint iPoint::operator / (const iPoint& p)
{
	iPoint r;
	r.x = x / p.x;
	r.y = y / p.y;
	return r;
}
iPoint iPoint::operator /= (const iPoint& p)
{
	x /= p.x;
	y /= p.y;
	return (*this);
}

iPoint iPoint::operator * (float f)
{
	iPoint r;
	r.x = x * f;
	r.y = y * f;
	return r;
}
iPoint iPoint::operator *= (float f)
{
	x *= f;
	y *= f;
	return (*this);
}

iPoint iPoint::operator / (float f)
{
	iPoint r;
	r.x = x / f;
	r.y = y / f;
	return r;
}
iPoint iPoint::operator /= (float f)
{
	x /= f;
	y /= f;
	return (*this);
}

iPoint iPointMake(float x, float y)
{
	iPoint p;
	p.x = x;
	p.y = y;
	return p;
}

bool iPointEqual(const iPoint& p0, const iPoint& p1)
{
	return (p0.x==p1.x && p0.y==p1.y);
	//return (fabsf(x-p.x)<0.00001f && fabsf(y-p.y)<0.00001f);
}

iPoint iPointAdd(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p0.x + p1.x;
	p.y = p0.y + p1.y;
	return p;
}
iPoint iPointSub(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p0.x - p1.x;
	p.y = p0.y - p1.y;
	return p;
}

iPoint iPointDot(const iPoint& p)
{
	iPoint r;
	r.x = p.x*p.x;
	r.y = p.y*p.y;
	return r;
}

iPoint iPointMult(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p0.x * p1.x;
	p.y = p0.y * p1.y;
	return p;
}
float iPointLength(const iPoint& p)
{
	return sqrtf(p.x*p.x + p.y*p.y);
}
float iPointDistance(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p0.x - p1.x;
	p.y = p0.y - p1.y;
	return sqrtf(p.x*p.x + p.y*p.y);
}
float iPointDistanceFast(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p0.x - p1.x;
	p.y = p0.y - p1.y;
	return (p.x*p.x + p.y*p.y);
}

iPoint iPointNormalize(const iPoint& p)
{
	float length = sqrtf(p.x*p.x + p.y*p.y);
	iPoint r;
	r.x = p.x / length;
	r.y = p.y / length;
	return r;
}
iPoint iPointVector(const iPoint& p0, const iPoint& p1)
{
	iPoint p;
	p.x = p1.x - p0.x;
	p.y = p1.y - p1.y;
	return p;
}

#include "iStd.h"
float iPointAngle(const iPoint& v1, const iPoint& v2, const iPoint& v3)
{
	iPoint a = iPointMake(v1.x-v2.x, v1.y-v2.y);// v1 - v2;
	iPoint b = iPointMake(v3.x-v2.x, v3.y-v2.y);// v3 - v2;
	iPoint o = iPointZero;

	double oa = iPointDistance(o, a);
	double ob = iPointDistance(o, b);
	double ab = iPointDistance(a, b);
	float degree = acos( (oa*oa+ob*ob-ab*ab)/(2*oa*ob) ) * 180 / M_PI;
	if( b.y > a.y )
	{
		if( degree )
			degree = 360 - degree;
	}
	return degree;
}

iPoint iPointRotate(const iPoint& p, const iPoint& t, float degree)
{
	while( degree < 0 )		degree += 360;
	while( degree > 360 )	degree -= 360;
	float sinr = _sin(degree);
	float cosr = _cos(degree);
#if 0// bottom|left - math
	iPoint r;
	r.x = t.x + (p.x-t.x)*cosr - (p.y-t.y)*sir;
	r.y = t.y + (p.y-t.y)*sinr + (p.y-t.y)*cosr;
#else// top|left
	iPoint r = iPointMake(p.x-t.x, t.y-p.y);
	iPoint _p;
	_p.x = r.x*cosr - r.y*sinr;
	_p.y = r.x*sinr + r.y*cosr;

	_p.x = t.x + _p.x;
	_p.y = t.y - _p.y;
	return _p;
#endif
}





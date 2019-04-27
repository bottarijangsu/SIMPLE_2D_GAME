#pragma once

struct iPoint
{
	float x, y;

	bool operator == (const iPoint& p);
	bool operator != (const iPoint& p);

	iPoint operator + (const iPoint& p);
	iPoint operator += (const iPoint& p);

	iPoint operator - (const iPoint& p);
	iPoint operator -= (const iPoint& p);

	iPoint operator * (const iPoint& p);
	iPoint operator *= (const iPoint& p);

	iPoint operator / (const iPoint& p);
	iPoint operator /= (const iPoint& p);

	iPoint operator * (float f);
	iPoint operator *= (float f);

	iPoint operator / (float f);
	iPoint operator /= (float f);
};

iPoint iPointMake(float x, float y);
bool iPointEqual(const iPoint& p0, const iPoint& p1);
iPoint iPointAdd(const iPoint& p0, const iPoint& p1);
iPoint iPointSub(const iPoint& p0, const iPoint& p1);
iPoint iPointDot(const iPoint& p);
iPoint iPointMult(const iPoint& p0, const iPoint& p1);
float iPointLength(const iPoint& p);
float iPointDistance(const iPoint& p0, const iPoint& p1);
float iPointDistanceFast(const iPoint& p0, const iPoint& p1);
iPoint iPointNormalize(const iPoint& p);
iPoint iPointVector(const iPoint& p0, const iPoint& p1);

#define iPointZero iPointMake(0,0)

float iPointAngle(const iPoint& v1, const iPoint& v2, const iPoint& v3);
iPoint iPointRotate(const iPoint& p, const iPoint& t, float degree);





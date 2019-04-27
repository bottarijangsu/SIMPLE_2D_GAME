#pragma once

struct iSize
{
	float width, height;

	bool operator == (const iSize& s);
	bool operator != (const iSize& s);

	iSize operator + (const iSize& s);
	iSize operator += (const iSize& s);

	iSize operator - (const iSize& s);
	iSize operator -= (const iSize& s);

	iSize operator * (const iSize& s);
	iSize operator *= (const iSize& s);

	iSize operator / (const iSize& s);
	iSize operator /= (const iSize& s);

	iSize operator * (float f);
	iSize operator *= (float f);

	iSize operator / (float f);
	iSize operator /= (float f);
};

iSize iSizeMake(float width, float height);
bool iSizeEqual(const iSize& s0, const iSize& s1);
iSize iSizeAdd(const iSize& s0, const iSize& s1);
iSize isizeSub(const iSize& s0, const iSize& s1);

#define iSizeZero iSizeMake(0,0)





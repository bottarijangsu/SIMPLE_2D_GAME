#include "iType.h"

#include <math.h>
bool iSize::operator == (const iSize& s)
{
	return (width==s.width && height==s.height);
	//return (fabsf(x-p.x)<0.00001f && fabsf(y-p.y)<0.00001f);
}

bool iSize::operator != (const iSize& s)
{
	//return !(x==p.x && y==p.y);
	return (width!=s.width || height!=s.height);
}

iSize iSize::operator + (const iSize& s)
{
	iSize r;
	r.width = width + s.width;
	r.height = height + s.height;
	return r;
}

iSize iSize::operator += (const iSize& s)
{
	width += s.width;
	height += s.height;
	return (*this);
}

iSize iSize::operator - (const iSize& s)
{
	iSize r;
	r.width = width - s.width;
	r.height = height - s.height;
	return r;
}
iSize iSize::operator -= (const iSize& s)
{
	width -= s.width;
	height -= s.height;
	return (*this);
}

iSize iSize::operator * (const iSize& s)
{
	iSize r;
	r.width = width * s.height;
	r.height = height * s.height;
	return r;
}
iSize iSize::operator *= (const iSize& s)
{
	width *= s.width;
	height *= s.height;
	return (*this);
}

iSize iSize::operator / (const iSize& s)
{
	iSize r;
	r.width = width / s.width;
	r.height = height / s.height;
	return r;
}
iSize iSize::operator /= (const iSize& s)
{
	width /= s.width;
	height /= s.height;
	return (*this);
}

iSize iSize::operator * (float f)
{
	iSize r;
	r.width = width * f;
	r.height = height * f;
	return r;
}
iSize iSize::operator *= (float f)
{
	width *= f;
	height *= f;
	return (*this);
}

iSize iSize::operator / (float f)
{
	iSize r;
	r.width = width / f;
	r.height = height / f;
	return r;
}
iSize iSize::operator /= (float f)
{
	width /= f;
	height /= f;
	return (*this);
}

iSize iSizeMake(float width, float height)
{
	iSize s;
	s.width = width;
	s.height = height;
	return s;
}

bool iSizeEqual(const iSize& s0, const iSize& s1)
{
	return (s0.width==s1.width && s0.height==s1.height);
	//return (fabsf(x-p.x)<0.00001f && fabsf(y-p.y)<0.00001f);
}

iSize iSizeAdd(const iSize& s0, const iSize& s1)
{
	iSize s;
	s.width = s0.width + s1.height;
	s.height = s0.width + s1.height;
	return s;
}
iSize iSizeSub(const iSize& s0, const iSize& s1)
{
	iSize s;
	s.width = s0.width - s1.width;
	s.width = s0.height - s1.height;
	return s;
}





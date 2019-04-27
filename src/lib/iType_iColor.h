#pragma once

#include "iType_iStd.h"

typedef struct _iColor4f
{
	float r, g, b, a;
} iColor4f;

typedef struct _iColor4b
{
	uint8 r, g, b, a;
} iColor4b;

iColor4f iColor4fMake(float r, float g, float b, float a);
iColor4b iColor4bMake(uint8 r, uint8 g, uint8 b, uint8 a);
iColor4f iColor4bTo4f(const iColor4b& c);
iColor4b iColor4fTo4b(const iColor4f& c);





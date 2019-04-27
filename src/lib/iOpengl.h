#pragma once

#include <GL/glew.h>

#include "iType.h"

void initOpenGL();
void reshapeOpenGL();

typedef enum _iBlend {
	iBlendAlpha = 0,
	iBlendColor,
	iBlendSolid,
} iBlend;

iBlend getGlBlend();
void setGlBlend(iBlend blend);

void applyTexParameters();
void setAntiAliasTexParameter(bool anti);
uint32 nextPOT(uint32 x);






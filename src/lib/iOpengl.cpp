#include "iOpengl.h"

#include "iStd.h"

void initOpenGL()
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND_SRC);// ios, mac, window

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glShadeModel(GL_SMOOTH);

	glFrontFace(GL_CCW);// GL_GW
	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	setAntiAliasTexParameter(true);
	setGlBlend(iBlendAlpha);
	setRGBA(1, 1, 1, 1);
}

void reshapeOpenGL()
{
	// viewport
	glViewport(viewport.origin.x, viewport.origin.y, viewport.size.width, viewport.size.height);

	// devSize
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, devSize.width, devSize.height, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static iBlend currBlend;
iBlend getGlBlend()
{
	return currBlend;
}

void setGlBlend(iBlend blend)
{
	currBlend = blend;
	switch( blend ) {
	default: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
	}
}

typedef struct _xTexParms {
	GLuint minFilter;
	GLuint magFilter;
	GLuint wrapS;
	GLuint wrapT;
} xTexParms;

static xTexParms _texParms = { GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };

void setAntiAliasTexParameter(bool anti)
{
	if( anti )
		_texParms.minFilter = _texParms.magFilter = GL_LINEAR;
	else
		_texParms.minFilter = _texParms.magFilter = GL_NEAREST;
}

void applyTexParameters()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _texParms.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _texParms.magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _texParms.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _texParms.wrapT);
}

// 2배수로 바꾸는 비트 연산
uint32 nextPOT(uint32 x)
{
	x = x - 1;
	x = x | (x >>  1);
	x = x | (x >>  2);
	x = x | (x >>  4);
	x = x | (x >>  8);
	x = x | (x >> 16);
	return x + 1;
}






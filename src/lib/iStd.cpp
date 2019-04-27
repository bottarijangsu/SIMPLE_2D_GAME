#include "iStd.h"

iSize monitorSize;
iSize wndSize;
iSize devSize;
iRect viewport;

ULONG_PTR gpToken;

static float _r, _g, _b, _a;

DWORD prevTickCount;

bool keys[256];
static uint32 keyDown;
static uint32 keyStat;

void loadLib(iSize devSize)
{
	GdiplusStartupInput gpInput;
	GdiplusStartup(&gpToken, &gpInput, NULL);

	_r = _g = _b = _a = 0.0f;

	prevTickCount = GetTickCount();

	memset(keys, 0x00, sizeof(bool)*256);
	keyDown = 0;
	keyStat = 0;
}

void freeLib()
{
	GdiplusShutdown(gpToken);
}

void drawLib(void* hdc, DRAW_METHOD method)
{
	DWORD c = GetTickCount();
	float dt = (c-prevTickCount)/1000.0f;
	prevTickCount = c;

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	method(dt);// drawGame
	glFlush();

	void drawCursor();
	drawCursor();

	keyDown = 0;
}

void _keyLib(uint32& key, iKeyState stat, int c)
{
	if( stat==iKeyStateBegan )
	{
		if( c==VK_LEFT || c==0x41 )
			key |= keyboard_left;
		else if( c==VK_RIGHT || c==0x44 )
			key |= keyboard_right;
		else if( c==VK_UP || c== 0x57 )
			key |= keyboard_top;
		else if( c==VK_DOWN || c==0x53 )
			key |= keyboard_bottom;
		else if( c==VK_RETURN )
			key |= keyboard_return;
		else if( c==VK_SPACE )
			key |= keyboard_space;
	}
	else if( stat==iKeyStateEnded )
	{
		if( c==VK_LEFT || c==0x41 )
			key &= ~keyboard_left;
		else if( c==VK_RIGHT || c==0x44 )
			key &= ~keyboard_right;
		else if( c==VK_UP || c== 0x57 )
			key &= ~keyboard_top;
		else if( c==VK_DOWN || c==0x53 )
			key &= ~keyboard_bottom;
		else if( c==VK_RETURN )
			key &= ~keyboard_return;
		else if( c==VK_SPACE )
			key &= ~keyboard_space;
	}
}

void keyLib(iKeyState stat, int c)
{
	if( stat==iKeyStateBegan )
	{
		if( keys[c]==false )
			_keyLib(keyDown, stat, c);

		keys[c] = true;
	}
	else if( stat==iKeyStateEnded )
	{
		keys[c] = false;
	}
	_keyLib(keyStat, stat, c);
}

uint32 getKeyDown() { return keyDown; }
uint32 getKeyStat() { return keyStat; }

void setRGBA(float r, float g, float b, float a)
{
	_r = r;	_g = g;	_b = b;	_a = a;
	glColor4f(r, g, b, a);
}

void getRGBA(float& r, float& g, float& b, float& a)
{
	r = _r;	g = _g; b = _b; a = _a;
}

void setAlpha(float a) { _a = a; };
float getAlpha() { return _a; }
void setRGB(float r, float g, float b)
{
	_r = r;	_g = g;	_b = b;
	glColor4f(r, g, b, _a);
}
void getRGB(float& r, float& g, float& b)
{
	r = _r;	g = _g; b = _b;
}

void setDotSize(float size)
{
	glPointSize(size);
}

void drawDot(int x, int y)
{
	iPoint p = iPointMake(x,y);
	glVertexPointer(2, GL_FLOAT, 0, &p);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_POINTS, 0, 1);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawDot(iPoint p)
{
	glVertexPointer(2, GL_FLOAT, 0, &p);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_POINTS, 0, 1);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawDots(iPoint* p, int pNum)
{
	glVertexPointer(2, GL_FLOAT, 0, p);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_POINTS, 0, pNum);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void setLineWidth(float width)
{
	glLineWidth(width);
}

void setLineSmooth(bool enable)
{
	if( enable )
		glEnable(GL_LINE_SMOOTH);
	else
		glDisable(GL_LINE_SMOOTH);
}

void drawLine(iPoint sp, iPoint ep)
{
	iPoint p[2] = {sp, ep};
	glVertexPointer(2, GL_FLOAT, 0, p);
	glEnableClientState(GL_VERTEX_ARRAY);

	iColor4f c[2] = { {0.847f,0.451f,0.451f,1.0f}, {0.847f,0.451f,0.451f,1.0f} };
	glColorPointer(4, GL_FLOAT, 0, c);
	glEnableClientState(GL_COLOR_ARRAY);

	glDrawArrays(GL_LINES, 0, 2);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void drawLine(int sx, int sy, int ex, int ey)
{
	iPoint p[2] = {{(float)sx, (float)sy}, {(float)ex, (float)ey}};
	glVertexPointer(2, GL_FLOAT, 0, p);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_LINES, 0, 2);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawRect(iRect rect)
{
	iPoint p[4];
	p[0] = rect.origin;
	p[1] = iPointMake(rect.origin.x+rect.size.width, rect.origin.y);
	p[2] = iPointMake(rect.origin.x+rect.size.width, rect.origin.y+rect.size.height);
	p[3] = iPointMake(rect.origin.x, rect.origin.y+rect.size.height);
	drawPoly(p, 4, false);
}

void drawRect(int x, int y, int width, int height, int radius)
{
	iPoint p[4];
	p[0] = iPointMake(x, 		y);
	p[1] = iPointMake(x+width,	y);
	p[2] = iPointMake(x+width,	y+height);
	p[3] = iPointMake(x, 		y+height);
	drawPoly(p, 4, false);
}

void fillRect(iRect rect)
{
	iPoint p[4];
	p[0] = rect.origin;
	p[1] = iPointMake(rect.origin.x+rect.size.width, rect.origin.y);
	p[2] = iPointMake(rect.origin.x+rect.size.width, rect.origin.y+rect.size.height);
	p[3] = iPointMake(rect.origin.x, rect.origin.y+rect.size.height);
	drawPoly(p, 4, true);
}

void fillRect(int x, int y, int width, int height, int radius)
{
	iPoint p[4];
	p[0] = iPointMake(x, 		y);
	p[1] = iPointMake(x+width,	y);
	p[2] = iPointMake(x+width,	y+height);
	p[3] = iPointMake(x, 		y+height);
	drawPoly(p, 4, true);
}

void drawPoly(iPoint* p, int pNum, bool fill)
{
	glVertexPointer(2, GL_FLOAT, 0, p);
	glEnableClientState(GL_VERTEX_ARRAY);

	if( fill )
		glDrawArrays(GL_TRIANGLE_FAN, 0, pNum);
	else
		glDrawArrays(GL_LINE_LOOP, 0, pNum);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void setClip(float x, float y, float dx, float dy)
{
	if( x==0 && y==0 && dx==0 && dy==0 )
	{
		glDisable(GL_SCISSOR_TEST);
	}
	else
	{
		float r0 = viewport.size.width / devSize.width;
		float r1 = viewport.size.height / devSize.height;
		glScissor(	viewport.origin.x + x*r0,
					viewport.origin.y + (devSize.height-y-dy)*r1,
					dx*r0, dy*r1);

		glEnable(GL_SCISSOR_TEST);
	}
}

wchar_t* utf8_to_utf16(const char* str);
Texture* createImage(const char* szFormat, ...)
{
	va_list args;
	va_start(args, szFormat);

	char szText[1024];
	_vsnprintf(szText, sizeof(szText), szFormat, args);

	va_end(args);

	wchar_t* path = utf8_to_utf16(szText);
	Bitmap* bmp = Bitmap::FromFile(path, false);
	free( path );
	if( bmp==NULL )
	{
		printf("createImage(%s) null\n", szText);
		return NULL;
	}

	uint32 width, height;
	uint8* rgba = iGraphics::bmp2rgba(bmp, width, height);
	delete bmp;

	Texture* tex = createImageWidthRGBA(rgba, width, height);
	free( rgba );

	return tex;
}

void freeImage(Texture* tex)
{
	if( tex->retainCount>1 )
	{
		tex->retainCount--;
		return;
	}
	glDeleteTextures(1, &tex->texID);
	free( tex );
}

void drawImage(Texture* tex,
		float x, float y,
		float ix, float iy, float idx, float idy,// src
		float rateX, float rateY,
		int xyz, int degree,
		int anc, int reverse)
{
	float	_x = ix / tex->potWidth,
			_y = iy / tex->potHeight,
			_dx = (ix+idx) / tex->potWidth,
			_dy = (iy+idy) / tex->potHeight,
			tmp;
	// 0, 0		1,0
	// 0, 1		1,1
	float coordinate[] = {	_x, _y,		_dx, _y,
							_x, _dy,	_dx, _dy };
	if( reverse==REVERSE_NONE ) {}
	else if( reverse==REVERSE_WIDTH )
	{
		tmp = coordinate[0];
		coordinate[0] = coordinate[2];
		coordinate[2] = tmp;

		tmp = coordinate[4];
		coordinate[4] = coordinate[6];
		coordinate[6] = tmp;
	}
	else if( reverse==REVERSE_HEIGHT )
	{
		tmp = coordinate[1];
		coordinate[1] = coordinate[3];
		coordinate[3] = tmp;

		tmp = coordinate[5];
		coordinate[5] = coordinate[7];
		coordinate[7] = tmp;
	}

	idx = idx * rateX;
	idy = idy * rateY;

	switch( anc ) {
	case TOP|LEFT:									break;
	case TOP|HCENTER:		x -= idx/2;				break;
	case TOP|RIGHT:			x -= idx;				break;
	case VCENTER|LEFT:					y -= idy/2;	break;
	case VCENTER|HCENTER:	x -= idx/2;	y -= idy/2;	break;
	case VCENTER|RIGHT:		x -= idx;	y -= idy/2;	break;
	case BOTTOM|LEFT:					y -= idy;	break;
	case BOTTOM|HCENTER:	x -= idx/2;	y -= idy;	break;
	case BOTTOM|RIGHT:		x -= idx;	y -= idy;	break; }

	float vertices[] = {	x, y,			x + idx, y,
							x, y + idy,		x + idx, y + idy };

	glPushMatrix();// 현재 매트릭스 백업
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, tex->texID);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, coordinate);

	if( degree > 0 )
	{
		_x = x + idx/2;
		_y = y + idx/2;
		vertices[0] -= _x; vertices[1] -= _y;	vertices[2] -= _x; vertices[3] -= _y;
		vertices[4] -= _x; vertices[5] -= _y;	vertices[6] -= _x; vertices[7] -= _y;

		glTranslatef(_x, _y, 0);
		int r[] = {0, 0, 0}; r[xyz] = 1;
		glRotatef(degree, r[0], r[1], r[2]);
	}

	iBlend prevBlend = getGlBlend();
	if( prevBlend==iBlendAlpha )
	{
		setGlBlend(iBlendAlpha);
		glColor4f(1, 1, 1, getAlpha());
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	else if( prevBlend==iBlendColor )
	{
		setGlBlend(iBlendAlpha);
		float r, g, b, a;
		getRGBA(r, g, b, a);
		glColor4f(r, g, b, a);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	else if( prevBlend==iBlendSolid )
	{
		setGlBlend(iBlendAlpha);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
		iColor4f c;
		getRGBA(c.r, c.g, c.b, c.a);
		glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, (float*)&c);
		glColor4f(c.r, c.g, c.b, c.a);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND_SRC);
	}
	setGlBlend(prevBlend);

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPopMatrix();
}

void drawImage(Texture* tex, int x, int y, int anc)
{
	drawImage(tex, x, y,
			0, 0, tex->width, tex->height,
			1.0f, 1.0f,
			2, 0, anc);
}

void drawImage(Texture* tex, int x, int y, int width, int height, int anc)
{
	drawImage(tex, x, y,
			0, 0, tex->width, tex->height,
			1.0f*width/tex->width, 1.0f*height/tex->height,
			2, 0, anc);
}

void randomize()
{
	srand(time(NULL));
}

int random()
{
	return rand();
}

float _sin(float degree)
{
	return sin(degree * M_PI/180);
}
float _cos(float degree)
{
	return cos(degree * M_PI/180);
}

float linear(float rate, float start, float end)
{
	return (1-rate)*start + rate*end;
}

float easeIn(float rate, float start, float end)
{
	return linear(_sin(rate*90), start, end);
}

float easeOut(float rate, float start, float end)
{
	return linear(1-_sin(90+rate*90), start, end);
}
float easeInOut(float rate, float start, float end)
{
	if( rate<0.5f )
		return easeIn(rate*2, start, (start+end)/2);
	return easeOut((rate-0.5f)*2, (start+end)/2, end);
}

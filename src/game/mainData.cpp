#include "mainData.h"
#include "iStd.h"

////////////////////////////////
// NUMBER
////////////////////////////////
Texture* NUMBER_0_TEXTURE()
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	int width = 64;
	int height = 128;
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//AREA LINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width, size.height / 8, 0);
		g->fillRect(0, 0, size.width / 4, size.height, 0);
		g->fillRect(size.width - size.width / 4, 0, size.width / 4, size.height,
				0);
		g->fillRect(0, size.height - size.height / 8, size.width,
				size.height / 8, 0);
		tex = g->getTexture();
	}
	return tex;
}
Texture* NUMBER_1_TEXTURE()
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	int width = 64;
	int height = 128;
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//AREA LINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width / 2, size.height / 8, 0);
		g->fillRect(size.width / 2 - size.width / 8, 0, size.width / 4,
				size.height, 0);
		g->fillRect(0, size.height - size.height / 8, size.width,
				size.height / 8, 0);
		tex = g->getTexture();
	}
	return tex;
}
Texture* NUMBER_2_TEXTURE()
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	int width = 64;
	int height = 128;
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//AREA LINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width, size.height / 8, 0);
		g->fillRect(size.width - size.width / 4, 0, size.width / 4,
				size.height / 2, 0);
		g->fillRect(0, size.height / 2 - size.height / 16, size.width,
				size.height / 8, 0);
		g->fillRect(0, size.height / 2 - size.height / 16, size.width / 4,
				size.height / 2, 0);
		g->fillRect(0, size.height - size.height / 8, size.width,
				size.height / 8, 0);
		tex = g->getTexture();
	}
	return tex;
}
Texture* NUMBER_3_TEXTURE()
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	int width = 64;
	int height = 128;
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//AREA LINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width, size.height / 8, 0);
		g->fillRect(size.width - size.width / 4, 0, size.width / 4, size.height,
				0);
		g->fillRect(0, size.height / 2, size.width, size.height / 8, 0);
		g->fillRect(0, size.height - size.height / 8, size.width,
				size.height / 8, 0);
		tex = g->getTexture();
	}
	return tex;
}
Texture* NUMBER_4_TEXTURE()
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	int width = 64;
	int height = 128;
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//AREA LINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width / 4, size.height / 2, 0);
		g->fillRect(0, size.height / 2, size.width, size.height / 8, 0);
		g->fillRect(size.width / 2, 0, size.width / 4, size.height, 0);

		tex = g->getTexture();
	}
	return tex;
}
Texture* NUMBER_5_TEXTURE()
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	int width = 64;
	int height = 128;
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//AREA LINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width, size.height / 8, 0);
		g->fillRect(0, 0, size.width / 4, size.height / 2, 0);
		g->fillRect(0, size.height / 2 - size.height / 16, size.width,
				size.height / 8, 0);
		g->fillRect(size.width - size.width / 4, size.height / 2,
				size.width / 4, size.height / 2, 0);
		g->fillRect(0, size.height - size.height / 8, size.width,
				size.height / 8, 0);
		tex = g->getTexture();
	}
	return tex;
}
Texture* NUMBER_6_TEXTURE()
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	int width = 64;
	int height = 128;
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//AREA LINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width / 4, size.height, 0);
		g->fillRect(0, size.height / 2 - size.height / 16, size.width,
				size.height / 8, 0);
		g->fillRect(size.width - size.width / 4, size.height / 2,
				size.width / 4, size.height / 2, 0);
		g->fillRect(0, size.height - size.height / 8, size.width,
				size.height / 8, 0);
		tex = g->getTexture();
	}
	return tex;
}
Texture* NUMBER_7_TEXTURE()
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	int width = 64;
	int height = 128;
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//AREA LINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width, size.height / 8, 0);
		g->fillRect(size.width - size.width / 4, 0, size.width / 4, size.height,
				0);
		tex = g->getTexture();
	}
	return tex;
}
Texture* NUMBER_8_TEXTURE()
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	int width = 64;
	int height = 128;
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//AREA LINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width, size.height / 8, 0);
		g->fillRect(0, 0, size.width / 4, size.height, 0);
		g->fillRect(0, size.height / 2 - size.height / 16, size.width,
				size.height / 8, 0);
		g->fillRect(size.width - size.width / 4, 0, size.width / 4, size.height,
				0);
		g->fillRect(0, size.height - size.height / 8, size.width,
				size.height / 8, 0);
		tex = g->getTexture();
	}
	return tex;
}
Texture* NUMBER_9_TEXTURE()
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	int width = 64;
	int height = 128;
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//AREA LINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width, size.height / 8, 0);
		g->fillRect(0, 0, size.width / 4, size.height / 2, 0);
		g->fillRect(0, size.height / 2 - size.height / 16, size.width,
				size.height / 8, 0);
		g->fillRect(size.width - size.width / 4, 0, size.width / 4, size.height,
				0);

		tex = g->getTexture();
	}
	return tex;
}

////////////////////////////////
// BG
////////////////////////////////
Texture* BG_STAGE()
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	int radius = 1024;
	int anchor = 64;
	iSize size = iSizeMake(radius, radius);
	{
		g->init(size);
		//AREA LINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(anchor, anchor, size.width - anchor * 2,
				size.height - anchor * 2, size.width - anchor * 2,
				size.width - anchor * 2, size.width - anchor * 2,
				size.width - anchor * 2);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(anchor + 8, anchor + 8, size.width - anchor * 2 - 16,
				size.width - anchor * 2 - 16, size.width - anchor * 2 - 16,
				size.width - anchor * 2 - 16, size.width - anchor * 2 - 16,
				size.width - anchor * 2 - 16);

		//DOT SIZE=64+16
		iPoint middleP = iPointMake(devSize.width / 2, devSize.height / 2);
		iPoint basicDot = iPointMake(devSize.width / 2, anchor);

		for (int i = 0; i < 12; i++)
		{
			iPoint rotateDot = iPointRotate(basicDot, middleP, i * 30);
			setRGBA(FLAT_COLOR_GREY, 1.0f);
			g->fillRect(rotateDot.x - 40, rotateDot.y - 40, 80, 80, 80, 80, 80,
					80);
			setRGBA(FLAT_COLOR_WHITE, 1.0f);
			g->fillRect(rotateDot.x - 40 + 8, rotateDot.y - 40 + 8, 80 - 16,
					80 - 16, 80 - 16, 80 - 16, 80 - 16, 80 - 16);
		}

		tex = g->getTexture();
	}
	return tex;
}

////////////////////////////////
// PLAYER
////////////////////////////////
iImage* PLAYER_SPRITE(int TopLeft, int TopRight, int BottomLeft,
		int BottomRight)
{
	iImage* img;
	Texture* tex;
	float width = PLAYER_WIDTH, height = PLAYER_HEIGHT;

	img = new iImage();
	iGraphics* g = iGraphics::share();
	//BODY
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		setRGBA(FLAT_COLOR_BLACK, 1.0f);
		g->fillRect(0, 0, size.width, size.height, TopLeft, TopRight,
				BottomRight, BottomLeft);

		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		TopLeft = (TopLeft - 16) * TopLeft / size.width;
		TopRight = (TopRight - 16) * TopRight / size.width;
		BottomRight = (BottomRight - 16) * BottomRight / size.width;
		BottomLeft = (BottomLeft - 16) * BottomLeft / size.width;
		g->fillRect(8, 8, size.width - 16, size.height - 16, TopLeft, TopRight,
				BottomRight, BottomLeft);
		tex = g->getTexture();
	}
	img->addObject(tex);
	freeImage(tex);

	return img;
}

////////////////////////////////
// ENEMY
////////////////////////////////
iImage* ENEMY_SPRITE()
{
	iImage* img;
	Texture* tex;
	float width = ENEMY_WIDTH, height = ENEMY_HEIGHT;

	img = new iImage();
	iGraphics* g = iGraphics::share();
	//BODY
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(0, 0, size.width, size.height, width, width, width, width);
		tex = g->getTexture();
	}
	img->addObject(tex);
	freeImage(tex);

	return img;
}

Texture* ENEMY_TEX(float width, float height)
{
	Texture* tex;
	iGraphics* g = iGraphics::share();
	//BODY
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(0, 0, size.width, size.height, width, width, width, width);
		tex = g->getTexture();
	}
	return tex;
}

EnemyData enemyInfo[12] =
{
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, },
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, },
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, },
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, },
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, },
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, },
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, },
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, },
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, },
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, },
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, },
{ EnemyStyle_8by8_line, 64, 0.5f, 1.0f,
iPointZero, }, };

////////////////////////////////
// BULLET
////////////////////////////////
Texture* BULLET_TEX()
{
	Texture* tex;
	float width = 16, height = 16;

	iGraphics* g = iGraphics::share();

	//BULLET
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		setRGBA(FLAT_COLOR_BLACK, 1.0f);
		g->fillRect(0, 0, size.width, size.height, 16, 16, 16, 16);
		tex = g->getTexture();
	}

	return tex;
}

////////////////////////////////
// ITEM
////////////////////////////////
Texture* ITEM_TEX()
{
	Texture* tex;
	float width = 64, height = 64;

	iGraphics* g = iGraphics::share();

	//ITEM
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		setRGBA(FLAT_COLOR_BLACK, 1.0f);
		g->fillRect(0, 0, size.width, size.height, 0, 0, 0, 0);
		setRGBA(FLAT_COLOR_BLUE, 1.0f);
		g->fillRect(8, 8, size.width - 16, size.height - 16, 0, 0, 0, 0);
		tex = g->getTexture();
	}

	return tex;
}

////////////////////////////////
// TRAIL
////////////////////////////////
Texture* TRAIL_TEX(int rate)
{

	Texture* tex;
	float width = rate, height = rate;

	iGraphics* g = iGraphics::share();

	//TRAIL
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(0, 0, size.width, size.height, 0, 0, 0, 0);
		tex = g->getTexture();
	}

	return tex;
}

////////////////////////////////
// ICON
////////////////////////////////
Texture* TITLE_ICON()
{
	Texture* tex;
	float width = 128, height = 128;
	iGraphics* g = iGraphics::share();

	//ICON
	iSize size = iSizeMake(width * 4, height);
	{
		g->init(size);
		//W
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, width, height, width / 2, width / 2, width / 2,
				width / 2);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(8, 8, width - 16, height - 16, (width - 16) / 2,
				(width - 16) / 2, (width - 16) / 2, (width - 16) / 2);

		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(32, 32, width / 16, height - 64, 0);
		g->fillRect(width / 2 - (width / 16) / 2, 32, width / 16, height - 64,
				0);
		g->fillRect(width - 32 - (width / 16), 32, width / 16, height - 64, 0);
		g->fillRect(32, height - 32 - 8, width - 64, height / 8, 0);

		//O
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(width, 0, width, height, width / 2, width / 2, width / 2,
				width / 2);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(width + 8, 8, width - 16, height - 16, (width - 16) / 2,
				(width - 16) / 2, (width - 16) / 2, (width - 16) / 2);

		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(width + 32, 32, width - 64, height / 8, 0);
		g->fillRect(width + 32, 32, width / 16, height - 64, 0);
		g->fillRect(width + width - 32 - (width / 16), 32, width / 16,
				height - 64, 0);
		g->fillRect(width + 32, height - 32 - 8, width - 64, height / 8, 0);

		//R
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(width * 2, 0, width, height, width / 2, width / 2,
				width / 2, width / 2);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(width * 2 + 8, 8, width - 16, height - 16, (width - 16) / 2,
				(width - 16) / 2, (width - 16) / 2, (width - 16) / 2);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(width * 2 + 32, 32, width / 16, height - 64, 0);
		g->fillRect(width * 2 + 32, 32, width - 64, height / 8, 0);
		g->fillRect(width * 2 + width - 32 - (width / 16), 32, width / 16,
				height / 2 - 32, 0);
		g->fillRect(width * 2 + 32, 56, width - 64, height / 8, 0);
		g->fillRect(width * 3 - 32 - (width / 16), 80, width / 16, 16, 0);
		g->fillRect(width * 2 + 32, 80, width - 64, height / 16, 0);

		//N
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(width * 3, 0, width, height, width / 2, width / 2,
				width / 2, width / 2);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(width * 3 + 8, 8, width - 16, height - 16, (width - 16) / 2,
				(width - 16) / 2, (width - 16) / 2, (width - 16) / 2);

		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(width * 3 + 32, 32, width / 16, height - 64, 0);
		g->fillRect(width * 3 + 32, 32, width - 64, height / 8, 0);
		g->fillRect(width * 4 - 32 - (width / 16), 32, width / 16, height - 64,
				0);

		tex = g->getTexture();
	}
	return tex;
}

Texture * UP_ARROW_ICON()
{
	Texture* tex;
	float width = 64, height = 64;

	iGraphics* g = iGraphics::share();

	//ICON
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width, size.height, width / 2, width / 2,
				width / 2, width / 2);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(4, 4, size.width - 8, size.height - 8, (width - 8) / 2,
				(width - 8) / 2, (width - 8) / 2, (width - 8) / 2);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(size.width / 2 - 4, size.height / 2 - 16, 8, 32, 0, 0, 0,
				0);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(size.width / 2 - 16, size.height / 4, 32, 16, 16, 16, 0, 0);

		tex = g->getTexture();
	}
	return tex;
}

Texture * DOWN_ARROW_ICON()
{
	Texture* tex;
	float width = 64, height = 64;

	iGraphics* g = iGraphics::share();

	//ICON
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width, size.height, width / 2, width / 2,
				width / 2, width / 2);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(4, 4, size.width - 8, size.height - 8, (width - 8) / 2,
				(width - 8) / 2, (width - 8) / 2, (width - 8) / 2);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(size.width / 2 - 4, size.height / 2 - 16, 8, 32, 0, 0, 0,
				0);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(size.width / 2 - 16, 3 * size.height / 4 - 16, 32, 16, 0, 0,
				16, 16);

		tex = g->getTexture();
	}
	return tex;
}

Texture * LEFT_ARROW_ICON()
{
	Texture* tex;
	float width = 64, height = 64;

	iGraphics* g = iGraphics::share();

	//ICON
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width, size.height, width / 2, width / 2,
				width / 2, width / 2);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(4, 4, size.width - 8, size.height - 8, (width - 8) / 2,
				(width - 8) / 2, (width - 8) / 2, (width - 8) / 2);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(size.width / 2 - 16, size.height / 2 - 4, 32, 8, 0, 0, 0,
				0);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(size.width / 4 - 0, size.height / 2 - 16, 16, 32, 16, 0, 0,
				16);

		tex = g->getTexture();
	}
	return tex;
}
Texture * RIGHT_ARROW_ICON()
{
	Texture* tex;
	float width = 64, height = 64;

	iGraphics* g = iGraphics::share();

	//ICON
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, size.width, size.height, width / 2, width / 2,
				width / 2, width / 2);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(4, 4, size.width - 8, size.height - 8, (width - 8) / 2,
				(width - 8) / 2, (width - 8) / 2, (width - 8) / 2);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(size.width / 2 - 16, size.height / 2 - 4, 32, 8, 0, 0, 0,
				0);
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(3 * size.width / 4 - 16, size.height / 2 - 16, 16, 32, 0,
				16, 16, 0);

		tex = g->getTexture();
	}
	return tex;
}

Texture* TOUCH_ICON()
{
	Texture* tex;
	float width = 128, height = 128;
	float circleW = 64, circleH = 64;

	iGraphics* g = iGraphics::share();

	//ICON
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//CIRCLE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(0, 0, circleW, circleH, circleW, circleW, circleW, circleW);
		setRGBA(FLAT_COLOR_WHITE, 1.0f);
		g->fillRect(4, 4, circleW - 8, circleH - 8, (circleH - 8),
				(circleH - 8), (circleH - 8), (circleH - 8));

		//HAND_OUTLINE
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(circleW / 2 - 8, 32, 16, 64, 16, 16, 0, 0);
		g->fillRect(circleW / 2 - 8 + 16, 64, 16, 32, 16, 16, 0, 0);
		g->fillRect(circleW / 2 - 8 + 32, 64, 16, 32, 16, 16, 0, 0);
		g->fillRect(circleW / 2 - 8 + 48, 64, 16, 32, 16, 16, 0, 0);
		g->fillRect(circleW / 2 - 8, 96, 64, 32, 0, 0, 32, 32);

		tex = g->getTexture();
	}
	return tex;
}

Texture* INTERACT_ICON()
{
	Texture* tex;
	float width = 96, height = 96; //32
	float boxW = 64, boxH = 64;

	iGraphics* g = iGraphics::share();

	//ICON
	iSize size = iSizeMake(width, height);
	{
		g->init(size);
		//BOX
		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(width / 2 - 32, 0, boxW, boxH, 0);
//		setRGBA(FLAT_COLOR_WHITE, 1.0f);
//		g->fillRect(width/2-32+4, 4, boxW - 8, boxH - 8, 0);

		setRGBA(FLAT_COLOR_GREY, 1.0f);
		g->fillRect(width / 2 - 32, boxH + 4, boxW, 8, 0);
		g->fillRect(width / 2 - 32 + 8, boxH + 4 + 8 + 4, boxW - 16, 4, 0);
		g->fillRect(width / 2 - 32 + 16, boxH + 4 + 8 + 4 + 8, boxW - 32, 2, 0);

		tex = g->getTexture();
	}
	return tex;
}

////////////////////////////////
// CURSOR
////////////////////////////////
Texture* MOUSE_CURSOR()
{
	Texture* tex;
	float width = 16, height = 16;

	iGraphics* g = iGraphics::share();

	//ICON
	iSize size = iSizeMake(width, height);
	{
		g->init(size);

		g->init(size);
		setRGBA(FLAT_COLOR_BLACK, 1.0f);
		g->fillRect(0, 0, size.width, size.height, width);

		tex = g->getTexture();
	}
	return tex;
}

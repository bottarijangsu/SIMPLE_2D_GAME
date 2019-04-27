#include "iPopup.h"

#include "iStd.h"

iPopup::iPopup(iPopupStyle style)
{
	imgList = new iArray(cbFree);

	this->style = style;
	bShow = false;
	stat = iPopupStatClose;
	openPoint = closePoint = iPointZero;

	_aniDt = iPopup_aniDt;
	aniDt = 0.0f;

	selected = -1;

	parm = this;
	methodOpen = NULL;
	methodClose = NULL;
	methodPaintBefore = NULL;
	methodPaintAfter = NULL;
}

iPopup::~iPopup()
{
	delete imgList;
}

void iPopup::cbFree(void* parm)
{
	iImage* img = (iImage*)parm;
	delete img;
}

void iPopup::addObject(iImage* img)
{
	imgList->addObject(img);
}

void iPopup::show(bool show)
{
	if( show )
	{
		if( stat!=iPopupStatClose )
			return;
		stat = iPopupStatOpen;
		bShow = true;
		aniDt = 0.0f;
	}
	else
	{
		if( stat!=iPopupStatProc )
			return;
		stat = iPopupStatClose;

		aniDt = 0.0f;
	}
}

void iPopup::setup(iPoint open, iPoint close)
{
	openPoint = open;
	closePoint = close;
}

void iPopup::paint(float dt)
{
	if( bShow==false )
		return;

	iPoint position;
	float alpha;
	float scale;

	if( style==iPopupStyleNone )
	{
		position = closePoint;
		scale = 1.0f;
		if( stat==iPopupStatOpen )
		{
			alpha = aniDt/_aniDt;

			aniDt += dt;
			if( aniDt>_aniDt )
			{
				stat = iPopupStatProc;
				if( methodOpen )
					methodOpen( parm );
			}
		}
		else if( stat==iPopupStatProc )
		{
			alpha = 1.0f;
		}
		else if( stat==iPopupStatClose )
		{
			alpha = 1 - aniDt/_aniDt;

			aniDt += dt;
			if( aniDt>_aniDt )
			{
				bShow = false;
				if( methodClose )
					methodClose( parm );
			}
		}
	}
	else if( style==iPopupStyleMove )
	{
		alpha = 1.0f;
		scale = 1.0f;
		if( stat==iPopupStatOpen )
		{
			float r = aniDt/_aniDt;
			position = openPoint * (1-r) + closePoint * r;

			aniDt += dt;
			if( aniDt>_aniDt )
			{
				stat = iPopupStatProc;
				if( methodOpen )
					methodOpen( parm );
			}
		}
		else if( stat==iPopupStatProc )
		{
			position = closePoint;
		}
		else if( stat==iPopupStatClose )
		{
			float r = aniDt/_aniDt;
			position = openPoint * r + closePoint * (1-r);

			aniDt += dt;
			if( aniDt>_aniDt )
			{
				bShow = false;
				if( methodClose )
					methodClose( parm );
			}
		}
	}
	else if( style==iPopupStyleZoom )
	{
		alpha = 1.0f;
		if( stat==iPopupStatOpen )
		{
			float r = aniDt/_aniDt;
			position = openPoint * (1-r) + closePoint * r;
			scale = r;

			aniDt += dt;
			if( aniDt>_aniDt )
			{
				stat = iPopupStatProc;
				if( methodOpen )
					methodOpen( parm );
			}
		}
		else if( stat==iPopupStatProc )
		{
			position = closePoint;
			scale = 1.0f;
		}
		else if( stat==iPopupStatClose )
		{
			float r = aniDt/_aniDt;
			position = openPoint * r + closePoint * (1-r);
			scale = 1 - r;

			aniDt += dt;
			if( aniDt>_aniDt )
			{
				bShow = false;
				if( methodClose )
					methodClose( parm );
			}
		}
	}

	float _alpha = getAlpha();
	if( methodPaintBefore )
		methodPaintBefore( parm, position, scale, alpha, dt );
	setAlpha(alpha);

	for(int i=0; i<imgList->count; i++)
	{
		iImage* img = (iImage*)imgList->getObjectAtIndex(i);
		Texture* tex = img->tex;
		iPoint p = position + img->position * scale;
		int xyz = 0, degree = 0;
		if( img->leftRight==1 )
		{
			xyz = 1;
			degree = 180;
		}
		drawImage(tex, p.x, p.y,
				0, 0, tex->width, tex->height,
				scale, scale,
				xyz, degree, TOP|LEFT);
		img->update(dt);
	}

	if( methodPaintAfter )
		methodPaintAfter( parm, position, scale, alpha, dt );

	setAlpha(_alpha);
}








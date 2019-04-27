#include "iImage.h"

#include "iStd.h"

iImage::iImage()
{
	imgList = new iArray(cbFree);
	imgIndex = 0;
	tex = NULL;
	position = iPointZero;
	leftRight = 0;

	selected = false;
	selectedSize = _selectedSize;
	selectedDt = _selectedDt;

	animation = false;
	_intervalDt = _ani_intervalDt;
	repeatNum = _repeatNum = 0;
	intervalDt = 0.0f;
	lastTex = false;
	methodAnimation = NULL;
}

iImage::~iImage()
{
	delete imgList;
}

void iImage::cbFree(void* parm)
{
	Texture* tex = (Texture*)parm;
	freeImage(tex);
}

iImage* iImage::copy()
{
	iImage* img = new iImage();

	iArray* a = img->imgList;
	memcpy(img, this, sizeof(iImage));
	img->imgList = a;

	for(int i=0; i<imgList->count; i++)
		img->addObject( getTexAtIndex(i) );

	return img;
}

void iImage::addObject(Texture* tex)
{
	imgList->addObject(tex);
	tex->retainCount++;

	if( this->tex==NULL )
		this->tex = tex;
}

void iImage::setTexAtIndex(int index)
{
	Texture* tex = (Texture*)imgList->getObjectAtIndex(index);
	if( tex )
	{
		this->tex = tex;
		imgIndex = index;
	}
}

Texture* iImage::getTexAtIndex(int index)
{
	return (Texture*)imgList->getObjectAtIndex(index);
}

iRect iImage::touchRect(iPoint point)
{
	iPoint p = position + point;
	return iRectMake(p.x, p.y, tex->width, tex->height);
}

void iImage::startAnimation(iImage_Method method)
{
	animation = true;
	intervalDt = 0;
	repeatNum = 0;

	setTexAtIndex(0);
}

void iImage::stopAnimation(bool init)
{
	animation = false;
	if( init )
	{
		intervalDt = 0;
		repeatNum = 0;

		setTexAtIndex(0);
	}
}

void iImage::paint(float dt, iPoint off,float scale,float deg, int anc)
{
	if( tex==NULL )
		return;

	iPoint p = position + off;
	float rx, ry;
	if( selected )
	{
		if( selectedDt < _selectedDt )
		{
			selectedDt += dt;
			if( selectedDt > _selectedDt )
				selectedDt = _selectedDt;
		}
	}
	else
	{
		if( selectedDt > 0.0f )
		{
			selectedDt -= dt;
			if( selectedDt < 0.0f )
				selectedDt = 0.0f;
		}
	}
	rx =
	ry = linear(selectedDt/_selectedDt, 1.0f, _selectedSize);
	p.x += (1-rx)/2*tex->width;
	p.y += (1-ry)/2*tex->height;

	drawImage(tex, p.x, p.y,
			0, 0, tex->width, tex->height,
			rx * scale, ry * scale,
			2, deg, anc, leftRight);

	update(dt);
}

void iImage::update(float dt)
{
	if( animation==false )
		return;

	intervalDt += dt;
	while( intervalDt > _intervalDt )
	{
		intervalDt -= _intervalDt;

		int ii = imgIndex + 1;
		if( ii > imgList->count-1 )
		{
			if( _repeatNum==0 )
			{
				ii = 0;
			}
			else
			{
				if( lastTex==false )
					ii = 0;

				repeatNum++;
				if( repeatNum==_repeatNum )
				{
					animation = false;

					if( methodAnimation )
						methodAnimation( this );
				}
			}
		}
		setTexAtIndex(ii);
	}
}



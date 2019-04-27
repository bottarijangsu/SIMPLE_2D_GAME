#pragma once

#include "iGraphics.h"
#include "iType.h"
#include "iImage.h"

typedef enum _iPopupStyle {
	iPopupStyleNone = 0,
	iPopupStyleMove,
	iPopupStyleZoom,
} iPopupStyle;

typedef enum _iPopupStat {
	iPopupStatOpen = 0,
	iPopupStatProc,
	iPopupStatClose,
} iPopupStat;

typedef void (*IPOPUP_CB_METHOD)(void* parm);
typedef void (*IPOPUP_PAINT_METHOD)(void* parm, iPoint point, float scale, float alpha, float dt);

class iPopup
{
public:
	iPopup(iPopupStyle style=iPopupStyleNone);
	virtual ~iPopup();

	static void cbFree(void* parm);

public:
	void addObject(iImage* img);
	void show(bool show);
	void setup(iPoint open, iPoint close);

	void paint(float dt);

public:
	iArray* imgList;

	iPopupStyle style;
	bool bShow;
	iPopupStat stat;
	iPoint openPoint, closePoint;
	float aniDt, _aniDt;

	int8 selected;

	void* parm;
	IPOPUP_CB_METHOD methodOpen;
	IPOPUP_CB_METHOD methodClose;
	IPOPUP_PAINT_METHOD methodPaintBefore;
	IPOPUP_PAINT_METHOD methodPaintAfter;
};

#define iPopup_aniDt 0.2f


#include "Main.h"
#include "iStd.h"
#include "mainData.h"

static Texture* texArea;

static float playDt;
void loadMain() {
	//mainDt
	playDt = 0.0;

	//BG
	texArea = BG_STAGE();

	//PLAYER
	player = new thisBot();
	player->position = iPointMake(devSize.width / 2, devSize.height / 2);

	//ITEM
	loadItem();

	//BULLET
	loadBullet();

	//TRAIL
	loadTrail();

	//ENEMY
	loadEnemy(enemyInfo);

	//POP MENU
	createPopMenu();
	showPopMenu(true);

	//FONT
	f = new iFont();
}

void freeMain() {
	delete player;

	freeImage(texArea);

	freeEnemy();
	freeBullet();
	freeItem();
	freeTrail();
	freePopMenu();

	delete f;
}

void drawMain(float dt) {
	//DEFAULT_BG
	setRGBA(FLAT_COLOR_WHITE, 1.0f);
	fillRect(iRectMake(0, 0, devSize.width, devSize.height));

	drawImage(texArea, devSize.width / 2, devSize.height / 2,
	HCENTER | VCENTER);

	updateMain(dt);

	//POP
	drawPopMenu(dt);
}

static float itemDt = 0.0f;
void updateMain(float dt) {
	float _dt = dt;
	if (!player->isAlive) {
		dt = 0.0f;
		showPopMenu(true);
		f->drawString(devSize.width / 2, devSize.height / 2,
		VCENTER | HCENTER, 1.0f, "%.0f", playDt);
	} else {
		dt = _dt;
		showPopMenu(false);
		drawObject(dt);
	}
}

void drawObject(float dt) {
	playDt += dt;
	//TIME
	f->drawString(devSize.width / 2, devSize.height / 2, VCENTER | HCENTER,
			1.0f, "%.0f", playDt);

	//TRAIL
	drawTrail(dt);

	//ITEM_SET
	if (itemDt < 2.5f) {
		itemDt += dt;
		if (itemDt >= 2.5f) {
			int uN = 0; //0 or 1
			if (random() % 2 == 0)
				uN = -1;
			else
				uN = 1;
			int rX = random() % 272;
			if (random() % 2 == 0)
				uN = -1;
			else
				uN = 1;
			int rY = random() % 272;
			iPoint p = iPointMake(devSize.width / 2 + (rX * uN),
					devSize.height / 2 + (rY * uN));
			addItem(0, p);
			itemDt = 0.0f;
		}
	}

	//ITEM
	drawItem(dt);

	//BULLET
	drawBullet(dt);

	//ENEMY
	drawEnemy(dt);

	//PLAYER
	player->paint(dt);
}

void keyMain(iKeyState stat, iPoint point) {
	if (keyPopMenu(stat, point))
		return;

	switch (stat) {
	case iKeyStateBegan:

		break;

	case iKeyStateMoved:

		break;

	case iKeyStateEnded:

		break;

	default:
		break;
	}
}

//////////////////////////////////////
// MENU POPUP
//////////////////////////////////////
iPopup* popMenu;

void drawPopMenuBefore(void* parm, iPoint point, float scale, float alpha,
		float dt);
void createPopMenu() {
	iImage* img;
	Texture* tex;

	iPopup* pop = new iPopup(iPopupStyleNone);

	iSize size = iSizeMake(devSize.width, devSize.height);

	//INTERACT__UI
	tex = TITLE_ICON();
	img = new iImage();
	img->addObject(tex);
	freeImage(tex);
	img->position = iPointMake(size.width / 2 - 256, 1 * size.height / 4 - 64);
	pop->addObject(img);

	//TOUCH_TO_START_UI
	tex = TOUCH_ICON();
	img = new iImage();
	img->addObject(tex);
	freeImage(tex);
	img->position = iPointMake(size.width / 2 - 256, 3 * size.height / 4 - 64);
	pop->addObject(img);

	//KEY_UI
	//LEFT_ARROW
	tex = LEFT_ARROW_ICON();
	img = new iImage();
	img->addObject(tex);
	freeImage(tex);
	img->position = iPointMake(size.width / 2 - 128 - 6,
			3 * size.height / 4 - 32);
	pop->addObject(img);

	//UP_ARROW
	tex = UP_ARROW_ICON();
	img = new iImage();
	img->addObject(tex);
	freeImage(tex);
	img->position = iPointMake(size.width / 2 - 64 - 2,
			3 * size.height / 4 - 32);
	pop->addObject(img);

	//DOWN_ARROW
	tex = DOWN_ARROW_ICON();
	img = new iImage();
	img->addObject(tex);
	freeImage(tex);
	img->position = iPointMake(size.width / 2 + 0 + 2,
			3 * size.height / 4 - 32);
	pop->addObject(img);

	//RIGHT_ARROW
	tex = RIGHT_ARROW_ICON();
	img = new iImage();
	img->addObject(tex);
	freeImage(tex);
	img->position = iPointMake(size.width / 2 + 64 + 6,
			3 * size.height / 4 - 32);
	pop->addObject(img);

	//INTERACT__UI
	tex = INTERACT_ICON();
	img = new iImage();
	img->addObject(tex);
	freeImage(tex);
	img->position = iPointMake(size.width / 2 + 128 + 20,
			3 * size.height / 4 - 48);
	pop->addObject(img);

	pop->methodPaintBefore = drawPopMenuBefore;
	pop->setup(iPointZero, iPointZero);
	popMenu = pop;
}

void freePopMenu() {
	delete popMenu;
}

void showPopMenu(bool show) {
	popMenu->show(show);
}

void drawPopMenu(float dt) {
	popMenu->paint(dt);
}

void drawPopMenuBefore(void* parm, iPoint point, float scale, float alpha,
		float dt) {

}

bool keyPopMenu(iKeyState stat, iPoint point) {
	switch (stat) {
	case iKeyStateBegan:
		if (!player->isAlive) {
			playDt = 0.0f;
			itemDt = 0.0f;

			//PLAYER
			player = new thisBot();
			player->position = iPointMake(devSize.width / 2,
					devSize.height / 2);

			//BULLET
			loadBullet();

			//ITEM
			loadItem();

			//TRAIL
			loadTrail();

			//ENEMY
			loadEnemy(enemyInfo);

			player->isAlive = true;
		}
		break;

	case iKeyStateMoved:

		break;

	case iKeyStateEnded:

		break;

	default:
		break;
	}
	return false;
}

//////////////////////////////////////////////////////
// iFont
//////////////////////////////////////////////////////
iFont* f;

iFont::iFont() {
	texs = (Texture**) calloc(sizeof(Texture*), 256);

	gap = 4;	//1.0f;

#if 1
	Texture* (*m[10])() = {
		NUMBER_0_TEXTURE,
		NUMBER_1_TEXTURE,
		NUMBER_2_TEXTURE,
		NUMBER_3_TEXTURE,
		NUMBER_4_TEXTURE,
		NUMBER_5_TEXTURE,
		NUMBER_6_TEXTURE,
		NUMBER_7_TEXTURE,
		NUMBER_8_TEXTURE,
		NUMBER_9_TEXTURE,
	};
	for (int i = 0; i < 10; i++)
		texs['0' + i] = m[i]();
#endif
}

iFont::~iFont() {
	for (int i = 0; i < 256; i++) {
		if (texs[i])
			freeImage(texs[i]);
	}
	free(texs);
}

iSize iFont::sizeOfString(float rate, const char* szFormat, ...) {
	va_list args;
	va_start(args, szFormat);

	char szText[1024];
	_vsnprintf(szText, sizeof(szText), szFormat, args);

	va_end(args);

	Texture* tex = NULL;
	int i, j, len = strlen(szText);
	float x = 0.0f;
	for (i = 0; i < len; i++) {
		j = szText[i];
		tex = texs[j];

		if (tex == NULL)
			continue;

		x += (tex->width + gap) * rate;
	}

	return iSizeMake(x, tex->height);
}

void iFont::drawString(float x, float y, int anc, float rate,
		const char* szFormat, ...) {
	va_list args;
	va_start(args, szFormat);

	char szText[1024];
	_vsnprintf(szText, sizeof(szText), szFormat, args);

	va_end(args);

	iSize size = sizeOfString(rate, szText);
	switch (anc) {
	case TOP | LEFT:
		break;
	case TOP | HCENTER:
		x -= size.width / 2;
		break;
	case TOP | RIGHT:
		x -= size.width;
		break;
	case VCENTER | LEFT:
		y -= size.height / 2;
		break;
	case VCENTER | HCENTER:
		x -= size.width / 2;
		y -= size.height / 2;
		break;
	case VCENTER | RIGHT:
		x -= size.width;
		y -= size.height / 2;
		break;
	case BOTTOM | LEFT:
		y -= size.height;
		break;
	case BOTTOM | HCENTER:
		x -= size.width / 2;
		y -= size.height;
		break;
	case BOTTOM | RIGHT:
		x -= size.width;
		y -= size.height;
		break;
	}

	Texture* tex;
	int i, j, len = strlen(szText);
	for (i = 0; i < len; i++) {
		j = szText[i];
		tex = texs[j];
#if 1
		if (tex == NULL)
			continue;
#endif
		drawImage(tex, x, y, 0, 0, tex->width, tex->height, rate, rate, 2, 0,
		TOP | LEFT);
		x += (tex->width + gap) * rate;
	}
}

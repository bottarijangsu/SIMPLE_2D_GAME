#include"mainItem.h"
#include "mainObject.h"

static Texture* texItem;

struct Item;
typedef void (*METHOD_ITEM_PATTERN)(float dt, Item* i, iPoint position);

struct Item {
	bool paint(float dt) {
		iPoint p = position;
		method(dt, this, p);

		p = position;
		if (p.x < -8 || p.x > devSize.width + 8 || p.y < -8
				|| p.y > devSize.height + 8) {
			alive = false;
			return true;
		}

		if (lifeDt < 6.0f) {
			lifeDt += dt;
			if (lifeDt >= 6.0f) {
				alive = false;
				lifeDt = 0.0f;
				return true;
			}
		}

		return false;
	}

	bool meet() {
		if (iPointDistance(position, player->position)
				< player->health / 2 + 64) {
			int degree = iPointAngle(iPointMake(1, 0), iPointZero,
					position - player->position);
			switch (degree / 90) {
			case 0: // top-right
				if (player->TopRight > 0) {
					player->TopRight -= 16;
					if (player->health < 64)
						player->health += 2;
				}
				break;
			case 1: // top-left
				if (player->TopLeft > 0) {
					player->TopLeft -= 16;
					if (player->health < 64)
						player->health += 2;
				}
				break;
			case 2: // bottom-left
				if (player->BottomLeft > 0) {
					player->BottomLeft -= 16;
					if (player->health < 64)
						player->health += 2;
				}
				break;
			case 3: // bottom_right
				if (player->BottomRight > 0) {
					player->BottomRight -= 16;
					if (player->health < 64)
						player->health += 2;
				}
				break;
			}
			delete player->sprite;
			player->sprite = PLAYER_SPRITE(player->TopLeft, player->TopRight,
					player->BottomLeft, player->BottomRight);
			alive = false;
			return true;
		}
		return false;
	}

	bool alive;
	iPoint position;
	int angle;
	float dt, lifeDt;
	METHOD_ITEM_PATTERN method;
};

#define patternNum 1
void itemPatternRandom(float dt, Item* b, iPoint p);

static METHOD_ITEM_PATTERN methodPattern[patternNum] = { itemPatternRandom, };

Item** _item;
Item** item;

#define _itemNum 10
int itemNum;

void loadItem() {
	int i, j;

	texItem = ITEM_TEX();
	_item = (Item**) calloc(sizeof(Item*), patternNum);
	for (i = 0; i < 2; i++) {
		_item[i] = (Item*) calloc(sizeof(Item), _itemNum);
		for (j = 0; j < _itemNum; j++)
			_item[i][j].method = methodPattern[i];
	}

	item = (Item**) malloc(sizeof(Item*) * _itemNum * patternNum);
	itemNum = 0;
}

void freeItem() {
	freeImage(texItem);
	for (int i = 0; i < patternNum; i++)
		free(_item[i]);
	free(_item);
	free(item);
}

void drawItem(float dt) {

	for (int i = 0; i < itemNum; i++) {
		if (item[i]->alive == false || item[i]->paint(dt) || item[i]->meet()) {
			itemNum--;
			item[i] = item[itemNum];
			i--;
		}
	}

}

void addItem(int index, iPoint point) {
	if (index)
		index = 0;

	for (int i = 0; i < _itemNum; i++) {
		Item* b = &_item[index][i];
		if (b->alive == false) {
			b->alive = true;
			b->position = point;
			b->dt = 0.0f;
			b->lifeDt = 0.0f;
			b->angle = 0;

			item[itemNum] = b;
			itemNum++;
			return;
		}
	}
}

void itemPatternRandom(float dt, Item* b, iPoint p) {
	if (b->angle == 360) {
		b->angle = 0;
	}

	if (b->dt < 0.1f) {
		b->dt += dt;
		if (b->dt >= 0.1f) {
			b->angle += 15;
			b->dt = 0.0f;
		}
	}

	drawImage(texItem, p.x, p.y, 0, 0, texItem->width, texItem->height, 1.0f,
			1.0f, 2, b->angle, VCENTER | HCENTER);
}

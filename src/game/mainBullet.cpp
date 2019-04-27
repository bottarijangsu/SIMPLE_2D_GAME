#include "mainBullet.h"

#include "mainObject.h"

////////////////////////////////
// BULLET
////////////////////////////////
static Texture* texBullet;

struct Bullet;
typedef void (*METHOD_BULLET_PATTERN)(float dt, Bullet* b, iPoint position);

struct Bullet {
	bool paint(float dt) {
		iPoint p = position;
		method(dt, this, p);

		p = position;
		if (p.x < -8 || p.x > devSize.width + 8 || p.y < -8
				|| p.y > devSize.height + 8) {
			alive = false;
			return true;
		}

		return false;
	}

	bool meet() {

		if (iPointDistance(position, player->position)
				< player->health / 2 + 16) {
			int degree = iPointAngle(iPointMake(1, 0), iPointZero,
					position - player->position);
			switch (degree / 90) {
			case 0: // top-right
				if (player->TopRight < 64) {
					player->TopRight += 16;
					if (player->health > 0)
						player->health -= 2;
				}
				break;
			case 1: // top-left
				if (player->TopLeft < 64) {
					player->TopLeft += 16;
					if (player->health > 0)
						player->health -= 2;
				}
				break;
			case 2: // bottom-left
				if (player->BottomLeft < 64) {
					player->BottomLeft += 16;
					if (player->health > 0)
						player->health -= 2;
				}
				break;
			case 3: // bottom_right
				if (player->BottomRight < 64) {
					player->BottomRight += 16;
					if (player->health > 0)
						player->health -= 2;
				}
				break;
			}
			delete player->sprite;
			player->sprite = PLAYER_SPRITE(player->TopLeft, player->TopRight,
					player->BottomLeft, player->BottomRight);
			player->sprite->selected = true;
			alive = false;
			return true;
		}

		if (iPointDistance(position,
				iPointMake(devSize.width / 2, devSize.height / 2)) > 512 - 64) {
			alive = false;
			return true;
		}

		return false;
	}

	bool alive;
	iPoint position, prevPosition;
	iPoint vector;
	float degree;
	float dt;
	void* attObj;
	METHOD_BULLET_PATTERN method;
};

#define patternNum 2
void bulletPatternLine(float dt, Bullet* b, iPoint position);
void bulletPatternCurve(float dt, Bullet* b, iPoint position);

static METHOD_BULLET_PATTERN methodPattern[patternNum] = { bulletPatternLine,
		bulletPatternCurve };

Bullet** _bullet;
Bullet** bullet;

#define _bulletNum 1000
int bulletNum;

void loadBullet() {
	int i, j;

	texBullet = BULLET_TEX();
	_bullet = (Bullet**) calloc(sizeof(Bullet*), patternNum);
	for (i = 0; i < 2; i++) {
		_bullet[i] = (Bullet*) calloc(sizeof(Bullet), _bulletNum);
		for (j = 0; j < _bulletNum; j++)
			_bullet[i][j].method = methodPattern[i];
	}

	bullet = (Bullet**) malloc(sizeof(Bullet*) * _bulletNum * patternNum);
	bulletNum = 0;
}

void freeBullet() {
	freeImage(texBullet);
	for (int i = 0; i < patternNum; i++)
		free(_bullet[i]);
	free(_bullet);
	free(bullet);
}

void drawBullet(float dt) {

	for (int i = 0; i < bulletNum; i++) {
		if (bullet[i]->paint(dt) || bullet[i]->meet()) {
			bulletNum--;

			bullet[i] = bullet[bulletNum];

			i--;
		}
	}
}

void addBullet(int index, iPoint sp, iPoint ep, void* attObj) {
	if (index)
		index = 0;

	for (int i = 0; i < _bulletNum; i++) {
		Bullet* b = &_bullet[index][i];
		if (b->alive == false) {
			b->alive = true;
			b->position = sp;
			iPoint v = ep - sp;
			b->vector = v / iPointLength(v);
			b->degree = 360 - iPointAngle(iPointMake(1, 0), iPointZero, v);
			b->prevPosition = sp;
			b->dt = 0.0f;
			b->attObj = attObj;

			bullet[bulletNum] = b;
			bulletNum++;
			return;
		}
	}
}

void bulletPatternLine(float dt, Bullet* b, iPoint p) {
	drawImage(texBullet, p.x, p.y, 0, 0, texBullet->width, texBullet->height,
			1.0f, 1.0f, 2, b->degree, VCENTER | HCENTER);

	b->position += b->vector * (256 * dt);
}

#define curve_dt 0.7f
void bulletPatternCurve(float dt, Bullet* b, iPoint p) {
	drawImage(texBullet, p.x, p.y, 0, 0, texBullet->width, texBullet->height,
			1.0f, 1.0f, 2, 0, VCENTER | HCENTER);

	b->position = b->prevPosition;
	b->position += b->vector * (256 * dt);
	b->prevPosition = b->position;

	if (b->dt < curve_dt) {
		b->position.x -= 80 * _sin(180 * b->dt / curve_dt);

		b->dt += dt;
	}
}

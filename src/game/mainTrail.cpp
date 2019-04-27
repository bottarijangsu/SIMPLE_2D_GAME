#include "mainTrail.h"
#include "mainObject.h"

static Texture* texTrail;

struct Trail;
typedef void (*METHOD_TRAIL_PATTERN)(float dt, Trail* b, iPoint position);

struct Trail {
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

		return false;
	}

	bool alive;
	iPoint position;
	float dt, scale;
	METHOD_TRAIL_PATTERN method;
};

#define patternNum 1
void trailPatternLine(float dt, Trail* b, iPoint position);

static METHOD_TRAIL_PATTERN methodPattern[patternNum] = { trailPatternLine, };

Trail** _trail;
Trail** trail;

#define _trailNum 1000
int trailNum;

void loadTrail() {
	int i, j;

	texTrail = TRAIL_TEX(64);
	_trail = (Trail**) calloc(sizeof(Trail*), patternNum);
	for (i = 0; i < 2; i++) {
		_trail[i] = (Trail*) calloc(sizeof(Trail), _trailNum);
		for (j = 0; j < _trailNum; j++)
			_trail[i][j].method = methodPattern[i];
	}

	trail = (Trail**) malloc(sizeof(Trail*) * _trailNum * patternNum);
	trailNum = 0;
}

void freeTrail() {
	freeImage(texTrail);
	for (int i = 0; i < patternNum; i++)
		free(_trail[i]);
	free(_trail);
	free(trail);
}
void drawTrail(float dt) {
	setGlBlend(iBlendColor);
	setRGBA(FLAT_COLOR_RED, 1);

	for (int i = 0; i < trailNum; i++) {
		if (trail[i]->alive==false || trail[i]->paint(dt) || trail[i]->meet()) {
			trailNum--;
			trail[i] = trail[trailNum];
			i--;
		}
	}

	setGlBlend(iBlendAlpha);
	setRGBA(FLAT_COLOR_WHITE, 1);
}

void addTrail(int index, iPoint point) {
	if (index)
		index = 0;

	for (int i = 0; i < _trailNum; i++) {
		Trail* b = &_trail[index][i];
		if (b->alive == false) {
			b->alive = true;
			b->position = point;
			b->dt = 0.0f;
			b->scale = (1+random()%100)/100.f;

			trail[trailNum] = b;
			trailNum++;
			return;
		}
	}
}

#define trail_dt 0.5f
void trailPatternLine(float dt, Trail* b, iPoint p) {
	drawImage(texTrail, p.x, p.y, 0, 0, texTrail->width, texTrail->height, b->scale,
			b->scale, 2, 0, VCENTER | HCENTER);
	if (b->dt < trail_dt) {
		b->dt += dt;
	}else
	{
		b->alive = false;
	}
}

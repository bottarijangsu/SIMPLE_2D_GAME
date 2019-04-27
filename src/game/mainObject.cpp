#include "mainObject.h"
#include "iStd.h"

////////////////////////////////
// PLAYER
////////////////////////////////
thisBot* player;

thisBot::thisBot() {
	position = iPointZero;
	v = iPointZero;

	TopLeft = 0;
	TopRight = 0;
	BottomLeft = 0;
	BottomRight = 0;

	sprite = new iImage();
	sprite = PLAYER_SPRITE(TopLeft, TopRight, BottomLeft, BottomRight);
	isAlive = false;

	health = 8 * 4;
	aniDt=0.0f;
}

thisBot::~thisBot() {
	delete sprite;
}

#define key_mask 15// keyboard_left|keyboard_right|keyboard_top|keyboard_bottom

void thisBot::paint(float dt) {
	update(dt);

	//DEBUG
//	drawLine(iPointMake(devSize.width / 2, devSize.height / 2),
//			player->position);

	if (sprite->selected) {
		if (aniDt < 0.25f) {
			aniDt += dt;
			setGlBlend(iBlendColor);
			setRGBA(FLAT_COLOR_RED, 1.0f);
			if(aniDt>= 0.25f)
			{
				setGlBlend(iBlendColor);
				setRGBA(FLAT_COLOR_WHITE, 1.0f);
				aniDt=0.0f;
				sprite->selected=false;
			}
		}
	}

	sprite->position = iPointMake(position.x, position.y);
	sprite->paint(dt, iPointZero, 1.0f, 0, VCENTER | HCENTER);

	setGlBlend(iBlendAlpha);
	setRGBA(FLAT_COLOR_WHITE, 1);

	if (getKeyStat() & keyboard_left) {
		if (!isAlive && health > 0)
			isAlive = true;
		addTrail(0, position);
		v.x -= dt;
		if (v.x < -1)
			v.x = -1;
	} else if (getKeyStat() & keyboard_right) {
		if (!isAlive && health > 0)
			isAlive = true;
		addTrail(0, position);
		v.x += dt;
		if (v.x > 1)
			v.x = 1;
	} else {
		if (v.x < 0) {
			addTrail(0, position);
			v.x += dt;
			if (v.x > 0)
				v.x = 0;
		} else if (v.x > 0) {
			addTrail(0, position);
			v.x -= dt;
			if (v.x < 0)
				v.x = 0;
		}
	}

	if (getKeyStat() & keyboard_top) {
		if (!isAlive && health > 0)
			isAlive = true;
		addTrail(0, position);
		v.y -= dt;
		if (v.y < -1)
			v.y = -1;
	} else if (getKeyStat() & keyboard_bottom) {
		if (!isAlive && health > 0)
			isAlive = true;
		addTrail(0, position);
		v.y += dt;
		if (v.y > 1)
			v.y = 1;
	} else {
		if (v.y < 0) {
			addTrail(0, position);
			v.y += dt;
			if (v.y > 0)
				v.y = 0;
		} else if (v.y > 0) {
			addTrail(0, position);
			v.y -= dt;
			if (v.x < 0)
				v.y = 0;
		}
	}

	if (v != iPointZero) {
		position += v * 300 * dt;

		iPoint c = iPointMake(devSize.width / 2, devSize.height / 2);
		float d = 256 + 64 + 32 + 16;
		float distance = iPointDistance(position, c);
		if (distance > d) {
			iPoint v = (position - c) / distance;
			position = c + v * d;
		}
	}

}

void thisBot::update(float dt) {

	if (health == 0) {
		isAlive = false;
	}

}

bool thisBot::key(iKeyState stat, iPoint point) {

	switch (stat) {
	case iKeyStateBegan:

		break;

	case iKeyStateMoved:

		break;

	case iKeyStateEnded:
		sprite->selected = false;
		break;

	default:
		break;
	}
	return true;
}

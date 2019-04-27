#pragma once

#include "iStd.h"
#include "mainData.h"

#include "mainEnemy.h"
#include "mainBullet.h"
#include "mainTrail.h"
#include "mainItem.h"

////////////////////////////////
// PLAYER
////////////////////////////////
class thisBot{
public:
	thisBot();
	virtual ~thisBot();

public:
	void paint(float dt);
	void update(float dt);
	bool key(iKeyState stat, iPoint point);

public:
	iImage* sprite;
	iPoint position, v;
	int health;
	bool isAlive;
	float aniDt;

	int TopLeft, TopRight, BottomLeft, BottomRight;
};

extern thisBot* player;

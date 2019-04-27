#pragma once
#include "iStd.h"

void loadBullet();
void freeBullet();
void drawBullet(float dt);

void addBullet(int index, iPoint sp, iPoint ep, void* attObj);

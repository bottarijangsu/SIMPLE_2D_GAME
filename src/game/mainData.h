#pragma once

#include "iStd.h"

////////////////////////////////
// COLOR DEFINE
////////////////////////////////
#define FLAT_COLOR_WHITE 0.984f,0.98f,0.976f
#define FLAT_COLOR_BLACK 0.339f,0.339f,0.339f
//#define FLAT_COLOR_BLACK 0.098f,0.098f,0.094f
#define FLAT_COLOR_GREY 0.678f, 0.678f, 0.686f
#define FLAT_COLOR_RED 0.847f,0.451f,0.451f
#define FLAT_COLOR_BLUE 0.337f, 0.522f, 0.698f

////////////////////////////////
// NUMBER
////////////////////////////////
Texture* NUMBER_0_TEXTURE();
Texture* NUMBER_1_TEXTURE();
Texture* NUMBER_2_TEXTURE();
Texture* NUMBER_3_TEXTURE();
Texture* NUMBER_4_TEXTURE();
Texture* NUMBER_5_TEXTURE();
Texture* NUMBER_6_TEXTURE();
Texture* NUMBER_7_TEXTURE();
Texture* NUMBER_8_TEXTURE();
Texture* NUMBER_9_TEXTURE();

////////////////////////////////
// BG
////////////////////////////////
Texture* BG_STAGE();

////////////////////////////////
// PLAYER
////////////////////////////////
#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 64
iImage* PLAYER_SPRITE(int TopLeft=0, int TopRight=0, int BottomLeft=0, int BottomRight=0);

////////////////////////////////
// ENEMY
////////////////////////////////
#define ENEMY_WIDTH 64
#define ENEMY_HEIGHT 64
iImage* ENEMY_SPRITE();
Texture* ENEMY_TEX(float width, float height);

typedef enum _EnemyStyle{
	EnemyStyle_none = -1,
	EnemyStyle_8by8_line = 0,
	EnemyStyle_8by8_spread,
}EnemyStyle;

typedef struct _EnemyData{
	EnemyStyle index;
	int health;
	float birthDt;
	float spawnDt;
	iPoint position;
}EnemyData;

extern EnemyData enemyInfo[12];

////////////////////////////////
// BULLET
////////////////////////////////
Texture* BULLET_TEX();

////////////////////////////////
// ITEM
////////////////////////////////
Texture* ITEM_TEX();

////////////////////////////////
// TRAIL
////////////////////////////////
Texture* TRAIL_TEX(int rate);

////////////////////////////////
// ICON
////////////////////////////////
Texture* UP_ARROW_ICON();
Texture* DOWN_ARROW_ICON();
Texture* LEFT_ARROW_ICON();
Texture* RIGHT_ARROW_ICON();

Texture* TITLE_ICON();
Texture* TOUCH_ICON();
Texture* INTERACT_ICON();

////////////////////////////////
// CURSOR
////////////////////////////////
Texture* MOUSE_CURSOR();

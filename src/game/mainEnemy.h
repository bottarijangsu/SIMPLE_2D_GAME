#pragma once
#include "iStd.h"
#include "mainData.h"

struct Enemy;
typedef void (*METHOD_ENEMY_AI)(Enemy* e, float dt);

struct Enemy{
	bool paint(float dt);

	Texture* tex;
	iPoint position;
	int health;
	bool active;
	float fireDt;
	float spawnDt, birthDt;

	METHOD_ENEMY_AI method;
};

extern Enemy** _enemy;
extern Enemy** enemy;
extern int enemyNum, _enemyNum;
extern iPoint enemySpawnPoint[12];

void loadEnemy(EnemyData* ed);
void freeEnemy();
void drawEnemy(float dt);

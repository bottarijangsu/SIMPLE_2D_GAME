#include "mainEnemy.h"
#include "mainObject.h"

void methodAI__8by8__LINE(Enemy* e, float dt);
void methodAI__8by8__SPREAD(Enemy* e, float dt);

METHOD_ENEMY_AI methodAI[3] =
{ methodAI__8by8__LINE, methodAI__8by8__SPREAD,};

static Texture* texEnemy;
bool Enemy::paint(float dt)
{
	if (active == false)
	{
		if (birthDt < spawnDt)
		{
			birthDt += dt;
			if (birthDt >= spawnDt)
			{
				active = true;
				birthDt = 0.0f;
			}
		}
		return false;
	}
	//ENEMY DRAW
	method(this, dt);

	return false;
}

Enemy** _enemy;
Enemy** enemy;
int enemyNum, _enemyNum;
iPoint enemySpawnPoint[12];
void loadEnemy(EnemyData* ed)
{
	int i;
	int anchor = 64;
	iPoint middleP = iPointMake(devSize.width / 2, devSize.height / 2);
	iPoint basicDot = iPointMake(devSize.width / 2, anchor);
	for (i = 0; i < 12; i++)
	{
		enemySpawnPoint[i] = iPointRotate(basicDot, middleP, i * 30);
	}

	_enemyNum = enemyNum = 12;

	_enemy = (Enemy**) malloc(sizeof(Enemy*) * _enemyNum);
	enemy = (Enemy**) malloc(sizeof(Enemy*) * enemyNum);

	for (i = 0; i < _enemyNum; i++)
	{
		Enemy* e = new Enemy();
		e->health = ed[i].health;
		e->tex = ENEMY_TEX(ed[i].health, ed[i].health);
		e->active = false;
		e->position = enemySpawnPoint[i];
		e->method = methodAI[random() % 2];
		e->fireDt = 0.0f;
		e->spawnDt = ed[i].birthDt;
		e->birthDt = 0.0f;

		_enemy[i] = enemy[i] = e;
	}
}
void freeEnemy()
{
	freeImage(texEnemy);
	for (int i = 0; i < _enemyNum; i++)
		delete _enemy[i];
	free(_enemy);
	free(enemy);
}

void drawEnemy(float dt)
{
	setGlBlend(iBlendColor);
	setRGBA(FLAT_COLOR_BLACK, 1);

	for (int i = 0; i < enemyNum; i++)
	{
		if (enemy[i]->paint(dt))
		{
			enemyNum--;

			enemy[i] = enemy[enemyNum];

			i--;
		}
	}

	setGlBlend(iBlendAlpha);
	setRGBA(FLAT_COLOR_WHITE, 1);
}

void methodAI__8by8__LINE(Enemy* e, float dt)
{
	iPoint targetP = player->position;
	if (e->active)
	{
		if (e->fireDt < 1.5f)
		{
			e->fireDt += dt;
		}
		else
		{
			if (e->health > 0)
			{
				addBullet(0, e->position, targetP, e);
				e->health -= 8;
			}
			else
			{
				e->active = false;
				e->method = methodAI[random() % 2];
				e->health = 8 * 8;
			}
			e->fireDt = 0.0f;
		}
	}
	drawImage(e->tex, e->position.x, e->position.y, 0, 0, e->tex->width,
			e->tex->height, e->health / 64.0f, e->health / 64.0f, 2, 0,
			VCENTER | HCENTER);

}

void methodAI__8by8__SPREAD(Enemy* e, float dt)
{
	iPoint anchorP = e->position;
	iPoint targetP = iPointMake(devSize.width / 2, devSize.height / 2);

	if (e->active)
	{
		if (e->fireDt < 3.0f)
		{
			e->fireDt += dt;
		}
		else
		{
			if (e->health > 0)
			{
				for (int i = 0; i < 4; i++)
				{
					addBullet(0, e->position,
							iPointRotate(anchorP, targetP, 135 + i * 30), e);
					e->health -= 8;
				}
			}
			else
			{
				e->active = false;
				e->method = methodAI[random() % 2];
				e->health = 8 * 8;
			}
			e->fireDt = 0.0f;
		}
	}
	drawImage(e->tex, e->position.x, e->position.y, 0, 0, e->tex->width,
			e->tex->height, e->health / 64.0f, e->health / 64.0f, 2, 0,
			VCENTER | HCENTER);
}

#pragma once

#include "iStd.h"

void loadGame();
void freeGame();
void drawGame(float dt);
void keyGame(iKeyState stat, iPoint point);

typedef enum _GameState {
	g_main =0,
} GameState;

extern GameState gameState;

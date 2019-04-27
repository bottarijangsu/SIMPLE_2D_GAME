#include "Game.h"

#include "Main.h"

GameState gameState;
void loadGame()
{
	loadMain();
	gameState = g_main;

}

void freeGame()
{
	switch( gameState ) {
	case g_main: freeMain(); break;
	}

}

void drawGame(float dt)
{

	switch( gameState ) {
	case g_main: drawMain(dt); break;
	}

}

void keyGame(iKeyState stat, iPoint point)
{
	switch( gameState ) {
	case g_main: keyMain(stat, point); break;
	}
}

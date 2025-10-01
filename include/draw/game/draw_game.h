#ifndef DRAW_GAME_H
#define DRAW_GAME_H

#include "game/grid.h"
#include "draw/button.h"

void DrawFinishedGame(GridInstance gridInstance, GlobalSettings *p_globalSettings, Images *p_images, GameState currentState, Button mainMenuButton);
void DrawGame(GridInstance gridInstance, GlobalSettings *p_globalSettings, Images *p_images, bool isFinished);
void DrawBackground(GlobalSettings *p_globalSettings, Images *p_images, bool isFinished);

#endif
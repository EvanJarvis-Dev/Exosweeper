#ifndef INPUT_GAME_H
#define INPUT_GAME_H

#include "raylib.h"

#include "game/settings.h"
#include "game/grid.h"
#include "draw/menu/menu.h"
#include "draw/button.h"

void ManageGameInput(GridInstance gridInstance, GameState *p_gameState, Audio *p_audio);
void ManageGameClick(GridInstance gridInstance, GameState *p_gameState, Audio *p_audio, int typeOfClick);

void ManageFinishedInput(GameState *p_gameState, Audio *p_audio, Menu menu);
void ManageGameFinishClick(GameState *p_gameState, Audio *p_audio, Button button);

#endif
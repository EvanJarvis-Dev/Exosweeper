#ifndef INPUT_MENU_H
#define INPUT_MENU_H

#include "raylib.h"

#include "game/grid.h"
#include "draw/menu/menu.h"
#include "game/audio.h"
#include "draw/button.h"

void ManageMenuInput(GlobalSettings *p_globalSettings, GameState *p_currentState, Images *p_images, Audio *p_audio, Menu menu, GridInstance *p_gridInstance);
void ManageMenuClick(GlobalSettings *p_globalSettings, GameState *p_currentState, Images *p_images, Audio *p_audio, Menu menu, GridInstance *p_gridInstance);
void CheckAndChangeStateButton(GlobalSettings *p_globalSettings, GameState *p_currentState, Images *p_images, Audio *p_audio, Vector2 mousePos, PlayButton playButton, GridInstance *p_gridInstance);

#endif
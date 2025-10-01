#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "game/settings.h"
#include "draw/button.h"

typedef struct 
{
    Button button;
    int gridWidth;
    int gridHeight;
    int cryoCharges;
} PlayButton;

typedef struct
{
    PlayButton playButton1;
    PlayButton playButton2;
    PlayButton playButton3;
    Button mainMenuButton;
} Menu;

Menu InitialiseMenus(GlobalSettings *p_globalSettings);
void DrawMainMenu(GlobalSettings *p_globalSettings, Images *p_images, Menu menu);
void DrawMainMenuBackground(GlobalSettings *p_globalSettings, Images *p_images);

#endif
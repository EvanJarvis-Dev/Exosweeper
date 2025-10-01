#include "game/grid.h"
#include "game/settings.h"
#include "draw/menu/menu.h"
#include <stdlib.h>

Menu InitialiseMenus(GlobalSettings *p_globalSettings)
{
    Vector2 size = { 340, 100 };
    int centerX = p_globalSettings -> SCREEN_WIDTH / 2;
    int segmentChunk = p_globalSettings -> SCREEN_HEIGHT / 12;

    Vector2 position1 = { centerX, segmentChunk * 5 };
    PlayButton playButton1 = { { size, position1, PLAY_STATE }, 10, 10, 1 };

    Vector2 position2 = { centerX, segmentChunk * 7 };
    PlayButton playButton2 = { { size, position2, PLAY_STATE }, 15, 15, 2 };

    Vector2 position3 = { centerX, segmentChunk * 9 };
    PlayButton playButton3 = { { size, position3, PLAY_STATE }, 20, 20, 3 };

    Vector2 positionMenu = { (p_globalSettings -> SCREEN_WIDTH - p_globalSettings -> SCREEN_HEIGHT) / 2, (5 * 118) + 50 };
    Button buttonMenu = {size, positionMenu, MENU_STATE};

    Menu menu = {
        .playButton1 = playButton1,
        .playButton2 = playButton2,
        .playButton3 = playButton3,
        .mainMenuButton = buttonMenu
    };

    return menu;
}

void DrawMainMenu(GlobalSettings *p_globalSettings, Images *p_images, Menu menu)
{   
    DrawMainMenuBackground(p_globalSettings, p_images);

    char playButton1Text[] = "10 x 10";
    DrawButton(p_globalSettings, p_images, menu.playButton1.button, playButton1Text);

    char playButton2Text[] = "15 x 15";
    DrawButton(p_globalSettings, p_images, menu.playButton2.button, playButton2Text);

    char playButton3Text[] = "20 x 20";
    DrawButton(p_globalSettings, p_images, menu.playButton3.button, playButton3Text);
}

void DrawMainMenuBackground(GlobalSettings *p_globalSettings, Images *p_images)
{
    if (p_images -> mainMenuBackground.id == 0) return;

    Vector2 topLeft = {0, 0};

    Rectangle source = {0, 0, (float)p_images -> mainMenuBackground.width, (float)p_images -> mainMenuBackground.height};
    Rectangle dest = {0, 0, (float)p_globalSettings -> SCREEN_WIDTH, (float)p_globalSettings -> SCREEN_HEIGHT};

    DrawTexturePro(p_images -> mainMenuBackground, source, dest, topLeft, 0, WHITE);
}

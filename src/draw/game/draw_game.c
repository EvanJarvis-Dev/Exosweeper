#include "game/grid.h"
#include "draw/button.h"
#include "draw/game/draw_game.h"
#include "draw/game/draw_grid.h"
#include "draw/game/draw_ui.h"

void DrawFinishedGame(GridInstance gridInstance, GlobalSettings *p_globalSettings, Images *p_images, GameState currentState, Button mainMenuButton)
{
    DrawGame(gridInstance, p_globalSettings, p_images, true);
    char mainMenuText[] = "MAIN MENU";
    DrawButton(p_globalSettings, p_images, mainMenuButton, mainMenuText);

    if (currentState == SUCCESS_STATE)
    {
        char finishText[] = "SUCCESS!";
        DrawFinishText(p_globalSettings, finishText);
    }
    else if (currentState == FAIL_STATE)
    {
        char finishText[] = "MISSION FAILED...";
        DrawFinishText(p_globalSettings, finishText);
    }  
}

void DrawGame(GridInstance gridInstance, GlobalSettings *p_globalSettings, Images *p_images, bool isFinished)
{
    DrawBackground(p_globalSettings, p_images, isFinished);
    DrawUI(gridInstance, p_globalSettings);
    DrawMineGrid(gridInstance, p_globalSettings, p_images);
}

void DrawBackground(GlobalSettings *p_globalSettings, Images *p_images, bool isFinished)
{
    if (p_images -> mainMenuBackground.id == 0) return;

    Vector2 topLeft = {0, 0};
    if (isFinished)
    {
        Rectangle source = {0, 0, (float)(p_images -> gameBackgroundOn.width), (float)(p_images -> gameBackgroundOn.height)};
        Rectangle dest = {0, 0, (float)(p_globalSettings -> SCREEN_WIDTH), (float)(p_globalSettings -> SCREEN_HEIGHT)};

        DrawTexturePro(p_images -> gameBackgroundOn, source, dest, topLeft, 0, WHITE);
    }
    else
    {
        Rectangle source = {0, 0, (float)(p_images -> gameBackgroundOff.width), (float)(p_images -> gameBackgroundOff.height)};
        Rectangle dest = {0, 0, (float)(p_globalSettings -> SCREEN_WIDTH), (float)(p_globalSettings -> SCREEN_HEIGHT)};

        DrawTexturePro(p_images -> gameBackgroundOff, source, dest, topLeft, 0, WHITE);
    }
    
}
#include "game/grid.h"
#include "input/input_menu.h"
#include "game/audio.h"
#include "draw/menu/menu.h"


void ManageMenuInput(GlobalSettings *p_globalSettings, GameState *p_currentState, Images *p_images, Audio *p_audio, Menu menu, GridInstance *p_gridInstance)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ManageMenuClick(p_globalSettings, p_currentState, p_images, p_audio, menu, p_gridInstance);
    }

    if (*(p_currentState) == MENU_STATE && !IsMusicStreamPlaying(p_audio->menuTheme))
    {
        PlayMusic(p_audio, true);
    }
}

void ManageMenuClick(GlobalSettings *p_globalSettings, GameState *p_currentState, Images *p_images, Audio *p_audio, Menu menu, GridInstance *p_gridInstance)
{
    Vector2 mousePos = GetMousePosition();

    CheckAndChangeStateButton(p_globalSettings, p_currentState, p_images, p_audio, mousePos, menu.playButton1, p_gridInstance);
    CheckAndChangeStateButton(p_globalSettings, p_currentState, p_images, p_audio, mousePos, menu.playButton2, p_gridInstance);
    CheckAndChangeStateButton(p_globalSettings, p_currentState, p_images, p_audio, mousePos, menu.playButton3, p_gridInstance);
}

void CheckAndChangeStateButton(GlobalSettings *p_globalSettings, GameState *p_currentState, Images *p_images, Audio *p_audio, Vector2 mousePos, PlayButton playButton, GridInstance *p_gridInstance)
{
    if (IsPositionOverButton(playButton.button, mousePos))
    {
        PlaySound(p_audio->button); 
        PlayMusic(p_audio, false);

        *(p_currentState) = playButton.button.STATE_CHANGE;

        FreeGrid(p_gridInstance);
        *p_gridInstance = CreateGrid(*p_globalSettings, p_images, playButton.gridWidth, playButton.gridHeight, playButton.cryoCharges);
    }
}
#include "game/settings.h"
#include "game/audio.h"
#include "game/grid.h"
#include "game/cryo_stabiliser.h"
#include "input/input_game.h"
#include "draw/menu/menu.h"
#include "draw/button.h"

void ManageGameInput(GridInstance gridInstance, GameState *p_currentState, Audio *p_audio)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            ManageGameClick(gridInstance, p_currentState, p_audio, KEY_LEFT_SHIFT);
        }
        else
        {
            ManageGameClick(gridInstance, p_currentState, p_audio, MOUSE_BUTTON_LEFT);
        }
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        ManageGameClick(gridInstance, p_currentState, p_audio, MOUSE_BUTTON_RIGHT);
    }

    if (*(p_currentState) == PLAY_STATE && !IsMusicStreamPlaying(p_audio -> gameTheme))
    {
        PlayMusic(p_audio, false);
    }
}

void ManageGameClick(GridInstance gridInstance, GameState *p_currentState, Audio *p_audio, int typeOfClick)
{
    Vector2 mousePos = GetMousePosition();
    if (!IsValidPosition(gridInstance.gridData, mousePos))
    {
        ResetHighlight(gridInstance);
        return;
    }

    Vector2Int coordinates = GlobalPositionToCoordinate(gridInstance.gridData, mousePos);

    if (typeOfClick == MOUSE_BUTTON_LEFT)
    {
        HighlightSquare(gridInstance, coordinates);
        RevealMineSquare(gridInstance, p_audio, coordinates);
    }

    if (typeOfClick == MOUSE_BUTTON_RIGHT)
    {
        ToggleFlag(gridInstance, p_audio, coordinates);
    }

    if (typeOfClick == KEY_LEFT_SHIFT)
    {
        StabiliseMineSquare(gridInstance, p_audio, coordinates);
    }

    if (IsSuccessState(gridInstance))
    {
        *(p_currentState) = SUCCESS_STATE;
    }
    if (IsFailState(gridInstance))
    {
        *(p_currentState) = FAIL_STATE;
    }
}

void ManageFinishedInput(GameState *p_currentState, Audio *p_audio, Menu menu)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ManageGameFinishClick(p_currentState, p_audio, menu.mainMenuButton);
    }
}

void ManageGameFinishClick(GameState *p_currentState, Audio *p_audio, Button button)
{
    Vector2 mousePos = GetMousePosition();
    if (IsPositionOverButton(button, mousePos))
    {
        PlaySound(p_audio -> button); 
        PlayMusic(p_audio, true);
        *(p_currentState) = button.STATE_CHANGE;        
    }
}


#ifndef SETTINGS_H
#define SETTINGS_H

#include "raylib.h"
#include "draw/images.h"

typedef enum
{
    MENU_STATE,
    PLAY_STATE,
    SUCCESS_STATE,
    FAIL_STATE
} GameState; 

typedef struct
{
    const Color BACKGROUND_COLOUR;
    const Color FONT_COLOUR;
    const float FONT_SIZE;
    const float SPACING;
} UIStyle;

typedef struct
{
    Color mineTextColours[8];
    
    const Color GRID_LINE_COLOUR;
    const Color HIGHLIGHTED_GRID_LINE_COLOUR;
    const Color UNREVEALED_COLOUR;
    const Color REVEALED_COLOUR;
    const Color MINE_COLOUR;
    const Color FLAG_COLOUR;
    const Color FONT_COLOUR;

    const float MINE_FONT_SIZE;
} GameStyle;

typedef struct 
{
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    GameStyle gameStyle;
    UIStyle uiStyle;
    Font font;
    Font numberFont;
} GlobalSettings;

typedef struct 
{
    int x;
    int y;
} Vector2Int;

GlobalSettings CreateGlobalSettings();

#endif
#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "game/settings.h"

typedef struct 
{
    Vector2 size;
    Vector2 centre;
    int STATE_CHANGE;
} Button;

void DrawButton(GlobalSettings *p_globalSettings, Images *p_images, Button button, char *p_text);
bool IsPositionOverButton(Button button, Vector2 position);

#endif
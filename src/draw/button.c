#include "draw/button.h"
#include "raylib.h"
#include "game/settings.h"

void DrawButton(GlobalSettings *p_globalSettings, Images *p_images, Button button, char *p_text)
{    
    if (p_images -> button.id == 0) return;

    Rectangle source = {0, 0, (float)p_images -> button.width, (float)p_images -> button.height};
    Rectangle dest = {button.centre.x, button.centre.y, button.size.x, button.size.y};

    Vector2 localButtonCentre = {button.size.x / 2, button.size.y / 2};
    DrawTexturePro(p_images -> button, source, dest, localButtonCentre, 0, WHITE);
    
    Vector2 textSize = MeasureTextEx(p_globalSettings -> font, p_text, p_globalSettings -> uiStyle.FONT_SIZE, p_globalSettings -> uiStyle.SPACING);
    Vector2 origin = {textSize.x / 2, textSize.y / 2};
    DrawTextPro(p_globalSettings -> font, p_text, button.centre, origin, 0.0f, p_globalSettings -> uiStyle.FONT_SIZE, p_globalSettings -> uiStyle.SPACING, p_globalSettings -> uiStyle.FONT_COLOUR);
}

bool IsPositionOverButton(Button button, Vector2 position)
{
    return (position.x > button.centre.x - (button.size.x / 2) &&
        position.x < button.centre.x + (button.size.x / 2) &&
        position.y > button.centre.y - (button.size.y / 2) &&
        position.y < button.centre.y + (button.size.y / 2));
}
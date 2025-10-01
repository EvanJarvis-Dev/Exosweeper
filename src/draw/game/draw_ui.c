#include <stdio.h>
#include <string.h>
#include "draw/game/draw_ui.h"
#include "game/settings.h"
#include "game/grid.h"

void DrawUI(GridInstance gridInstance, GlobalSettings *p_globalSettings)
{
    DrawFlagsPlacedText(gridInstance, p_globalSettings);
    DrawTotalMinesText(gridInstance, p_globalSettings);
    DrawTotalChargesText(gridInstance, p_globalSettings);
    DrawTimerText(gridInstance, p_globalSettings);
}

void DrawFlagsPlacedText(GridInstance gridInstance, GlobalSettings *p_globalSettings)
{
    char flagsText[] = "MAGMA MARKED"; 
    Vector2 flagsPosition = {7*5, 58*5};
    DrawTextLeftAligned(p_globalSettings, flagsText, flagsPosition);


    char remainingText[50];
    sprintf(remainingText, "%d", GetFlagsPlaced(gridInstance));
    Vector2 remainingPosition = {98*5, 58*5};
    DrawTextCentred(p_globalSettings, remainingText, remainingPosition);
}

void DrawTotalMinesText(GridInstance gridInstance, GlobalSettings *p_globalSettings)
{
    char minesText[] = "MAGMA VEINS";
    Vector2 minesPosition = {7*5, 44*5};
    DrawTextLeftAligned(p_globalSettings, minesText, minesPosition);

    char remainingText[50];
    sprintf(remainingText, "%d", GetTotalAmountOfMines(gridInstance));
    Vector2 remainingPosition = {98*5, 44*5};
    DrawTextCentred(p_globalSettings, remainingText, remainingPosition);
}

void DrawTotalChargesText(GridInstance gridInstance, GlobalSettings *p_globalSettings)
{
    char cryoText[50] = "CRYO-STABILISER";
    Vector2 cryoPosition = {7*5, 72*5};
    DrawTextLeftAligned(p_globalSettings, cryoText, cryoPosition);

    char remainingText[50];
    sprintf(remainingText, "%d", *gridInstance.p_cryoCharges);
    Vector2 remainingPosition = {98*5, 72*5};
    DrawTextCentred(p_globalSettings, remainingText, remainingPosition);
}

void DrawTimerText(GridInstance gridInstance, GlobalSettings *p_globalSettings)
{
    char timerText[50] = "TIME";
    Vector2 timerPosition = {7*5, 86*5};
    DrawTextLeftAligned(p_globalSettings, timerText, timerPosition);

    char remainingText[50];
    sprintf(remainingText, "%d", GetGridTime(gridInstance.timer));
    Vector2 remainingPosition = {98*5, 86*5};
    DrawTextCentred(p_globalSettings, remainingText, remainingPosition);
}

void DrawFinishText(GlobalSettings *p_globalSettings, char text[])
{
    Vector2 position = {(p_globalSettings -> SCREEN_WIDTH - p_globalSettings -> SCREEN_HEIGHT) / 2, 107 * 5};
    DrawTextCentred(p_globalSettings, text, position);
}

void DrawTextCentred(GlobalSettings *p_globalSettings, char text[], Vector2 position)
{
    Vector2 textSize = MeasureTextEx(p_globalSettings -> font, text, p_globalSettings -> uiStyle.FONT_SIZE, p_globalSettings -> uiStyle.SPACING);
    Vector2 origin = {textSize.x / 2, textSize.y / 2};
    DrawTextOrigin(p_globalSettings, text, position, origin);
}

void DrawTextLeftAligned(GlobalSettings *p_globalSettings, char text[], Vector2 position)
{
    Vector2 textSize = MeasureTextEx(p_globalSettings -> font, text, p_globalSettings -> uiStyle.FONT_SIZE, p_globalSettings -> uiStyle.SPACING);
    Vector2 origin = {0, textSize.y / 2};
    DrawTextOrigin(p_globalSettings, text, position, origin);
}

void DrawTextOrigin(GlobalSettings *p_globalSettings, char text[], Vector2 position, Vector2 origin)
{
    DrawTextPro(p_globalSettings -> font, text, position, origin, 0.0f, p_globalSettings -> uiStyle.FONT_SIZE, p_globalSettings -> uiStyle.SPACING, p_globalSettings -> uiStyle.FONT_COLOUR);
}
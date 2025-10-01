#ifndef DRAW_UI_H
#define DRAW_UI_H

#include "game/grid.h"

void DrawUI(GridInstance gridInstance, GlobalSettings *p_globalSettings);
void DrawFlagsPlacedText(GridInstance gridInstance, GlobalSettings *p_globalSettings);
void DrawTotalMinesText(GridInstance gridInstance, GlobalSettings *p_globalSettings);
void DrawTotalChargesText(GridInstance gridInstance, GlobalSettings *p_globalSettings);
void DrawTimerText(GridInstance gridInstance, GlobalSettings *p_globalSettings);
void DrawFinishText(GlobalSettings *p_globalSettings, char text[]);
void DrawTextCentred(GlobalSettings *p_globalSettings, char text[], Vector2 position);
void DrawTextLeftAligned(GlobalSettings *p_globalSettings, char text[], Vector2 position);
void DrawTextOrigin(GlobalSettings *p_globalSettings, char text[], Vector2 position, Vector2 origin);

#endif
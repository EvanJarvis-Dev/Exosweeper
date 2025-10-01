#ifndef DRAW_GRID_H
#define DRAW_GRID_H

#include <stdbool.h>
#include "game/grid.h"

void DrawMineGrid(GridInstance gridInstance, GlobalSettings *p_globalSettings, Images *p_images);
void DrawSquareBackground(GridInstance gridInstance, Images *p_images, Vector2Int coordinates);
void DrawNumberText(GridInstance gridInstance, GlobalSettings *p_globalSettings, Vector2Int coordinates);
void DrawFlag(GridInstance gridInstance, Images *p_images, Vector2Int coordinates);
void DrawSquareImage(GridInstance gridInstance, Texture2D image, Vector2 topLeft);
void DrawGridLines(GridInstance gridInstance, GlobalSettings *p_globalSettings);
void DrawHighlightedLines(GridInstance gridInstance, GlobalSettings *p_globalSettings);

#endif
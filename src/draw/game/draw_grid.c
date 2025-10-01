#include <stdio.h>
#include <stdlib.h>
#include "draw/game/draw_grid.h"
#include "draw/button.h"
#include "game/grid.h"

void DrawMineGrid(GridInstance gridInstance, GlobalSettings *p_globalSettings, Images *p_images)
{
    int gridWidth = gridInstance.gridData.GRID_WIDTH;
    int gridHeight = gridInstance.gridData.GRID_HEIGHT;

    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            Vector2Int coordinates = {.x = i, .y = j};
            DrawSquareBackground(gridInstance, p_images, coordinates);
            if (gridInstance.p_grid[i][j].isRevealed)
            {
                if (gridInstance.p_grid[i][j].amountOfNeighbours != 0 && !gridInstance.p_grid[i][j].hasMine)
                {
                    DrawNumberText(gridInstance, p_globalSettings, coordinates);
                }
            }
            else
            {
                if (gridInstance.p_grid[i][j].isFlagged)
                {
                    DrawFlag(gridInstance, p_images, coordinates);
                }
            } 
        }
    }

    DrawGridLines(gridInstance, p_globalSettings);
}

void DrawSquareBackground(GridInstance gridInstance, Images *p_images, Vector2Int coordinates)
{
    Vector2 topLeft = {
        (coordinates.x * gridInstance.gridData.BOX_LENGTH_PIXELS) + gridInstance.gridData.OFFSET_X,
        (coordinates.y * gridInstance.gridData.BOX_LENGTH_PIXELS) + gridInstance.gridData.OFFSET_Y
    };

    if (gridInstance.p_grid[coordinates.x][coordinates.y].isRevealed)
    {
        if (gridInstance.p_grid[coordinates.x][coordinates.y].isFrozen)
        {
            DrawSquareImage(gridInstance, p_images -> ice[gridInstance.p_grid[coordinates.x][coordinates.y].randomIceIndex], topLeft);
        }
        else if (gridInstance.p_grid[coordinates.x][coordinates.y].hasMine)
        {
            DrawSquareImage(gridInstance, p_images -> magma, topLeft);
        }
        else
        {
            DrawSquareImage(gridInstance, p_images -> ore[gridInstance.p_grid[coordinates.x][coordinates.y].randomOreIndex], topLeft);
        }
    }
    else
    {
        DrawSquareImage(gridInstance, p_images -> grass[gridInstance.p_grid[coordinates.x][coordinates.y].randomGrassIndex], topLeft);
    }
}

void DrawNumberText(GridInstance gridInstance, GlobalSettings *p_globalSettings, Vector2Int coordinates)
{
    char text[2];
    sprintf(text, "%d", gridInstance.p_grid[coordinates.x][coordinates.y].amountOfNeighbours);
    Vector2 centre = GetGridItemCentre(gridInstance.gridData, coordinates);

    Vector2 textSize = MeasureTextEx(p_globalSettings ->numberFont, text, p_globalSettings -> gameStyle.MINE_FONT_SIZE, p_globalSettings -> uiStyle.SPACING);
    Vector2 origin = {textSize.x / 2, textSize.y / 2};

    centre.x += 3;
    centre.y += 4;

    Color colourToUse = p_globalSettings -> gameStyle.mineTextColours[gridInstance.p_grid[coordinates.x][coordinates.y].amountOfNeighbours - 1];

    DrawTextPro(p_globalSettings -> numberFont, text, centre, origin, 0.0f, p_globalSettings -> gameStyle.MINE_FONT_SIZE, p_globalSettings -> uiStyle.SPACING, colourToUse);
}


void DrawFlag(GridInstance gridInstance, Images *p_images, Vector2Int coordinates)
{
    Vector2 topLeft = {
        (coordinates.x * gridInstance.gridData.BOX_LENGTH_PIXELS) + gridInstance.gridData.OFFSET_X, 
        (coordinates.y * gridInstance.gridData.BOX_LENGTH_PIXELS) + gridInstance.gridData.OFFSET_Y
    };

    DrawSquareImage(gridInstance, p_images -> marker, topLeft);
}

void DrawSquareImage(GridInstance gridInstance, Texture2D image, Vector2 topLeft)
{
    Rectangle source = {0, 0, (float)image.width, (float)image.height};
    Rectangle dest = {topLeft.x, topLeft.y, (float)gridInstance.gridData.BOX_LENGTH_PIXELS, (float)gridInstance.gridData.BOX_LENGTH_PIXELS};

    Vector2 origin = {0, 0};
    DrawTexturePro(image, source, dest, origin, 0, WHITE);
}

void DrawGridLines(GridInstance gridInstance, GlobalSettings *p_globalSettings)
{
    GridData gridData = gridInstance.gridData;
    int boxLength = gridData.BOX_LENGTH_PIXELS;
    int offsetX = gridData.OFFSET_X;
    int offsetY = gridData.OFFSET_Y;
    int gridWidth = gridInstance.gridData.GRID_WIDTH;
    int gridHeight = gridInstance.gridData.GRID_HEIGHT;

    for (int i = 0; i < gridWidth + 1; i++)
    {
        Vector2 startPos = {
            (i * boxLength) + offsetX, 
            offsetY
        };

        Vector2 endPos = {
            (i * boxLength) + offsetX, 
            (gridHeight * boxLength) + offsetY
        };

        DrawLineV(startPos, endPos, p_globalSettings -> gameStyle.GRID_LINE_COLOUR);
    }
    for (int j = 0; j < gridHeight + 1; j++)
    {
        Vector2 startPos = {
            offsetX, 
            (j * boxLength) + offsetY
        };

        Vector2 endPos = {
            (gridWidth * boxLength) + offsetX, 
            (j * boxLength) + offsetY
        };

        DrawLineV(startPos, endPos, p_globalSettings -> gameStyle.GRID_LINE_COLOUR);
    }
    DrawHighlightedLines(gridInstance, p_globalSettings);
}

void DrawHighlightedLines(GridInstance gridInstance, GlobalSettings *p_globalSettings)
{
    Vector2Int coordinateToHighlight = *(gridInstance.p_selectedCoordinate);

    if (!IsValidCoordinate(gridInstance.gridData, coordinateToHighlight))
    {
        return;
    }

    GridData gridData = gridInstance.gridData;
    int boxLength = gridData.BOX_LENGTH_PIXELS;
    int offsetX = gridData.OFFSET_X;
    int offsetY = gridData.OFFSET_Y;

    int maxXcoordinate = coordinateToHighlight.x + 2;
    int maxYcoordinate = coordinateToHighlight.y + 2;
    int minXcoordinate = coordinateToHighlight.x - 1;
    int minYcoordinate = coordinateToHighlight.y - 1;

    if (maxXcoordinate > gridInstance.gridData.GRID_WIDTH)
    {
        maxXcoordinate = gridInstance.gridData.GRID_WIDTH;
    }
    if (minXcoordinate < 0)
    {
        minXcoordinate = 0;
    }
    if (maxYcoordinate > gridInstance.gridData.GRID_WIDTH)
    {
        maxYcoordinate = gridInstance.gridData.GRID_WIDTH;
    }
    if (minYcoordinate < 0)
    {
        minYcoordinate = 0;
    }

    Vector2 topLeft = {
        ((minXcoordinate) * boxLength) + offsetX,
        ((minYcoordinate) * boxLength) + offsetY
    };
    Vector2 topRight = {
        ((maxXcoordinate) * boxLength) + offsetX,
        ((minYcoordinate) * boxLength) + offsetY
    };
    Vector2 BottomLeft = {
        ((minXcoordinate) * boxLength) + offsetX,
        ((maxYcoordinate) * boxLength) + offsetY
    };
    Vector2 BottomRight = {
        ((maxXcoordinate) * boxLength) + offsetX,
        ((maxYcoordinate) * boxLength) + offsetY
    };


    DrawLineV(topLeft, topRight, p_globalSettings -> gameStyle.HIGHLIGHTED_GRID_LINE_COLOUR);
    DrawLineV(BottomLeft, BottomRight, p_globalSettings -> gameStyle.HIGHLIGHTED_GRID_LINE_COLOUR);

    DrawLineV(topLeft, BottomLeft, p_globalSettings -> gameStyle.HIGHLIGHTED_GRID_LINE_COLOUR);
    DrawLineV(topRight, BottomRight, p_globalSettings -> gameStyle.HIGHLIGHTED_GRID_LINE_COLOUR);
}

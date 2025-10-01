#include "game/grid.h"
#include "game/settings.h"
#include <stdlib.h>
#include "game/audio.h"

Vector2 GetGridItemCentre(GridData gridData, Vector2Int coordinate)
{
    Vector2 centre;
    centre.x = (coordinate.x * gridData.BOX_LENGTH_PIXELS) + (gridData.BOX_LENGTH_PIXELS / 2) + gridData.OFFSET_X;
    centre.y = (coordinate.y * gridData.BOX_LENGTH_PIXELS) + (gridData.BOX_LENGTH_PIXELS / 2) + gridData.OFFSET_Y;
    return centre;
}

void InitialiseNeighbours(GridInstance gridInstance)
{
    for (int i = 0; i < gridInstance.gridData.GRID_WIDTH; i++)
    {
        for (int j = 0; j < gridInstance.gridData.GRID_HEIGHT; j++)
        {
            gridInstance.p_grid[i][j].amountOfNeighbours = 0;
        }
    }

    for (int i = 0; i < gridInstance.gridData.GRID_WIDTH; i++)
    {
        for (int j = 0; j < gridInstance.gridData.GRID_HEIGHT; j++)
        {
            if (gridInstance.p_grid[i][j].hasMine)
            {
                for (int x = -1; x <= 1; x++)
                {
                    for (int y = -1; y <= 1; y++)
                    {
                        if (x == 0 && y == 0)
                        {
                            continue;
                        }

                        int neighbourX = i + x;
                        int neighbourY = j + y;

                        Vector2Int coordinate = {neighbourX, neighbourY};

                        if (IsValidCoordinate(gridInstance.gridData, coordinate))
                        {
                            gridInstance.p_grid[neighbourX][neighbourY].amountOfNeighbours += 1;
                        }
                    }
                }
            }
        }
    }
}

GridInstance CreateGridInstance(GlobalSettings globalSettings, int gridWidth, int gridHeight, int cryoCharges)
{
    int boxLength = 35;
    int offsetX = (globalSettings.SCREEN_WIDTH - globalSettings.SCREEN_HEIGHT) + ((globalSettings.SCREEN_HEIGHT / 2) - ((boxLength * gridWidth) / 2));
    int offsetY = (globalSettings.SCREEN_HEIGHT / 2) - ((boxLength * gridHeight) / 2);

    GridData gridData = {
        .GRID_WIDTH = gridWidth,
        .GRID_HEIGHT = gridHeight,
        .BOX_LENGTH_PIXELS = boxLength,
        .OFFSET_X = offsetX,
        .OFFSET_Y = offsetY,
        .PERCENT_CHANCE_OF_MINES = 20.0f
    };

    int *p_cryoCharges = malloc(sizeof(int));
    *p_cryoCharges = cryoCharges;
    Vector2Int *p_selectedCoordinate = malloc(sizeof(Vector2Int));
    (*p_selectedCoordinate).x = -1;
    (*p_selectedCoordinate).y = -1;

    GridInstance gridInstance = { 
        .gridData = gridData, 
        .timer = InitialiseTimer(), 
        .p_selectedCoordinate = p_selectedCoordinate, 
        .p_cryoCharges = p_cryoCharges 
    };

    gridInstance.p_grid = calloc(gridInstance.gridData.GRID_WIDTH, sizeof(MineSquare *));
    for (int i = 0; i < gridInstance.gridData.GRID_WIDTH; i++)
    {
        gridInstance.p_grid[i] = calloc(gridInstance.gridData.GRID_HEIGHT, sizeof(MineSquare));
    }

    return gridInstance;
}

void PopulateGrid(GlobalSettings globalSettings, GridInstance gridInstance, Images *p_images)
{
    for (int i = 0; i < gridInstance.gridData.GRID_WIDTH; i++)
    {
        for (int j = 0; j < gridInstance.gridData.GRID_HEIGHT; j++)
        {
            MineSquare tempSquare;
            tempSquare.hasMine = (rand() % 100) < gridInstance.gridData.PERCENT_CHANCE_OF_MINES;
            tempSquare.isRevealed = false;
            tempSquare.isFlagged = false;
            tempSquare.amountOfNeighbours = 0;

            tempSquare.randomGrassIndex = rand() % p_images -> grassCount;
            tempSquare.randomOreIndex = rand() % p_images -> oreCount;
            tempSquare.randomIceIndex = rand() % p_images -> iceCount;

            gridInstance.p_grid[i][j] = tempSquare;
        }
    }
}

GridInstance CreateGrid(GlobalSettings globalSettings, Images *p_images, int gridWidth, int gridHeight, int cryoCharges)
{
    GridInstance gridInstance = CreateGridInstance(globalSettings, gridWidth, gridHeight, cryoCharges);
    PopulateGrid(globalSettings, gridInstance, p_images);
    InitialiseNeighbours(gridInstance);

    return gridInstance;
}

void InitialiseStartingArea(GridInstance gridInstance, Audio *audio, Vector2Int coordinate)
{
    gridInstance.p_grid[coordinate.x][coordinate.y].hasMine = false;
    gridInstance.p_grid[coordinate.x][coordinate.y].isRevealed = true;

    // Remove mines from all squares 2 away and reveal them
    for (int i = -2; i <= 2; i++)
    {
        for (int j = -2; j <= 2; j++)
        {
            if(abs(i) + abs(j) > 2 || (i == 0 && j == 0))
            {
                continue;
            }
            Vector2Int coordinateToReveal = {coordinate.x + i, coordinate.y + j};
            if (IsValidCoordinate(gridInstance.gridData, coordinateToReveal))
            {
                gridInstance.p_grid[coordinateToReveal.x][coordinateToReveal.y].hasMine = false;
            }
        }
    }

    InitialiseNeighbours(gridInstance);

    for (int i = -2; i <= 2; i++)
    {
        for (int j = -2; j <= 2; j++)
        {
            if(abs(i) + abs(j) > 2 || (i == 0 && j == 0))
            {
                continue;
            }
            Vector2Int coordinateToReveal = {coordinate.x + i, coordinate.y + j};
            if (IsValidCoordinate(gridInstance.gridData, coordinateToReveal))
            {
                RevealMineSquare(gridInstance, audio, coordinateToReveal);
            }
        }
    }
}

void FreeGrid(GridInstance *p_gridInstance)
{
    for (int i = 0; i < p_gridInstance -> gridData.GRID_WIDTH; i++)
    {
        free(p_gridInstance -> p_grid[i]);
    }
    
    free(p_gridInstance -> p_grid);
    free(p_gridInstance -> p_selectedCoordinate);
    FreeTimer((*p_gridInstance).timer);
    free(p_gridInstance -> p_cryoCharges);
}

bool IsValidPosition(GridData gridData, Vector2 position)
{
    if (position.x < gridData.OFFSET_X || position.x > gridData.OFFSET_X + (gridData.BOX_LENGTH_PIXELS * gridData.GRID_WIDTH))
    {
        return false;
    }
    if (position.y < gridData.OFFSET_Y || position.y > gridData.OFFSET_Y + (gridData.BOX_LENGTH_PIXELS * gridData.GRID_HEIGHT))
    {
        return false;
    }
    return true;
}

bool IsValidCoordinate(GridData gridData, Vector2Int coordinate)
{
    if (coordinate.x < 0 || coordinate.x >= gridData.GRID_WIDTH)
    {
        return false;
    }
    if (coordinate.y < 0 || coordinate.y >= gridData.GRID_HEIGHT)
    {
        return false;
    }
    return true;
}

Vector2Int GlobalPositionToCoordinate(GridData gridData, Vector2 position)
{
    Vector2Int coordinate;
    for (int i = 0; i < gridData.GRID_WIDTH; i++)
    {
        float lowerBound = (i * gridData.BOX_LENGTH_PIXELS) + gridData.OFFSET_X;
        float upperBound = ((i + 1) * gridData.BOX_LENGTH_PIXELS) + gridData.OFFSET_X;
        if (position.x <= upperBound && position.x >= lowerBound)
        {
            coordinate.x = i;
        }
    }
    for (int j = 0; j < gridData.GRID_HEIGHT; j++)
    {
        float lowerBound = (j * gridData.BOX_LENGTH_PIXELS) + gridData.OFFSET_Y;
        float upperBound = ((j + 1) * gridData.BOX_LENGTH_PIXELS) + gridData.OFFSET_Y;
        if (position.y <= upperBound && position.y >= lowerBound)
        {
            coordinate.y = j;
        }
    }
    return coordinate;
}

void RevealMineSquare(GridInstance gridInstance, Audio *p_audio, Vector2Int coordinate)
{
    if (!IsValidCoordinate(gridInstance.gridData, coordinate))
    {
        return;
    }

    if (!HasASquareBeenRevealed(gridInstance))
    {
        InitialiseStartingArea(gridInstance, p_audio, coordinate);
    }
    else if (!gridInstance.p_grid[coordinate.x][coordinate.y].isFlagged)
    {
        if ((!(gridInstance.p_grid[coordinate.x][coordinate.y].amountOfNeighbours == 0) ||
            gridInstance.p_grid[coordinate.x][coordinate.y].hasMine) &&
            !(gridInstance.p_grid[coordinate.x][coordinate.y].isRevealed))
        {
            PlayRandomDigSound(p_audio);
        }

        gridInstance.p_grid[coordinate.x][coordinate.y].isRevealed = true;

        if ((gridInstance.p_grid[coordinate.x][coordinate.y].amountOfNeighbours == 0) &&
            !(gridInstance.p_grid[coordinate.x][coordinate.y].hasMine))
        {
            RevealAllNeighbours(gridInstance, p_audio, coordinate);
        }
    }
}

void ToggleFlag(GridInstance gridInstance, Audio *p_audio, Vector2Int coordinate)
{
    if (!IsValidCoordinate(gridInstance.gridData, coordinate) || gridInstance.p_grid[coordinate.x][coordinate.y].isRevealed)
    {
        return;
    }

    PlaySound(p_audio -> marker);
    gridInstance.p_grid[coordinate.x][coordinate.y].isFlagged = !gridInstance.p_grid[coordinate.x][coordinate.y].isFlagged;
}

void RevealAllNeighbours(GridInstance gridInstance, Audio *p_audio, Vector2Int coordinate)
{
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
            {
                continue;
            }

            int neighbourX = coordinate.x + x;
            int neighbourY = coordinate.y + y;

            if (neighbourX < gridInstance.gridData.GRID_WIDTH && neighbourX >= 0 &&
                neighbourY < gridInstance.gridData.GRID_HEIGHT && neighbourY >= 0)
            {
                if (!gridInstance.p_grid[neighbourX][neighbourY].hasMine && 
                    !gridInstance.p_grid[neighbourX][neighbourY].isRevealed)
                {
                    Vector2Int coordinate = {.x = neighbourX, .y = neighbourY};
                    RevealMineSquare(gridInstance, p_audio, coordinate);
                }
            }
        }
    }
}

void HighlightSquare(GridInstance gridInstance, Vector2Int coordinate)
{
    if (!IsValidCoordinate(gridInstance.gridData, coordinate) ||
        !gridInstance.p_grid[coordinate.x][coordinate.y].isRevealed ||
        ((*(gridInstance.p_selectedCoordinate)).x == coordinate.x &&
        (*(gridInstance.p_selectedCoordinate)).y == coordinate.y))
    {
        ResetHighlight(gridInstance);
        return;
    }

    *(gridInstance.p_selectedCoordinate) = coordinate;
}

void ResetHighlight(GridInstance gridInstance)
{
    (*(gridInstance.p_selectedCoordinate)).x = -1;
    (*(gridInstance.p_selectedCoordinate)).y = -1;
}

void RevealAllZeroNeighbours(GridInstance gridInstance, Audio *p_audio)
{
    for (int i = 0; i < gridInstance.gridData.GRID_WIDTH; i++)
    {
        for (int j = 0; j < gridInstance.gridData.GRID_HEIGHT; j++)
        {
            if (gridInstance.p_grid[i][j].isRevealed)
            {
                Vector2Int coordinate = {i, j};
                RevealMineSquare(gridInstance, p_audio, coordinate);
            }
        }
    }
}

int GetRemainingAmountOfMines(GridInstance gridInstance)
{
    int count = 0;
    for (int i = 0; i < gridInstance.gridData.GRID_WIDTH; i++)
    {
        for (int j = 0; j < gridInstance.gridData.GRID_HEIGHT; j++)
        {
            if (gridInstance.p_grid[i][j].hasMine && !gridInstance.p_grid[i][j].isFlagged)
            {
                count++;
            }
        }
    }
    return count;
}

int GetTotalAmountOfMines(GridInstance gridInstance)
{
    int count = 0;
    for (int i = 0; i < gridInstance.gridData.GRID_WIDTH; i++)
    {
        for (int j = 0; j < gridInstance.gridData.GRID_HEIGHT; j++)
        {
            if (gridInstance.p_grid[i][j].hasMine)
            {
                count++;
            }
        }
    }
    return count;
}

int GetFlagsPlaced(GridInstance gridInstance)
{
    int count = 0;
    for (int i = 0; i < gridInstance.gridData.GRID_WIDTH; i++)
    {
        for (int j = 0; j < gridInstance.gridData.GRID_HEIGHT; j++)
        {
            if (gridInstance.p_grid[i][j].isFlagged && !gridInstance.p_grid[i][j].isRevealed)
            {
                count++;
            }
        }
    }
    return count;
}

bool IsFailState(GridInstance gridInstance)
{
    for (int i = 0; i < gridInstance.gridData.GRID_WIDTH; i++)
    {
        for (int j = 0; j < gridInstance.gridData.GRID_HEIGHT; j++)
        {
            if (gridInstance.p_grid[i][j].isRevealed && gridInstance.p_grid[i][j].hasMine)
            {
                return true;
            }
        }
    }
    return false;
}

bool IsSuccessState(GridInstance gridInstance)
{
    for (int i = 0; i < gridInstance.gridData.GRID_WIDTH; i++)
    {
        for (int j = 0; j < gridInstance.gridData.GRID_HEIGHT; j++)
        {
            if (!gridInstance.p_grid[i][j].isRevealed && !gridInstance.p_grid[i][j].hasMine)
            {
                return false;
            }
        }
    }
    return true;
}

bool HasASquareBeenRevealed(GridInstance gridInstance)
{
    for (int i = 0; i < gridInstance.gridData.GRID_WIDTH; i++)
    {
        for (int j = 0; j < gridInstance.gridData.GRID_HEIGHT; j++)
        {
            if (gridInstance.p_grid[i][j].isRevealed)
            {
                return true;
            }
        }
    }
    return false;
}
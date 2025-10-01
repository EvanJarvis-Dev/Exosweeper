#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#include <stdbool.h>
#include "game/settings.h"
#include "game/timer.h"
#include "game/audio.h"

typedef struct  
{
    bool hasMine;
    bool isRevealed;
    bool isFlagged;
    bool isFrozen;
    int amountOfNeighbours;

    int randomGrassIndex;
    int randomOreIndex;
    int randomIceIndex;
} MineSquare;

typedef struct
{
    int GRID_WIDTH;
    int GRID_HEIGHT;
    int BOX_LENGTH_PIXELS;
    int OFFSET_X;
    int OFFSET_Y;
    float PERCENT_CHANCE_OF_MINES;
} GridData;

typedef struct 
{
    int *p_cryoCharges;
    Vector2Int *p_selectedCoordinate;
    Timer timer;
    GridData gridData;
    MineSquare **p_grid;
} GridInstance;

Vector2 GetGridItemCentre(GridData gridData, Vector2Int);

void InitialiseNeighbours(GridInstance gridInstance);
GridInstance CreateGridInstance(GlobalSettings globalSettings, int gridWidth, int gridHeight, int cryoCharges);
void PopulateGrid(GlobalSettings globalSettings, GridInstance gridInstance, Images *p_images);
GridInstance CreateGrid(GlobalSettings globalSettings, Images *p_images, int gridWidth, int gridHeight, int cryoCharges);
void InitialiseStartingArea(GridInstance gridInstance, Audio *p_audio, Vector2Int coordinate);
void FreeGrid(GridInstance *p_gridInstance);

bool IsValidPosition(GridData gridData, Vector2 position);
bool IsValidCoordinate(GridData gridData, Vector2Int coordinate);
Vector2Int GlobalPositionToCoordinate(GridData gridData, Vector2 position);

void RevealMineSquare(GridInstance gridInstance, Audio *p_audio, Vector2Int coordinate);
void ToggleFlag(GridInstance gridInstance, Audio *p_audio, Vector2Int coordinate);
void RevealAllNeighbours(GridInstance gridInstance, Audio *p_audio, Vector2Int coordinate);
void HighlightSquare(GridInstance gridInstance, Vector2Int coordinate);
void ResetHighlight(GridInstance gridInstance);
void RevealAllZeroNeighbours(GridInstance gridInstance, Audio *p_audio);

int GetRemainingAmountOfMines(GridInstance gridInstance);
int GetTotalAmountOfMines(GridInstance gridInstance);
int GetFlagsPlaced(GridInstance gridInstance);
bool IsFailState(GridInstance gridInstance);
bool IsSuccessState(GridInstance gridInstance);
bool HasASquareBeenRevealed(GridInstance gridInstance);

#endif
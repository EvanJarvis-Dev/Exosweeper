#include "game/cryo_stabiliser.h"
#include "game/grid.h"
#include "game/settings.h"

void StabiliseMineSquare(GridInstance gridInstance, Audio *p_audio, Vector2Int coordinate)
{
    if (!IsValidCoordinate(gridInstance.gridData, coordinate))
    {
        return;
    }

    if (!gridInstance.p_grid[coordinate.x][coordinate.y].isFrozen &&
        !gridInstance.p_grid[coordinate.x][coordinate.y].isRevealed &&
        *gridInstance.p_cryoCharges > 0)
    {
        gridInstance.p_grid[coordinate.x][coordinate.y].isFrozen = true;
        gridInstance.p_grid[coordinate.x][coordinate.y].isFlagged = false;
        gridInstance.p_grid[coordinate.x][coordinate.y].hasMine = false;

        InitialiseNeighbours(gridInstance);
        RevealAllZeroNeighbours(gridInstance, p_audio);
        RevealMineSquare(gridInstance, p_audio, coordinate);
        *gridInstance.p_cryoCharges -= 1;
    }
}


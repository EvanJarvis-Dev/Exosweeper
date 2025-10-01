#include <stdlib.h>
#include "raylib.h"
#include "game/timer.h"

Timer InitialiseTimer()
{
    int startTime = GetTime();
    int *p_finishTime = malloc(sizeof(int));

    if (p_finishTime)
    {
        *p_finishTime = 0;
    }

    Timer timer = {
        .startTime = startTime,
        .p_finishTime = p_finishTime
    };
    return timer;
}

int GetGridTime(Timer timer)
{
    return *(timer.p_finishTime) - timer.startTime;
}

void UpdateFinishTime(Timer timer)
{
    *(timer.p_finishTime) = GetTime();
}

void FreeTimer(Timer timer)
{
    free(timer.p_finishTime);
}

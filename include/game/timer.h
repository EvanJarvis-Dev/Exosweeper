#ifndef TIMER_H
#define TIMER_H

typedef struct 
{
    int startTime;
    int *p_finishTime;
} Timer;

Timer InitialiseTimer();
int GetGridTime(Timer timer);
void UpdateFinishTime(Timer timer);
void FreeTimer(Timer timer);

#endif
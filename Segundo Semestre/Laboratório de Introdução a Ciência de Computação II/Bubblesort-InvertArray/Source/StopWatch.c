#include "StopWatch.h"

double getExecutionTime(time_t startTime, time_t endTime)
{
    double time_taken = (endTime-startTime)/(double)CLOCKS_PER_SEC; // in seconds
    #ifdef DEBUG
        printf("Tempo para executar tarefa: %.4lf\n", time_taken);
    #endif
    return time_taken;
}

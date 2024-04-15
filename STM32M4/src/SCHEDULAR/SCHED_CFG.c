
#include "SCHED_CFG.h"
#include "SCHED.h"



runnable_t Runnables[_NUM_RUNNABLES]= {
    [runnable_1] = {
        .runnable_name = "led",
        .periodicityMS = 200,
        .periority = 0,
        .cb = NULL,
        .delay_ms = 0
    }
};
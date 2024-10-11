// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"

#include "xparameters.h"
#include "xttcps.h"

#include "log.h"

#include <assert.h>
#include <stdbool.h>

#define LOG_TAG "STATS_SETUP"

void FreeRTOS_SetupStatsTimer()
{
    log_warn(LOG_TAG, "Starting\n");
}

uint32_t FreeRTOS_StatsTimerValue()
{
    assert(false && "timer value");
}

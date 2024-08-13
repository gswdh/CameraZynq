#include "system.h"

// Drivers
#include "pipe.h"
#include "cpubsub.h"
#include "messages.h"
#include "log.h"

// Xilinx includes
#include "xil_printf.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

// System headers
#include <stdbool.h>
#include <stdint.h>

#define LOG_TAG "SYSTEM"

static pipe_t pipe = {0};

static void system_timer_cb(TimerHandle_t xTimer)
{
    log_info(LOG_TAG, "system_timer_cb tick = %u", xTaskGetTickCount());

    uint8_t msg[64] = {0};
    cps_result_t result = cps_receive(&pipe, (void *)msg, PIPE_WAIT_POLL);
    if (result == CPS_OK)
    {
        log_info(LOG_TAG, "Got message with MID = %u", cps_get_mid((void *)msg));
    }
}

void system_main(void *params)
{
    cps_subscribe(MSGButtonPress_MID, MSGButtonPress_LEN, &pipe);

    TimerHandle_t system_timer = xTimerCreate("System Timer", pdMS_TO_TICKS(1000), true, NULL, &system_timer_cb);
    xTimerStart(system_timer, 0);

    vTaskDelete(NULL);
}
#include "heartbeat.h"

#include <stdint.h>
#include <stdbool.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "log.h"

#include "gpio.h"

static void heartbeat_task(TimerHandle_t pxTimer)
{
    (void)pxTimer;
    gpio_toggle(FPGA_LED_0);
}

void heartbeat_start()
{
    // Start the task
    TimerHandle_t timer = xTimerCreate((const char *)"Heartbeat Timer",
                                       pdMS_TO_TICKS(1000),
                                       pdTRUE,
                                       NULL,
                                       heartbeat_task);

    xTimerStart(timer, 0);
}
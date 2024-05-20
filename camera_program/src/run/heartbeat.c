#include "heartbeat.h"

#include <stdint.h>
#include <stdbool.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "log.h"
#include "dmgui.h"

#include "cpubsub.h"
#include "messages.h"

#include "gpio.h"

static MSGTick_t tick_msg = {0};

static void heartbeat_task(TimerHandle_t pxTimer)
{
    gpio_toggle(FPGA_LED_0);

    /* Publish tick message */
    tick_msg.mid = MSGTick_MID;
    tick_msg.time = xTaskGetTickCount();
    cps_publish(&tick_msg);
}

void heartbeat_start()
{
    // Start the task
    TimerHandle_t timer = xTimerCreate((const char *)"Heartbeat Timer",
                                       pdMS_TO_TICKS(200),
                                       pdTRUE,
                                       NULL,
                                       heartbeat_task);

    xTimerStart(timer, 0);
}
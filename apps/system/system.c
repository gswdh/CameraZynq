#include "system.h"

// Drivers
#include "pipe.h"
#include "cpubsub.h"
#include "messages.h"
#include "log.h"
#include "gpio.h"

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
#include <stdlib.h>

#define LOG_TAG "SYSTEM"

static pipe_t pipe = {0};

static uint8_t *buffer = NULL;

static void system_timer_cb(TimerHandle_t xTimer)
{
    log_info(LOG_TAG, "system_timer_cb tick = %u\n", xTaskGetTickCount());

    // Toggle an LED for aliveness
    gpio_write(FPGA_LED_0, !gpio_read(FPGA_LED_0));

    // Process messages for debugging
    while (cps_receive(&pipe, (void *)buffer, PIPE_WAIT_POLL) == CPS_OK)
    {
        topic_t mid = cps_get_mid((void *)buffer);

        switch (mid)
        {
        case MSGChargingStats_MID:
            log_info(LOG_TAG, "Battery charging %5s\n", ((((MSGChargingStats_t *)buffer)->charging) == 1) ? "true " : "false");
            break;

        default:
            log_warn(LOG_TAG, "Unrecognised MID (%04X)\n", mid);
            break;
        }
    }
}

void system_main(void *params)
{
    cps_subscribe(MSGChargingStats_MID, MSGChargingStats_LEN, &pipe);
    buffer = (uint8_t *)malloc(pipe_item_size(&pipe));

    TimerHandle_t system_timer = xTimerCreate("System Timer", pdMS_TO_TICKS(1000), true, NULL, &system_timer_cb);
    xTimerStart(system_timer, 0);

    vTaskDelete(NULL);
}
#include "system.h"

#include "apps_config.h"

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

static volatile system_t sys = {0};

static void system_timer_cb(TimerHandle_t xTimer)
{
    // Toggle an LED for aliveness
    gpio_write(FPGA_LED_0, !gpio_read(FPGA_LED_0));
}

void system_main(void *params)
{
    // Init the system
    sys.imaging.iso = 100;
    sys.imaging.speed_us = 10000;

    TimerHandle_t system_timer = xTimerCreate("System Timer", pdMS_TO_TICKS(SYS_TICK_BLINK_PERIOD_MS), true, NULL, &system_timer_cb);
    xTimerStart(system_timer, 0);

    xTaskCreate(actions_main, "Actions Main", SYS_ACT_APP_STACK_SIZE_B, (void *)&sys, SYS_APP_ACTIONS_PRIORITY, NULL);
    xTaskCreate(imaging_main, "Imaging Main", SYS_IMG_APP_STACK_SIZE_B, (void *)&sys, SYS_IMG_APP_PRIORITY, NULL);

    vTaskDelete(NULL);
}
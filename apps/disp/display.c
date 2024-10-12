#include "display.h"

#include "apps_config.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "log.h"

#include "spi.h"
#include "gpio.h"

#include "dmgui.h"
#include "ssd1309z.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define LOG_TAG "DSP"

static uint8_t *buffer = NULL;

static bool run = false;

static void display_timer_cb(TimerHandle_t xTimer)
{
    run = true;
}

static void display_task(void *params)
{
    (void *)params;

    while (true)
    {
        if ((dmgui_update_needed() == true) && (run == true))
        {
            run = false;

            ssd_update_display(buffer);

            dmgui_update_done();
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }

    vTaskDelete(NULL);
}

void display_start()
{
    /* Assign some space for the display buffer */
    buffer = (uint8_t *)malloc(SSD_DISP_BUFFER_LEN);
    if (buffer == NULL)
    {
        log_error(LOG_TAG, "malloc failed.\n");
    }

    else
    {
        /* Init the display HW */
        ssd_init();

        /* Init the GUI */
        dmgui_init(buffer);

        /* Start the task */
        xTaskCreate(display_task, "Display Task", 256, NULL, tskIDLE_PRIORITY, NULL);

        // Start a timer
        TimerHandle_t display_timer = xTimerCreate("Display Timer", pdMS_TO_TICKS(DSP_TICK_PERIOD_MS), true, NULL, &display_timer_cb);
        xTimerStart(display_timer, 0);
    }

    vTaskDelete(NULL);
}
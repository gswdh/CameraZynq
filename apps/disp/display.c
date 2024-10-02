#include "display.h"

#include <stdint.h>
#include <stdbool.h>

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

#define LOG_TAG "DISP"

static uint8_t *buffer = NULL;

static void display_task(void *params)
{
    (void *)params;

    while (true)
    {
        if (true) // dmgui_update_needed())
        {
            ssd_update_display(buffer);

            dmgui_update_done();
        }

        ssd_delay_ms(100);
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
        xTaskCreate(display_task, "Display Task", 1024, NULL, tskIDLE_PRIORITY, NULL);
    }

    vTaskDelete(NULL);
}
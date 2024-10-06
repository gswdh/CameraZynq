#include "system.h"

#include "apps_config.h"

#include "pipe.h"
#include "cpubsub.h"
#include "messages.h"
#include "log.h"
#include "gmax0505.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include <string.h>
#include <stdlib.h>

#define LOG_TAG "IMG"

static bool tick = false;
static bool run = false;

static void imaging_timer_cb(TimerHandle_t timer)
{
    tick = true;
}

void imaging_main(void *params)
{
    run = true;
    pipe_t pipe = {0};
    uint8_t *buffer = NULL;

    system_t *sys = (system_t *)params;
    if (sys == NULL)
    {
        log_error(LOG_TAG, "sys == NULL.\n");
        run = false;
    }

    pipe_set_length(&pipe, SYS_ACTION_PIPE_LEN);
    cps_subscribe(MSGButtonPress_MID, MSGButtonPress_LEN, &pipe);

    /* Assign some space for the display buffer */
    buffer = (uint8_t *)malloc((size_t)pipe_item_size(&pipe));
    if (buffer == NULL)
    {
        log_error(LOG_TAG, "malloc failed.\n");

        // Do not continue
        run = false;
    }

    // Init the sensor
    gmax_error_t error = gmax_init();
    if (error == GMAX_OK)
    {
        log_info(LOG_TAG, "GMAX init success\n");
        sys->imaging.sync = true;
    }

    else
    {
        log_error(LOG_TAG, "GMAX init fail with %s\n", gmax_error_string(error));
        run = false;
        sys->imaging.sync = false;
    }

    // Default screen
    TimerHandle_t timer = xTimerCreate("Imaging Tick", pdMS_TO_TICKS(SYS_IMG_TICK_PERIOD_MS), true, NULL, imaging_timer_cb);
    xTimerStart(timer, 0);

    // Go forever
    while (run == true)
    {
        // Wait for the tick to arrive
        if (tick == true)
        {
            // Reset the flag
            tick = false;

            if (sys->imaging.take_image == true)
            {
                sys->imaging.take_image = false;

                gmax_frame_request(sys->imaging.speed_us, sys->imaging.iso, sys->imaging.res);

                log_info(LOG_TAG, "Taking image\n");
            }

            gmax_sensor_temperature(&sys->imaging.sensor_temp_c);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }

    // Should never reach here if all is okay
    vTaskDelete(NULL);
}